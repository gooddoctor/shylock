#ifndef __DATA_H
#define __DATA_H

#include "engine.h"

namespace data {
    template <typename T, typename... Args>
    T D(Args... args);

    class XML {};

    template <>
    XML* D(engine::String id, engine::String path);
}
#endif
