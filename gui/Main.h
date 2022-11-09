/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for Main
*/

#ifndef MAIN_H
#define MAIN_H

#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include "ListUI.h"

class Main : public Wt::WTemplate {
    private:
        Wt::WPushButton* openListUI;
    public:
        Main();
        ~Main();
};

#endif