#ifndef __WINDOW_H
#define __WINDOW_H

#include "engine.h"

#include <list>
#include <initializer_list>
#include <functional>

namespace window {

    template <typename T, typename... Args>
    T W(Args... args);
    
    enum {CLICK = 0};

    using Sizer = wxSizer;
    using Size = wxSize;
    const int HORIZONTAL = wxHORIZONTAL;
    const int VERTICAL = wxVERTICAL;
    const int EXPAND = wxEXPAND;

    class Window {
	friend Sizer* W<Sizer*>(const engine::String& name);
    public:
	Window(const engine::String& id_value, const engine::String& category_value);
	virtual Window* create(wxWindow* parent, const Size& size, Sizer* sizer_value, 
			       int proportion = 0, int flag = 0, int border = 0);
    protected:
	engine::String id;
	engine::String category;
	wxWindow* win;
	Sizer* sizer;
	static std::list<Window*> all_of_them;
    };
  
    class Label : public Window {
    public:
	using Window::Window;

	Label(const engine::String& id_value, const engine::String& category_value,
	      const engine::String& text_value);
	Label* create(wxWindow* parent, const Size& size, Sizer* sizer,
		      int proportion = 0, int flag = 0, int border = 0) override;
    protected:
	engine::String text;
    };

    class Button : public Window {
    public:
	using Window::Window;
	Button(const engine::String& id_value, const engine::String& category_value,
	       const engine::String& text_value);
	Button* create(wxWindow* parent, const Size& size, Sizer* sizer,
		       int proportion = 0, int flag = 0, int border = 0) override;

	template <int S>
	window::Button* bind(const std::function<void()>& callback);

    protected:
	engine::String text;
    };

    template <>
    Label* W(engine::String id, engine::String category, engine::String text) {
	return new Label(id, category, text);
    }
    
    template <>
    Button* W(engine::String id, engine::String category, engine::String text) {
    	return new Button(id, category, text);
    }

    template <>
    Sizer* W(const engine::String& name) {
	using iter = std::list<Window*>::iterator;
	for (iter it = Window::all_of_them.begin(); it != Window::all_of_them.end(); it++) {
	    if ((*it)->id == name) {
		return (*it)->sizer;
	    }
	}
	wxASSERT_MSG(0, name + _(" not found"));
	return nullptr;
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
    Sizer* W(int orient) {
	return new wxBoxSizer(orient);
    }
}


#endif
