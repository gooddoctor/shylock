#include "widget.h"

BEGIN_EVENT_TABLE(wxShylockButton, wxPanel)
EVT_PAINT(wxShylockButton::on_paint)
EVT_ERASE_BACKGROUND(wxShylockButton::on_erase_background)
EVT_LEFT_DOWN(wxShylockButton::on_mouse_down)
EVT_LEFT_UP(wxShylockButton::on_mouse_up)
END_EVENT_TABLE()

wxShylockButton::wxShylockButton(wxWindow* parent, wxWindowID id, 
				 const wxString& text_value, 
				 const wxPoint& pos,
				 const wxSize& size, 
				 const wxFont& font_value,
				 const wxBrush& clicked_brush_value, 
				 const wxBrush& brush_value, 
				 const wxPen& pen_value) 
: wxPanel(parent, id, pos, size, wxFULL_REPAINT_ON_RESIZE | wxBORDER_NONE),
    text(text_value),
    font(font_value),
    clicked_brush(clicked_brush_value),
    brush(brush_value),
    pen(pen_value),
    enabled(true) {SetBackgroundStyle(wxBG_STYLE_CUSTOM);}

wxShylockButton* wxShylockButton::add_click_callback(const std::function<void()>& callback) {
    notification_callbacks.push_back(callback);
    return this;
}

void wxShylockButton::fire_notification_callbacks() {
    using iter = std::list<std::function<void()> >::iterator;
    for (iter it = notification_callbacks.begin(); it != notification_callbacks.end(); it++) {
	(*it)();
    }
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

    if (!clicked)
	dc->SetBrush(brush);
    if (clicked || !enabled)
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

void wxShylockButton::on_mouse_down(wxMouseEvent& event) {
  if (enabled) {
    clicked = true;
    fire_notification_callbacks();
    Refresh();
  }
}

void wxShylockButton::on_mouse_up(wxMouseEvent& event) {
  if (enabled) {
    clicked = false;
    Refresh();
  }
}
