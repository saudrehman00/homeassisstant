/* Jun Shao
* 251258566
* November 7 2022
* Header file containing member and function delcarations for ListUI
*/

#ifndef LISTUI_H
#define LISTUI_H

#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WComboBox.h>
#include <Wt/WTemplate.h>
#include <Wt/WApplication.h>
#include <Wt/WValidator.h>
#include <Wt/WSignal.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <memory>
#include <string>
#include "../data/list/ListMap.h"
#include "Main.h"

class ListUI : public Wt::WTemplate {
    private:
        Wt::WPopupMenu* popup;
        Wt::WComboBox* cbFilter;
        Wt::WComboBox* cbSort;
        Wt::WLineEdit* addListField;
        Wt::WLineEdit* addTypeField;
        Wt::WPushButton* addBtn;
        Wt::WPushButton* popupBtn;
        Wt::WPushButton* backBtn;
        Wt::WTable* table;
        int listCount;
        ListMap lists;

    public:
        ListUI();
        ~ListUI();
        void add();
        void load();
        std::string getTypeInput(Wt::WPopupMenu* popup);
};

#endif