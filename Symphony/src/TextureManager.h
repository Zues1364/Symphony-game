#pragma once
#ifndef TextureManager_h
#define TextureManager_h

#include <string>

#include <SDL_image.h>

#include "Symphony.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(std::string path);
};

#endif // TextureManager_h
