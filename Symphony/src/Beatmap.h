#pragma once
#ifndef Beatmap_h
#define Beatmap_h

#include <string>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <queue>
#include "label.h"

#include "Symphony.h"

class FallingRhythm;

class Beatmap
{
public:
    Beatmap(int _BPM, float _speed, std::string pathToMusic, std::string songName);
    ~Beatmap();
    void HandleEvent();
    void Update();
    void Render();
    void Play();
    void AddScore(int _score);
    void getSongTime();

private:
    void LoadText(std::string text, SDL_Color color);
    SDL_Color Black = {0,0,0};
    int BPM;
    float speed;
    TTF_Font *font;
    Mix_Music *music;
    Uint64 songTime;
    SDL_Texture *printSongTime;
    int textWidth, textHeight;
    std::ofstream beatFileOut;
    std::ifstream beatFileInp;
    std::queue<Uint64> timeToSpawnRhythm;
    std::vector<FallingRhythm*> rhythms;
    bool playing = false;
    int score = 0;
    std::string songName;
    std::string scoreStr;

private:
    SDL_Thread *getTimeThread;
    static int ThreadFunction(void* data)
    {
        Beatmap* self = static_cast<Beatmap*>(data);
        while(true)
        {
            self->getSongTime();
        }
    }
    Label *ScoreText;
};
#endif // Beatmap_h
