#include "window.h"
#include "wxShylockWidget/widget.h"

std::list<window::Window*> window::Window::all_of_them;

template <typename T>
T window::find(const engine::String& id) {
    using iter = std::list<window::Window*>::iterator;
    iter win_pos = std::find_if(window::Window::all_of_them.begin(), 
                                window::Window::all_of_them.end(),
                                [&id](window::Window* entry) -> bool {
                                    return entry->id == id;
                                });
    wxASSERT_MSG(win_pos != window::Window::all_of_them.end(), id + _(" not found"));
    wxASSERT_MSG(dynamic_cast<T>(*win_pos), id + _(" has wrong type"));
    return static_cast<T>(*win_pos);
}

window::Window::Window(const engine::String& id_value, 
		       const engine::String& category_value) : 
      id(id_value), category(category_value), win(nullptr) {
    all_of_them.push_back(this);
}

window::Window* window::Window::create(wxWindow* parent_value, const window::Size& size_value,
				       window::Sizer* sizer_value, 
				       int proportion, int flag, 
				       int border) {
    wxASSERT_MSG(win, _("win ptr is zero"));
    sizer_value->Add(win, proportion, flag, border);
    sizer = sizer_value;
    return this;
}

window::Window* window::Window::show() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Show(true);
    return this;
}
 
window::Window* window::Window::hide() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Show(false);
    return this;
}


window::Window* window::Window::enabled() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Enable(true);
    return this;
}

window::Window* window::Window::disabled() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Enable(false);
    return this;
}

wxWindow* window::Window::wx() {
    wxASSERT_MSG(win, _("probably wrong. win is zero"));
    return win;
}

window::Frame::Frame(const engine::String& id_value, const engine::String& category_value,
                     const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }

window::Frame* window::Frame::create(wxWindow* parent_value, const window::Size& size_value, 
                                     window::Sizer* sizer_value,
                                     int proportion, int flag, int border) {
    wxASSERT_MSG(parent_value == nullptr, _("frame is top level window"));

    win = new wxShylockFrame(text);
    sizer = sizer_value;

    return this;
}

window::Frame* window::Frame::fit() {
    wxASSERT_MSG(win != nullptr, _("frame is null"));
    wxASSERT_MSG(sizer != nullptr, _("sizer is null"));
    win->SetSizerAndFit(sizer);
    return this;
}

window::None* window::None::create(wxWindow* parent_value, const window::Size& size_value, 
                                   window::Sizer* sizer_value,
                                   int proportion, int flag, int border) {
    wxASSERT_MSG(parent_value != nullptr, _("None create on null parent"));    
    win = new wxWindow(parent_value, wxID_ANY, wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

window::Label::Label(const engine::String& id_value,
		     const engine::String& category_value,
		     const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }


window::Label* window::Label::create(wxWindow* parent_value, 
                                     const window::Size& size_value, 
                                     window::Sizer* sizer_value,
				     int proportion, int flag, 
				     int border) {
    wxASSERT_MSG(parent_value != nullptr, _("label create on null parent"));    
    win = new wxStaticText(parent_value, wxID_ANY, text, wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

window::Button::Button(const engine::String& id_value,
		       const engine::String& category_value,
		       const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }

window::Button* window::Button::create(wxWindow* parent_value, const window::Size& size_value, 
				       window::Sizer* sizer_value, int proportion, int flag, 
				       int border) {
    wxASSERT_MSG(parent_value != nullptr, _("button create on null parent"));    
    win = new wxShylockButton(parent_value, wxID_ANY, text, 
			      wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

template <>
window::Button* window::Button::bind<window::CLICK>(const std::function<void()>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));    
    static_cast<wxShylockButton*>(win)->add_click_callback(callback);
    return this;
}

template <>
window::Button* 
window::Button::bind<window::IDLE>(const std::function<void(window::UpdateUIEvent&)>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));
    static_cast<wxShylockButton*>(win)->add_idle_callback(callback);
    return this;
}
    
window::Button* window::Button::click() {
    wxASSERT_MSG(win, _("call click() only after create()"));
    static_cast<wxShylockButton*>(win)->click();
    return this;
}

window::ListBox::ListBox(const engine::String& id_value, const engine::String& category_value) : 
      Window(id_value, category_value) { }

window::ListBox* window::ListBox::create(wxWindow* parent_value, const window::Size& size_value, 
					 window::Sizer* sizer_value, int proportion, int flag, 
					 int border) {
    wxASSERT_MSG(parent_value != nullptr, _("listbox create on null parent"));    
    
    win = new wxShylockListbox(parent_value, wxID_ANY, 
			       wxDefaultPosition, size_value, 0, nullptr);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);

    return this;
}

int window::ListBox::which() {
    int i = static_cast<wxShylockListbox*>(win)->GetSelection();
    if (i == wxNOT_FOUND) 
        return -1; 
    else 
        return i;
}

window::ListBox* window::ListBox::filter(const engine::String& value) {
    wxASSERT_MSG(win, _("call filter only after create()"));
    static_cast<wxShylockListbox*>(win)->filter(value);
    return this;
}

window::Text::Text(const engine::String& id_value,
                   const engine::String& category_value,
                   const engine::String& text_value) :
      Window(id_value, category_value), text(text_value) { }

window::Text* window::Text::create(wxWindow* parent_value, const window::Size& size_value, 
                                   window::Sizer* sizer_value, int proportion, int flag, 
                                   int border) {
    wxASSERT_MSG(parent_value != nullptr, _("text create on null parent"));
    win = new wxShylockText(parent_value, wxID_ANY, text, 
                            wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

engine::String window::Text::txt() {
    if (win == nullptr)
        return text;
    return static_cast<wxShylockText*>(win)->GetValue();
}

window::Text* window::Text::key_press(const engine::String& key, bool dry) {
    wxASSERT_MSG(win, _("call key_press<>() only after create()"));    
    if (dry) {
        static_cast<wxTextCtrl*>(win)->Clear();
    }
    static_cast<wxTextCtrl*>(win)->AppendText(key);
    return this;
}

template <>
window::Text* window::Text::bind<window::FOCUS>(const std::function<void()>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));    
    static_cast<wxShylockText*>(win)->add_focus_callback(callback);
    return this;
}

template <>
window::Text* 
window::Text::bind<window::TEXT>(const std::function<void(engine::String)>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));    
    static_cast<wxShylockText*>(win)->add_text_callback(callback);
    return this;
}

