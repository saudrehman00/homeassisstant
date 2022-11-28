/* Jun Shao
 * 251258566
 * November 7 2022
 * List contains the logic for rendering the todo list UI
 * and for interacting with the user input from the UI
 */

#include "NoteUI.h"

using namespace std;
using namespace Wt;

NoteUI::NoteUI(string username) : notes(username)
{
	setWindowTitle("Sticky Notes");
	setModal(false);
	setResizable(true);
	setMinimumSize("350", "500");
	setMaximumSize("1920", "500");
	contents()->setOverflow(Overflow::Scroll, Orientation::Vertical);
	contents()->addStyleClass("form-group");
	footer()->setStyleClass("d-flex flex-row mb-3 mx-3");
	load();

	WPushButton *backBtn = titleBar()->addNew<WPushButton>();
	backBtn->addStyleClass("btn-close");
	backBtn->setToolTip("Close window", TextFormat::XHTML);
	backBtn->clicked().connect([=]
							   {
		notes.delData();
		notes.saveData();
		this->reject(); });

	WPushButton *addBtn = footer()->addNew<WPushButton>("+");
	addBtn->setToolTip("New note", TextFormat::XHTML);
	addBtn->setStyleClass("btn btn-primary bg-secondary");
	addBtn->clicked().connect(this, &NoteUI::createDialog);

	search = footer()->addNew<WLineEdit>();
	search->setPlaceholderText("Filter...");
	search->keyWentUp().connect([=]
								{ filter(search->text().toUTF8()); });

	unique_ptr<WPopupMenu> popupPtr = make_unique<WPopupMenu>();
	popup = popupPtr.get();
	popup->setHideOnSelect(true);
	WPushButton *popupBtn = footer()->addNew<WPushButton>();
	popupBtn->setMenu(move(popupPtr));
	WMenuItem *item = popup->addItem("All");
	item->setCloseable(false);
	item->clicked().connect([=]
							{ search->setText("All"); });
}

NoteUI::~NoteUI() {}

void NoteUI::filter(string type)
{
	int count = contents()->count();
	for (int i = 0; i < count; i++)
	{
		WWidget *w = contents()->widget(i);
		if (w->objectName() == type)
		{
			w->show();
		}
		else if (type == "All")
		{
			w->show();
		}
		else
		{
			w->hide();
		}
	}
}

void NoteUI::addType(WLineEdit *typeEdit)
{
	vector<WMenuItem *> items = popup->items();
	bool found = false;
	for (WMenuItem *i : items)
	{
		if (i->text() == typeEdit->text().toUTF8())
		{
			found = true;
			break;
		}
	}
	if (!found)
	{
		WMenuItem *item = popup->addItem(typeEdit->text().toUTF8());
		item->setCloseable(true);
		item->clicked().connect([=]
								{ search->setText(typeEdit->text().toUTF8()); });
	}
}

// save() save the sticky note and display it in the list
// @param nothing
// @return nothing
void NoteUI::save(string content, string type)
{
	Note note(type, content);
	string date = note.getDateAdded();
	notes.add(note);
	renderNote(note);
}

// createDialog() adds a new List list and a new type if necessary
// @param nothing
// @return nothing
void NoteUI::createDialog()
{
	shared_ptr<WValidator> validator = std::make_shared<WValidator>(true);
	hide();

	WDialog *note = contents()->addChild(make_unique<WDialog>());
	note->setWindowTitle("New note");
	note->rejectWhenEscapePressed();
	note->setMovable(false);

	WTextArea *content = note->contents()->addNew<WTextArea>();
	content->setPlaceholderText("Take a note...");
	content->setValidator(validator);

	WLineEdit *type = note->titleBar()->addNew<WLineEdit>();
	type->setPlaceholderText("Type of note");
	type->setValidator(validator);

	WPushButton *save = note->footer()->addNew<WPushButton>("Save");
	save->setDefault(true);
	save->disable();
	WPushButton *cancel = note->footer()->addNew<WPushButton>("Cancel");

	save->clicked().connect([=]
							{
        if (type->validate() == ValidationState::Valid)
            note->accept(); });

	type->keyWentUp().connect([=]
							  { save->setDisabled(type->validate() != ValidationState::Valid); });

	content->keyWentUp().connect([=]
								 { save->setDisabled(type->validate() != ValidationState::Valid); });

	cancel->clicked().connect(note, &WDialog::reject);

	note->finished().connect([=]
							 {
        if (note->result() == DialogCode::Accepted) {
			NoteUI::save(content->text().toUTF8(), type->text().toUTF8());
			bool found = false;
			addType(type);
		}
        removeChild(note);
		show(); });

	note->show();
}

