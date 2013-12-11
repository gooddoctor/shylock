#include "main.h"

#include "dep/prefix.h"

#include <boost/date_time/gregorian/gregorian.hpp>

using window::W;
using data::D;
using namespace engine;

std::vector<engine::String> 
only(const engine::String& value, 
     const std::vector<std::map<engine::String, engine::String> >& entries) {
    std::vector<String> items;
    for (auto it = entries.begin(); it != entries.end(); it++)
        if (it->find(value) != it->end())
            items.push_back(it->at(value));
    return items;
}

std::vector<engine::String> 
only(const engine::String& value1, const engine::String& value2, 
     std::function<String(const engine::String& value1, const engine::String& value2)> formatter,
     const std::vector<std::map<engine::String, engine::String> >& entries) {
    std::vector<String> items;
    for (auto it = entries.begin(); it != entries.end(); it++)
        if ((it->find(value1) != it->end()) && (it->find(value2) != it->end()))
            items.push_back(formatter(it->at(value1), it->at(value2)));
    return items;
}


bool window_thing::init() {
    state = MAIN;

    window::Frame* frame = W<window::Frame*>(String(_("TOP")),
                                             String(_("NONE")),
                                             String(_("Shylock")))->
        create(nullptr, W<window::Size>(-1, -1), 
               W<window::Sizer*>(window::VERTICAL));
    
    ent(frame);
    add(frame);
    edt(frame);
    pay(frame);

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("1")),
                           String(_("NONE")),
                           String(_("1")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("1")));
                        } 
                    }));
	W<window::Button*>(String(_("2")),
                           String(_("NONE")),
                           String(_("2")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("2")));
                        } 
                    }));
	W<window::Button*>(String(_("3")),
                           String(_("NONE")),
                           String(_("3")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("3")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("4")),
                           String(_("NONE")),
                           String(_("4")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("4")));
                        } 
                    }));
	W<window::Button*>(String(_("5")),
                           String(_("NONE")),
                           String(_("5")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("6")));
                        } 
                    }));
	W<window::Button*>(String(_("6")),
                           String(_("NONE")),
                           String(_("6")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("6")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("7")),
                           String(_("NONE")),
                           String(_("7")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("7")));
                        } 
                    }));
	W<window::Button*>(String(_("8")),
                           String(_("NONE")),
                           String(_("8")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("8")));
                        } 
                    }));
	W<window::Button*>(String(_("9")),
                           String(_("NONE")),
                           String(_("9")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("9")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("0")),
                           String(_("NONE")),
                           String(_("0")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("0")));
                        } 
                    }));
	W<window::Button*>(String(_("ENTER_BTN")),
                           String(_("NONE")),
                           String(_("Enter")))->
	    create(frame->wx(), W<window::Size>(120, 45), sizer,
		   1, window::EXPAND)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr && text_traverse.find(focus) != text_traverse.end()) {
                            text_traverse.at(focus)->require_focus();
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("DELL_BTN")),
                           String(_("NONE")),
                           String(_("DEL")))->
	    create(frame->wx(), W<window::Size>(80, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(window::K_BACK);
                        } 
                    }));
	W<window::Button*>(String(_("FIND_BTN")),
                           String(_("NONE")),
                           String(_("поиск")))->
	    create(frame->wx(), W<window::Size>(100, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        static bool toggle = true;
                        if (toggle) {
                            W<window::Sizer*>(_("ENT.LIST"))->
                                Hide(W<window::Sizer*>(_("ENT.FIND_LABEL")));
                        } else {
                            W<window::Sizer*>(_("ENT.LIST"))->
                                Show(W<window::Sizer*>(_("ENT.FIND_LABEL")));
                        }
                        W<window::Sizer*>(_("ENT.LIST"))->Layout();
                        toggle = !toggle;
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("1")));
        sizer->Add(W<window::Sizer*>(_("4")));
        sizer->Add(W<window::Sizer*>(_("7")));
        sizer->Add(W<window::Sizer*>(_("0")));
        sizer->Add(W<window::Sizer*>(_("DELL_BTN")));
	W<window::Button*>(String(_("BACK_BTN")),
                           String(_("NONE")),
                           String(_("Назад")))->
	    create(frame->wx(), W<window::Size>(180, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        state = MAIN; 
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ADD.ADD_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("EDT.EDIT_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("PAY.PAY_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (state == MAIN)
                                           event.Enable(false);
                                       else 
                                           event.Enable(true);
                                   }));
    }(W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("ADD_BTN")),
                           String(_("NONE")),
                           String(_("Добавить клиента")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        state = ADD;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("ADD.ADD_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (state == MAIN) {
                                           event.Enable(true);
                                       } else {
                                           event.Enable(false);
                                       }
                                   }));
	W<window::Button*>(String(_("REMOVE_BTN")),
                           String(_("NONE")),
                           String(_("Удалить клиента")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        //get promiser
                        int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                        auto promiser = W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<engine::String, engine::String> >(i);
                        //remove promiser
                        D<data::XML*>(_("db"))->remove<data::TOP>(promiser);
                        W<window::ListBox*>(String(_("ENT.LIST")))->
                            set(only(engine::String(_("nominal")), 
                                     D<data::XML*>(_("db"))->select<data::TOP>()),
                                D<data::XML*>(_("db"))->select<data::TOP>());
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                                       if (state == MAIN && i != -1) {
                                           event.Enable(true);
                                       } else {
                                           event.Enable(false);
                                       }
                                   }));
	W<window::Button*>(String(_("PAY_BTN")),
                           String(_("NONE")),
                           String(_("Оплатить")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        state = PAY;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("PAY.PAY_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();

                        //setting nominal text
                        std::map<String, String> data = []() {
                            int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                            return W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<String, String> >(i);
                        }();
                        W<window::Text*>(String(_("PAY.NOMINAL_TEXT")))->
                            key_press(data.at(_("nominal")), true);

                        //get promiser
                        int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                        auto promiser = W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<engine::String, engine::String> >(i);
                        W<window::ListBox*>(String(_("PAY.LIST")))->
                            set(only(engine::String(_("when")), engine::String(_("amt")),
                                     [](const String& value1, const String& value2) {
                                         using namespace boost::gregorian;
                                         //we need date to transform it to diffrent string repr
                                         date when = 
                                             from_undelimited_string(std::string(value1.mb_str()));
                                         //return yyyy-mm-dd оплачено amout грн
                                         return 
                                             String::FromUTF8(to_iso_extended_string(when).c_str()) + 
                                             _(" оплачено ") + value2 + _(" грн.");
                                     },  D<data::XML*>(_("db"))->select<data::CHILD>(promiser)),
                                D<data::XML*>(_("db"))->select<data::CHILD>(promiser));
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                                       if (state == MAIN && i != -1) {
                                           event.Enable(true);
                                       } else {
                                           event.Enable(false);
                                       }
                                   }));
	W<window::Button*>(String(_("EDIT_BTN")),
                           String(_("NONE")),
                           String(_("Редактировать")))->
	    create(frame->wx(), W<window::Size>(180, 69), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        state = EDIT;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("EDT.EDIT_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();

                        std::map<String, String> data = []() {
                            int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                            return W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<String, String> >(i);
                        }();
                        W<window::Text*>(String(_("EDT.NOMINAL_TEXT")))->
                            key_press(data.at(_("nominal")), true);
                        W<window::Text*>(String(_("EDT.COST_TEXT")))->
                            key_press(data.at(_("cost")), true);
                        W<window::Time*>(String(_("EDT.TIME_INPUT")))->
                            time(data.at(_("when")));
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                                       if (state == MAIN && i != -1) {
                                           event.Enable(true);
                                       } else {
                                           event.Enable(false);
                                       }
                                   }));
    }(W<window::Sizer*>(window::VERTICAL));
    
    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ENT.LIST")), 1, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("ADD.ADD_BTN")), 1, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("EDT.EDIT_BTN")), 1, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("PAY.PAY_BTN")), 1, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("BACK_BTN")));
        sizer->Add(W<window::Sizer*>(_("EDIT_BTN")));

        sizer->Hide(W<window::Sizer*>(_("ADD.ADD_BTN")));
        sizer->Hide(W<window::Sizer*>(_("EDT.EDIT_BTN")));
        sizer->Hide(W<window::Sizer*>(_("PAY.PAY_BTN")));

        W<window::None*>(String(_("CONTENT")),
                         String(_("NONE")))->
            create(frame->wx(), W<window::Size>(0, 0), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(String(_("Q")),
                           String(_("KEY")),
                           String(_("й")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("й"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("й")));
                        } 
                    }));
        W<window::Button*>(String(_("W")),
                           String(_("KEY")),
                           String(_("ц")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ц"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ц")));
                        } 
                    }));
        W<window::Button*>(String(_("E")),
                           String(_("KEY")),
                           String(_("у")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("у"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("у")));
                        } 
                    }));
        W<window::Button*>(String(_("R")),
                           String(_("KEY")),
                           String(_("к")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("к"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("к")));
                        } 
                    }));
        W<window::Button*>(String(_("T")),
                           String(_("KEY")),
                           String(_("е")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("е"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("е")));
                        } 
                    }));
        W<window::Button*>(String(_("Y")),
                           String(_("KEY")),
                           String(_("н")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("н"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("н")));
                        } 
                    }));
        W<window::Button*>(String(_("U")),
                           String(_("KEY")),
                           String(_("г")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("г"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("г")));
                        } 
                    }));
        W<window::Button*>(String(_("I")),
                           String(_("KEY")),
                           String(_("ш")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ш"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ш")));
                        } 
                    }));
        W<window::Button*>(String(_("O")),
                           String(_("KEY")),
                           String(_("щ")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("щ"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("щ")));
                        } 
                    }));
        W<window::Button*>(String(_("P")),
                           String(_("KEY")),
                           String(_("з")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("з"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("з")));
                        } 
                    }));
        W<window::Button*>(String(_("[")),
                           String(_("KEY")),
                           String(_("х")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("х"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("х")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(String(_("A")),
                           String(_("KEY")),
                           String(_("ф")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ф"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ф")));
                        } 
                    }));
        W<window::Button*>(String(_("S")),
                           String(_("KEY")),
                           String(_("ы")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ы"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ы")));
                        } 
                    }));
        W<window::Button*>(String(_("D")),
                           String(_("KEY")),
                           String(_("в")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("в"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("в")));
                        } 
                    }));
        W<window::Button*>(String(_("F")),
                           String(_("KEY")),
                           String(_("а")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("а"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("а")));
                        } 
                    }));
        W<window::Button*>(String(_("G")),
                           String(_("KEY")),
                           String(_("п")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("п"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("п")));
                        } 
                    }));
        W<window::Button*>(String(_("H")),
                           String(_("KEY")),
                           String(_("р")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("р"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("р")));
                        } 
                    }));
        W<window::Button*>(String(_("J")),
                           String(_("KEY")),
                           String(_("о")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("о"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("о")));
                        } 
                    }));
        W<window::Button*>(String(_("K")),
                           String(_("KEY")),
                           String(_("л")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("л"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("л")));
                        } 
                    }));
        W<window::Button*>(String(_("L")),
                           String(_("KEY")),
                           String(_("д")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("д"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("д")));
                        } 
                    }));
        W<window::Button*>(String(_(";")),
                           String(_("KEY")),
                           String(_("ж")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ж"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ж")));
                        } 
                    }));
        W<window::Button*>(String(_("'")),
                           String(_("KEY")),
                           String(_("э")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("э"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("э")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(String(_("Z")),
                           String(_("KEY")),
                           String(_("я")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("я"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("я")));
                        } 
                    }));
        W<window::Button*>(String(_("X")),
                           String(_("KEY")),
                           String(_("ч")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ч"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ч")));
                        } 
                    }));
        W<window::Button*>(String(_("C")),
                           String(_("KEY")),
                           String(_("с")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("с"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("с")));
                        } 
                    }));
        W<window::Button*>(String(_("V")),
                           String(_("KEY")),
                           String(_("м")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("м"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("м")));
                        } 
                    }));
        W<window::Button*>(String(_("B")),
                           String(_("KEY")),
                           String(_("и")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("и"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("и")));
                        } 
                    }));
        W<window::Button*>(String(_("N")),
                           String(_("KEY")),
                           String(_("т")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("т"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("т")));
                        } 
                    }));
        W<window::Button*>(String(_("M")),
                           String(_("KEY")),
                           String(_("ь")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("ь"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ь")));
                        } 
                    }));
        W<window::Button*>(String(_(",")),
                           String(_("KEY")),
                           String(_("б")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       completion(event, _("б"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("б")));
                        } 
                    }));
        W<window::Button*>(String(_(".")),
                           String(_("KEY")),
                           String(_("ю")))->
            create(frame->wx(), W<window::Size>(150, 30), sizer, 0)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                           completion(event, _("ю"));
                                   }))->
            bind<window::CLICK>(std::function<void()>([](){
                        if (focus != nullptr) {
                            focus->key_press(String(_("ю")));
                        } 
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("Q")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("A")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("Z")), 0, window::EXPAND);
        W<window::None*>(String(_("KEYBOARD")),
                         String(_("NONE")))->
            create(frame->wx(), W<window::Size>(0, 0), sizer);
    }(W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("CONTENT")), 0, window::EXPAND | window::LEFT, 5);
        sizer->Add(W<window::Sizer*>(_("KEYBOARD")), 1, window::EXPAND | window::LEFT, 5);
    }(W<window::Sizer*>(_("TOP")));

    gen_traverse();

    frame->fit();
    frame->show();

    return true;
}

