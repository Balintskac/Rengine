#include "windowsWindow.h"

RengineWindow::WindowManager*  RengineWindow::WindowManager::Create(const WindowProps& props) {
    return new WindowsWindow(props);
}