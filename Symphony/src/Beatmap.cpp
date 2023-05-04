#include "Beatmap.h"

#include "FallingRhythm.h"
Beatmap::Beatmap(int _BPM, float _speed, std::string pathToMusic, std::string songName)
{
    BPM = _BPM;
    speed = _speed;
    music = Mix_LoadMUS(pathToMusic.c_str());
    ScoreText = new Label("font/Carlito-Italic.ttf", "Your score: 0", 40, 2500, 100, SDL_Color{255,255,255}, 300);
    if(!music)
    {
        std::cerr << "Can not load beat music! Mix_Error: " << Mix_GetError() << std::endl;
        return;
    }

    getTimeThread = SDL_CreateThread(&Beatmap::ThreadFunction,"Get Time Song", this);
    this->songName = songName;
}


Beatmap::~Beatmap()
{
    Mix_FreeMusic(music);
    music = NULL;
    beatFileInp.close();
    if(getTimeThread != nullptr)
    {
        SDL_WaitThread(getTimeThread, nullptr);
        getTimeThread = nullptr;
    }
    //beatFileOut.close();
}

void Beatmap::HandleEvent()
{
    return;
    songTime = Mix_GetMusicPosition(music)*1000.0;
    if(Symphony::event.type == SDL_KEYDOWN && Symphony::event.key.repeat == 0)
    {
        switch(Symphony::event.key.keysym.sym)
        {
        case SDLK_UP:
            beatFileOut << songTime << std::endl;
            break;
        case SDLK_DOWN:
            beatFileOut << songTime << std::endl;
            break;
        case SDLK_RIGHT:
            beatFileOut << songTime << std::endl;
            break;
        case SDLK_LEFT:
            beatFileOut << songTime << std::endl;
            break;
        }
    }
}

void Beatmap::Update()
{
    if(!playing) return;
    Uint64 head = timeToSpawnRhythm.front();

    int pos = 0;
    for(auto& r : rhythms)
    {
        if(r->active == false)
        {
            rhythms.erase(rhythms.begin() + pos);
            pos--;
        }
        pos++;
    }

    if(songTime >= head)
    {
        rhythms.push_back(new FallingRhythm(head));
        timeToSpawnRhythm.pop();
    }

    for(auto& r : rhythms)
    {
        r->Update(songTime, speed);
    }

    //LoadText(, SDL_Color{255,255,255});
    std::string newScoreStr = "Your score: " + std::to_string(score);
    if(scoreStr != newScoreStr)
    {
        scoreStr = newScoreStr;
        ScoreText->Reset();
        ScoreText = new Label("font/Carlito-Italic.ttf", scoreStr.c_str(), 40, 2100, 100, SDL_Color{255,255,255}, 300);
    }
}

void Beatmap::Render()
{
    if(!playing) return;
    for(auto& r : rhythms)
    {
        r->Render();
    }
    ScoreText->Render();
    //SDL_Rect destRect = {2400, 50, textWidth, textHeight};
    //SDL_RenderCopy(Symphony::gRenderer, ScoreText, NULL, &destRect);
}

void Beatmap::Play()
{
    songTime = 0;
    Mix_HaltMusic();
    Mix_PlayMusic(music, 0);
    playing = true;
    while(!timeToSpawnRhythm.empty()) timeToSpawnRhythm.pop();
    songTime = 0;
    //beatFileOut.open("testbeat.txt");
    //return;
    if(songName == "Pentakill") beatFileInp.open("Pentakill.txt");
    else if(songName == "Cupid")beatFileInp.open("Cupid.txt");
    Uint64 tmp;
    while(!beatFileInp.eof())
    {
        beatFileInp >> tmp;
        timeToSpawnRhythm.push(tmp - 1440/speed);
    }
}


void Beatmap::AddScore(int _score)
{
    score = score + _score;
}

void Beatmap::getSongTime()
{
    if(!playing) return;
    songTime = Mix_GetMusicPosition(music)*1000.0;
}