void window_thing::ent(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("ENT.FIND_LABEL")),
                          String(_("NONE")),
                          String(_("Фильтр")))->
            create(frame->wx(), W<window::Size>(60, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("ENT.FIND_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(225, 30), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("ENT.FIND_TEXT")));
                    }))->
            bind<window::TEXT>(std::function<void(String)>([](String value){
                        W<window::ListBox*>(String(_("ENT.LIST")))->filter(value);
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ENT.FIND_TEXT")), 0, window::EXPAND);

	W<window::ListBox*>(String(_("ENT.LIST")),
                            String(_("NONE")))->
	    create(frame->wx(), W<window::Size>(550, 0), sizer,
		   1, window::EXPAND)->
            set_font(window::Font(14))->
            set(only(engine::String(_("nominal")), D<data::XML*>(_("db"))->select<data::TOP>()),
                D<data::XML*>(_("db"))->select<data::TOP>());
    }(W<window::Sizer*>(window::VERTICAL));
}

void window_thing::add(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("ADD.NOMINAL_LABEL")),
                          String(_("NONE")),
                          String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("ADD.NOMINAL_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("ADD.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("ADD.COST_LABEL")),
                          String(_("NONE")),
                          String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("ADD.COST_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("ADD.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("ADD.TIME_LABEL")),
                          String(_("NONE")),
                          String(_("Дата выплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(String(_("ADD.TIME_INPUT")),
                         String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ADD.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("ADD.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("ADD.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(String(_("ADD.ADD_BTN")),
                           String(_("NONE")),
                           String(_("Добавить")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        String nominal = W<window::Text*>(String(_("ADD.NOMINAL_TEXT")))->txt();
                        String cost = W<window::Text*>(String(_("ADD.COST_TEXT")))->txt();
                        String when = W<window::Time*>(String(_("ADD.TIME_INPUT")))->time();
                        
                        if (nominal.IsEmpty() || cost.IsEmpty() || when.IsEmpty()) {
                            W<window::MessageBox>(String(_("Некоторые поля остались пусты")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        if (!valid<double>(cost)) {
                            W<window::MessageBox>(String(_("Неверное значение стоимости")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        std::map<String, String> entry;
                        entry.insert(std::pair<String, String>{_("nominal"), nominal});
                        entry.insert(std::pair<String, String>{_("cost"), cost});
                        entry.insert(std::pair<String, String>{_("when"), when});
 
                        D<data::XML*>(_("db"))->insert<data::TOP>(entry);

                        W<window::Button*>(String(_("BACK_BTN")))->click();
                    }));
    }(W<window::Sizer*>(window::VERTICAL));    
}
 
void window_thing::edt(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("EDT.NOMINAL_LABEL")),
                          String(_("NONE")),
                          String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("EDT.NOMINAL_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("EDT.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("EDT.COST_LABEL")),
                          String(_("NONE")),
                          String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("EDT.COST_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("EDT.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("EDT.TIME_LABEL")),
                          String(_("NONE")),
                          String(_("Дата выплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(String(_("EDT.TIME_INPUT")),
                         String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("EDT.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("EDT.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("EDT.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(String(_("EDT.EDIT_BTN")),
                           String(_("NONE")),
                           String(_("Редактировать")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        // get value
                        String nominal = W<window::Text*>(String(_("EDT.NOMINAL_TEXT")))->txt();
                        String cost = W<window::Text*>(String(_("EDT.COST_TEXT")))->txt();
                        String when = W<window::Time*>(String(_("EDT.TIME_INPUT")))->time();

                        // test value
                        if (nominal.IsEmpty() || cost.IsEmpty() || when.IsEmpty()) {
                            W<window::MessageBox>(String(_("Некоторые поля остались пусты")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        if (!valid<double>(cost)) {
                            W<window::MessageBox>(String(_("Неверное значение стоимости")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        //get old map
                        int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                        auto from = W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<engine::String, engine::String> >(i);

                        // create new  map  
                        std::map<String, String> to;
                        to.insert(std::pair<String, String>{_("nominal"), nominal});
                        to.insert(std::pair<String, String>{_("cost"), cost});
                        to.insert(std::pair<String, String>{_("when"), when});
 
                        // change old on new
                        D<data::XML*>(_("db"))->update<data::TOP>(from, to);

                        // return to main window
                        W<window::Button*>(String(_("BACK_BTN")))->click();

                    }));
    }(W<window::Sizer*>(window::VERTICAL));    
}
 
void window_thing::pay(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("PAY.NOMINAL_LABEL")),
                          String(_("NONE")),
                          String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("PAY.NOMINAL_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("PAY.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("PAY.COST_LABEL")),
                          String(_("NONE")),
                          String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(String(_("PAY.COST_TEXT")),
                         String(_("NONE")),
                         String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        focus = W<window::Text*>(String(_("PAY.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(String(_("PAY.TIME_LABEL")),
                          String(_("NONE")),
                          String(_("Дата оплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(String(_("PAY.TIME_INPUT")),
                         String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("PAY.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("PAY.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("PAY.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(String(_("PAY.PAY_BTN")),
                           String(_("NONE")),
                           String(_("Внести платеж")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        // get value
                        String amt = W<window::Text*>(String(_("PAY.COST_TEXT")))->txt();
                        String when = W<window::Time*>(String(_("PAY.TIME_INPUT")))->time();

                        // test value
                        if (amt.IsEmpty() || when.IsEmpty()) {
                            W<window::MessageBox>(String(_("Некоторые поля остались пусты")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        if (!valid<double>(amt)) {
                            W<window::MessageBox>(String(_("Неверное значение оплаты")),
                                                  String(_("Ошибка ввода")), 
                                                  window::OK | window::ICON_ERROR);
                            return;
                        }

                        //get promiser
                        int i = W<window::ListBox*>(String(_("ENT.LIST")))->which();
                        auto promiser = W<window::ListBox*>(String(_("ENT.LIST")))->
                            get<std::map<engine::String, engine::String> >(i);
                        // create new  payment  
                        std::map<String, String> payment;
                        payment.insert(std::pair<String, String>{_("amt"), amt});
                        payment.insert(std::pair<String, String>{_("when"), when});
 
                        // insert payment
                        D<data::XML*>(_("db"))->insert<data::CHILD>(promiser, payment);

                        // return to main window
                        W<window::Button*>(String(_("BACK_BTN")))->click();

                    }));
        W<window::ListBox*>(String(_("PAY.LIST")),
                            String(_("NONE")))->
	    create(frame->wx(), W<window::Size>(), sizer,
		   1, window::EXPAND)->
            set_font(window::Font(14));
    }(W<window::Sizer*>(window::VERTICAL));    
}

void window_thing::gen_traverse() {
    text_traverse.insert({W<window::Text*>(String(_("ADD.NOMINAL_TEXT"))),
                          W<window::Text*>(String(_("ADD.COST_TEXT")))});
    text_traverse.insert({W<window::Text*>(String(_("ADD.COST_TEXT"))),
                          W<window::Text*>(String(_("ADD.NOMINAL_TEXT")))});
    text_traverse.insert({W<window::Text*>(String(_("PAY.NOMINAL_TEXT"))),
                          W<window::Text*>(String(_("PAY.COST_TEXT")))});
    text_traverse.insert({W<window::Text*>(String(_("PAY.COST_TEXT"))),
                          W<window::Text*>(String(_("PAY.NOMINAL_TEXT")))});
    text_traverse.insert({W<window::Text*>(String(_("EDT.NOMINAL_TEXT"))),
                          W<window::Text*>(String(_("EDT.COST_TEXT")))});
    text_traverse.insert({W<window::Text*>(String(_("EDT.COST_TEXT"))),
                          W<window::Text*>(String(_("EDT.NOMINAL_TEXT")))});
}
    

void window_thing::completion(window::UpdateUIEvent& event, const wchar_t* letter) {
    if (state == MAIN) {
        auto entries = W<window::ListBox*>(String(_("ENT.LIST")))->entries();
        auto flt = W<window::Text*>(String(_("ENT.FIND_TEXT")))->txt().MakeLower();
        for (auto it = entries.begin(); it != entries.end(); it++)
            if (it->MakeLower().Find(flt + letter) != wxNOT_FOUND) {
                event.Enable(true);
                return;
            }
        event.Enable(false);
    } else {
        event.Enable(true);
    }
}


template <>
bool window_thing::valid<double>(engine::String value) {
    double tmp;
    return value.ToDouble(&tmp);
}

bool data_thing::init() {
    D<data::XML*>(String(_("db")), String::FromUTF8("C:\\") + String(_("db.xml")))->
        bind<data::INSERT>([](std::map<engine::String, engine::String>& top,
                              std::map<engine::String, engine::String>& child) {
                               W<window::ListBox*>(String(_("ENT.LIST")))->
                                   set(only(engine::String(_("nominal")), 
                                            D<data::XML*>(_("db"))->select<data::TOP>()),
                                       D<data::XML*>(_("db"))->select<data::TOP>());
                           });
    D<data::XML*>(_("db"))->
        bind<data::UPDATE>([](std::map<engine::String, engine::String>& from,
                              std::map<engine::String, engine::String>& to) {
                               W<window::ListBox*>(String(_("ENT.LIST")))->
                                   set(only(engine::String(_("nominal")), 
                                            D<data::XML*>(_("db"))->select<data::TOP>()),
                                       D<data::XML*>(_("db"))->select<data::TOP>());
                           });
    return true;
}


int main(int argc, char** argv) {
    D<data::RUN>(std::function<bool(void)>(data_thing::init), argc, argv);
    W<window::RUN>(std::function<bool(void)>(window_thing::init), argc, argv);
}


