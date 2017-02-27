// context.h

#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"
#include "mobile.h"
#include "missile.h"
#include "animation.h"
#include "context.h"

enum Direction {NOTHING, RIGHT, LEFT};

struct Context
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	struct Sprite *s_spaceship, *s_missile, *s_enemy, *s_background, *s_score, *s_heart, *s_number, *s_explosion,*s_menu;
	MobileList *enemies_list, *missiles_list;
	AnimationList *animation_list;
	struct Mobile *spaceship;
	enum Direction direction;
	int enemy_time, shoot_time, points, life_points;
};


void display_score(struct Context *c);
void display_life(struct Context *c);
int init_context(struct Context *c);
void display_context(struct Context *c);
void destroy_context(struct Context *c);
int manage_collision(struct Context *c);
void update_level(struct Context *c);

#endif
