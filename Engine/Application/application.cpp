#include "application.h"
#include "Core/Logger/logger.h"
#include "Core/Logger/consoleSink.h"

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
        Logger::Get().AddSink(std::make_shared<ConsoleSink>());
        Logger::Get().Log(LogLevel::Info, "Renderer", "Initialized OpenGL context");

        m_Window->OnUpdate();
    //    while (m_Running) {
            // Game loop logic goes here
            // Process events, update, render, etc.
           // m_Running = false; // for now, exit after one frame
    //    }
    }
}
