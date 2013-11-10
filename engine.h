#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <wx/wx.h>
#include <iostream>
#include <vector>

namespace engine {
  template <typename T>
  class Dozens : public std::vector<T> {
    using std::vector<T>::vector;
  };

  class String : public wxString {
  public:
    using wxString::wxString;
  };

  std::ostream& operator<< (std::ostream& os, const String& obj);
};
#endif
