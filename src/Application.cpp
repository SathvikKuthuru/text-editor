#include "Application.h"
#include <iostream>

Application::Application() : isRunning(false) {}

Application::~Application() {
    SDL_Quit();
    TTF_Quit();
}

bool Application::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }
    if (!window.create("Text Editor", 800, 600) || !renderer.create(window.getSDLWindow())) {
        return false;
    }
    if (!editor.initialize(renderer.getSDLRenderer())) {
        return false;
    }
    isRunning = true;
    return true;
}

void Application::run() {
    if (!initialize()) return;
    SDL_StartTextInput();

    while (isRunning) {
        handleEvents();
        render();
    }

    SDL_StopTextInput();
}

void Application::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        editor.handleEvent(event);
    }
}

void Application::render() {
    renderer.clear();
    editor.render();
    renderer.present();
}
