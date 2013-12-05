#ifndef __WIDGET_H
#define __WIDGET_H

#include <wx/wx.h>
#include <functional>
#include <list>
#include <vector>
#include <algorithm>

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
private:
    std::vector<std::pair<wxString, void*> > all_data;
    std::vector<std::pair<wxString, void*> > filter_data;
public:
    using wxListBox::wxListBox;
    
    template <typename T>
    wxShylockListbox* set(const std::vector<wxString>& choices, const std::vector<T>& data) {
        wxASSERT_MSG(choices.size() == data.size(), 
                     _("size of choices and data must be equal"));
        //generate vector of pair
        all_data.clear();
        for (int i = 0; i < choices.size(); i++) 
            all_data.push_back({choices[i], static_cast<void*>(new T(data[i]))});
        //geneerate filter
        filter_data = all_data;
        //generate and set items
        wxArrayString items = [this]() {
            wxArrayString tmp;
            for (int i = 0; i < filter_data.size(); i++)
                tmp.Add(filter_data[i].first);
            return tmp;
        }();
        Set(items);

        return this;
    }

    template <typename T>
    T get(unsigned int i) {
        wxASSERT_MSG(i >= 0 && i < filter_data.size(), _("oops. i out of interval"));
        return *(static_cast<T*>(filter_data[i].second));
    }

    wxShylockListbox* filter(wxString value);
};

class wxShylockText : public wxTextCtrl {
private:
    std::list<std::function<void()> > focus_notification_callbacks;
    std::list<std::function<void(wxString)> > text_notification_callbacks;
public:
    using wxTextCtrl::wxTextCtrl;
    wxShylockText* add_focus_callback(const std::function<void()>& callback);
    wxShylockText* add_text_callback(const std::function<void(wxString)>& callback);	
private:
    void fire_focus_notification_callbacks();
handlers:
    void on_focus(wxFocusEvent& event);
    void on_text(wxCommandEvent& event);
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
