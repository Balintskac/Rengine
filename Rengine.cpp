#include "engine.h"

Engine* Engine::instance = nullptr;
#define engine Engine::get()

int main() {
	engine.createcontext();
	engine.renderLoop();
	engine.destruct();
	return 0;
}