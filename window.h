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
    
    enum {CLICK = 0, IDLE, FOCUS};

    using Sizer = wxSizer;
    using Size = wxSize;
    using UpdateUIEvent = wxUpdateUIEvent;
    using MessageBox = int;

    const int HORIZONTAL = wxHORIZONTAL;
    const int VERTICAL = wxVERTICAL;
    const int EXPAND = wxEXPAND;
    const int ALIGN_CENTER = wxALIGN_CENTER_VERTICAL;
    const int OK = wxOK;
    const int ICON_ERROR = wxICON_ERROR;
    
    class RUN {};

    class Window {
	friend Sizer* W<Sizer*>(engine::String name);
        template <typename T>
        friend T find(const engine::String& id);
    public:
	Window(const engine::String& id_value, const engine::String& category_value);
	virtual Window* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value, 
			       int proportion = 0, int flag = 0, int border = 0) = 0;
        virtual Window* show();
        virtual Window* hide();
       virtual Window* enabled();
        virtual Window* disabled();

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
	Button* bind(const std::function<void(Args...)>& callback);

        Button* click();

    protected:
	engine::String text;
    };

    class ListBox : public Window {
    private:
	std::vector<engine::String> entries;
    public:
	ListBox(const engine::String& id_value, const engine::String& category_value,
		std::vector<engine::String>& entries_value);
	ListBox* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
			int proportion = 0, int flag = 0, int border = 0) override;
    };

    class Text : public Window {
    private:
        engine::String text;
    public:
        Text(const engine::String& id_value, const engine::String& category_value,
             const engine::String& text_value);
        Text* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                     int proportion = 0, int flag = 0, int border = 0) override;
        engine::String txt();
        Text* key_press(const engine::String& key);
        template <int S, typename... Args>
	Text* bind(const std::function<void(Args...)>& callback);
    };

    class Time : public Window {
    public:
        using Window::Window;
        Time* create(wxWindow* parent_value, const Size& size_value, Sizer* sizer_value,
                     int proportion = 0, int flag = 0, int border = 0) override;
        engine::String time();
    };

    template <>
    RUN W(std::function<bool(void)> callback, int argc, char** argv);
    
    template <>
    Frame* W(engine::String id, engine::String category, engine::String text);

    template <>
    Frame* W(engine::String id);

    template <>
    None* W(engine::String id, engine::String category);

    template <>
    None* W(engine::String id);

    template <>
    Label* W(engine::String id, engine::String category, engine::String text);

    template <>
    Label* W(engine::String id);
    
    template <>
    Button* W(engine::String id, engine::String category, engine::String text);
    
    template <>
    Button* W(engine::String id);
    
    template <>
    ListBox* W(engine::String id, engine::String category,
	       std::vector<engine::String> entries);

    template <>
    ListBox* W(engine::String id);

    template <>
    Text* W(engine::String id, engine::String category, engine::String text);

    template <>
    Text* W(engine::String id);

    template <>
    Time* W(engine::String id, engine::String category);

    template <>
    Time* W(engine::String id);

    template <>
    Sizer* W(engine::String& name);

    template <>
    Sizer* W(const wchar_t* name);
  
    template <>
    Size W(int width, int height);

    template <>
    Size W();

    template <>
    Sizer* W(int orient);

    template <>
    MessageBox W(engine::String text, engine::String caption, int style);
}


#endif
