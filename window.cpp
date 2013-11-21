#include "window.h"
#include "wxShylockWidget/widget.h"


std::list<window::Window*> window::Window::all_of_them;

window::Window::Window(const engine::String& id_value, 
		       const engine::String& category_value) : 
      id(id_value), category(category_value), win(nullptr) {
    all_of_them.push_back(this);
}

window::Window* window::Window::create(wxWindow* parent_value, const window::Size& size_value,
				       window::Sizer* sizer_value, 
				       int proportion, int flag, 
				       int border) {
    wxASSERT_MSG(win, _("win ptr is zero"));
    sizer_value->Add(win, proportion, flag, border);
    sizer = sizer_value;
    return this;
}

window::Window* window::Window::show() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Show(true);
    return this;
}
 
window::Window* window::Window::hide() {
    wxASSERT_MSG(win, _("win ptr is zero"));
    win->Show(false);
    return this;
}

wxWindow* window::Window::wx() {
    wxASSERT_MSG(win, _("probably wrong. win is zero"));
    return win;
}

window::Frame::Frame(const engine::String& id_value, const engine::String& category_value,
                     const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }

window::Frame* window::Frame::create(wxWindow* parent_value, const window::Size& size_value, 
                                     window::Sizer* sizer_value,
                                     int proportion, int flag, int border) {
    wxASSERT_MSG(parent_value == nullptr, _("frame is top level window"));

    win = new wxShylockFrame(text);
    sizer = sizer_value;

    return this;
}

window::Frame* window::Frame::fit() {
    wxASSERT_MSG(win != nullptr, _("frame is null"));
    wxASSERT_MSG(sizer != nullptr, _("sizer is null"));
    win->SetSizerAndFit(sizer);
    return this;
}

