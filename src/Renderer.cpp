#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : sdlRenderer(nullptr) {}

Renderer::~Renderer() {
    if (sdlRenderer) {
        SDL_DestroyRenderer(sdlRenderer);
    }
}

bool Renderer::create(SDL_Window* window) {
    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!sdlRenderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Renderer* Renderer::getSDLRenderer() const {
    return sdlRenderer;
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(sdlRenderer, 173, 216, 230, 255);
    SDL_RenderClear(sdlRenderer);
}

void Renderer::present() {
    SDL_RenderPresent(sdlRenderer);
}
