#include "rengine.h"
#include <iostream>

class SandboxApp : public Rengine::Application {
public:
    SandboxApp() {
        std::cout << "SandboxApp Created!\n";
    }
    ~SandboxApp() override {
        std::cout << "SandboxApp Destroyed!\n";
    }
};

Rengine::Application* Rengine::CreateApplication() {
    return new SandboxApp();
}