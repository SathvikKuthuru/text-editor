#include "TextEditor.h"
#include <iostream>
#include <sstream>

TextEditor::TextEditor() : font(nullptr), renderer(nullptr), textColor{255, 255, 255, 255}, inputText("Type here..."),
cursorVisible(true), cursorBlinkTimer(0) {}

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
    } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
            inputText.pop_back();
        } else if (event.key.keysym.sym == SDLK_RETURN) {
            inputText += "\n";  // Add a new line on Enter
        }
    }

    // Keep the cursor visible
    if(event.type == SDL_KEYDOWN || event.type == SDL_TEXTINPUT) {
        cursorBlinkTimer = SDL_GetTicks();
        cursorVisible = true;
    }
}


void TextEditor::renderCursor() {
    // Handles Blinking
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - cursorBlinkTimer > cursorBlinkInterval) {
        cursorVisible = !cursorVisible;
        cursorBlinkTimer = currentTime;
    }

    if(cursorVisible) {
        int cursorX, cursorY;
        if(inputText.empty()) {
            cursorX = 50;
            cursorY = 55;
        } else {
            std::istringstream iss(inputText);
            std::string line;

            cursorX = 50;
            cursorY = 27;

            // Move to the last line
            while (std::getline(iss, line)) {
                cursorY += TTF_FontHeight(font); // Move cursorY to the last line height
            }
            // Check for new line at the end
            if(inputText.back() == '\n') {
                cursorY += TTF_FontHeight(font);
            }
            // Calculate cursor position at the end of the last line
            if (!line.empty()) {
                cursorX += TTF_RenderText_Solid(font, line.c_str(), textColor)->w;
            }
        }


        SDL_Rect cursorRect = {cursorX, cursorY, 2, 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &cursorRect);
    }
}


void TextEditor::renderText() {
    if (!inputText.empty()) {
        std::istringstream iss(inputText);
        std::string line;
        int lineY = 50;

        // Render each line
        while (std::getline(iss, line)) {
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, line.c_str(), textColor);
            if (textSurface) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_Rect textRect = {50, lineY, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
                
                // Move Y position down for the next line
                lineY += textSurface->h;
            } else {
                std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
            }
        }
    }
}

void TextEditor::render() {
    renderText();
    renderCursor();
}

