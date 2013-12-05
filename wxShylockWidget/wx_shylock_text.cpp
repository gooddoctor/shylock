#include "widget.h"

#include <algorithm>

BEGIN_EVENT_TABLE(wxShylockText, wxTextCtrl)
EVT_SET_FOCUS(wxShylockText::on_focus)
EVT_TEXT(wxID_ANY, wxShylockText::on_text)
END_EVENT_TABLE()


wxShylockText* wxShylockText::add_focus_callback(const std::function<void()>& callback) {
    focus_notification_callbacks.push_back(callback);
    return this;
}

wxShylockText* 
wxShylockText::add_text_callback(const std::function<void(wxString)>& callback) {
    text_notification_callbacks.push_back(callback);
    return this;
}


void wxShylockText::fire_focus_notification_callbacks() {
    std::for_each(focus_notification_callbacks.begin(), focus_notification_callbacks.end(),
                  [](std::function<void()> callback) {
                      callback();
                  });
}   

void wxShylockText::on_focus(wxFocusEvent& event) {
    fire_focus_notification_callbacks();
}

void wxShylockText::on_text(wxCommandEvent& event) {
    std::for_each(text_notification_callbacks.begin(), text_notification_callbacks.end(),
                  [this](std::function<void(wxString)> callback) {
                      callback(GetValue());
                  });
}
