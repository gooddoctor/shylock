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

    std::list<std::function<void()> > click_notification_callbacks;
    std::list<std::function<void(wxUpdateUIEvent&)> > idle_notification_callbacks;
public:
    wxShylockButton(wxWindow *parent, wxWindowID id, const wxString& text,
		    const wxPoint& pos = wxDefaultPosition,
		    const wxSize& size = wxDefaultSize);
    wxShylockButton* click();	
    wxShylockButton* add_click_callback(const std::function<void()>& callback);	
    wxShylockButton* add_idle_callback(const std::function<void(wxUpdateUIEvent&)>& callback);	
private:
    void fire_click_notification_callbacks();
    void fire_idle_notification_callbacks(wxUpdateUIEvent& event);
handlers:
    void on_paint(wxPaintEvent& event);
    void on_erase_background(wxEraseEvent& event);
    void on_idle(wxUpdateUIEvent& event);
    void on_mouse_up(wxMouseEvent& event);
    void on_mouse_down(wxMouseEvent& event);
wx_parts:
    DECLARE_EVENT_TABLE()
};

class wxShylockListbox : public wxListBox {
public:
    using wxListBox::wxListBox;
};

class wxShylockText : public wxTextCtrl {
private:
    std::list<std::function<void()> > focus_notification_callbacks;
public:
    using wxTextCtrl::wxTextCtrl;
    wxShylockText* add_focus_callback(const std::function<void()>& callback);
private:
    void fire_focus_notification_callbacks();
handlers:
    void on_focus(wxFocusEvent& event);
wx_parts:
    DECLARE_EVENT_TABLE()
};

class wxShylockTime : public wxPanel {
    enum {
        ID_YEAR = 10000,
        ID_MONTH = 10001,
        ID_DAY = 10002
    };
public:
    wxShylockTime(wxWindow* parent, wxWindowID id, 
                  const wxPoint& pos = wxDefaultPosition, 
                  const wxSize& size = wxDefaultSize);
    void set(const wxString& date);
    wxString get();
private:
    wxChoice* year;
    wxChoice* month;
    wxChoice* day;
handlers:
    void on_day_update(wxCommandEvent& event);
wx_parts:
    DECLARE_EVENT_TABLE()
};
    
#endif
