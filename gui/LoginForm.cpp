/* Jun Shao
* 251258566
* November 7 2022
* LoginForm contains the logic for rendering the login UI
* and for getting the user input from the UI
*/

#include "LoginForm.h"
using namespace std;
using namespace Wt;

// LoginForm() is the constructor for a LoginForm object
// @param nothing
// @return nothing
LoginForm::LoginForm() : WTemplate{tr("login")} {
    WApplication *app = WApplication::instance();
    addFunction("tr", &WTemplate::Functions::tr);

    // components for username input
    userInput = bindWidget("userInput", make_unique<WLineEdit>());
    userInput->setStyleClass("form-control form-outline bg-dark text-white");
    userInput->setPlaceholderText("Username");
    userInput->setId("userInput");

    // components for password input
    passInput = bindWidget("passInput", make_unique<WLineEdit>());
    passInput->setStyleClass("form-control form-outline bg-dark text-white");
    passInput->setPlaceholderText("Password");
    passInput->setId("passInput");

    // components for input validation
    auto validator = make_shared<WValidator>(true);
    userInput->setValidator(validator);
    passInput->setValidator(validator);

    // components for form title
    title = bindWidget("title", make_unique<WText>("Login"));
    title->setStyleClass("fw-bold");

    // components for text helping the user
    help = bindWidget("help", make_unique<WText>("Please fill in your information."));
    help->setStyleClass("text-white-50 mt-4");

    // components for the submission button
    okBtn = bindWidget("okBtn", make_unique<WPushButton>("Submit"));
    okBtn->setStyleClass("btn btn-outline-light btn");

    // components for the button changing forms
    linkBtn = bindWidget("linkBtn", make_unique<WPushButton>("Register"));
    linkBtn->setStyleClass("btn btn-link text-white-50 fw-bold");
    
    // components for text helping to navigate the user
    bottomTxt = bindWidget("bottomTxt", make_unique<WText>("New here?"));
    bottomTxt->setStyleClass("mt-5");

    // change the form to login
    logging();
}

// ~LoginForm() is the destructor for a LoginForm object
// @param nothing
// @return nothing
LoginForm::~LoginForm() {}

// getUserInput() returns the inputted username as string
// @param nothing
// @return userInput the username of the user
string LoginForm::getUserInput() {
    return userInput->text().toUTF8();
}

// getPassInput() returns the inputted password as string
// @param nothing
// @return passInput the password of the user
string LoginForm::getPassInput() {
    return passInput->text().toUTF8();
}

// getOkBtn() gets a pointer to the submit button
// @param nothing
// @return okBtn the reference to the submit object
WPushButton *LoginForm::getOkBtn() {
    return okBtn;
}

// getTitle() returns the form title as string
// @param nothing
// @return title the form title as string
string LoginForm::getTitle() {
    return title->text().toUTF8();
}

// getHelp() returns the reference to the help text object
// @param nothing
// @return help the pointer to the text object
WText* LoginForm::getHelp() {
    return help;
}

// logging() changes the UI form for logging in
// @param nothing
// @return nothing
void LoginForm::logging() {
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Login");
    help->setText("Please fill in your information.");
    linkBtn->setText("Register");
    bottomTxt->setText("New here?");
    linkBtn->clicked().connect(this, &LoginForm::registering);
    animateShow(WAnimation(AnimationEffect::Fade));
}

// registering() changes the UI form for registering
// @param nothing
// @return nothing
void LoginForm::registering() {
    animateHide(WAnimation(AnimationEffect::Fade));
    title->setText("Register");
    help->setText("Please fill in your information.");
    linkBtn->setText("Login");
    bottomTxt->setText("Returning?");
    linkBtn->clicked().connect(this, &LoginForm::logging);
    animateShow(WAnimation(AnimationEffect::Fade));
}