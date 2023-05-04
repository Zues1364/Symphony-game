#include "Symphony.h"

#include "NoteBar.h"
#include "FallingRhythm.h"
#include "Beatmap.h"

SDL_Renderer* Symphony::gRenderer = nullptr;
SDL_Event Symphony::event;

Uint64 nextTimeSpawn = 0;
int spawnSpeed = 4000;

FallingRhythm* note;
Beatmap* Symphony::beatmap;
SDL_Texture *menu1,*menu2;
SDL_Texture *song1,*song2;
SDL_Texture* background = nullptr;

Symphony::Symphony()
{

}

Symphony::~Symphony()
{
    Clear();
}

void Symphony::Initialize()
{
    gWindow = SDL_CreateWindow("Symphony", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr)
    {
        std::cerr << "Can not initialize SDL! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == nullptr)
    {
        std::cerr << "Can not create renderer! SDL_Error: " << SDL_GetError() << std::endl;
        return ;
    }

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialize PNG loading
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return;
    }

     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    if( TTF_Init() == -1 )
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }
    menu1= TextureManager::LoadTexture("images/HoldOnStart.png");
    menu2= TextureManager::LoadTexture("images/HoldOnExit.png");
    song1= TextureManager::LoadTexture("images/pressingpentakill.png");
    song2= TextureManager::LoadTexture("images/pressingcupid.png");
    srand(time(0));
    noteBar = new NoteBar();

    running = true;
}

void Symphony::HandleEvent()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    }
    noteBar->HandleEvent();
    beatmap->HandleEvent();
}

void Symphony::Update()
{
    noteBar->Update();
    beatmap->Update();
}

void Symphony::Render()
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, background, NULL, NULL);
    noteBar->Render();
    beatmap->Render();

    SDL_RenderPresent(gRenderer);
}

bool Symphony::isRunning()
{
    return running;
}

void Symphony::Clear()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = nullptr;
    gWindow = nullptr;

    delete noteBar;
    delete beatmap;
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

void Symphony::StartMenu(){
    printMenu=true;
     // Start = 0 && Exit = 1;
    while(printMenu==true){
        if(StartOrExit == 0) SDL_RenderCopy(gRenderer,menu1,NULL,NULL);
        else SDL_RenderCopy(gRenderer,menu2,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        SDL_Event e;
        SDL_PollEvent(&e);
        switch(e.type){
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                    case SDLK_RETURN:
                        if(StartOrExit == 0)
                           {
                            printMenu=false;
                            choose_song = true;
                            }
                        else{
                            choose_song = false;
                            running=false;
                            printMenu=false;
                        }
                        break;
                    case SDLK_DOWN:
                        StartOrExit = 1;
                        break;
                    case SDLK_UP:
                        StartOrExit = 0;
                        break;
                }
            break;
            case SDL_QUIT:
                running=false;
                printMenu=false;
                break;
            }
    }

}

void Symphony::Choose_song()
{
    while(choose_song==true)
    {
        if(PentakillOrCupid == 0) SDL_RenderCopy(gRenderer,song1,NULL,NULL);
        else SDL_RenderCopy(gRenderer,song2,NULL,NULL);
        SDL_RenderPresent(gRenderer);
        SDL_Event e;
        SDL_PollEvent(&e);
        switch(e.type){
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                    case SDLK_RETURN:
                        if(PentakillOrCupid == 0)
                           {
                            choose_song=false;
                            running = true;
                            beatmap = new Beatmap(100, 0.2,"music/pentakill.mp3", "Pentakill");
                            background = TextureManager::LoadTexture("images/pentakill.png");
                            }
                        else{
                            choose_song=false;
                            running = true;
                            beatmap = new Beatmap(100, 0.2,"music/cupid.mp3", "Cupid");
                            background = TextureManager::LoadTexture("images/cupid.png");
                        }
                        break;
                    case SDLK_DOWN:
                        PentakillOrCupid = 1;
                        break;
                    case SDLK_UP:
                        PentakillOrCupid = 0;
                        break;
                }
            break;
            case SDL_QUIT:
                running=false;
                break;
            }
        }
    Symphony::beatmap->Play();
}
