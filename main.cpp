#include "main.h"

#include "dep/prefix.h"

using window::W;
using data::D;
using namespace engine;

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
	    bind<window::CLICK>(std::function<void(void)>(
                                    []() {
                                        std::cout << "2 is selected" << std::endl;
                                    }));
	W<window::Button*>(String(_("3")),
                           String(_("NONE")),
                           String(_("3")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("4")),
                           String(_("NONE")),
                           String(_("4")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(String(_("5")),
                           String(_("NONE")),
                           String(_("5")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(String(_("6")),
                           String(_("NONE")),
                           String(_("6")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("7")),
                           String(_("NONE")),
                           String(_("7")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(String(_("8")),
                           String(_("NONE")),
                           String(_("8")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(String(_("9")),
                           String(_("NONE")),
                           String(_("9")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("0")),
                           String(_("NONE")),
                           String(_("0")))->
	    create(frame->wx(), W<window::Size>(60, 45), sizer);
	W<window::Button*>(String(_("ENTER_BTN")),
                           String(_("NONE")),
                           String(_("enter")))->
	    create(frame->wx(), W<window::Size>(120, 45), sizer,
		   1, window::EXPAND);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	W<window::Button*>(String(_("DELL_BTN")),
                           String(_("NONE")),
                           String(_("DEL")))->
	    create(frame->wx(), W<window::Size>(80, 45), sizer);
	W<window::Button*>(String(_("FIND_BTN")),
                           String(_("NONE")),
                           String(_("поиск")))->
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
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (state == MAIN)
                                           event.Enable(true);
                                       else
                                           event.Enable(false);
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
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (state == MAIN)
                                           event.Enable(true);
                                       else
                                           event.Enable(false);
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
                    }))->
            bind<window::IDLE>(std::function<void(window::UpdateUIEvent&)>(
                                   [](window::UpdateUIEvent& event) {
                                       if (state == MAIN) {
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
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("W")),
                           String(_("KEY")),
                           String(_("ц")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("E")),
                           String(_("KEY")),
                           String(_("у")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("R")),
                           String(_("KEY")),
                           String(_("к")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("T")),
                           String(_("KEY")),
                           String(_("е")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("Y")),
                           String(_("KEY")),
                           String(_("н")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("U")),
                           String(_("KEY")),
                           String(_("г")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("I")),
                           String(_("KEY")),
                           String(_("ш")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("O")),
                           String(_("KEY")),
                           String(_("щ")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("P")),
                           String(_("KEY")),
                           String(_("з")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("[")),
                           String(_("KEY")),
                           String(_("х")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(String(_("A")),
                           String(_("KEY")),
                           String(_("ф")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("S")),
                           String(_("KEY")),
                           String(_("ы")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("D")),
                           String(_("KEY")),
                           String(_("в")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("F")),
                           String(_("KEY")),
                           String(_("а")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("G")),
                           String(_("KEY")),
                           String(_("п")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("H")),
                           String(_("KEY")),
                           String(_("р")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("J")),
                           String(_("KEY")),
                           String(_("о")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("K")),
                           String(_("KEY")),
                           String(_("л")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("L")),
                           String(_("KEY")),
                           String(_("д")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_(";")),
                           String(_("KEY")),
                           String(_("ж")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("'")),
                           String(_("KEY")),
                           String(_("э")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        W<window::Button*>(String(_("Z")),
                           String(_("KEY")),
                           String(_("я")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("X")),
                           String(_("KEY")),
                           String(_("ч")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("C")),
                           String(_("KEY")),
                           String(_("с")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("V")),
                           String(_("KEY")),
                           String(_("м")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("B")),
                           String(_("KEY")),
                           String(_("и")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("N")),
                           String(_("KEY")),
                           String(_("т")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_("M")),
                           String(_("KEY")),
                           String(_("ь")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_(",")),
                           String(_("KEY")),
                           String(_("б")))->
            create(frame->wx(), W<window::Size>(50, 30), sizer, 1);
        W<window::Button*>(String(_(".")),
                           String(_("KEY")),
                           String(_("ю")))->
            create(frame->wx(), W<window::Size>(150, 30), sizer, 0);
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
        sizer->Add(W<window::Sizer*>(_("CONTENT")), 0, window::EXPAND);
        sizer->Add(W<window::Sizer*>(_("KEYBOARD")), 1, window::EXPAND);
    }(W<window::Sizer*>(_("TOP")));

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
                    }));
    }(W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(W<window::Sizer*>(_("ENT.FIND_TEXT")), 0, window::EXPAND);
        sizer->Hide(W<window::Sizer*>(_("ENT.FIND_TEXT")));

	W<window::ListBox*>(String(_("ENT.LIST")),
                            String(_("NONE")),
                            std::vector<String> {_("hello"), _("how")})->
	    create(frame->wx(), W<window::Size>(550, 0), sizer,
		   1, window::EXPAND);
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
            create(frame->wx(), W<window::Size>(180, 30), sizer);
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
            create(frame->wx(), W<window::Size>(180, 30), sizer);
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
            create(frame->wx(), W<window::Size>(180, 30), sizer);
        W<window::ListBox*>(String(_("PAY.LIST")),
                            String(_("NONE")),
                            std::vector<String> {_("hello"), _("how")})->
	    create(frame->wx(), W<window::Size>(), sizer,
		   1, window::EXPAND);
    }(W<window::Sizer*>(window::VERTICAL));    
}

bool data_thing::init() {
    D<data::XML*>(String(_("db")), String::FromUTF8(DATADIR) + String(_("/db.xml")));
    D<data::XML*>(_("db"))->insert<data::TOP>(std::map<String, String>{
            {_("nominal"), _("fred")},
            {_("price"), _("122.2")}
        });
    D<data::XML*>(_("db"))->
        insert<data::CHILD>(std::map<String, String>{{_("nominal"), _("fred")}},
                            std::map<String, String>{
                                {_("amount"), _("255")},
                                {_("when"), _("19292912")}
                            });
    return true;
}


int main(int argc, char** argv) {
    D<data::RUN>(std::function<bool(void)>(data_thing::init), argc, argv);
    W<window::RUN>(std::function<bool(void)>(window_thing::init), argc, argv);
}


