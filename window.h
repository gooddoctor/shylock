#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <boost/any.hpp>
#include <map>

#include "engine.h"

namespace window {
    
    class Window {
    };

    void W(const engine::String& element, const std::map<engine::String, boost::any>& args);

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
