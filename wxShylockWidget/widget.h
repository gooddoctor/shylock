#ifndef __WIDGET_H
#define __WIDGET_H

#include <wx/wx.h>
#include <functional>
#include <list>

#define wx_parts private
#define handlers private

class wxShylockApp : public wxApp {
private:
    static std::function<bool(void)> init;
public:
    void static run(const std::function<bool(void)>& callback, int argc, char** argv);
    bool OnInit() override;
};

class wxShylockFrame : public wxFrame {
public:
    wxShylockFrame(const wxString& title);
handlers:
    void on_quit(wxCommandEvent& event);
    void on_about(wxCommandEvent& event);
wx_parts:
    DECLARE_EVENT_TABLE()
};

class wxShylockButton : public wxPanel {
private:
    wxString text;
    wxFont font = *wxNORMAL_FONT;
    wxPen pen = wxPen(*wxBLACK, 3);

    wxBrush brush = *wxLIGHT_GREY_BRUSH;
    wxBrush clicked_brush = *wxGREY_BRUSH;

    bool clicked;
    bool enabled = true;

    std::list<std::function<void()> > notification_callbacks;
public:
    wxShylockButton(wxWindow *parent, wxWindowID id, const wxString& text,
		    const wxPoint& pos = wxDefaultPosition,
		    const wxSize& size = wxDefaultSize);
    wxShylockButton* add_click_callback(const std::function<void()>& callback);	
private:
    void fire_notification_callbacks();
handlers:
    void on_paint(wxPaintEvent& event);
    void on_erase_background(wxEraseEvent& event);
    void on_mouse_up(wxMouseEvent& event);
    void on_mouse_down(wxMouseEvent& event);
    void fire_click_event();
wx_parts:
    DECLARE_EVENT_TABLE()
};

class wxShylockListbox : public wxListBox {
public:
    using wxListBox::wxListBox;
};

class wxShylockText : public wxTextCtrl {
public:
    wxShylockText(wxWindow *parent, wxWindowID id, const wxString& text,
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxDefaultSize);
};
    
#endif
