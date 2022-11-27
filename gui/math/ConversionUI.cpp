#include "ConversionUI.h"

using namespace std;
using namespace Wt;

const double KM = 100000;
const double METER = 100;
const double CM = 1;
const double MM = 0.1;
const double MILE = 160934;
const double FOOT = 30.48;
const double INCH = 2.54;

const double TONNE = 1000000;
const double KG = 1000;
const double GRAM = 1;
const double MG = 0.001;
const double STONE = 6350.29;
const double POUND = 453.592;
const double OUNCE = 28.3495;

const double YEAR = 31540000;
const double MONTH = 2628000;
const double WEEK = 604800;
const double DAY = 86400;
const double HOUR = 3600;
const double MINUTE = 60;
const double SECOND = 1;
const double MILLISECOND = 0.001;



ConversionUI::ConversionUI() {
    setWindowTitle("Unit conversion");
    setModal(false);
    setResizable(true);
    setMinimumSize("600", "250");
    setMaximumSize("1920", "250");
    contents()->addStyleClass("form-group");
    auto layout = contents()->addNew<WTemplate>(tr("converter"));
    auto validator = make_shared<WRegExpValidator>("^\\d*\\.?\\d+$");

    WPushButton *backBtn = titleBar()->addNew<WPushButton>();
    backBtn->addStyleClass("btn-close");
    backBtn->setToolTip("Close window", TextFormat::XHTML);
    backBtn->clicked().connect(this, &WDialog::reject);

    leftSel = layout->bindWidget("leftSel", make_unique<WComboBox>());
    rightSel = layout->bindWidget("rightSel", make_unique<WComboBox>());
    type = layout->bindWidget("type", make_unique<WComboBox>());

    //top type dropdown options
    type->addItem("length");
    type->addItem("mass");
    type->addItem("temperature");
    type->addItem("time");
    //type->addItem("volume");

    //start the program with length selected
    createDropdowns("length");

    type->changed().connect([=] {
        string typeStr = type->itemText(type->currentIndex()).toUTF8(); 
        leftSel->clear();
        rightSel->clear();
        ConversionUI::createDropdowns(typeStr);
    });


    
    // typePop->get units

    left = layout->bindWidget("left", make_unique<WLineEdit>());
    right = layout->bindWidget("right", make_unique<WLineEdit>());
    left->setValidator(validator);
    right->setValidator(validator);

    left->changed().connect([=] {
        convertUnits("left");
    });
    right->changed().connect([=] {
        convertUnits("right");
    });
    leftSel->changed().connect([=] {
        convertUnits("selL");
    });
    rightSel->changed().connect([=] {
        convertUnits("selR");
    });
}

ConversionUI::~ConversionUI() {}

void topListener(){
    cout << "whoo mama " << endl;
}

void ConversionUI::createDropdowns(string type) {
    if(type == "length"){
        addItemBothSides("kilometre");
        addItemBothSides("meter");
        addItemBothSides("centimetre");
        addItemBothSides("millimetre");
        addItemBothSides("mile");
        addItemBothSides("foot");
        addItemBothSides("inch");
    } 
    else if(type == "mass"){
        addItemBothSides("tonne");
        addItemBothSides("kilogram");
        addItemBothSides("gram");
        addItemBothSides("milligram");
        addItemBothSides("stone");
        addItemBothSides("pound");
        addItemBothSides("ounce");
    }
    else if(type == "temperature"){
        addItemBothSides("celsius");
        addItemBothSides("fahrenheit");
        addItemBothSides("kelvin");
    } 
    else if(type == "time"){
        addItemBothSides("year");
        addItemBothSides("month");
        addItemBothSides("week");
        addItemBothSides("day");
        addItemBothSides("hour");
        addItemBothSides("minute");
        addItemBothSides("second");
        addItemBothSides("millisecond");
    }
}

void ConversionUI::addItemBothSides(string item){
        leftSel->addItem(item);
        rightSel->addItem(item);
}

