#ifndef SOUND
#define SOUND

#include <SDL_mixer.h>

static Mix_Chunk* dropeffect;
void playdropsound();

static Mix_Chunk* bombeffect;
void playbombsound();

static Mix_Chunk* collecteffect;
void playcollectsound();

void initsound();


#endif // SOUND
