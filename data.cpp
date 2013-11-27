#include "data.h"

template <>
data::XML* data::D(engine::String id, engine::String path) {
    if (FILE* file = fopen(path.mb_str(), "r")) {
        std::cout << "file exist";
        fclose(file);
    } else {
        std::cout << "file not exist";
    }
    return 0;
}
