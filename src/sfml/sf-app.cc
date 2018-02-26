#include "sfml/sf-app.hh"

SfApp& SfApp::instance()
{
    static SfApp instance;
    return instance;
}

SfApp::SfApp()
        : SfWindow()
{}
