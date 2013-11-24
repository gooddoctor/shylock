#include "widget.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>


template <typename To, typename From>
To to(From from) {
  return boost::lexical_cast<To>(from);
}


BEGIN_EVENT_TABLE(wxShylockTime, wxPanel)
EVT_CHOICE(ID_YEAR, wxShylockTime::on_day_update)
EVT_CHOICE(ID_MONTH, wxShylockTime::on_day_update)
END_EVENT_TABLE()

wxShylockTime::wxShylockTime(wxWindow* parent, wxWindowID id, 
                             const wxPoint& pos, const wxSize& size) :
      wxPanel(parent, id, pos, size) {
    year = new wxChoice(this, ID_YEAR, wxDefaultPosition,
                        wxDefaultSize, 0, nullptr);
    month = new wxChoice(this, ID_MONTH, wxDefaultPosition,
                         wxDefaultSize, 0, nullptr);
    day = new wxChoice(this, ID_DAY, wxDefaultPosition,
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
    day->Append(wxArrayString(current.end_of_month().day(), days.data()));
    day->SetSelection(current.day() - 1);
}

wxString wxShylockTime::get() {
    return year->GetStringSelection() + month->GetStringSelection() + day->GetStringSelection();
}

void wxShylockTime::on_day_update(wxCommandEvent& event) {
    boost::gregorian::date current = [this]() {
        using namespace boost::gregorian;
        return from_undelimited_string(std::string(year->GetStringSelection().mb_str()) +
                                       std::string(month->GetStringSelection().mb_str()) +
                                       "1");
    }();
    std::array<wxString, 31> days = []() {
        std::array<wxString, 31> values;
        int day = 1;
        std::generate(values.begin(), values.end(),
                      [&day]() {
                          return wxString(to<std::string>(day++).c_str(), wxConvUTF8);
                      });
        return values;
    }();
    int selection = [&]() -> int {
        int previous_day = to<int>(std::string(day->GetStringSelection().mb_str()));
        if (current.end_of_month().day() < previous_day) 
            return current.end_of_month().day() - 1;
        else
            return previous_day - 1;
    }();

    day->Clear();
    day->Append(wxArrayString(current.end_of_month().day(), days.data()));
    day->SetSelection(selection);

 }
