#include "application.h"

namespace Rengine 
{

    Application::Application() {
        std::cout << "Engine Application Created!\n";
        m_Window = std::unique_ptr<RengineWindow::WindowManager>(RengineWindow::WindowManager::Create());
    }

    Application::~Application() {
        std::cout << "Engine Application Destroyed!\n";
    }

    void Application::Run() {
        std::cout << "Welcome to Rengine! \n";
        std::cout << "Running Engine Loop...\n";

        m_Window->OnUpdate();
    //    while (m_Running) {
            // Game loop logic goes here
            // Process events, update, render, etc.
           // m_Running = false; // for now, exit after one frame
    //    }
    }
}
