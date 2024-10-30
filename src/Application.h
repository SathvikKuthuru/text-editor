#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Window.h"
#include "Renderer.h"
#include "TextEditor.h"

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    bool initialize();
    void handleEvents();
    void render();

    bool isRunning;
    Window window;
    Renderer renderer;
    TextEditor editor;
};
