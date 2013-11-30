#include "widget.h"

#include <algorithm>

BEGIN_EVENT_TABLE(wxShylockButton, wxPanel)
EVT_PAINT(wxShylockButton::on_paint)
EVT_ERASE_BACKGROUND(wxShylockButton::on_erase_background)
EVT_UPDATE_UI(wxID_ANY, wxShylockButton::on_idle)
EVT_LEFT_DOWN(wxShylockButton::on_mouse_down)
EVT_LEFT_UP(wxShylockButton::on_mouse_up)
END_EVENT_TABLE()

wxShylockButton::wxShylockButton(wxWindow* parent, wxWindowID id, 
				 const wxString& text_value, 
				 const wxPoint& pos,
				 const wxSize& size) : 
      wxPanel(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE), text(text_value) {
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    Enable(true);
}

wxShylockButton* wxShylockButton::click() {
    wxMouseEvent event;
    on_mouse_down(event);
    on_mouse_up(event);
    return this;
}

wxShylockButton* wxShylockButton::add_click_callback(const std::function<void()>& callback) {
    click_notification_callbacks.push_back(callback);
    return this;
}

wxShylockButton* 
wxShylockButton::add_idle_callback(const std::function<void(wxUpdateUIEvent&)>& callback) {
    idle_notification_callbacks.push_back(callback);
    return this;
}

void wxShylockButton::fire_click_notification_callbacks() {
    if (IsEnabled()) {
        std::for_each(click_notification_callbacks.begin(), click_notification_callbacks.end(),
                      [](std::function<void()> callback) {
                          callback();
                      });
    }
}

void wxShylockButton::fire_idle_notification_callbacks(wxUpdateUIEvent& event) {
    using iter = std::list<std::function<void(wxUpdateUIEvent&)> >::iterator;
    for (iter i = idle_notification_callbacks.begin(); i != idle_notification_callbacks.end(); i++) 
        (*i)(event);
}

void wxShylockButton::on_paint(wxPaintEvent& event) {
    /* draw text in the middle */
    wxPaintDC dc(this);
    dc.SetFont(font);

    wxCoord text_width = [this](wxDC& dc) {
	return dc.GetTextExtent(text).GetWidth();
    }(dc);
    wxCoord text_height = [this](wxDC& dc) {
	return dc.GetTextExtent(text).GetHeight();
    }(dc);

    int width = [this]() {
	return GetSize().GetWidth();
    }();
    int height = [this]() {
	return GetSize().GetHeight();
    }();

    dc.DrawText(text, int((width - text_width) / 2), int((height - text_height) / 2));
}


void wxShylockButton::on_erase_background(wxEraseEvent& event) {
    /* draw rounded background */
    wxDC* dc = event.GetDC();
    dc->SetBackground(brush);
    dc->Clear();

    if (!clicked && IsEnabled())
	dc->SetBrush(brush);
    else
        dc->SetBrush(clicked_brush);
    dc->SetPen(pen);

    int width = [this]() {
	return GetSize().GetWidth();
    }();
    int height = [this]() {
	return GetSize().GetHeight();
    }();

    dc->DrawRoundedRectangle(pen.GetWidth(),
                             pen.GetWidth(),
                             width - 2 * pen.GetWidth(),
                             height - 2 * pen.GetWidth(), 10);
}

void wxShylockButton::on_idle(wxUpdateUIEvent& event) {
    fire_idle_notification_callbacks(event);
}

void wxShylockButton::on_mouse_down(wxMouseEvent& event) {
    clicked = true;
    Refresh();
}

void wxShylockButton::on_mouse_up(wxMouseEvent& event) {
    clicked = false;
    Refresh();
    fire_click_notification_callbacks();
}
