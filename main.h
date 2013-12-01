#ifndef __MAIN_H
#define __MAIN_H

#include "window.h"
#include "data.h"

namespace window_thing {
    enum State {MAIN, ADD, EDIT, PAY} state;

    window::Text* focus;

    bool init();
    void ent(window::Frame* frame);
    void add(window::Frame* frame);
    void edt(window::Frame* frame);
    void pay(window::Frame* frame);

    template <typename T>
    bool valid(engine::String value);
    template <>
    bool valid<double>(engine::String value);

    std::vector<engine::String> 
    only(const engine::String& value, 
         const std::vector<std::map<engine::String, engine::String> >& entries);
}

namespace data_thing {
    bool init();
}

#endif

