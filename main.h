#ifndef __MAIN_H
#define __MAIN_H

#include "window.h"

namespace window_thing {
    bool init();
    void ent(window::Frame* frame);
    void add(window::Frame* frame);
    void edt(window::Frame* frame);
    void pay(window::Frame* frame);
}

#endif

