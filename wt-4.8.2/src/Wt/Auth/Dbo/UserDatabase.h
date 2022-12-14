// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2011 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef WT_AUTH_DBO_USER_DATABASE_H_
#define WT_AUTH_DBO_USER_DATABASE_H_

#include <Wt/Auth/AbstractUserDatabase.h>
#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/WException.h>
#include <Wt/WLogger.h>

namespace Wt {
  namespace Auth {
    namespace Dbo {

/*! \class UserDatabase Wt/Auth/Dbo/UserDatabase.h
 *  \brief A default implementation for an authentication user database.
 *
 * This is a template class, and needs as parameter the Dbo type which
 * models the authentication information. A suitable implementation,
 * which stores authentication information outside the "user" class,
 * is provided by AuthInfo.
 *
 * \sa AuthInfo
 *
 * \ingroup auth
 */
template <class DboType>
class UserDatabase : public AbstractUserDatabase
{
  typedef typename DboType::AuthTokenType AuthTokenType;
  typedef Wt::Dbo::collection< Wt::Dbo::ptr<AuthTokenType> > AuthTokens;

  typedef typename DboType::AuthIdentityType AuthIdentityType;
  typedef Wt::Dbo::collection< Wt::Dbo::ptr<AuthIdentityType> > AuthIdentities;

public:
  /*! \brief Constructor
   *
   * The AuthService parameter is optional, and decides some of the
   * UserDatabase's behaviour. Currently, this decides whether findWithIdentity()
   * should be case sensitive or not. If the identity policy of the AuthService is
   * EmailAddressIdentity, then findWithIdentity() will be case insensitive. Otherwise
   * it is case sensitive.
   */
  UserDatabase(Wt::Dbo::Session& session, const AuthService *authService = 0)
    : session_(session),
      newUserStatus_(AccountStatus::Normal),
      authService_(authService),
      maxAuthTokensPerUser_(50)
  { }

  /*! \brief Sets the initial status for a new user.
   *
   * This status is set on a user that just registered.
   *
   * The default value is AccountStatus::Normal.
   */
  void setNewUserStatus(AccountStatus status)
  {
    newUserStatus_ = status;
  }

  virtual Transaction *startTransaction() override {
    return new TransactionImpl(session_);
  }

  /*! \brief Returns the %Dbo user type corresponding to an Auth::User.
   */
  Wt::Dbo::ptr<DboType> find(const User& user) const {
    getUser(user.id(), false);
    return user_;
  }

  /*! \brief Returns the Auth::User corresponding to a %Dbo user.
   */
  User find(const Wt::Dbo::ptr<DboType> user) const {
    setUser(user);
    return User(std::to_string(user_->id()), *this);
  }

  virtual User findWithId(const std::string& id) const override {
    getUser(id, false);

    if (user_)
      return User(id, *this);
    else
      return User();
  }

  virtual User findWithIdentity(const std::string& provider,
                                const WString& identity) const override {
    if (userProvider_ != provider || userIdentity_ != identity) {
      Wt::Dbo::Transaction t(session_);
      Wt::Dbo::Query<Wt::Dbo::ptr<DboType> > query =
          session_.query<Wt::Dbo::ptr<DboType> >(std::string() +
               "select u from " + session_.tableNameQuoted<DboType>() + " u "
               "join " + session_.tableNameQuoted<AuthIdentityType>() + " i "
               "on u.id = i.\"" + session_.tableName<DboType>() + "_id\"")
              .where("i.\"provider\" = ?").bind(provider);
      if (authService_ && authService_->identityPolicy() == IdentityPolicy::EmailAddress) {
        query.where("lower(i.\"identity\") = lower(?)").bind(identity);
      } else {
        query.where("i.\"identity\" = ?").bind(identity);
      }
      setUser(query.resultValue());
      t.commit();
    }

    if (user_) {
      userProvider_ = provider;
      userIdentity_ = identity;
      return User(std::to_string(user_.id()), *this);
    } else
      return User();
  }

  virtual WString identity(const User& user,
                           const std::string& provider) const override {
    WithUser find(*this, user);

    AuthIdentities c
      = user_->authIdentities().find().where("\"provider\" = ?").bind(provider);

    typename AuthIdentities::const_iterator i = c.begin();

    if (i != c.end())
      return (*i)->identity();
    else
      return WString::Empty;
  }

  virtual void removeIdentity(const User& user,
                              const std::string& provider) override {
    Wt::Dbo::Transaction t(session_);

    session_.execute
      (std::string() +
       "delete from " + session_.tableNameQuoted<AuthIdentityType>() +
       " where \"" + session_.tableName<DboType>() + "_id\" = ?"
       " and \"provider\" = ?").bind(user.id()).bind(provider);

    t.commit();
  }

  virtual User registerNew() override {
    auto user = std::make_unique<DboType>();
    user->setStatus(newUserStatus_);
    setUser(session_.add(std::move(user)));
    user_.flush();
    return User(std::to_string(user_.id()), *this);
  }