// update() update the sticky note and display it in the list
// @param nothing
// @return nothing
void NoteUI::update(WLabel *contentLabel, WLabel *typeLabel, WLabel *dateLabel)
{
	string date = dateLabel->text().toUTF8();
	string oldContent = contentLabel->text().toUTF8();
	string oldType = typeLabel->text().toUTF8();
	shared_ptr<WValidator> validator = std::make_shared<WValidator>(true);
	hide();

	WDialog *note = contents()->addChild(make_unique<WDialog>());
	note->setWindowTitle("Edit note");
	note->rejectWhenEscapePressed();
	note->setMovable(false);

	WTextArea *content = note->contents()->addNew<WTextArea>();
	content->setText(oldContent);
	content->setValidator(validator);

	WLineEdit *type = note->titleBar()->addNew<WLineEdit>();
	type->setText(oldType);
	type->setValidator(validator);

	unique_ptr<WPopupMenu> popupPtr = make_unique<WPopupMenu>();
	WPopupMenu *popup = popupPtr.get();
	popup->setHideOnSelect(true);
	WPushButton *popupBtn = note->titleBar()->addNew<WPushButton>();
	popupBtn->setMenu(move(popupPtr));

	WPushButton *save = note->footer()->addNew<WPushButton>("Save");
	save->setDefault(true);
	save->disable();
	WPushButton *cancel = note->footer()->addNew<WPushButton>("Cancel");

	save->clicked().connect([=]
							{
        if (type->validate() == ValidationState::Valid) {
			note->accept(); 
		} });

	type->keyWentUp().connect([=]
							  { save->setDisabled(type->validate() != ValidationState::Valid); });

	content->keyWentUp().connect([=]
								 { save->setDisabled(type->validate() != ValidationState::Valid); });

	cancel->clicked().connect(note, &WDialog::reject);

	note->finished().connect([=]
							 {
        if (note->result() == DialogCode::Accepted) {
			if (oldContent != content->text().toUTF8()) {
				notes.get(date).editDesc(content->text().toUTF8());
				contentLabel->setText(content->text().toUTF8());
			}
			if (oldType != type->text().toUTF8()) {
				notes.get(date).editType(type->text().toUTF8());
				typeLabel->setText(type->text().toUTF8());
			}
		}
        removeChild(note);
		show(); });

	note->show();
}

// load() loads all of the users saved lists
// @param nothing
// @return nothing
void NoteUI::load()
{
	unordered_map<string, Note> map = notes.getNotes();
	for (auto const& note : map)
	{
		renderNote(note.second);
	}
}

void NoteUI::renderNote(Note note)
{
	WContainerWidget *sticky = contents()->addNew<WContainerWidget>();
	WContainerWidget *top = sticky->addNew<WContainerWidget>();
	WContainerWidget *bot = sticky->addNew<WContainerWidget>();

	sticky->setObjectName(note.getType());
	bot->addStyleClass("d-flex flex-row justify-content-between");
	top->addStyleClass("row");
	sticky->addStyleClass("sticky py-2 my-3 px-2");
	WLabel *contentLabel = top->addNew<WLabel>(note.getDesc());
	contentLabel->addStyleClass("overflow-hidden text-truncate");
	contentLabel->setMaximumSize("500", "50");
	WLabel *typeLabel = top->addNew<WLabel>(note.getType());
	typeLabel->addStyleClass("overflow-hidden text-truncate pt-1");
	typeLabel->setMinimumSize("80", "50");
	typeLabel->setMaximumSize("80", "50");
	WLabel *dateLabel = bot->addNew<WLabel>(note.getDateAdded());
	WPushButton *del = bot->addNew<WPushButton>();
	del->setStyleClass("btn-close");
	del->clicked().connect([=] { 
		contents()->removeChild(sticky);
		notes.del(note); 
	});
	sticky->clicked().connect([=] { 
		update(contentLabel, typeLabel, dateLabel); 
	});
}