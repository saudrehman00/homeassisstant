#ifndef CHECKLISTUI_H
#define CHECKLISTUI_H

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
#include <unordered_map>
#include <string>
#include "../data/list/Checklist.h"

class ChecklistUI : public Wt::WTemplate {
    private:
        Wt::WPopupMenu* popup;
        Wt::WComboBox* cbFilter;
        Wt::WComboBox* cbSort;
        Wt::WLineEdit* addListField;
        Wt::WLineEdit* addTypeField;
        Wt::WPushButton* addBtn;
        Wt::WPushButton* popupBtn;
        Wt::WTable* table;
        int listCount;
        std::unordered_map<std::string, Checklist> lists;

    public:
        ChecklistUI();
        ~ChecklistUI();
        void add();
        std::string getTypeInput(Wt::WPopupMenu* popup);
};

#endif