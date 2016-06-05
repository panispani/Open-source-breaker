#ifndef __SOUND_H
#define __SOUND_H

extern Mix_Music *background_music;
extern Mix_Chunk *bounce_sound;

void initialise_music();
void destroy_music();
void play_collision_sound();

#endif //__SOUND_H
