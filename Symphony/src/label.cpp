#include "Label.h"

Label::Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor, Uint32 wrapLength)
:  text(NULL)
{
    font = TTF_OpenFont(fontFile, fontSize);
    if(textContent != NULL)
    {
        text = LoadText(font, textContent, textColor, wrapLength);
        SDL_QueryTexture(text, NULL, NULL, &Width, &Height);
    }else {Width = 0; Height = 0;}
    srcRect.x = srcRect.y = 0;
    destRect.x = x;
    destRect.y = y;

    srcRect.w = destRect.w = Width;
    srcRect.h = destRect.h = Height;
}

Label::~Label()
{
    Reset();
}


void Label::Render()
{
    if(text == NULL) return;
    SDL_RenderCopy(Symphony::gRenderer, text, &srcRect, &destRect);
}

void Label::Reset()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);
    font = NULL;
    text = NULL;
}

int Label::getWidth()
{
    return Width;
}

int Label::getHeight()
{
    return Height;
}

SDL_Texture* Label::LoadText(TTF_Font* font,const char* text, SDL_Color textColor, Uint32 wrapLength)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = TTF_RenderText_Blended_Wrapped(font, text, textColor, wrapLength);
    if(tempSurface == NULL)
    {
        std::cout << "Unable to load text! TTF_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* Texture = NULL;
    Texture = SDL_CreateTextureFromSurface(Symphony::gRenderer, tempSurface);
    if(Texture == NULL)
    {
        std::cout << "Unable to create text from surface! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(tempSurface);
    return Texture;
}
