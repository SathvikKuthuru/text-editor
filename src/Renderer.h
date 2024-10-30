#pragma once
#include <SDL2/SDL.h>

class Renderer {
public:
    Renderer();
    ~Renderer();
    bool create(SDL_Window* window);
    SDL_Renderer* getSDLRenderer() const;
    void clear();
    void present();

private:
    SDL_Renderer* sdlRenderer;
};
