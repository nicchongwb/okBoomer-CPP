#include "Sound.h"
#include <iostream>
#include <SDL.h>

bool soundReady = false;

void playdropsound()
{
    if (!soundReady)
        initsound();

    Mix_PlayChannel(-1, dropeffect, 0);
}

void playbombsound()
{
    if (!soundReady)
        initsound();

    Mix_PlayChannel(-1, bombeffect, 0);
}

void playcollectsound()
{
    if (!soundReady)
        initsound();

    Mix_PlayChannel(-1, collecteffect, 0);
}

void initsound()
{
    SDL_Init(SDL_INIT_AUDIO);
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels,
        audio_buffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s",
            Mix_GetError());
        exit(-3);
    }

    // Load drop bomb sound effect here
    dropeffect = Mix_LoadWAV("res/audio/drop.wav");
    if (dropeffect == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Unable to load audio: %s",
            Mix_GetError()); // Get error if cannot load
    }

    // Load bomb damage on player sound effect here
   bombeffect = Mix_LoadWAV("res/audio/bomb.wav");
    if (bombeffect == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Unable to load audio: %s",
            Mix_GetError()); // Get error if cannot load
    }

    // Load collect bomb sound effect here
    collecteffect = Mix_LoadWAV("res/audio/collect.wav");
    if (collecteffect == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Unable to load audio: %s", 
            Mix_GetError()); // Get error if cannot load
    }

    // Sound is ready and can be played
    soundReady = true; 
}
