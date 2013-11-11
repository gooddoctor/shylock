#include "window.h"


window::Window::Window(const engine::String& id_value, 
		       const engine::String& category_value) : id(id_value), 
							       category(category_value) {}


window::Window* window::Window::create(wxWindow* parent, wxSizer* sizer, 
				       int proportion, int flag, 
				       int border) {
  win = new wxWindow(parent, wxID_ANY);
  sizer->Add(win, proportion, flag, border);
  return this;
}


window::Label::Label(const engine::String& id_value,
		      const engine::String& category_value,
		      const engine::String& text_value) : 
  Label(id_value, category_value) {
  text = text_value;
}

window::Label* window::Label::create(wxWindow* parent, wxSizer* sizer, 
				     int proportion, int flag, 
				     int border) {
  win = new wxStaticText(parent, wxID_ANY, text);
  sizer->Add(win, proportion, flag, border);
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
    // Create the main application window
    MyFrame *frame = new MyFrame(wxT("Minimal wxWidgets App"));
    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    window::Label* label = window::W<window::Label>(engine::String(_("unknown")),
						    engine::String(_("Unknown")),
						    engine::String(_("unknown soldier")));
    label->create(frame, sizer);
    
    

    // Show it
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

