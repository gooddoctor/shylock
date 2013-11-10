#include "window.h"

namespace window {
  std::map<engine::String, 
	   std::function<wxWindow*(std::map<engine::String, engine::Any> arg)> > create;
}
