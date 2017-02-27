// event.h

#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>
#include "event.h"

struct Input
{
	SDL_bool key[SDL_NUM_SCANCODES];
	SDL_bool quit;
};

void update_event(struct Input *input);

#endif
