#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <wx/wx.h>
#include <iostream>
#include <vector>
#include <boost/any.hpp>

namespace engine {
  template <typename T>
  class Dozens : public std::vector<T> {
    using std::vector<T>::vector;
  };

  class String : public wxString {
  public:
    using wxString::wxString;
  };

  class Any : public boost::any {
  public:
    using boost::any::any;
    template <typename T>
    T to() {
      return boost::any_cast<T>(*this);
    }
  };
    

  std::ostream& operator<< (std::ostream& os, const String& obj);
};
#endif
