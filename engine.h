#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <wx/wx.h>
#include <iostream>
#include <vector>
#include <map>

namespace engine {
    class String : public wxString {
    public:
	using wxString::wxString;
    };

    class Info : public std::map<String, String> {
        using std::map<String, String>::map;
    };

    std::ostream& operator<< (std::ostream& os, const String& obj);
};
#endif
