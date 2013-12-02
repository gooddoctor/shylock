#ifndef __DATA_H
#define __DATA_H

#include "engine.h"
#include "dep/tinyxml.h"

#include <functional>
#include <list>

namespace data {
    template <typename T, typename... Args>
    T D(Args... args);

    enum {TOP = 0, CHILD, INSERT, UPDATE};

    class RUN {};

    class XML {
        friend XML* D<XML*>(engine::String id);
    private:
        TiXmlDocument* db;
        engine::String id;
        std::list<std::function<void(std::map<engine::String, engine::String>&, 
                                     std::map<engine::String, engine::String>&)> >insert_callbacks;
        std::list<std::function<void(std::map<engine::String, engine::String>&, 
                                     std::map<engine::String, engine::String>&)> >update_callbacks;
    public:
        XML(TiXmlDocument* db_value, const engine::String& id_value);

        template <int S, typename... Args>
        XML* insert(Args... args);

        template <int S, typename... Args>
        XML* update(Args... args);

        template <int S, typename... Args>
        std::vector<std::map<engine::String, engine::String> > select(Args... args);

        template <int S>
        XML* bind(std::function<void(std::map<engine::String, engine::String>&, 
                                     std::map<engine::String, engine::String>&)> callback);
    private: 
        void fire_insert_callback(std::map<engine::String, engine::String>& top,
                                  std::map<engine::String, engine::String>& child);
        void fire_update_callback(std::map<engine::String, engine::String>& from,
                                  std::map<engine::String, engine::String>& to);

    protected:
        static std::list<XML*> all_of_them;
    };

    template <>
    RUN D(std::function<bool(void)> callback, int argc, char** argv);

    template <>
    XML* D(engine::String id, engine::String path);
}
#endif
