#include "window.h"


std::list<window::Window*> window::Window::all_of_them;

window::Window::Window(const engine::String& id_value, 
		       const engine::String& category_value) : 
    id(id_value), category(category_value) {
    all_of_them.push_back(this);
}

window::Window* window::Window::create(wxWindow*, const wxSize&,
				       wxSizer* sizer_value, 
				       int proportion, int flag, 
				       int border) {
    assert(win);
    sizer_value->Add(win, proportion, flag, border);
    sizer = sizer_value;
    return this;
}

window::Label::Label(const engine::String& id_value,
		     const engine::String& category_value,
		     const engine::String& text_value) : 
    Label(id_value, category_value) {
    text = text_value;
}

window::Label* window::Label::create(wxWindow* parent, const wxSize& size, wxSizer* sizer,
				     int proportion, int flag, 
				     int border) {
    win = new wxStaticText(parent, wxID_ANY, text, wxDefaultPosition, size);
    Window::create(parent, size, sizer, proportion, flag, border);
    return this;
}




// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Declare the application class
class MyApp : public wxApp
{
public:
    // Called on application startup
    virtual bool OnInit();
};

// Declare our main frame class
class MyFrame : public wxFrame
{
public:
    // Constructor
    MyFrame(const wxString& title);

    // Event handlers
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    // This class handles events
    DECLARE_EVENT_TABLE()
};

// Implements MyApp& GetApp()
DECLARE_APP(MyApp)

// Give wxWidgets the means to create a MyApp object
IMPLEMENT_APP(MyApp)

// Initialize the application
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));

    wxSizer* main_sizer = window::W<wxSizer*>(wxVERTICAL);

    //list
    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("list")),
				  engine::String(_("none")),
				  engine::String(_("list")))->
	    create(frame, window::W<wxSize>(100, 200), sizer,
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));

    wxSizer* buttons = window::W<wxSizer*>(wxVERTICAL);
    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("1")),
				  engine::String(_("none")),
				  engine::String(_("1")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("2")),
				  engine::String(_("none")),
				  engine::String(_("2")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("3")),
				  engine::String(_("none")),
				  engine::String(_("3")))->
	    create(frame, window::W<wxSize>(30, 30), sizer, 1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));
    buttons->Add(window::W<wxSizer*>(_("1")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("4")),
				  engine::String(_("none")),
				  engine::String(_("4")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("5")),
				  engine::String(_("none")),
				  engine::String(_("5")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("6")),
				  engine::String(_("none")),
				  engine::String(_("6")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));
    buttons->Add(window::W<wxSizer*>(_("4")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("7")),
				  engine::String(_("none")),
				  engine::String(_("7")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("8")),
				  engine::String(_("none")),
				  engine::String(_("8")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("9")),
				  engine::String(_("none")),
				  engine::String(_("9")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));
    buttons->Add(window::W<wxSizer*>(_("7")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("0")),
				  engine::String(_("none")),
				  engine::String(_("0")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("enter")),
				  engine::String(_("none")),
				  engine::String(_("enter")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));
    buttons->Add(window::W<wxSizer*>(_("0")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("DELL_BTN")),
				  engine::String(_("none")),
				  engine::String(_("DEL")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("FIND_BTN")),
				  engine::String(_("none")),
				  engine::String(_("поиск")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));
    buttons->Add(window::W<wxSizer*>(_("DELL_BTN")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("BACK_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Назад")))->
	    create(frame, window::W<wxSize>(30, 30), sizer,
		   1, wxEXPAND);
    }(buttons);

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("ADD_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Добавить клиента")))->
	    create(frame, window::W<wxSize>(90, 60), sizer, 
		   1, wxEXPAND);
	window::W<window::Label*>(engine::String(_("REMOVE_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Удалить клиента")))->
	    create(frame, window::W<wxSize>(90, 60), sizer, 
		   1, wxEXPAND);

	window::W<window::Label*>(engine::String(_("PAY_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Оплатить")))->
	    create(frame, window::W<wxSize>(90, 60), sizer, 
		   1, wxEXPAND);

	window::W<window::Label*>(engine::String(_("EDIT_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Редактировать")))->
	    create(frame, window::W<wxSize>(90, 60), sizer, 
		   1, wxEXPAND);
    }(window::W<wxSizer*>(wxVERTICAL));
    
    window::W<wxSizer*>(_("list"))->Add(buttons, 1, wxEXPAND);
    window::W<wxSizer*>(_("list"))->Add(window::W<wxSizer*>(_("EDIT_BTN")));

    [frame](wxSizer* sizer) {
	window::W<window::Label*>(engine::String(_("KEYBOARD")),
				  engine::String(_("none")),
				  engine::String(_("клавиатура")))->
	    create(frame, window::W<wxSize>(300, 100), sizer, 1, wxEXPAND);
    }(window::W<wxSizer*>(wxHORIZONTAL));

    main_sizer->Add(window::W<wxSizer*>(_("list")), 0, wxEXPAND);
    main_sizer->Add(window::W<wxSizer*>(_("KEYBOARD")), 1, wxEXPAND);

    frame->SetSizerAndFit(main_sizer);
    frame->Show(true);

    // Start the event loop
    return true;
}

// Event table for MyFrame
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT,  MyFrame::OnQuit)
END_EVENT_TABLE()

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"),
               wxVERSION_STRING);


    wxMessageBox(msg, wxT("About Minimal"),
                 wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& event)
{
    // Destroy the frame
    Close();
}


MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
{
    // Create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // The "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&About...\tF1"),
                     wxT("Show about dialog"));

    fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"),
                     wxT("Quit this program"));

    // Now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    // Create a status bar just for fun
    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}

