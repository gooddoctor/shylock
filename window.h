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
    
    enum {CLICK = 0, IDLE};

    using Sizer = wxSizer;
    using Size = wxSize;
    using UpdateUIEvent = wxUpdateUIEvent;

    const int HORIZONTAL = wxHORIZONTAL;
    const int VERTICAL = wxVERTICAL;
    const int EXPAND = wxEXPAND;
    const int ALIGN_CENTER = wxALIGN_CENTER_VERTICAL;

    class RUN {};

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

	template <int S, typename... Args>
	window::Button* bind(const std::function<void(Args...)>& callback);

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

    class Time : public Window {
    public:
        using Window::Window;
        Time* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                     int proportion = 0, int flag = 0, int border = 0) override;
    };

    template <>
    window::RUN W(std::function<bool(void)> callback, int argc, char** argv);

    template <>
    Frame* W(engine::String id, engine::String category, engine::String text);

    template <>
    None* W(engine::String id, engine::String category);

    template <>
    Label* W(engine::String id, engine::String category, engine::String text);

    
    template <>
    Button* W(engine::String id, engine::String category, engine::String text);
    
    template <>
    ListBox* W(engine::String id, engine::String category,
	       std::vector<engine::String> entries);

    template <>
    Text* W(engine::String id, engine::String category, engine::String text);

    template <>
    Time* W(engine::String id, engine::String category);

    template <>
    Sizer* W(const engine::String& name);

    template <>
    Sizer* W(const wchar_t* name);
  
    template <>
    Size W<Size>(int width, int height);

    template <>
    Size W<Size>();

    template <>
    Sizer* W(int orient);
}


#endif
