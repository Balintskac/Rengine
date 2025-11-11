#include "Core/Window/windowManager.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


namespace RengineWindow {

    class WindowsWindow : public RengineWindow::WindowManager {
    public:
        WindowsWindow(const WindowProps& props) { Init(props); }
        virtual ~WindowsWindow() { Shutdown(); }

        void OnUpdate() override {
            // render loop
            while(!glfwWindowShouldClose(m_Window))
            {
                glClearColor(0.2f, 0.1f, 0.9f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                glfwPollEvents();
                glfwSwapBuffers(m_Window);
            }
        }

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn& callback) override {
            m_Data.EventCallback = callback;
        }

        void SetVSync(bool enabled) override {
            glfwSwapInterval(enabled ? 1 : 0);
            m_Data.VSync = enabled;
        }

        bool IsVSync() const override { return m_Data.VSync; }

    private:
        void Init(const WindowProps& props) {
            m_Data.Title = props.Title;
            m_Data.Width = props.Width;
            m_Data.Height = props.Height;

            if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW!\n";
                return;
            }

            m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.data(), nullptr, nullptr);
            if (!m_Window) {
                std::cerr << "Failed to create GLFW window!\n";
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(m_Window);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD!" << std::endl;
                return;
            }
            
            SetVSync(true);

            std::cout << "Created window: " << props.Title << " (" 
                      << props.Width << ", " << props.Height << ")\n";
        }

        void Shutdown() {
            glfwDestroyWindow(m_Window);
            glfwTerminate();
        }

    private:
        GLFWwindow* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}
