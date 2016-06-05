#include "includes.h"
#define SOUND_FREQUENCY 44100

Mix_Music *background_music = NULL;
//sound effect
Mix_Chunk *bounce_sound = NULL;

void initialise_music() {
   //SDL Mixel initialisation
    if(Mix_OpenAudio(SOUND_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer could not initialize!");
        exit(EXIT_FAILURE);
    }
    background_music = Mix_LoadMUS("");
    if(background_music == NULL) {
        fprintf(stderr, "Failed to load background music");
        exit(EXIT_FAILURE);
    }
    bounce_sound = Mix_LoadWAV("bouncing.wav");
    if(bounce_sound == NULL) {
        fprintf(stderr, "Failed to load bounce sound");
        exit(EXIT_FAILURE);
    } 
}

void destroy_music() {
    //Free sound effects
    Mix_FreeChunk(bounce_sound);
    bounce_sound = NULL; 
    //Free music
    Mix_FreeMusic(background_music);
    background_music = NULL;
    //Quit SDL subsystem
    Mix_Quit();
}

void play_collision_sound() {
    Mix_PlayChannel(-1, bounce_sound, 0);
}
