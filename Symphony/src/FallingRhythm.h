#pragma once
#ifndef FallingRhythm_h
#define FallingRhythm_h

#include <SDL.h>
#include "TextureManager.h"
#include "Symphony.h"
#include "Beatmap.h"

enum NOTE_KEY
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class FallingRhythm
{
public:
    FallingRhythm(Uint64 _startTime);
    ~FallingRhythm();
    void Update(Uint64 songTime, float speed);
    void Render();
    bool active = true;
private:
    Uint64 startTime;
    int x,y;
    int width, height;
    SDL_Texture *RhythmTexture;
    SDL_Rect srcRect, destRect;
    int key;
};

#endif // FallingRhythm_h


