//utils.h


#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"

double randomSize(void);
int randint(const int a, const int b);
SDL_Surface *load_surface(const char path[]);
int init_SDL(SDL_Window **window, SDL_Renderer **renderer, int w, int h, const char title[]);

#endif
