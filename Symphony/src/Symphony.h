#ifndef Symphony_h
#define Symphony_h

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "TextureManager.h"
#include "Settings.h"

class Beatmap;
class NoteBar;

class Symphony
{
public:
    Symphony();
    ~Symphony();
    void Initialize();
    bool isRunning();
    void HandleEvent();
    void Update();
    void Render();
    void Clear();
    void StartMenu();
    void Choose_song();
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static Beatmap* beatmap;
private:
    bool running;
    bool printMenu= true;
    bool choose_song = true;
    int StartOrExit = 0;
    int PentakillOrCupid = 0;
    SDL_Window* gWindow;
    NoteBar* noteBar;
};

#endif // Symphony_h
