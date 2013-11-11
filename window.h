#ifndef __WINDOW_H
#define __WINDOW_H

#include "engine.h"

namespace window {
  class Window {
  public:
    Window(const engine::String& id_value, const engine::String& category_value);
    virtual Window* create(wxWindow* parent, wxSizer* sizer,
			   int proportion = 0, int flag = 0, int border = 0);
  protected:
    engine::String id;
    engine::String category;
    wxWindow* win;
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

  template <typename T, typename... Args>
  T* W(Args... args);

  template <>
  Window* W(engine::String id, engine::String category) {
    return new Window(id, category);
  }

  template <>
  Label* W(engine::String id, engine::String category, engine::String text) {
    return new Label(id, category, text);
  }

  template <>
  Button* W(int id, int foo) {
    return new Button();
  }
}


#endif
