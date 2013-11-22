#include "widget.h"

DECLARE_APP(wxShylockApp)
IMPLEMENT_APP_NO_MAIN(wxShylockApp);

std::function<bool(void)> wxShylockApp::init;

void wxShylockApp::run(const std::function<bool(void)>& callback, int argc, char** argv) {
    init = callback;
    wxEntry(argc, argv);
}

bool wxShylockApp::OnInit() {
    return init();
}