window::None* window::None::create(wxWindow* parent_value, const window::Size& size_value, 
                                   window::Sizer* sizer_value,
                                   int proportion, int flag, int border) {
    wxASSERT_MSG(parent_value != nullptr, _("None create on null parent"));    
    win = new wxWindow(parent_value, wxID_ANY, wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

window::Label::Label(const engine::String& id_value,
		     const engine::String& category_value,
		     const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }


window::Label* window::Label::create(wxWindow* parent_value, 
                                     const window::Size& size_value, 
                                     window::Sizer* sizer_value,
				     int proportion, int flag, 
				     int border) {
    wxASSERT_MSG(parent_value != nullptr, _("label create on null parent"));    
    win = new wxStaticText(parent_value, wxID_ANY, text, wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

window::Button::Button(const engine::String& id_value,
		       const engine::String& category_value,
		       const engine::String& text_value) : 
      Window(id_value, category_value), text(text_value) { }

window::Button* window::Button::create(wxWindow* parent_value, const window::Size& size_value, 
				       window::Sizer* sizer_value, int proportion, int flag, 
				       int border) {
    wxASSERT_MSG(parent_value != nullptr, _("button create on null parent"));    
    win = new wxShylockButton(parent_value, wxID_ANY, text, 
			      wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}

template <>
window::Button* window::Button::bind<window::CLICK>(const std::function<void()>& callback) {
    wxASSERT_MSG(win, _("call bind<>() only after create()"));    
    static_cast<wxShylockButton*>(win)->add_click_callback(callback);
    return this;
}



window::ListBox::ListBox(const engine::String& id_value, const engine::String& category_value,
			 std::vector<engine::String>& entries_value) : 
      Window(id_value, category_value), entries(entries_value) { }

window::ListBox* window::ListBox::create(wxWindow* parent_value, const window::Size& size_value, 
					 window::Sizer* sizer_value, int proportion, int flag, 
					 int border) {
    wxASSERT_MSG(parent_value != nullptr, _("listbox create on null parent"));    

    engine::String* values = new engine::String[entries.size()];
    std::copy(entries.begin(), entries.end(), values);

    win = new wxShylockListbox(parent_value, wxID_ANY, 
			       wxDefaultPosition, size_value, entries.size(), values);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);

    return this;
}

window::Text::Text(const engine::String& id_value,
                   const engine::String& category_value,
                   const engine::String& text_value) :
      Window(id_value, category_value), text(text_value) { }

window::Text* window::Text::create(wxWindow* parent_value, const window::Size& size_value, 
                                   window::Sizer* sizer_value, int proportion, int flag, 
                                   int border) {
    wxASSERT_MSG(parent_value != nullptr, _("text create on null parent"));
    win = new wxShylockText(parent_value, wxID_ANY, text, 
                            wxDefaultPosition, size_value);
    Window::create(parent_value, size_value, sizer_value, proportion, flag, border);
    return this;
}



// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Declare the application class
class MyApp : public wxApp
{
public:
    // Called on application startup
    virtual bool OnInit();
};

// Implements MyApp& GetApp()
DECLARE_APP(MyApp)

// Give wxWidgets the means to create a MyApp object
IMPLEMENT_APP(MyApp)

// Initialize the application
bool MyApp::OnInit()
{
    window::Frame* frame = window::W<window::Frame*>(engine::String(_("TOP")),
                                                     engine::String(_("NONE")),
                                                     engine::String(_("Shylock")))->
        create(nullptr, window::W<window::Size>(-1, -1), 
               window::W<window::Sizer*>(window::VERTICAL));
    
    //list
    [frame](window::Sizer* sizer) {
        window::W<window::Label*>(engine::String(_("ENT.FIND_LABEL")),
                                  engine::String(_("NONE")),
                                  engine::String(_("Фильтр")))->
            create(frame->wx(), window::W<window::Size>(60, -1), sizer, 0, window::ALIGN_CENTER);
        window::W<window::Text*>(engine::String(_("ENT.FIND_TEXT")),
                                 engine::String(_("NONE")),
                                 engine::String(_("")))->
            create(frame->wx(), window::W<window::Size>(225, 30), sizer, 1);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(window::W<window::Sizer*>(_("ENT.FIND_TEXT")), 0, window::EXPAND);
        sizer->Hide(window::W<window::Sizer*>(_("ENT.FIND_TEXT")));

	window::W<window::ListBox*>(engine::String(_("ENT.LIST")),
				    engine::String(_("NONE")),
				    std::vector<engine::String> {_("hello"), _("how")})->
	    create(frame->wx(), window::W<window::Size>(550, 0), sizer,
		   1, window::EXPAND);
    }(window::W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("1")),
				   engine::String(_("NONE")),
				   engine::String(_("1")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>([](){
		    std::cout << "1 is selected" << std::endl;
		});
	window::W<window::Button*>(engine::String(_("2")),
				  engine::String(_("NONE")),
				  engine::String(_("2")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer)->
	    bind<window::CLICK>([]() {
		    std::cout << "2 is selected" << std::endl;
		});
	window::W<window::Button*>(engine::String(_("3")),
				  engine::String(_("NONE")),
				  engine::String(_("3")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("4")),
				  engine::String(_("NONE")),
				  engine::String(_("4")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("5")),
				  engine::String(_("NONE")),
				  engine::String(_("5")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("6")),
				   engine::String(_("NONE")),
				   engine::String(_("6")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("7")),
				  engine::String(_("NONE")),
				  engine::String(_("7")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("8")),
				   engine::String(_("NONE")),
				   engine::String(_("8")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("9")),
				  engine::String(_("NONE")),
				  engine::String(_("9")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("0")),
				  engine::String(_("NONE")),
				  engine::String(_("0")))->
	    create(frame->wx(), window::W<window::Size>(60, 45), sizer);
	window::W<window::Button*>(engine::String(_("ENTER_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("enter")))->
	    create(frame->wx(), window::W<window::Size>(120, 45), sizer,
		   1, window::EXPAND);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("DELL_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("DEL")))->
	    create(frame->wx(), window::W<window::Size>(80, 45), sizer);
	window::W<window::Button*>(engine::String(_("FIND_BTN")),
				   engine::String(_("NONE")),
				   engine::String(_("поиск")))->
	    create(frame->wx(), window::W<window::Size>(100, 45), sizer)->
            bind<window::CLICK>([](){
                    static bool toggle = true;
                    if (toggle) {
                        window::W<window::Sizer*>(_("ENT.LIST"))->
                            Show(window::W<window::Sizer*>(_("ENT.FIND_LABEL")));
                    } else {
                        window::W<window::Sizer*>(_("ENT.LIST"))->
                            Hide(window::W<window::Sizer*>(_("ENT.FIND_LABEL")));
                    }
                    window::W<window::Sizer*>(_("ENT.LIST"))->Layout();
                    toggle = !toggle;
                });
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(window::W<window::Sizer*>(_("1")));
        sizer->Add(window::W<window::Sizer*>(_("4")));
        sizer->Add(window::W<window::Sizer*>(_("7")));
        sizer->Add(window::W<window::Sizer*>(_("0")));
        sizer->Add(window::W<window::Sizer*>(_("DELL_BTN")));
	window::W<window::Button*>(engine::String(_("BACK_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("Назад")))->
	    create(frame->wx(), window::W<window::Size>(180, 45), sizer);
    }(window::W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
	window::W<window::Button*>(engine::String(_("ADD_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("Добавить клиента")))->
	    create(frame->wx(), window::W<window::Size>(180, 67), sizer)->
            bind<window::CLICK>([]() {
                    static bool toggle = false;
                    if (toggle) {
                        window::W<window::Sizer*>(_("CONTENT"))->
                            Show(window::W<window::Sizer*>(_("ENT.LIST")));
                    } else {
                        window::W<window::Sizer*>(_("CONTENT"))->
                            Hide(window::W<window::Sizer*>(_("ENT.LIST")));
                    }
                    window::W<window::Sizer*>(_("CONTENT"))->Layout();
                    toggle = !toggle;
                });
	window::W<window::Button*>(engine::String(_("REMOVE_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("Удалить клиента")))->
	    create(frame->wx(), window::W<window::Size>(180, 67), sizer);
	window::W<window::Button*>(engine::String(_("PAY_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("Оплатить")))->
	    create(frame->wx(), window::W<window::Size>(180, 67), sizer);
	window::W<window::Button*>(engine::String(_("EDIT_BTN")),
				  engine::String(_("NONE")),
				  engine::String(_("Редактировать")))->
	    create(frame->wx(), window::W<window::Size>(180, 69), sizer);
    }(window::W<window::Sizer*>(window::VERTICAL));
    
    [frame](window::Sizer* sizer) {
        sizer->Add(window::W<window::Sizer*>(_("ENT.LIST")), 1, window::EXPAND);
        sizer->Add(window::W<window::Sizer*>(_("BACK_BTN")));
        sizer->Add(window::W<window::Sizer*>(_("EDIT_BTN")));
        window::W<window::None*>(engine::String(_("CONTENT")),
                                engine::String(_("NONE")))->
            create(frame->wx(), window::W<window::Size>(0, 0), sizer);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        window::W<window::Button*>(engine::String(_("Q")),
                                   engine::String(_("KEY")),
                                   engine::String(_("й")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("W")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ц")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("E")),
                                   engine::String(_("KEY")),
                                   engine::String(_("у")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("R")),
                                   engine::String(_("KEY")),
                                   engine::String(_("к")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("T")),
                                   engine::String(_("KEY")),
                                   engine::String(_("е")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("Y")),
                                   engine::String(_("KEY")),
                                   engine::String(_("н")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("U")),
                                   engine::String(_("KEY")),
                                   engine::String(_("г")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("I")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ш")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("O")),
                                   engine::String(_("KEY")),
                                   engine::String(_("щ")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("P")),
                                   engine::String(_("KEY")),
                                   engine::String(_("з")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("[")),
                                   engine::String(_("KEY")),
                                   engine::String(_("х")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        window::W<window::Button*>(engine::String(_("A")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ф")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("S")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ы")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("D")),
                                   engine::String(_("KEY")),
                                   engine::String(_("в")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("F")),
                                   engine::String(_("KEY")),
                                   engine::String(_("а")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("G")),
                                   engine::String(_("KEY")),
                                   engine::String(_("п")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("H")),
                                   engine::String(_("KEY")),
                                   engine::String(_("р")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("J")),
                                   engine::String(_("KEY")),
                                   engine::String(_("о")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("K")),
                                   engine::String(_("KEY")),
                                   engine::String(_("л")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("L")),
                                   engine::String(_("KEY")),
                                   engine::String(_("д")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_(";")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ж")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("'")),
                                   engine::String(_("KEY")),
                                   engine::String(_("э")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
        window::W<window::Button*>(engine::String(_("Z")),
                                   engine::String(_("KEY")),
                                   engine::String(_("я")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("X")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ч")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("C")),
                                   engine::String(_("KEY")),
                                   engine::String(_("с")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("V")),
                                   engine::String(_("KEY")),
                                   engine::String(_("м")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("B")),
                                   engine::String(_("KEY")),
                                   engine::String(_("и")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("N")),
                                   engine::String(_("KEY")),
                                   engine::String(_("т")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_("M")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ь")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_(",")),
                                   engine::String(_("KEY")),
                                   engine::String(_("б")))->
            create(frame->wx(), window::W<window::Size>(50, 30), sizer, 1);
        window::W<window::Button*>(engine::String(_(".")),
                                   engine::String(_("KEY")),
                                   engine::String(_("ю")))->
            create(frame->wx(), window::W<window::Size>(150, 30), sizer, 0);
    }(window::W<window::Sizer*>(window::HORIZONTAL));

    [frame](window::Sizer* sizer) {
    sizer->Add(window::W<window::Sizer*>(_("Q")), 0, window::EXPAND);
    sizer->Add(window::W<window::Sizer*>(_("A")), 0, window::EXPAND);
    sizer->Add(window::W<window::Sizer*>(_("Z")), 0, window::EXPAND);
    window::W<window::None*>(engine::String(_("KEYBOARD")),
                             engine::String(_("NONE")))->
        create(frame->wx(), window::W<window::Size>(0, 0), sizer);
    }(window::W<window::Sizer*>(window::VERTICAL));

    [frame](window::Sizer* sizer) {
        sizer->Add(window::W<window::Sizer*>(_("CONTENT")), 0, window::EXPAND);
        sizer->Add(window::W<window::Sizer*>(_("KEYBOARD")), 1, window::EXPAND);
    }(window::W<window::Sizer*>(_("TOP")));

    frame->fit();
    frame->show();

    // Start the event loop
    return true;
}

