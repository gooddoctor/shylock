#include "widget.h"

BEGIN_EVENT_TABLE(wxShylockFrame, wxFrame)
EVT_MENU(wxID_EXIT,  wxShylockFrame::on_quit)
EVT_MENU(wxID_ABOUT, wxShylockFrame::on_about)
END_EVENT_TABLE()

wxShylockFrame::wxShylockFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxMenu* file_menu = []() {
        wxMenu* menu = new wxMenu();
        menu->Append(wxID_EXIT, _("E&xit\tAlt-X"), _("Quit this program"));
        return menu;
    }();
    wxMenu* help_menu = []() {
        wxMenu* menu = new wxMenu();
        menu->Append(wxID_ABOUT, _("&About...\tF1"), _("Show about dialog"));
        return menu;
    }();

    wxMenuBar* menu_bar = [](wxMenu* file_menu, wxMenu* help_menu) {
        wxMenuBar* menu = new wxMenuBar();
        menu->Append(file_menu, _("&File"));
        menu->Append(help_menu, _("&Help"));
        return menu;
    }(file_menu, help_menu);

    SetMenuBar(menu_bar);

    CreateStatusBar(2);
    SetStatusText(wxT("Welcome to wxWidgets!"));
}

void wxShylockFrame::on_quit(wxCommandEvent& event) {
    Close();
}

void wxShylockFrame::on_about(wxCommandEvent& event) {
    wxString msg = []() {
        wxString str;
        str.Printf(_("Hello and welcome to %s"),
                   wxVERSION_STRING);
        return str;
    }();

    wxMessageBox(msg, _("About Minimal"),
                 wxOK | wxICON_INFORMATION, this);
}

