#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <map>

#include "engine.h"

namespace window {
    
    class Window {
    public:
	Window(const engine::String& id_value, const engine::String& class_value,
	       int proportion = 0, int flag = 0, int border = 0);
	Window* attach_to(const wxWindow* other);
    private:
	engine::String id_value;
	engine::String class_value;
	engine::String type;
	int proportion_value, flag_value, border_value;
    };
    
    bool init();

    void W(const engine::String& element, const std::map<engine::String, engine::Any>& args);

    enum amount {ONE, LOT};

    template <amount N>
    engine::Dozens<Window*> W(const engine::String&);

    template <>
    engine::Dozens<Window*> W<ONE>(const engine::String& id_name) {
    	return engine::Dozens<Window*>();
    }
    
    template <>
    engine::Dozens<Window*> W<LOT>(const engine::String& class_name) {
    	return engine::Dozens<Window*>();
    }
}
#endif
