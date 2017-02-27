//sprite.h

#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"

struct Sprite
{
	SDL_Texture *texture;
	int w, h;
};
struct Sprite *load_sprite(char path[], SDL_Renderer *renderer, SDL_Color *key);
struct Sprite *free_sprite(struct Sprite *sprite);
void display_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y);
void display_scaled_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, int scale);
void set_background_sprite(SDL_Renderer *renderer, struct Sprite *sprite);
void display_cliped_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, SDL_Rect *src);
void display_scaled_cliped_sprite(SDL_Renderer *renderer, struct Sprite *sprite, int x, int y, SDL_Rect *src, int scale);


#endif
