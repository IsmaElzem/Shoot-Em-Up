// animation.h

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include "sprite.h"
#include "list.h"
#include "animation.h"
#include <stdio.h>


struct Animation
{
	int nb_image, actual_image, x, y, delay, last_time;
	struct Sprite *sprite;
	SDL_bool loop; 
};

typedef struct List AnimationList;

struct Animation *create_animation(struct Sprite *sprite, int x, int y, int nb_image, int delay, SDL_bool loop);
void free_animation(struct Animation *animation);
SDL_bool update_animation(struct Animation *animation, int actual_time);
void display_animation(SDL_Renderer *renderer, struct Animation *animation);
AnimationList *create_animation_list(void);
void free_animation_list(AnimationList *animation_list);
int append_animation(AnimationList *animation_list, struct Animation *animation);
void display_animation_list(SDL_Renderer *renderer, AnimationList *animation_list);
void update_animation_list(AnimationList *animation_list, int actual_time);
int add_animation(AnimationList *animation_list, struct Sprite *sprite, int x, int y, int nb_image, int delay, SDL_bool loop);

#endif
