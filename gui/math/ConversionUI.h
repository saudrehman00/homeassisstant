#ifndef CONVERSIONUI_H
#define CONVERSIONUI_H

#include <Wt/WTemplate.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WString.h>
#include <unordered_map>
#include <string>

class ConversionUI : public Wt::WDialog {
    private:
        Wt::WLineEdit *left;
        Wt::WLineEdit *right;
        Wt::WComboBox *leftSel;
        Wt::WComboBox *rightSel;
        Wt::WComboBox *type;
        void getUnits();
        void getTypes();
    public:
        ConversionUI();
        ~ConversionUI();
};

#endif