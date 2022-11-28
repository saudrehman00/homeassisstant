/* Jun Shao
* 251258566
* November 7 2022
* Authenticate contains the logic for authenticating a given
* username and password from the login UI
*/

#include "Authenticate.h"

using namespace Wt;
using namespace std;

// Authenticate() is the constructor for an Authenticate object
// @param nothing
// @return nothing
Authenticate::Authenticate() {}

// ~Authenticate() is the destructor for an Authenticate object
// @param nothing
// @return nothing
Authenticate::~Authenticate() {}

// startAuth() processes the validitiy username or password
// @param nothing
// @return nothing
void Authenticate::startAuth() {
    WApplication *app = WApplication::instance();
    LoginForm* f = app->root()->addNew<LoginForm>();

    // function that determines if the main window should be launched
    auto verify = [f, app] {
        string username = f->getUserInput();
        string password = f->getPassInput();
        LoginInfo info(username, password);
        
        // determines if the user is registering or logging in
        string page = f->getTitle();
        bool exists = info.exists(); // determines if the user exists

        // cerr << "\nAuthenticate: username found.\n";
        if (exists && page == "Login") {
             cerr << "\nAuthenticate: checking password.\n";
            if (info.authenticate()) {
                cerr << "\nAuthenticate: password correct.\n";
                app->root()->removeWidget(f);
                app->root()->addNew<MainUI>(username);
                Logger::instance().log(username + " started a session.");
            } else {
                f->getHelp()->setText("Please check that your username or password is correct.");
            }
        } else if (exists && page == "Register") {
            f->getHelp()->setText("That username already exists!");
        } else if (!exists && page == "Login") {
            f->getHelp()->setText("Username doesn't exist.");
        } else if (!exists && page == "Register") {
            info.saveData();
            f->getHelp()->setText("Registration complete!");
        }
    };

    f->getOkBtn()->clicked().connect(verify); // bind function with submit button
}