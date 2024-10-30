#include "Window.h"
#include <iostream>

Window::Window() : sdlWindow(nullptr) {}

Window::~Window() {
    if (sdlWindow) {
        SDL_DestroyWindow(sdlWindow);
    }
}

bool Window::create(const char* title, int width, int height) {
    sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!sdlWindow) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Window* Window::getSDLWindow() const {
    return sdlWindow;
}
