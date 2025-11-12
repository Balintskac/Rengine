#include "windowsWindow.h"

RengineWindow::WindowManager*  RengineWindow::WindowManager::Create(const WindowProps& props) {
    return new WindowsWindow(props);
}

void RengineWindow::WindowsWindow::setCallBacks()
{
    g_dispatcher.addListener<KeyboardEvent>([](auto&& e) {
        std::cout << "Keyboard: key=" << e.keyCode << ", action=" << e.isPressed << "\n";
        });

    g_dispatcher.addListener<MouseEvent>([](const MouseEvent& e) {
        std::cout << e.x << " " << e.y << " Mouse: button=" << e.button << ", action=" << e.mods << "\n";
        });

    glfwSetWindowUserPointer(m_Window, &g_dispatcher);

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        EventDispacther* dispatcher = static_cast<EventDispacther*>(glfwGetWindowUserPointer(window));
        
        KeyboardEvent e{ key, true };
        dispatcher->trigger(e);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        EventDispacther* dispatcher = static_cast<EventDispacther*>(glfwGetWindowUserPointer(window));
        
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        MouseEvent e{ xpos, ypos, button, action };
        dispatcher->trigger(e);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
       EventDispacther* dispatcher = static_cast<EventDispacther*>(glfwGetWindowUserPointer(window));

        MouseEvent e{ xpos, ypos, 1, 1 };
        dispatcher->trigger(e);
    });

    
}
