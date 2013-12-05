#include "widget.h"

wxShylockListbox* wxShylockListbox::filter(wxString value) {
    value = value.Trim().Trim(false);
    //filter items
    filter_data = all_data;
    filter_data.erase(std::remove_if(filter_data.begin(), filter_data.end(), 
                                     [&value](const std::pair<wxString, void*>& entry) {
                                         return entry.first.Find(value) == wxNOT_FOUND;
                                     }), 
                      filter_data.end());
    //set it
    wxArrayString items = [this]() {
        wxArrayString tmp;
        for (int i = 0; i < filter_data.size(); i++)
            tmp.Add(filter_data[i].first);
        return tmp;
    }();
    Set(items);
    return this;
}
