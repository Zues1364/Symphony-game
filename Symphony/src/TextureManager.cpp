#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(std::string path)
{
    SDL_Surface* loadedSurface = nullptr;
    loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr)
    {
        std::cerr << "Can not load image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return nullptr;
    }

    SDL_Texture* loadedTexture = nullptr;
    loadedTexture = SDL_CreateTextureFromSurface(Symphony::gRenderer, loadedSurface);
    if(loadedTexture == nullptr)
    {
        std::cerr << "Can not create texture from surface! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        loadedSurface = nullptr;
        SDL_DestroyTexture(loadedTexture);
        return nullptr;
    }
    return loadedTexture;
}
