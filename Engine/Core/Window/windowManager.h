#pragma once
#include <string>
#include <functional>

namespace RengineWindow 
{
    struct WindowProps {
        std::string_view Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Rengine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class WindowManager {
    public:
        using EventCallbackFn = std::function<void()>; // later replaced with Event system

        virtual ~WindowManager() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static WindowManager* Create(const WindowProps& props = WindowProps());
    };
}
