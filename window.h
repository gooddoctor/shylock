#ifndef __WINDOW_H
#define __WINDOW_H

#include "engine.h"

#include <list>
#include <initializer_list>
#include <functional>
#include <vector>
#include <algorithm>

namespace window {

    template <typename T, typename... Args>
    T W(Args... args);
    
    enum {CLICK = 0};

    using Sizer = wxSizer;
    using Size = wxSize;

    const int HORIZONTAL = wxHORIZONTAL;
    const int VERTICAL = wxVERTICAL;
    const int EXPAND = wxEXPAND;
    const int ALIGN_CENTER = wxALIGN_CENTER_VERTICAL;

    class Window {
	friend Sizer* W<Sizer*>(const engine::String& name);
    public:
	Window(const engine::String& id_value, const engine::String& category_value);
	virtual Window* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value, 
			       int proportion = 0, int flag = 0, int border = 0) = 0;
        virtual Window* show();
        virtual Window* hide();
        virtual wxWindow* wx();
    protected:
	engine::String id;
	engine::String category;
	wxWindow* win;
	Sizer* sizer;
	static std::list<Window*> all_of_them;
    };

    class Frame : public Window {
    public:
        Frame(const engine::String& id_value, const engine::String& category_value,
	      const engine::String& text_value);
        Frame* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                      int proportion = 0, int flag = 0, int border = 0);
        Frame* fit();
    protected:
        engine::String text;
    };

    class None : public Window {
    public:
        using Window::Window;
        None* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                     int proportion = 0, int flag = 0, int border = 0) override;
    };

    class Label : public Window {
    public:
	Label(const engine::String& id_value, const engine::String& category_value,
	      const engine::String& text_value);
	Label* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
		      int proportion = 0, int flag = 0, int border = 0) override;
    protected:
	engine::String text;
    };

    class Button : public Window {
    public:
	Button(const engine::String& id_value, const engine::String& category_value,
	       const engine::String& text_value);
	Button* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
		       int proportion = 0, int flag = 0, int border = 0) override;

	template <int S>
	window::Button* bind(const std::function<void()>& callback);

    protected:
	engine::String text;
    };

    class ListBox : public Window {
    public:
	ListBox(const engine::String& id_value, const engine::String& category_value,
		std::vector<engine::String>& entries_value);
	ListBox* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
			int proportion = 0, int flag = 0, int border = 0) override;
    private:
	std::vector<engine::String> entries;
    };

    class Text : public Window {
    public:
        Text(const engine::String& id_value, const engine::String& category_value,
             const engine::String& text_value);
        Text* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                     int proportion = 0, int flag = 0, int border = 0) override;
    private:
        engine::String text;
    };

    template <>
    Frame* W(engine::String id, engine::String category, engine::String text) {
        return new Frame(id, category, text);
    }

    template <>
    None* W(engine::String id, engine::String category) {
	return new None(id, category);
    }

    template <>
    Label* W(engine::String id, engine::String category, engine::String text) {
	return new Label(id, category, text);
    }
    
    template <>
    Button* W(engine::String id, engine::String category, engine::String text) {
    	return new Button(id, category, text);
    }

    template <>
    ListBox* W(engine::String id, engine::String category,
	       std::vector<engine::String> entries) {
	return new ListBox(id, category, entries);
    }

    template <>
    Text* W(engine::String id, engine::String category, engine::String text) {
        return new Text(id, category, text);
    }

    template <>
    Sizer* W(const engine::String& name) {
	using iter = std::list<Window*>::iterator;
	iter win_pos = std::find_if(Window::all_of_them.begin(), Window::all_of_them.end(),
				    [&name](Window* entry) -> bool {
					return entry->id == name;
				    });
	wxASSERT_MSG(win_pos != Window::all_of_them.end(), name + _(" not found"));
	return (*win_pos)->sizer;
    }

    template <>
    Sizer* W(const wchar_t* name) {
	return W<Sizer*, const engine::String&>(engine::String(name));
    }
  
    template <>
    Size W<Size>(int width, int height) {
	return Size(width, height);
    }

    template <>
    Size W<Size>() {
	return Size(-1, -1);
    }

    template <>
    Sizer* W(int orient) {
	return new wxBoxSizer(orient);
    }
}


#endif