  virtual void deleteUser(const User& user) override {
    Wt::Dbo::Transaction t(session_);
    Wt::Dbo::ptr<DboType> u = find(user);
    u.remove();
    t.commit();
  }

  virtual AccountStatus status(const User& user) const override {
    WithUser find(*this, user);
    return user_->status();
  }

  virtual void setStatus(const User& user, AccountStatus status) override {
    WithUser find(*this, user);
    user_.modify()->setStatus(status);
  }

  virtual void setPassword(const User& user, const PasswordHash& password) override {
    WithUser find(*this, user);
    user_.modify()->setPassword(password.value(),
                                password.function(),
                                password.salt());
  }

  virtual PasswordHash password(const User& user) const override {
    WithUser find(*this, user);
    return PasswordHash(user_->passwordMethod(), user_->passwordSalt(),
                        user_->passwordHash());
  }

  virtual void addIdentity(const User& user, const std::string& provider,
                           const WT_USTRING& identity) override {
    WithUser find(*this, user);

    if (session_.find<AuthIdentityType>()
        .where("\"identity\" = ?").bind(identity)
        .where("\"provider\" = ?").bind(provider).resultList().size() != 0) {
      Wt::log("error") << "cannot add identity " << provider
                       << ":'" << identity << "': already exists";
      return;
    }

    /*
     * It's okay to have more than one identity from that provider
     */
    user_.modify()->authIdentities().insert
      (Wt::Dbo::ptr<AuthIdentityType>(
         std::make_unique<AuthIdentityType>(provider, identity)));
  }

  virtual void setIdentity(const User& user, const std::string& provider,
                           const WT_USTRING& identity) override {
    WithUser find(*this, user);

    AuthIdentities c
      = user_->authIdentities().find().where("\"provider\" = ?").bind(provider);

    typename AuthIdentities::const_iterator i = c.begin();

    if (i != c.end())
      i->modify()->setIdentity(identity);
    else
      user_.modify()->authIdentities().insert
        (Wt::Dbo::ptr<AuthIdentityType>(
           std::make_unique<AuthIdentityType>(provider, identity)));
  }

  virtual bool setEmail(const User& user, const std::string& address) override {
    WithUser find(*this, user);

    if (session_.find<DboType>().where("lower(\"email\") = lower(?)")
        .bind(address).resultList().size() != 0)
      return false;

    user_.modify()->setEmail(address);

    return true;
  }

  virtual std::string email(const User& user) const override {
    WithUser find(*this, user);
    return user_->email();
  }

  virtual void setUnverifiedEmail(const User& user,
                                  const std::string& address) override {
    WithUser find(*this, user);
    user_.modify()->setUnverifiedEmail(address);
  }

  virtual std::string unverifiedEmail(const User& user) const override {
    WithUser find(*this, user);
    return user_->unverifiedEmail();
  }

  virtual User findWithEmail(const std::string& address) const override {
    Wt::Dbo::Transaction t(session_);
    setUser(session_.find<DboType>().where("lower(\"email\") = lower(?)").bind(address));
    t.commit();

    if (user_)
      return User(std::to_string(user_.id()), *this);
    else
      return User();
  }

  virtual void setEmailToken(const User& user, const Token& token,
                             EmailTokenRole role) override {
    WithUser find(*this, user);
    user_.modify()->setEmailToken(token.hash(), token.expirationTime(), role);
  }

  virtual Token emailToken(const User& user) const override {
    WithUser find(*this, user);
    return Token(user_->emailToken(), user_->emailTokenExpires());
  }

  virtual EmailTokenRole emailTokenRole(const User& user) const override {
    WithUser find(*this, user);
    return user_->emailTokenRole();
  }

  virtual User findWithEmailToken(const std::string& hash) const override {
    Wt::Dbo::Transaction t(session_);
    setUser(session_.find<DboType>()
            .where("\"email_token\" = ?").bind(hash));
    t.commit();

    if (user_)
      return User(std::to_string(user_.id()), *this);
    else
      return User();
  }

  virtual void addAuthToken(const User& user, const Token& token) override {
    WithUser find(*this, user);

    /*
     * This should be statistically very unlikely but also a big
     * security problem if we do not detect it ...
     */
    if (session_.find<AuthTokenType>().where("\"value\" = ?")
        .bind(token.hash())
        .resultList().size() > 0)
      throw WException("Token hash collision");

    /*
     * Prevent a user from piling up the database with tokens
     */
    size_t tokens_number = user_->authTokens().size();
    if (tokens_number >= maxAuthTokensPerUser_) {
      // remove so many tokens, that their number
      // would be (maxAuthTokensPerUser_ - 1)
      int tokens_to_remove = tokens_number - (maxAuthTokensPerUser_ - 1);
      // remove the first token(s) to expire
      Wt::Dbo::collection<Wt::Dbo::ptr<AuthTokenType> > earliest_tokens =
        user_->authTokens().find().orderBy("expires").limit(tokens_to_remove);
      std::vector<Wt::Dbo::ptr<AuthTokenType> > earliest_tokens_v(
        earliest_tokens.begin(), earliest_tokens.end());

      for (auto& token : earliest_tokens_v)
        token.remove();
    }

    user_.modify()->authTokens().insert
      (Wt::Dbo::ptr<AuthTokenType>
       (std::make_unique<AuthTokenType>(token.hash(), token.expirationTime())));
  }

