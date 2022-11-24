#ifndef CALCULATORUI_H
#define CALCULATORUI_H

#include <Wt/WGridLayout.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WLabel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDialog.h>
#include <Wt/WRegExpValidator.h>
#include <unordered_map>
#include <string>

class CalculatorUI : public Wt::WDialog {
    private:
        double first;
        double second;
        Wt::WLineEdit *input;
        Wt::WContainerWidget *btnArea;
        std::unordered_map<std::string, Wt::WPushButton*> btns;
        Wt::WPushButton *operand;
        void append(std::string s);
        void operate(std::string btn);
        void compute();
        void createOperand(std::string type);
        void createNum(std::string val);

    public:
        CalculatorUI();
        ~CalculatorUI();
};

#endif