#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"

// Fonction random, initialise la libraire SDL, la window, le renderer ...

double randomSize(void)
{
    return (double) rand() / RAND_MAX;
}
 
int randint(const int a, const int b)
{
    return (int)(a + (b - a) * randomSize());
}
 
SDL_Surface *load_surface(const char path[])
{
    SDL_Surface *tmp = IMG_Load(path);
    if(NULL == tmp)
        fprintf(stderr, "Erreur IMG_Load : %s", SDL_GetError());
    return tmp;
}
 
int init_SDL(SDL_Window **window, SDL_Renderer **renderer, int w, int h, const char title[])
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              w, h, SDL_WINDOW_SHOWN);
    if(NULL == *window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return -1;
    }
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == &*renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}
