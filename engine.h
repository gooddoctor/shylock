#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <wx/wx.h>
#include <iostream>
#include <vector>

namespace engine {
    class String : public wxString {
    public:
	using wxString::wxString;
    };

    std::ostream& operator<< (std::ostream& os, const String& obj);
};
#endif
