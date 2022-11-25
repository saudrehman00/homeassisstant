#include "ConversionUI.h"

using namespace std;
using namespace Wt;

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

    // Create some menu items for the popup menu
    leftSel->addItem("temp");
    // fromPop->get units
    rightSel->addItem("temp");
    // toPop->get units
    type->addItem("temp");
    // typePop->get units

    left = layout->bindWidget("left", make_unique<WLineEdit>());
    right = layout->bindWidget("right", make_unique<WLineEdit>());
    left->setValidator(validator);
    right->setValidator(validator);
}

ConversionUI::~ConversionUI() {}