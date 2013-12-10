#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <wx/wx.h>
#include <iostream>
#include <vector>
#include <map>

namespace engine {
    using String = wxString;

    class Info : public std::map<String, String> {
        using std::map<String, String>::map;
    };

};
#endif
