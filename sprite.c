#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"
 
struct Sprite *load_sprite(char path[], SDL_Renderer *renderer, SDL_Color *key)
{
    struct Sprite *sprite = malloc(sizeof(struct Sprite));
    if(NULL == sprite)
    {
        perror("Error creating Sprite : ");
        return NULL;
    }
    SDL_Surface *tmp = load_surface(path);
    if(NULL == tmp)
    {
        free(sprite);
        return NULL;
    }
    sprite->w = tmp->w;
    sprite->h = tmp->h;
    if(key)
        SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key->r, key->g, key->b));
    sprite->texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == sprite->texture)
    {
        fprintf(stderr, "Error creating sprite : %s.", SDL_GetError());
        return NULL;
    }
    return sprite;
}
 
struct Sprite *free_sprite(struct Sprite *sprite)
{
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
    return NULL;
}
 
void display_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y)
{
    SDL_Rect dst = {x, y, sprite->w, sprite->h};
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}
 
void display_scaled_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, int scale)
{
    SDL_Rect dst = {x, y, sprite->w * scale, sprite->h * scale};
    SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
}
 
void set_background_sprite(SDL_Renderer *renderer, struct Sprite *sprite)
{
    SDL_RenderCopy(renderer, sprite->texture, NULL, NULL);
}
 
void display_cliped_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, SDL_Rect *src)
{
    SDL_Rect dst = {x, y, src->w, src->h};
    SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}
 
void display_scaled_cliped_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, SDL_Rect *src, int scale)
{
    SDL_Rect dst = {x, y, src->w * scale, src->h * scale};
    SDL_RenderCopy(renderer, sprite->texture, src, &dst);
}
