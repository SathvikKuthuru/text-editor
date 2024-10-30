#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextEditor {
public:
    TextEditor();
    ~TextEditor();
    bool initialize(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event);
    void renderCursor();
    void renderText();
    void render();

private:
    std::string inputText;
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Renderer* renderer;
    bool cursorVisible;
    Uint32 cursorBlinkTimer;
    const Uint32 cursorBlinkInterval = 500;
};