window::Time* window::Time::create(wxWindow* parent_value, const window::Size& size_value, 
                                   window::Sizer* sizer_value, int proportion, int flag, 
                                   int border) {
    wxASSERT_MSG(parent_value != nullptr, _("time create on null parent"));
    win = new wxShylockTime(parent_value, wxID_ANY, 
                            wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

engine::String window::Time::time() {
    wxASSERT_MSG(win != nullptr, _("getting time on null parent"));
    return static_cast<wxShylockTime*>(win)->get();
}

window::Time* window::Time::time(const engine::String& value) {
    try {
        static_cast<wxShylockTime*>(win)->set(value);
    } catch (std::exception& e) {
        wxASSERT_MSG(false, engine::String::FromUTF8(e.what()));
    }
    return this;
}

template <>
window::Frame* window::W(engine::String id, engine::String category, engine::String text) {
    return new window::Frame(id, category, text);
}

template <>
window::Frame* window::W(engine::String id) {
    return window::find<Frame*>(id);
}

template <>
window::None* window::W(engine::String id, engine::String category) {
    return new window::None(id, category);
}

template <>
window::None* window::W(engine::String id) {
    return window::find<None*>(id);
}

template <>
window::Label* window::W(engine::String id, engine::String category, engine::String text) {
    return new window::Label(id, category, text);
}

template <>
window::Label* window::W(engine::String id) {
    return window::find<Label*>(id);
}

template <>
window::Button* window::W(engine::String id, engine::String category, engine::String text) {
    return new window::Button(id, category, text);
}

template <>
window::Button* window::W(engine::String id) {
    return window::find<Button*>(id);
}

template <>
window::ListBox* window::W(engine::String id, engine::String category) {
    return new window::ListBox(id, category);
}

template <>
window::ListBox* window::W(engine::String id) {
    return window::find<ListBox*>(id);
}

template <>
window::Text* window::W(engine::String id, engine::String category, engine::String text) {
        return new window::Text(id, category, text);
}

template <>
window::Text* window::W(engine::String id) {
    return window::find<Text*>(id);
}

template <>
window::Time* window::W(engine::String id, engine::String category) {
    return new window::Time(id, category);
}

template <>
window::Time* window::W(engine::String id) {
    return window::find<Time*>(id);
}

template <>
window::Sizer* window::W(engine::String name) {
    using iter = std::list<window::Window*>::iterator;
    iter win_pos = std::find_if(window::Window::all_of_them.begin(), 
                                window::Window::all_of_them.end(),
                                [&name](window::Window* entry) -> bool {
                                    return entry->id == name;
                                });
    wxASSERT_MSG(win_pos != window::Window::all_of_them.end(), name + _(" not found"));
    return (*win_pos)->sizer;
}

template <>
window::Sizer* window::W(const wchar_t* name) {
    return window::W<window::Sizer*, engine::String>(engine::String(name));
}

template <>
window::Size window::W(int width, int height) {
    return window::Size(width, height);
}

template <>
window::Size window::W() {
	return window::Size(-1, -1);
}

template <>
window::Sizer* window::W(int orient) {
    return new wxBoxSizer(orient);
}

template <>
window::MessageBox window::W(engine::String text, engine::String caption, int style) {
    return wxMessageBox(text, caption, style, nullptr);
}

template <>
window::RUN window::W(std::function<bool(void)> callback, int argc, char** argv) {
    wxShylockApp::run(callback, argc, argv);
    return window::RUN();
}





