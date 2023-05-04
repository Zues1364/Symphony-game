#include "FallingRhythm.h"

FallingRhythm::FallingRhythm(Uint64 _startTime)
: startTime(_startTime)
{
    srcRect = {0,0,226,230};
    int note = rand()%4;
    switch(note)
    {
    case 0:
        RhythmTexture = TextureManager::LoadTexture("images/LeftArrowNor.png");
        destRect = {489, -230, 226, 230};
        key = 0;
        break;
    case 1:
        RhythmTexture = TextureManager::LoadTexture("images/DownArrowNor.png");
        destRect = {941, -230, 226, 230};
        key = 1;
        break;
    case 2:
        RhythmTexture = TextureManager::LoadTexture("images/UpArrowNor.png");
        destRect = {1393, -230, 226, 230};
        key =2;
        break;
    case 3:
        RhythmTexture = TextureManager::LoadTexture("images/RightArrowNor.png");
        destRect = {1845, -230, 226, 230};
        key = 3;
        break;
    }

    x = destRect.x;
    y = destRect.y;
    width = destRect.w;
    height = destRect.h;

}

FallingRhythm::~FallingRhythm()
{
    //SDL_DestroyTexture(RhythmTexture);
    RhythmTexture = NULL;
}

void FallingRhythm::Update(Uint64 songTime, float speed)
{
    if(!active) return;
    switch(Symphony::event.key.keysym.sym)
    {
    case SDLK_UP:
        if(key == 2)
        {
            if(destRect.y >= 975 && destRect.y < 985)  {active = false; Symphony::beatmap->AddScore(5);}
            if(destRect.y >= 985 && destRect.y < 1150)  {active = false; Symphony::beatmap->AddScore(10);}
            if(destRect.y >= 1150 && destRect.y < 1330)  {active = false; Symphony::beatmap->AddScore(5);}
        }
        break;
    case SDLK_DOWN:
        if(key == 1)
        {
            if(destRect.y >= 975 && destRect.y < 985)  {active = false; Symphony::beatmap->AddScore(5);}
            if(destRect.y >= 985 && destRect.y < 1150)  {active = false; Symphony::beatmap->AddScore(10);}
            if(destRect.y >= 1150 && destRect.y < 1330)  {active = false; Symphony::beatmap->AddScore(5);}
        }
        break;
    case SDLK_LEFT:
        if(key == 0)
        {
            if(destRect.y >= 975 && destRect.y < 985)  {active = false; Symphony::beatmap->AddScore(5);}
            if(destRect.y >= 985 && destRect.y < 1150)  {active = false; Symphony::beatmap->AddScore(10);}
            if(destRect.y >= 1150 && destRect.y < 1330)  {active = false; Symphony::beatmap->AddScore(5);}
        }
        break;
    case SDLK_RIGHT:
        if(key == 3)
        {
            if(destRect.y >= 975 && destRect.y < 985)  {active = false; Symphony::beatmap->AddScore(5);}
            if(destRect.y >= 985 && destRect.y < 1150)  {active = false; Symphony::beatmap->AddScore(10);}
            if(destRect.y >= 1150 && destRect.y < 1330)  {active = false; Symphony::beatmap->AddScore(5);}
        }
        break;
    }
    destRect.y = static_cast<int>((songTime - startTime)*speed);
    if(destRect.y >= 1440) active = false;

}
void FallingRhythm::Render()
{
    if(!active) return;
    SDL_RenderCopy(Symphony::gRenderer, RhythmTexture, &srcRect, &destRect);
}
