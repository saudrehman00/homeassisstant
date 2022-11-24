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
#include <Wt/WValidator.h>
#include <Wt/WTextArea.h>
#include <Wt/WLabel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <vector>
#include "../data/list/ListMap.h"

class ListUI : public Wt::WDialog {
    private:
        Wt::WLineEdit* search;
        Wt::WPopupMenu* popup;
        Wt::WPushButton* addBtn;
        Wt::WPushButton* popupBtn;
        ListMap lists;
        std::string getTypeInput(Wt::WPopupMenu* popup);
        void create();
        void save(std::string note, std::string type);
        void update(Wt::WLabel* contentLabel, Wt::WLabel* typeLabel, Wt::WLabel* dateLabel);
        void addType(Wt::WLineEdit* typeEdit);
        void filter(std::string type);
        void load();

    public:
        ListUI();
        ~ListUI();
};

#endif