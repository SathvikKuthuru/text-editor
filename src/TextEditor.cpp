#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor() : font(nullptr), renderer(nullptr), textColor{255, 255, 255, 255}, inputText("Type here...") {}

TextEditor::~TextEditor() {
    if (font) {
        TTF_CloseFont(font);
    }
}

bool TextEditor::initialize(SDL_Renderer* renderer) {
    this->renderer = renderer;
    font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24); // Adjust font path as needed
    if (!font) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void TextEditor::handleEvent(const SDL_Event& event) {
    if (event.type == SDL_TEXTINPUT) {
        inputText += event.text.text;
    } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
        inputText.pop_back();
    }
}

void TextEditor::render() {
    // Render text
    if (!inputText.empty()) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
        if (textSurface) {
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = {50, 50, textSurface->w, textSurface->h};
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        } else {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        }
    }

    // Draw cursor
    int cursorX = 50 + (inputText.empty() ? 0 : TTF_RenderText_Solid(font, inputText.c_str(), textColor)->w);
    SDL_Rect cursorRect = {cursorX, 55, 2, 20}; // Adjust the height and width of the cursor as needed
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for the cursor
    SDL_RenderFillRect(renderer, &cursorRect);
}

