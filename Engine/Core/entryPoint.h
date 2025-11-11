#pragma once

#include "../Application/Application.h"

// ---- Entry Point ---- //
#ifdef RE_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
    Rengine::Application* app = Rengine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
#endif