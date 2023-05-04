#pragma once
#ifndef Label_h
#define Label_h

#include "Symphony.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Label
{
public:
    Label() {}
    Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor, Uint32 wrapLength);
    ~Label();
    SDL_Texture* LoadText(TTF_Font* font,const char* text, SDL_Color textColor, Uint32 wrapLength);
    void Render();
    void Reset();
    int getWidth();
    int getHeight();
private:
    bool inside = false;
    int Width, Height;
    SDL_Rect srcRect, destRect;
    SDL_Texture* text;
    TTF_Font* font;
};

#endif // Label_h
