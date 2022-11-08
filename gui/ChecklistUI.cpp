#include "ChecklistUI.h"

using namespace std;
using namespace Wt;

namespace {
	const int ITEM_COL = 0;
	const int TYPE_COL = 1;
	const int DATE_COL = 2;
	const int RMV_COL = 3;
	const int HEADER_ROW = 0;
}

ChecklistUI::ChecklistUI() : WTemplate{tr("checklist")}, listCount(0) {
	WApplication *app = WApplication::instance();
	addFunction("id", &WTemplate::Functions::id);
	addFunction("tr", &WTemplate::Functions::tr);
	shared_ptr<WValidator> validator = std::make_shared<WValidator>(true);

	addListField = bindWidget("addListField", make_unique<WLineEdit>());
	addListField->setStyleClass("form-control form-control-lg");
	addListField->setId("addListField");
	addListField->setPlaceholderText("New list");
    addListField->setValidator(validator);

	addTypeField = bindWidget("addTypeField", make_unique<WLineEdit>());
	addTypeField->setStyleClass("form-control form-control-lg");
	addTypeField->setPlaceholderText("New type");
	addTypeField->setId("addTypeField");
	addTypeField->setValidator(validator);

	unique_ptr<WPopupMenu> popupPtr  = make_unique<WPopupMenu>();
	popup = popupPtr.get();
	popup->setHideOnSelect(true);
	popupBtn = bindWidget("popupBtn", make_unique<WPushButton>());
	popupBtn->setMenu(move(popupPtr));

	addBtn = bindWidget("addBtn", make_unique<WPushButton>("Add"));
	addBtn->setStyleClass("btn btn-primary bg-secondary");
	addBtn->clicked().connect(this, &ChecklistUI::add);

	cbFilter = bindWidget("cbFilter", make_unique<WComboBox>());

	cbSort = bindWidget("cbSort", make_unique<WComboBox>());
	cbSort->addItem("Add date");
	cbSort->addItem("Calendar date");

	table = bindWidget("table", make_unique<WTable>());
	table->setHeaderCount(1);
	table->setWidth(WLength("100%"));
	table->elementAt(HEADER_ROW, ITEM_COL)->addNew<Wt::WText>("To do");
	table->elementAt(HEADER_ROW, TYPE_COL)->addNew<Wt::WText>("Type");
	table->elementAt(HEADER_ROW, DATE_COL)->addNew<Wt::WText>("Date added");
	table->elementAt(HEADER_ROW, RMV_COL)->addNew<Wt::WText>();
	table->columnAt(ITEM_COL)->setWidth(WLength("55%"));
	table->columnAt(TYPE_COL)->setWidth(WLength("20%"));
	table->columnAt(DATE_COL)->setWidth(WLength("15%"));
	table->columnAt(DATE_COL)->setStyleClass("d-flex justify-content-center align-items-center");
	table->setStyleClass("table-hover");
	table->rowAt(HEADER_ROW)->setStyleClass("lead rounded fw-normal bg-light");
	table->columnAt(DATE_COL)->setStyleClass("lead rounded fw-normal bg-light d-flex justify-content-center align-items-center");
}

ChecklistUI::~ChecklistUI() {
	
}

// add() adds a new Checklist list and a new type if necessary
// @param nothing
// @return nothing
void ChecklistUI::add() {
	listCount++;
	string type = addTypeField->text().toUTF8();
	string desc = addListField->text().toUTF8();
	WMenuItem *item = popup->addItem(type);
	item->setCheckable(true);
	item->triggered().connect([=] {
		if(item->isChecked()) {
			cbFilter->removeItem(cbFilter->findText(type));
			item->close();
		}
	});
	item->clicked().connect([=]{
		addTypeField->setText(type);
	});
	cbFilter->addItem(type);

	Checklist list(type, desc);
	string key = list.getDateAdded();
	lists.emplace(key, list);

	WLineEdit* rowDesc = table->elementAt(listCount, ITEM_COL)->addNew<WLineEdit>(WString(desc));
	WLineEdit* rowType = table->elementAt(listCount, TYPE_COL)->addNew<WLineEdit>(WString(type));
	table->elementAt(listCount, DATE_COL)->addNew<WText>(WString(list.getDateAdded()));
	WPushButton* rmv = table->elementAt(listCount, RMV_COL)->addWidget(make_unique<WPushButton>("Remove"));

	int row = table->rowAt(listCount)->rowNum();
	rmv->clicked().connect([=] {
		table->removeRow(row);
		listCount--;
	});
	rowDesc->keyWentUp().connect([=] {
		lists.at(key).editDesc(rowDesc->text().toUTF8());
	});
	rowType->keyWentUp().connect([=] {
		lists.at(key).editType(rowType->text().toUTF8());
	});
}

// getTypeInput(pu) adds a new Checklist type
// @param pu is the reference to the popup menu
// @return the text of the selected item as string
string ChecklistUI::getTypeInput(WPopupMenu* popup) {
	if (popup->result()) {
		return popup->result()->text().toUTF8();
	}
	return "";
}
