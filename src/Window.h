#pragma once
#include <SDL2/SDL.h>

class Window {
public:
    Window();
    ~Window();
    bool create(const char* title, int width, int height);
    SDL_Window* getSDLWindow() const;

private:
    SDL_Window* sdlWindow;
};
