#pragma once

namespace Rengine {

    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        bool m_Running = true;
    };

        // To be defined in Sandbox
    Application* CreateApplication();
}
