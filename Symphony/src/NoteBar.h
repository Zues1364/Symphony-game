#pragma once
#ifndef NoteBar_h
#define NoteBar_h

#include "Symphony.h"
#include "TextureManager.h"

class NoteBar
{
public:
    NoteBar();
    ~NoteBar();

    void HandleEvent();
    void Update();
    void Render();

    SDL_Rect srcLeft[3], destLeft;
    SDL_Rect srcRight[3], destRight;
    SDL_Rect srcDown[3], destDown;
    SDL_Rect srcUp[3], destUp;

    SDL_Rect currentLeft, currentRight, currentDown, currentUp;

private:
    SDL_Texture *NoteTexture;

};

#endif // NoteBar_h
