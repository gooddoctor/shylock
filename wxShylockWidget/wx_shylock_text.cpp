#include "widget.h"

#include <algorithm>

BEGIN_EVENT_TABLE(wxShylockText, wxTextCtrl)
EVT_SET_FOCUS(wxShylockText::on_focus)
END_EVENT_TABLE()


wxShylockText* wxShylockText::add_focus_callback(const std::function<void()>& callback) {
    focus_notification_callbacks.push_back(callback);
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
