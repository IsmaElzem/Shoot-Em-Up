#include <SDL2/SDL.h>
#include "event.h"
 
// Met à jour la structure Input en fonction des évènements qui ont eu lieu

void update_event(struct Input *input)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            input->quit = SDL_TRUE;
        else if(event.type == SDL_KEYDOWN)
            input->key[event.key.keysym.scancode] = SDL_TRUE;
        else if(event.type == SDL_KEYUP)
            input->key[event.key.keysym.scancode] = SDL_FALSE;
    }
}
