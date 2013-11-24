#include "widget.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


template <typename To, typename From>
To to(From from) {
  return boost::lexical_cast<To>(from);
}


wxShylockTime::wxShylockTime(wxWindow* parent, wxWindowID id, 
                             const wxPoint& pos, const wxSize& size) :
      wxPanel(parent, id, pos, size) {
    year = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                        wxDefaultSize, 0, nullptr);
    month = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                         wxDefaultSize, 0, nullptr);
    day = new wxChoice(this, wxID_ANY, wxDefaultPosition,
                       wxDefaultSize, 0, nullptr);

    set(wxString(boost::gregorian::
                 to_iso_string(boost::gregorian::day_clock::local_day()).c_str(), wxConvUTF8));
    
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(year, 0, wxALL | wxEXPAND, 3);
    sizer->Add(month, 0, wxALL | wxEXPAND, 3);
    sizer->Add(day, 0, wxALL | wxEXPAND, 3);
    SetSizerAndFit(sizer);
}

void wxShylockTime::set(const wxString& date) {
    boost::gregorian::date current = 
        boost::gregorian::from_undelimited_string(std::string(date.mb_str()));

    std::array<wxString, 10> years = [](int year) {
        std::array<wxString, 10> values;
        std::generate(values.begin(), values.end(),
                      [&year]() {
                          return wxString(to<std::string>(year++).c_str(), wxConvUTF8);
                      });
        return values;
    }(current.year());
    year->Clear();
    year->Append(wxArrayString(years.size(), years.data()));
    year->SetSelection(0);

    std::array<wxString, 12> months = []() {
        std::array<wxString, 12> values;
        int month = 1;
        std::generate(values.begin(), values.end(),
                      [&month]() {
                          return wxString(to<std::string>(month++).c_str(), wxConvUTF8);
                      });
        return values;
    }();
    month->Clear();
    month->Append(wxArrayString(months.size(), months.data()));
    month->SetSelection(current.month() - 1);

    std::array<wxString, 31> days = []() {
        std::array<wxString, 31> values;
        int day = 1;
        std::generate(values.begin(), values.end(),
                      [&day]() {
                          return wxString(to<std::string>(day++).c_str(), wxConvUTF8);
                      });
        return values;
    }();
    day->Clear();
    day->Append(wxArrayString(days.size(), days.data()));
    day->SetSelection(current.day() - 1);
}

wxString wxShylockTime::get() {
    return _("");
}