void ConversionUI::convertUnits(string field){
    string leftDropText = leftSel->itemText(leftSel->currentIndex()).toUTF8();
    string rightDropText = rightSel->itemText(rightSel->currentIndex()).toUTF8();

    if(left->text() != ""){
        leftD = stod(left->text().toUTF8());
    }
    if(right->text() != ""){
        rightD = stod(right->text().toUTF8());
    }

    if(field == "left"){
        right->setText(cleanText(convert(leftD, leftDropText, rightDropText)));
    }
    if(field == "right"){
        left->setText(cleanText(convert(rightD, rightDropText, leftDropText)));
    }
    if(field == "selL"){
        right->setText(cleanText(convert(leftD, leftDropText, rightDropText)));
    }
    if(field == "selR"){
        left->setText(cleanText(convert(rightD, rightDropText, leftDropText)));
    }
    
}

string ConversionUI::cleanText(string text){
        string textstr = text;
        textstr.erase(textstr.find_last_not_of('0') + 1, string::npos);
        textstr.erase (textstr.find_last_not_of('.') + 1, string::npos );
        return textstr;
}

string ConversionUI::cleanText(double text){
        string textstr = to_string(text);
        textstr.erase(textstr.find_last_not_of('0') + 1, string::npos);
        textstr.erase (textstr.find_last_not_of('.') + 1, string::npos );
        return textstr;
}

double ConversionUI::convert(double source, string sourceType, string resultType){
    if(sourceType != "fahrenheit" && sourceType != "celsius" && sourceType != "kelvin"){
        return (source*matchType(sourceType))/matchType(resultType);
    } else {
        //don't look at this, avert your eyes
        if(sourceType == "celsius" && resultType == "celsius"){
            return source;
        }
        else if(sourceType == "kelvin" && resultType == "kelvin"){
            return source;
        }
        else if(sourceType == "fahrenheit" && resultType == "fahrenheit"){
            return source;
        }
        else if(sourceType == "celsius" && resultType == "kelvin"){
            return source + 273.15;
        } 
        else if(sourceType == "kelvin" && resultType == "celsius"){
            return source - 273.15;
        }
        else if(sourceType == "celsius" && resultType == "fahrenheit"){
            return (source*9/5) + 32;
        } 
        else if(sourceType == "fahrenheit" && resultType == "celsius"){
            return (source-32)*5/9;
        }
        else if(sourceType == "kelvin" && resultType == "fahrenheit"){
            return (source-32)*5/9 + 273.15;
        } 
        else if(sourceType == "fahrenheit" && resultType == "kelvin"){
            return (source-273.15)*9/5 + 32;
        }
    }
}

double ConversionUI::matchType(string type){
    if(type == "kilometre"){
        return KM;
    } 
    else if(type == "meter"){
        return METER;
    }
    else if(type == "centimetre"){
        return CM;
    }
    else if(type == "millimetre"){
        return MM;
    }
    else if(type == "mile"){
        return MILE;
    }
    else if(type == "foot"){
        return FOOT;
    }
    else if(type == "inch"){
        return INCH;
    }
    else if(type == "tonne"){
        return TONNE;
    }
    else if(type == "kilogram"){
        return KG;
    }
    else if(type == "gram"){
        return GRAM;
    }
    else if(type == "milligram"){
        return MG;
    }
    else if(type == "stone"){
        return STONE;
    }
    else if(type == "pound"){
        return POUND;
    }
    else if(type == "ounce"){
        return OUNCE;
    }
    else if(type == "year"){
        return YEAR;
    }
    else if(type == "month"){
        return MONTH;
    }
    else if(type == "week"){
        return WEEK;
    }
    else if(type == "day"){
        return DAY;
    }
    else if(type == "hour"){
        return HOUR;
    }
    else if(type == "minute"){
        return MINUTE;
    }
    else if(type == "second"){
        return SECOND;
    }
    else if(type == "millisecond"){
        return MILLISECOND;
    }

    
}