  virtual void removeAuthToken(const User& user, const std::string& hash) override {
    WithUser find(*this, user);

    for (typename AuthTokens::const_iterator i = user_->authTokens().begin();
         i != user_->authTokens().end(); ++i) {
      Wt::Dbo::ptr<AuthTokenType> t = *i;
      if (t->value() == hash) {
        t.remove();
        break;
      }
    }
  }

  virtual int updateAuthToken(const User& user, const std::string& hash,
                              const std::string& newHash) override {
    WithUser find(*this, user);

    for (typename AuthTokens::const_iterator i = user_->authTokens().begin();
         i != user_->authTokens().end(); ++i) {
      Wt::Dbo::ptr<AuthTokenType> t = *i;
      if (t->value() == hash) {
        t.modify()->setValue(newHash);
        return std::max(0, WDateTime::currentDateTime().secsTo(t->expires()));
      }
    }

    return 0;
  }

  virtual User findWithAuthToken(const std::string& hash) const override {
    Wt::Dbo::Transaction t(session_);
    setUser(session_.query< Wt::Dbo::ptr<DboType> >
            (std::string() +
             "select u from " + session_.tableNameQuoted<DboType>() + " u "
             "join " + session_.tableNameQuoted<AuthTokenType>() + " t "
             "on u.id = t.\"" + session_.tableName<DboType>() + "_id\"")
            .where("t.\"value\" = ?").bind(hash)
            .where("t.\"expires\" > ?").bind(WDateTime::currentDateTime()));
    t.commit();

    if (user_)
      return User(std::to_string(user_.id()), *this);
    else
      return User();
  }

  virtual void setFailedLoginAttempts(const User& user, int count) override {
    WithUser find(*this, user, true);
    return user_.modify()->setFailedLoginAttempts(count);
  }

  virtual int failedLoginAttempts(const User& user) const override {
    WithUser find(*this, user, true);
    return user_->failedLoginAttempts();
  }

  virtual void setLastLoginAttempt(const User& user, const WDateTime& t) override {
    WithUser find(*this, user, true);
    return user_.modify()->setLastLoginAttempt(t);
  }

  virtual WDateTime lastLoginAttempt(const User& user) const override {
    WithUser find(*this, user, true);
    return user_->lastLoginAttempt();
  }

  /*! \brief Returns max number of tokens user can have in the database
   *
   * Default value is 50.
   */
  unsigned maxAuthTokensPerUser() const {
    return maxAuthTokensPerUser_;
  }

  /*! \brief Sets max number of tokens user can have in the database
   */
  void setMaxAuthTokensPerUser(unsigned maxAuthTokensPerUser) {
    maxAuthTokensPerUser_ = maxAuthTokensPerUser;
  }

private:
  Wt::Dbo::Session& session_;
  AccountStatus newUserStatus_;
  const AuthService *authService_;
  mutable Wt::Dbo::ptr<DboType> user_;
  mutable std::string userProvider_;
  mutable Wt::WString userIdentity_;
  unsigned maxAuthTokensPerUser_;

  struct WithUser {
    WithUser(const UserDatabase<DboType>& self, const User& user,
             bool reread = false)
      : transaction(self.session_)
    {
      self.getUser(user.id(), reread);
      if (!self.user_)
        throw WException("Invalid user");
    }

    ~WithUser() {
      transaction.commit();
    }

    Wt::Dbo::Transaction transaction;
  };

  void getUser(const std::string& id, bool reread) const {
    if (!user_ || std::to_string(user_.id()) != id) {
      Wt::Dbo::Transaction t(session_);
      setUser(session_.load<DboType>(std::stoll(id)));
      t.commit();
    } else
      if (reread && !user_.isDirty())
        user_.reread();
  }

  void setUser(Wt::Dbo::ptr<DboType> user) const {
    user_ = user;
    userProvider_.clear();
    userIdentity_ = WString::Empty;
  }

  struct TransactionImpl final : public Transaction, public Wt::Dbo::Transaction
  {
    TransactionImpl(Wt::Dbo::Session& session)
      : Wt::Dbo::Transaction(session)
    { }

    virtual ~TransactionImpl()
    { }

    virtual void commit() override
    {
      Wt::Dbo::Transaction::commit();
    }

    virtual void rollback() override
    {
      Wt::Dbo::Transaction::rollback();
    }
  };
};

    }
  }
}

#endif // WT_AUTH_DBO_USER_DATABASE
