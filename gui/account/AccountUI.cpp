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

    // components for form title
    title = bindWidget("title", make_unique<WText>("Change Password"));
    title->setStyleClass("fw-bold");

    // components for text helping the user
    help = bindWidget("help", make_unique<WText>("Please enter your current password and desired new password."));
    help->setStyleClass("text-dark-50 mt-4");

    okBtn = bindWidget("okBtn", make_unique<WPushButton>("Submit"));
    okBtn->setStyleClass("btn-dark text-white btn-outline-secondary");
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

    linkBtn = bindWidget("linkBtn", make_unique<WPushButton>("Delete Account"));
    linkBtn->setStyleClass("btn-link text-dark-50 fw-bold");

    changing();


}

AccountUI::~AccountUI() {}

void AccountUI::validatePassword(){
    if(okBool){
    string currP, newP;
    currP = getCurrPass();
    newP = getNewPass();
    if(accountExists()){
        //gets all entries in the logininfo table with the user's username
        vector<vector<string>> data =  db.readAllUser(username);
        //cout << data.at(0).at(0) << endl;
        if(data.at(0).at(0) == currP){
            //correct password
            cout << "what" << endl;
            db.delData(username);
            db.saveData({username, newP});
            help->setText("Password Change Succesful.");
        } else {
            cout << "wha@@t" << endl;
            //wrong password
            help->setText("You entered the wrong password. Please try again.");
        }
        currentPass->setText("");
        newPass->setText("");
    }
    } else if (!okBool){
        string currP, newP;
    currP = getCurrPass();
    newP = getNewPass();
    cout << currP << " SSEES  " << newP << endl;
    if(accountExists()){
        //gets all entries in the logininfo table with the user's username
        vector<vector<string>> data =  db.readAllUser(username);
        //cout << data.at(0).at(0) << endl;
        if(data.at(0).at(0) == currP && data.at(0).at(0) == newP){
            //correct password
            db.delData(username);
            help->setText("Account Deletion Successful. Please exit the app to finalize changes.");
        } else {
            //wrong password
            help->setText("Incorrect Password. Please try again.");
        }
        currentPass->setText("");
        newPass->setText("");
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

void AccountUI::changing(){
    okBool = true;
    animateHide(WAnimation(AnimationEffect::Fade));

    title->setText("Change Password");
    help->setText("Please enter your current password and then your desired new password.");
    linkBtn->setText("Delete Account");
    linkBtn->clicked().connect([=] {
        deleting();
    });

    animateShow(WAnimation(AnimationEffect::Fade));
}

void AccountUI::deleting(){
    okBool = false;
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Delete Account");
    help->setText("Warning: Account deletion is permanent. Enter your password twice to confirm.");
    linkBtn->setText("Change Password");
    linkBtn->clicked().connect([=] {
        changing();
    });

    animateShow(WAnimation(AnimationEffect::Fade));
}
