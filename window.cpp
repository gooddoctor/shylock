#include "window.h"
#include "wxShylockWidget/widget.h"


std::list<window::Window*> window::Window::all_of_them;

window::Window::Window(const engine::String& id_value, 
		       const engine::String& category_value) : 
    id(id_value), category(category_value), win(nullptr) {
    all_of_them.push_back(this);
}

window::Window* window::Window::create(wxWindow*, const window::Size&,
				       window::Sizer* sizer_value, 
				       int proportion, int flag, 
				       int border) {
    wxASSERT_MSG(win, _("win ptr is zero"));
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

window::Label* window::Label::create(wxWindow* parent, const window::Size& size, window::Sizer* sizer,
				     int proportion, int flag, 
				     int border) {
    win = new wxStaticText(parent, wxID_ANY, text, wxDefaultPosition, size);
    Window::create(parent, size, sizer, proportion, flag, border);
    return this;
}

window::Button::Button(const engine::String& id_value,
		       const engine::String& category_value,
		       const engine::String& text_value) : Button(id_value, category_value) {
    text = text_value;
}

window::Button* window::Button::create(wxWindow* parent, const window::Size& size, window::Sizer* sizer,
				       int proportion, int flag, 
				       int border) {
    win = new wxShylockButton(parent, wxID_ANY, text, 
			      wxDefaultPosition, size);
    Window::create(parent, size, sizer, proportion, flag, border);
    return this;
}

template <>
window::Button* window::Button::bind<window::CLICK>(const std::function<void()>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));    
    static_cast<wxShylockButton*>(win)->add_click_callback(callback);
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

    window::Sizer* main_sizer = window::W<window::Sizer*>(window::VERTICAL);

    //list
    [frame](window::Sizer* sizer) {
	window::W<window::Label*>(engine::String(_("list")),
				  engine::String(_("none")),
				  engine::String(_("list")))->
	    create(frame, window::W<window::Size>(500, 0), sizer,
		   1, window::EXPAND);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    window::Sizer* buttons = window::W<window::Sizer*>(window::VERTICAL);
    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("1")),
				   engine::String(_("none")),
				   engine::String(_("1")))->
	    create(frame, window::W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>([](){
		    std::cout << "1 is selected" << std::endl;
		});
	window::W<window::Button*>(engine::String(_("2")),
				  engine::String(_("none")),
				  engine::String(_("2")))->
	    create(frame, window::W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>([]() {
		    std::cout << "2 is selected" << std::endl;
		});
	window::W<window::Button*>(engine::String(_("3")),
				  engine::String(_("none")),
				  engine::String(_("3")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));
    buttons->Add(window::W<window::Sizer*>(_("1")));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("4")),
				  engine::String(_("none")),
				  engine::String(_("4")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("5")),
				  engine::String(_("none")),
				  engine::String(_("5")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("6")),
				   engine::String(_("none")),
				   engine::String(_("6")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));
    buttons->Add(window::W<window::Sizer*>(_("4")));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("7")),
				  engine::String(_("none")),
				  engine::String(_("7")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("8")),
				   engine::String(_("none")),
				   engine::String(_("8")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("9")),
				  engine::String(_("none")),
				  engine::String(_("9")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));
    buttons->Add(window::W<window::Sizer*>(_("7")));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("0")),
				  engine::String(_("none")),
				  engine::String(_("0")))->
	    create(frame, window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("enter")),
				  engine::String(_("none")),
				  engine::String(_("enter")))->
	    create(frame, window::W<window::Size>(120, 45), sizer,
		   1, window::EXPAND);
    }(window::W<window::Sizer*>(window::HORIZONTAL));
    buttons->Add(window::W<window::Sizer*>(_("0")));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("DELL_BTN")),
				  engine::String(_("none")),
				  engine::String(_("DEL")))->
	    create(frame, window::W<window::Size>(80, 45), sizer);
	window::W<window::Button*>(engine::String(_("FIND_BTN")),
				   engine::String(_("none")),
				   engine::String(_("поиск")))->
	    create(frame, window::W<window::Size>(100, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));
    buttons->Add(window::W<window::Sizer*>(_("DELL_BTN")));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("BACK_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Назад")))->
	    create(frame, window::W<window::Size>(180, 45), sizer);
    }(buttons);

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("ADD_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Добавить клиента")))->
	    create(frame, window::W<window::Size>(180, 67), sizer);
	window::W<window::Button*>(engine::String(_("REMOVE_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Удалить клиента")))->
	    create(frame, window::W<window::Size>(180, 67), sizer);
	window::W<window::Button*>(engine::String(_("PAY_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Оплатить")))->
	    create(frame, window::W<window::Size>(180, 67), sizer);
	window::W<window::Button*>(engine::String(_("EDIT_BTN")),
				  engine::String(_("none")),
				  engine::String(_("Редактировать")))->
	    create(frame, window::W<window::Size>(180, 69), sizer);
    }(window::W<window::Sizer*>(window::VERTICAL));
    
    window::W<window::Sizer*>(_("list"))->Add(buttons);
    window::W<window::Sizer*>(_("list"))->Add(window::W<window::Sizer*>(_("EDIT_BTN")));

    [frame](window::Sizer* sizer) {
	window::W<window::Label*>(engine::String(_("KEYBOARD")),
				  engine::String(_("none")),
				  engine::String(_("клавиатура")))->
	    create(frame, window::W<window::Size>(300, 100), sizer, 1, window::EXPAND);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    main_sizer->Add(window::W<window::Sizer*>(_("list")), 0, window::EXPAND);
    main_sizer->Add(window::W<window::Sizer*>(_("KEYBOARD")), 1, window::EXPAND);

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

