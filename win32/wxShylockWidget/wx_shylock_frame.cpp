#include "widget.h"

BEGIN_EVENT_TABLE(wxShylockFrame, wxFrame)
EVT_MENU(wxID_EXIT,  wxShylockFrame::on_quit)
END_EVENT_TABLE()

wxShylockFrame::wxShylockFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxMenu* file_menu = []() {
        wxMenu* menu = new wxMenu();
        menu->Append(wxID_EXIT, _("Выход"), _("Выход из программы"));
        return menu;
    }();

    wxMenuBar* menu_bar = [](wxMenu* file_menu) {
        wxMenuBar* menu = new wxMenuBar();
        menu->Append(file_menu, _("&Файл"));
        return menu;
    }(file_menu);

    SetMenuBar(menu_bar);

    CreateStatusBar(1);
    SetStatusText(_("Добро пожаловать в ") + title);

    SetBackgroundStyle(wxBG_STYLE_SYSTEM);
}

void wxShylockFrame::on_quit(wxCommandEvent& event) {
    Close();
}


