#include "src/Symphony.h"

int main(int argc, char* argv[])
{
    Symphony* symphony = new Symphony();
    symphony->Initialize();
    symphony->StartMenu();
    symphony->Choose_song();

    Uint64 frameStart;
    int frameTime;
    int frameDelay = 1000/30;
    while(symphony->isRunning())
    {
        frameStart = SDL_GetTicks64();
        symphony->HandleEvent();
        symphony->Update();
        symphony->Render();
        //frameTime = SDL_GetTicks64() - frameStart;
        //if(frameDelay > frameTime)
        //{
        //    SDL_Delay(frameDelay - frameTime);
        //}
    }

    symphony->Clear();
    delete symphony;
    return 0;
}
