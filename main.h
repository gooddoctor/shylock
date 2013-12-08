#ifndef __MAIN_H
#define __MAIN_H

#include "window.h"
#include "data.h"

namespace window_thing {
    enum State {MAIN, ADD, EDIT, PAY} state;

    window::Text* focus;

    std::map<window::Text*, window::Text*> text_traverse;

    bool init();
    void ent(window::Frame* frame);
    void add(window::Frame* frame);
    void edt(window::Frame* frame);
    void pay(window::Frame* frame);
    void gen_traverse();

    void completion(window::UpdateUIEvent& event, const wchar_t* letter);

    template <typename T>
    bool valid(engine::String value);
    template <>
    bool valid<double>(engine::String value);
}

namespace data_thing {
    bool init();
}

#endif

