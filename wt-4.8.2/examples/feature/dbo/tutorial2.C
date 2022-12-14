/*
 * Copyright (C) 2010 Emweb bv, Herent, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

/*****
 * This file is part of the Wt::Dbo tutorial:
 * http://www.webtoolkit.eu/wt/doc/tutorial/dbo/tutorial.html
 *****/

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <string>

namespace dbo = Wt::Dbo;

/*****
 * Dbo tutorial section 6. Mapping relations
 *****/

class Post;
class User;
class Tag;

class Post {
public:
  dbo::ptr<User> user;
  dbo::collection< dbo::ptr<Tag> > tags;

  template<class Action>
  void persist(Action& a)
  {
    dbo::belongsTo(a, user, "user");
    dbo::hasMany(a, tags, dbo::ManyToMany, "post_tags");
  }
};

class Tag {
public:
  std::string name;
  dbo::collection< dbo::ptr<Post> > posts;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, name, "name");
    dbo::hasMany(a, posts, dbo::ManyToMany, "post_tags");
  }
};

class Settings {
public:
  std::string theme;

  dbo::ptr<User> user;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, theme, "theme");
    dbo::belongsTo(a, user);
  }
};

enum class Role {
  Visitor = 0,
  Admin = 1,
  Alien = 42
};

class User {
public:
  std::string name;
  std::string password;
  Role        role;
  int         karma;

  dbo::collection< dbo::ptr<Post> > posts;
  dbo::weak_ptr<Settings> settings;

  template<class Action>
  void persist(Action& a)
  {
    dbo::field(a, name,     "name");
    dbo::field(a, password, "password");
    dbo::field(a, role,     "role");
    dbo::field(a, karma,    "karma");

    dbo::hasMany(a, posts, dbo::ManyToOne, "user");
    dbo::hasOne(a, settings);
  }
};

void run()
{
  /*
   * Setup a session, would typically be done once at application startup.
   */
  std::unique_ptr<dbo::backend::Sqlite3> sqlite3(new dbo::backend::Sqlite3(":memory:"));
  sqlite3->setProperty("show-queries", "true");
  dbo::Session session;
  session.setConnection(std::move(sqlite3));

  session.mapClass<User>("user");
  session.mapClass<Post>("post");
  session.mapClass<Tag>("tag");
  session.mapClass<Settings>("settings");

  /*
   * Try to create the schema (will fail if already exists).
   */
  session.createTables();

  {
    dbo::Transaction transaction(session);

    std::unique_ptr<User> user{new User()};
    user->name = "Joe";
    user->password = "Secret";
    user->role = Role::Visitor;
    user->karma = 13;

    dbo::ptr<User> userPtr = session.add(std::move(user));
  }

  dbo::ptr<Post> post;
  {
    dbo::Transaction transaction(session);

    dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

    post = session.add(std::unique_ptr<Post>{new Post()});
    post.modify()->user = joe;

    // will print 'Joe has 1 post(s).'
    std::cerr << "Joe has " << joe->posts.size() << " post(s)." << std::endl;
  }

  {
    dbo::Transaction transaction(session);

    dbo::ptr<Tag> cooking = session.add(std::unique_ptr<Tag>{new Tag()});
    cooking.modify()->name = "Cooking";

    post.modify()->tags.insert(cooking);

    // will print '1 post(s) tagged with Cooking.'
    std::cerr << cooking->posts.size() << " post(s) tagged with Cooking."
              << std::endl;
  }

  {
    dbo::Transaction transaction(session);

    dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

    dbo::ptr<Settings> settings = session.add(std::unique_ptr<Settings>{new Settings()});
    settings.modify()->theme = "fancy-pink";
    joe.modify()->settings = settings;

    // will print 'Settings apply to Joe.'
    std::cerr << "Settings apply to " << settings->user->name << std::endl;
  }
}

int main(int argc, char **argv)
{
  run();
}
