#ifndef __WINDOW_H
#define __WINDOW_H

#include "engine.h"

#include <list>

namespace window {

  template <typename T, typename... Args>
  T* W(Args... args);

  class Window {
    friend wxSizer* W<wxSizer>(const engine::String& name);
  public:
    Window(const engine::String& id_value, const engine::String& category_value);
    virtual Window* create(wxWindow* parent, wxSizer* sizer_value,
			   int proportion = 0, int flag = 0, int border = 0);
  protected:
    engine::String id;
    engine::String category;
    wxWindow* win;
    wxSizer* sizer;
    static std::list<Window*> all_of_them;
  };
  
  class Label : public Window {
  public:
    using Window::Window;

    Label(const engine::String& id_value, const engine::String& category_value,
	  const engine::String& text_value);
    Label* create(wxWindow* parent, wxSizer* sizer,
		  int proportion = 0, int flag = 0, int border = 0) override;
  protected:
    engine::String text;
  };

  class Button {
  };

  template <>
  Label* W(engine::String id, engine::String category, engine::String text) {
    return new Label(id, category, text);
  }

  template <>
  Button* W(int id, int foo) {
    return new Button();
  }

  template <>
  wxSizer* W<wxSizer>(const engine::String& name) {
    using iter = std::list<Window*>::iterator;
    for (iter it = Window::all_of_them.begin(); it != Window::all_of_them.end(); it++) {
      if ((*it)->id == name) {
	return (*it)->sizer;
      }
    }
    wxASSERT_MSG(0, name + _(" not found"));
    assert(0);
  }

  template <>
  wxSizer* W<wxSizer>(const wchar_t* name) {
    return W<wxSizer, const engine::String&>(engine::String(name));
  }
}


#endif
