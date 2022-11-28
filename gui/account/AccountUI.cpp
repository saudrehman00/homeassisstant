#include "AccountUI.h"

using namespace std;
using namespace Wt;

AccountUI::AccountUI(string username) : WTemplate{tr("changePass")}, db("LoginInfo", "username", {"username", "encryptedPassword"}) {
    this->username = username;
    addFunction("tr", &WTemplate::Functions::tr);

    // components for username input
    currentPass = bindWidget("currentPass", make_unique<WLineEdit>());
    currentPass->setStyleClass("form-control form-outline bg-dark text-white");
    currentPass->setPlaceholderText("Current Password");
    currentPass->setId("currentPass");

    // components for password input
    newPass = bindWidget("newPass", make_unique<WLineEdit>());
    newPass->setStyleClass("form-control form-outline bg-dark text-white");
    newPass->setPlaceholderText("New Password");
    newPass->setId("newPass");

    // components for input validation
    auto validator = make_shared<WValidator>(true);
    currentPass->setValidator(validator);
    newPass->setValidator(validator);

    // components for form title
    title = bindWidget("title", make_unique<WText>("Change Password"));
    title->setStyleClass("fw-bold");

    // components for text helping the user
    help = bindWidget("help", make_unique<WText>("Please enter your current password and desired new password."));
    help->setStyleClass("text-dark-50 mt-4");

    okBtn = bindWidget("okBtn", make_unique<WPushButton>("Submit"));
    okBtn->setStyleClass("btn-dark text-white btn-outline-secondary");
    okBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    okBtn->clicked().connect([=] {
        validatePassword();
    });

    // components for the button changing forms
    backBtn = bindWidget("backBtn", make_unique<WPushButton>("Back"));
    backBtn->setStyleClass("btn-link text-dark-50 fw-bold");
    backBtn->setLink(WLink(LinkType::InternalPath, "/main"));
    backBtn->clicked().connect([=] {
        this->parent()->removeChild(this);
    });

    title->setText("Change Password");
    help->setText("Please enter your current and desired new password.");
}

AccountUI::~AccountUI() {}

void AccountUI::validatePassword(){
    string currP, newP;
    currP = getCurrPass();
    newP = getNewPass();
    if(accountExists()){
        //gets all entries in the logininfo table with the user's username
        vector<vector<string>> data =  db.readAllUser(username);
        //cout << data.at(0).at(0) << endl;
        if(data.at(0).at(0) == currP){
            //correct password
            db.delData(username);
            db.saveData({username, newP});
        } else {
            //wrong password
            help->setText("You entered the wrong password. Please try again.");
            currentPass->setPlaceholderText("Current Password");
            newPass->setPlaceholderText("New Password");

        }
    }
}

// getCurrPass() returns the inputted current password as string
// @param nothing
// @return currentPass the current username input
string AccountUI::getCurrPass() {
    return currentPass->text().toUTF8();
}

// getNewPass() returns the inputted new password as string
// @param nothing
// @return newPass the new desired password of the user
string AccountUI::getNewPass() {
    return newPass->text().toUTF8();
}

// exists() determines if the username exists in the database
// @param nothing
// @return bool whether or not the username is saved
bool AccountUI::accountExists() {
    return db.exists("LoginInfo", {"username=\"" + username + "\""});
}
