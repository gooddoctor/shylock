#ifndef __WIDGET_H
#define __WIDGET_H
#include <wx/wx.h>

#define wx_parts private
#define handlers private

class wxShylockButton : public wxPanel {
private:
    wxString text;
    wxFont font;
    wxPen pen;

    wxBrush brush;
    wxBrush clicked_brush;

    bool clicked;
    bool enabled;
public:
    wxShylockButton(wxWindow *parent, wxWindowID id, const wxString& text,
		    const wxPoint& pos = wxDefaultPosition,
		    const wxSize& size = wxDefaultSize, 
		    const wxFont& font = *wxNORMAL_FONT,
		    const wxBrush& clicked_brush = *wxGREY_BRUSH, 
		    const wxBrush& brush = *wxLIGHT_GREY_BRUSH, 
		    const wxPen& pen = wxPen(*wxBLACK, 3)); 
handlers:
    void on_paint(wxPaintEvent& event);
    void on_erase_background(wxEraseEvent& event);
    void on_mouse_up(wxMouseEvent& event);
    void on_mouse_down(wxMouseEvent& event);
    void fire_click_event();
wx_parts:
    DECLARE_EVENT_TABLE()
};
#endif
