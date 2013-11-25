#include "main.h"

using window::W;

bool window_thing::init() {
    window::Frame* frame = W<window::Frame*>(engine::String(_("TOP")),
                                             engine::String(_("NONE")),
                                             engine::String(_("Shylock")))->
        create(nullptr, W<window::Size>(-1, -1), 
               W<window::Sizer*>(window::VERTICAL));
    
    ent(frame);
    add(frame);
    edt(frame);
    pay(frame);

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("1")),
                           engine::String(_("NONE")),
                           engine::String(_("1")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>(std::function<void()>([](){
                        if (window_thing::focus != nullptr) {
                            window_thing::focus->key_press(engine::String(_("1")));
                        }
                    }));
	W<window::Button*>(engine::String(_("2")),
                           engine::String(_("NONE")),
                           engine::String(_("2")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>(std::function<void(void)>(
                                    []() {
                                        std::cout << "2 is selected" << std::endl;
                                    }));
	W<window::Button*>(engine::String(_("3")),
                           engine::String(_("NONE")),
                           engine::String(_("3")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("4")),
                           engine::String(_("NONE")),
                           engine::String(_("4")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(engine::String(_("5")),
                           engine::String(_("NONE")),
                           engine::String(_("5")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(engine::String(_("6")),
                           engine::String(_("NONE")),
                           engine::String(_("6")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("7")),
                           engine::String(_("NONE")),
                           engine::String(_("7")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(engine::String(_("8")),
                           engine::String(_("NONE")),
                           engine::String(_("8")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(engine::String(_("9")),
                           engine::String(_("NONE")),
                           engine::String(_("9")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("0")),
                           engine::String(_("NONE")),
                           engine::String(_("0")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(engine::String(_("ENTER_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("enter")))->
	    create(frame->wx(), W<window::Size>(120, 45), sizer,
		   1, window::EXPAND);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("DELL_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("DEL")))->
	    create(frame->wx(), W<window::Size>(80, 45), sizer);
	W<window::Button*>(engine::String(_("FIND_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("поиск")))->
	    create(frame->wx(), W<window::Size>(100, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        static bool toggle = true;
                        if (toggle) {
                            W<window::Sizer*>(_("ENT.LIST"))->
                                Show(W<window::Sizer*>(_("ENT.FIND_LABEL")));
                        } else {
                            W<window::Sizer*>(_("ENT.LIST"))->
                                Hide(W<window::Sizer*>(_("ENT.FIND_LABEL")));
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
	W<window::Button*>(engine::String(_("BACK_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Назад")))->
	    create(frame->wx(), W<window::Size>(180, 45), sizer)->
            bind<window::CLICK>(std::function<void()>([](){
                        window_thing::state = window_thing::MAIN; 
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
                                       if (window_thing::state == window_thing::MAIN)
                                           event.Enable(false);
                                       else 
                                           event.Enable(true);
                                   }));
    }(W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(engine::String(_("ADD_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Добавить клиента")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        window_thing::state = window_thing::ADD;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("ADD.ADD_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (window_thing::state == window_thing::MAIN) {
                                           event.Enable(true);
                                       } else {
                                           event.Enable(false);
                                       }
                                   }));
	W<window::Button*>(engine::String(_("REMOVE_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Удалить клиента")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (window_thing::state == window_thing::MAIN)
                                           event.Enable(true);
                                       else
                                           event.Enable(false);
                                   }));
	W<window::Button*>(engine::String(_("PAY_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Оплатить")))->
	    create(frame->wx(), W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        window_thing::state = window_thing::PAY;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("PAY.PAY_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (window_thing::state == window_thing::MAIN)
                                           event.Enable(true);
                                       else
                                           event.Enable(false);
                                   }));
	W<window::Button*>(engine::String(_("EDIT_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Редактировать")))->
	    create(frame->wx(), W<window::Size>(180, 69), sizer)->
            bind<window::CLICK>(std::function<void()>([]() {
                        window_thing::state = window_thing::EDIT;
                        W<window::Sizer*>(_("CONTENT"))->
                            Show(W<window::Sizer*>(_("EDT.EDIT_BTN")));
                        W<window::Sizer*>(_("CONTENT"))->
                            Hide(W<window::Sizer*>(_("ENT.LIST")));
                        W<window::Sizer*>(_("CONTENT"))->Layout();
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (window_thing::state == window_thing::MAIN) {
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

        W<window::None*>(engine::String(_("CONTENT")),
                         engine::String(_("NONE")))->
            create(frame->wx(), W<window::Size>(0, 0), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(engine::String(_("Q")),
                           engine::String(_("KEY")),
                           engine::String(_("й")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("W")),
                           engine::String(_("KEY")),
                           engine::String(_("ц")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("E")),
                           engine::String(_("KEY")),
                           engine::String(_("у")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("R")),
                           engine::String(_("KEY")),
                           engine::String(_("к")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("T")),
                           engine::String(_("KEY")),
                           engine::String(_("е")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("Y")),
                           engine::String(_("KEY")),
                           engine::String(_("н")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("U")),
                           engine::String(_("KEY")),
                           engine::String(_("г")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("I")),
                           engine::String(_("KEY")),
                           engine::String(_("ш")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("O")),
                           engine::String(_("KEY")),
                           engine::String(_("щ")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("P")),
                           engine::String(_("KEY")),
                           engine::String(_("з")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("[")),
                           engine::String(_("KEY")),
                           engine::String(_("х")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(engine::String(_("A")),
                           engine::String(_("KEY")),
                           engine::String(_("ф")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("S")),
                           engine::String(_("KEY")),
                           engine::String(_("ы")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("D")),
                           engine::String(_("KEY")),
                           engine::String(_("в")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("F")),
                           engine::String(_("KEY")),
                           engine::String(_("а")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("G")),
                           engine::String(_("KEY")),
                           engine::String(_("п")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("H")),
                           engine::String(_("KEY")),
                           engine::String(_("р")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("J")),
                           engine::String(_("KEY")),
                           engine::String(_("о")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("K")),
                           engine::String(_("KEY")),
                           engine::String(_("л")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("L")),
                           engine::String(_("KEY")),
                           engine::String(_("д")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_(";")),
                           engine::String(_("KEY")),
                           engine::String(_("ж")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("'")),
                           engine::String(_("KEY")),
                           engine::String(_("э")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(engine::String(_("Z")),
                           engine::String(_("KEY")),
                           engine::String(_("я")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("X")),
                           engine::String(_("KEY")),
                           engine::String(_("ч")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("C")),
                           engine::String(_("KEY")),
                           engine::String(_("с")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("V")),
                           engine::String(_("KEY")),
                           engine::String(_("м")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("B")),
                           engine::String(_("KEY")),
                           engine::String(_("и")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("N")),
                           engine::String(_("KEY")),
                           engine::String(_("т")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_("M")),
                           engine::String(_("KEY")),
                           engine::String(_("ь")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_(",")),
                           engine::String(_("KEY")),
                           engine::String(_("б")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(engine::String(_(".")),
                           engine::String(_("KEY")),
                           engine::String(_("ю")))->
            create(frame->wx(), W<window::Size>(150, 30), sizer, 0);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("Q")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("A")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("Z")), 0, window::EXPAND);
        W<window::None*>(engine::String(_("KEYBOARD")),
                         engine::String(_("NONE")))->
            create(frame->wx(), W<window::Size>(0, 0), sizer);
    }(W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("CONTENT")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("KEYBOARD")), 1, window::EXPAND);
    }(W<window::Sizer*>(_("TOP")));

    frame->fit();
    frame->show();

    return true;
}

void window_thing::ent(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("ENT.FIND_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Фильтр")))->
            create(frame->wx(), W<window::Size>(60, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("ENT.FIND_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(225, 30), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = W<window::Text*>(engine::String(_("ENT.FIND_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ENT.FIND_TEXT")), 0, window::EXPAND);
        sizer->Hide(W<window::Sizer*>(_("ENT.FIND_TEXT")));

	W<window::ListBox*>(engine::String(_("ENT.LIST")),
                            engine::String(_("NONE")),
                            std::vector<engine::String> {_("hello"), _("how")})->
	    create(frame->wx(), W<window::Size>(550, 0), sizer,
		   1, window::EXPAND);
    }(W<window::Sizer*>(window::VERTICAL));
}

void window_thing::add(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("ADD.NOMINAL_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("ADD.NOMINAL_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("ADD.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("ADD.COST_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("ADD.COST_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("ADD.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("ADD.TIME_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Дата выплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(engine::String(_("ADD.TIME_INPUT")),
                         engine::String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ADD.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("ADD.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("ADD.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(engine::String(_("ADD.ADD_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Добавить")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer);
    }(W<window::Sizer*>(window::VERTICAL));    
}
 
void window_thing::edt(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("EDT.NOMINAL_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("EDT.NOMINAL_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("EDT.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("EDT.COST_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("EDT.COST_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("EDT.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("EDT.TIME_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Дата выплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(engine::String(_("EDT.TIME_INPUT")),
                         engine::String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("EDT.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("EDT.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("EDT.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(engine::String(_("EDT.EDIT_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Редактировать")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer);
    }(W<window::Sizer*>(window::VERTICAL));    
}
 
void window_thing::pay(window::Frame* frame) {
    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("PAY.NOMINAL_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Имя")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("PAY.NOMINAL_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("PAY.NOMINAL_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("PAY.COST_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Количество")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Text*>(engine::String(_("PAY.COST_TEXT")),
                         engine::String(_("NONE")),
                         engine::String(_("")))->
            create(frame->wx(), W<window::Size>(), sizer, 1)->
            bind<window::FOCUS>(std::function<void()>([](){
                        window_thing::focus = 
                            W<window::Text*>(engine::String(_("PAY.COST_TEXT")));
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Label*>(engine::String(_("PAY.TIME_LABEL")),
                          engine::String(_("NONE")),
                          engine::String(_("Дата оплаты")))->
            create(frame->wx(), W<window::Size>(90, -1), sizer, 0, window::ALIGN_CENTER);
        W<window::Time*>(engine::String(_("PAY.TIME_INPUT")),
                         engine::String(_("NONE")))->
            create(frame->wx(), W<window::Size>(), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("PAY.NOMINAL_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("PAY.COST_LABEL")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("PAY.TIME_LABEL")), 0, window::EXPAND);
        W<window::Button*>(engine::String(_("PAY.PAY_BTN")),
                           engine::String(_("NONE")),
                           engine::String(_("Внести платеж")))->
            create(frame->wx(), W<window::Size>(180, 30), sizer);
        W<window::ListBox*>(engine::String(_("PAY.LIST")),
                            engine::String(_("NONE")),
                            std::vector<engine::String> {_("hello"), _("how")})->
	    create(frame->wx(), W<window::Size>(), sizer,
		   1, window::EXPAND);
    }(W<window::Sizer*>(window::VERTICAL));    
}


int main(int argc, char** argv) {
    window_thing::state = window_thing::MAIN;
    W<window::RUN>(std::function<bool(void)>(window_thing::init), argc, argv);
}


