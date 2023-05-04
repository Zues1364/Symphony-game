#include "NoteBar.h"

NoteBar::NoteBar()
{
    NoteTexture = TextureManager::LoadTexture("images/ArrowTexture.png");
    for(int i = 0; i < 3; i++) srcUp[i] = {0,i*230, 226,230};
    for(int i = 0; i < 3; i++) srcRight[i] = {226, i*230, 226,230};
    for(int i = 0; i < 3; i++) srcLeft[i] = {452,i*230, 226,230};
    for(int i = 0; i < 3; i++) srcDown[i] = {678,i*230, 226,230};
    currentUp = srcUp[0];
    currentDown = srcDown[0];
    currentLeft = srcLeft[0];
    currentRight = srcRight[0];
}

NoteBar::~NoteBar()
{

}

void NoteBar::HandleEvent()
{
    if(Symphony::event.type == SDL_KEYDOWN)
    {
        switch(Symphony::event.key.keysym.sym)
        {
        case SDLK_UP:
            currentUp = srcUp[1];
            break;
        case SDLK_DOWN:
            currentDown = srcDown[1];
            break;
        case SDLK_LEFT:
            currentLeft = srcLeft[1];
            break;
        case SDLK_RIGHT:
            currentRight = srcRight[1];
            break;
        }
    }

    if(Symphony::event.type == SDL_KEYUP)
    {
        switch(Symphony::event.key.keysym.sym)
        {
        case SDLK_UP:
            currentUp = srcUp[0];
            break;
        case SDLK_DOWN:
            currentDown = srcDown[0];
            break;
        case SDLK_LEFT:
            currentLeft = srcLeft[0];
            break;
        case SDLK_RIGHT:
            currentRight = srcRight[0];
            break;
        }
    }
}

void NoteBar::Update()
{
    destLeft = {489,1100,226,230};
    destDown = {941,1100,226,230};
    destUp = {1393,1100,226,230};
    destRight = {1845,1100,226,230};
}

void NoteBar::Render()
{
    SDL_RenderCopy(Symphony::gRenderer, NoteTexture, &currentLeft, &destLeft);
    SDL_RenderCopy(Symphony::gRenderer, NoteTexture, &currentDown, &destDown);
    SDL_RenderCopy(Symphony::gRenderer, NoteTexture, &currentUp, &destUp);
    SDL_RenderCopy(Symphony::gRenderer, NoteTexture, &currentRight, &destRight);
}
