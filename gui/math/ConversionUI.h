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
        double leftD, rightD;;
        double convert(double source, std::string sourceType, std::string resultType);
        double matchType(std::string type);
        std::string cleanText(std::string text);
        std::string cleanText(double text);
        Wt::WLineEdit *left;
        Wt::WLineEdit *right;
        Wt::WComboBox *leftSel;
        Wt::WComboBox *rightSel;
        Wt::WComboBox *type;
        void addItemBothSides(std::string item);
        void createDropdowns(std::string type);
        void convertUnits(std::string field);
        void getUnits();
        void getTypes();
        void topListener();

    public:
        ConversionUI();
        ~ConversionUI();
};

#endif