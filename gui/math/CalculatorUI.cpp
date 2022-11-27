#include "CalculatorUI.h"

using namespace std;
using namespace Wt;

CalculatorUI::CalculatorUI() {
    setWindowTitle("Calculator");
	setModal(false);
	setResizable(true);
	setMinimumSize("350", "500");
    contents()->addStyleClass("form-group");

    calc = Calculator();
    first = 0;
    second = 0;
    operand = nullptr;

    WPushButton *backBtn = titleBar()->addNew<WPushButton>();
	backBtn->addStyleClass("btn-close");
	backBtn->setToolTip("Close window", TextFormat::XHTML);
	backBtn->clicked().connect(this, &WDialog::reject);

    input = contents()->addNew<WLineEdit>();
    auto validator = make_shared<WRegExpValidator>("^\\d*\\.?\\d+$");
    input->setValidator(validator);
    input->setStyleClass("bg-dark text-white");
    input->setText("0");

    btnArea = contents()->addNew<WContainerWidget>();
    btnArea->setStyleClass("calculator-keys h-75");

    createOperand("+");
    createOperand("-");
    createOperand("x");
    createOperand("÷");
    createNum("7");
    createNum("8");
    createNum("9");
    createOperand("^");
    createNum("4");
    createNum("5");
    createNum("6");
    createOperand("√");
    createNum("1");
    createNum("2");
    createNum("3");
    createOperand("mod");
    createNum("0");
    createNum(".");

    btns["="] = btnArea->addWidget(make_unique<WPushButton>("="));
    btns["="]->clicked().connect([=] { this->compute(); });

    btns["AC"] = btnArea->addWidget(make_unique<WPushButton>("AC"));
    btns["AC"]->setStyleClass("btn-danger text-white");
    btns["AC"]->clicked().connect([=] { input->setText("0"); });
}

CalculatorUI::~CalculatorUI() {}

void CalculatorUI::append(string s) {
    if (input->text().toUTF8() == "0") {
        input->setText(s);
    } else {
        input->setText(input->text() + s);
    }
}

void CalculatorUI::operate(string btn) {
    first = stod(input->text().toUTF8());
    operand = btns[btn];
    if(operand->text().toUTF8() == "√"){
        first = calc.root(first);
        string inputString = to_string(first);
        inputString.erase(inputString.find_last_not_of('0') + 1, string::npos);
        inputString.erase ( inputString.find_last_not_of('.') + 1, string::npos );
        input->setText(inputString);
    } else {
        input->setText("0");
    }
}

void CalculatorUI::compute() {
    if (operand != nullptr) {
        string opStr = operand->text().toUTF8();
        second = stod(input->text().toUTF8());
        cerr << "\n calculating " << first << " " + opStr + " " << second << "\n";
        
        //if statement logics
        if(opStr == "+"){
            first = calc.addition(first,second);
        }
        if(opStr == "-"){
            first = calc.subtraction(first,second);
        }
        if(opStr == "x"){
            first = calc.multiplication(first,second);
        }
        if(opStr == "÷"){
            first = calc.division(first,second);
        }
        if(opStr == "^"){
            first = calc.exponent(first,second);
        }
        string inputString = to_string(first);
        inputString.erase(inputString.find_last_not_of('0') + 1, string::npos);
        inputString.erase ( inputString.find_last_not_of('.') + 1, string::npos );
        input->setText(inputString);
    }
}

void CalculatorUI::createOperand(string type) {
    btns[type] = btnArea->addWidget(make_unique<WPushButton>(type));
    btns[type]->setStyleClass("btn-warning text-dark");
    btns[type]->clicked().connect([=] { this->operate(type); });
}

void CalculatorUI::createNum(string val) {
    btns[val] = btnArea->addWidget(make_unique<WPushButton>(val));
    btns[val]->setStyleClass("btn-dark text-white");
    btns[val]->clicked().connect([=] { this->append(val); });
}