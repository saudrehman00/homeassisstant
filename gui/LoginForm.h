/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for LoginForm
*/

#ifndef LOGIN_H
#define LOGIN_H

#include <Wt/WLineEdit.h>
#include <Wt/WAnimation.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h> 
#include <Wt/WValidator.h>
#include <Wt/WSignal.h>
#include <Wt/WText.h>
#include "../data/login/LoginInfo.h"

class LoginForm : public Wt::WTemplate {
    private:
        Wt::WLineEdit* userInput;
        Wt::WLineEdit* passInput;
        Wt::WPushButton* okBtn;
        Wt::WPushButton* linkBtn;
        Wt::WText* bottomTxt;
        Wt::WText* help;
        Wt::WText* title;
        bool newUser;
        void logging();
        void registering();

    public:
        LoginForm();
        ~LoginForm();
        std::string getUserInput();
        std::string getPassInput();
        std::string getTitle();
        Wt::WText* getbottomTxt();
        Wt::WText* getHelp();
        Wt::WPushButton* getOkBtn();
};

#endif