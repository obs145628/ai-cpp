#pragma once

#include "sf-window.hh"

class SfApp : public SfWindow
{

public:

    static SfApp& instance();

    SfApp(const SfApp&) = delete;
    SfApp(SfApp&&) = delete;
    SfApp& operator=(const SfApp&) = delete;
    SfApp& operator=(SfApp&&) = delete;

private:

    SfApp();




};
