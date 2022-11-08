/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for Assistant
*/

#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WString.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrap5Theme.h>
#include "auth/Authenticate.h"

class Assistant: public Wt::WApplication{
    public:
        Assistant(const Wt::WEnvironment &env);
        ~Assistant();
        Wt::WApplication* createApplication(const Wt::WEnvironment &env);
};

#endif