#pragma once
#include <iostream>
#include <memory>

#include "Core/Window/windowManager.h"

namespace Rengine {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        bool m_Running = true;
        std::unique_ptr<RengineWindow::WindowManager> m_Window;
    };

        // To be defined in Sandbox
    Application* CreateApplication();
}
