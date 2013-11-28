#ifndef __DATA_H
#define __DATA_H

#include "engine.h"
#include "dep/tinyxml.h"

#include <functional>
#include <list>

namespace data {
    template <typename T, typename... Args>
    T D(Args... args);

    enum {TOP = 0, CHILD};

    class RUN {};

    class XML {
        friend XML* find(const engine::String& id);
    private:
        TiXmlDocument* db;
        engine::String id;
    public:
        XML(TiXmlDocument* db_value, const engine::String& id_value);

        template <int S, typename... Args>
        XML* insert(Args... args);
    protected:
        static std::list<XML*> all_of_them;
    };

    template <>
    RUN D(std::function<bool(void)> callback, int argc, char** argv);

    template <>
    XML* D(engine::String id, engine::String path);
}
#endif
