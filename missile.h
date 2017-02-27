//missile.h


#ifndef MISSILE_H
#define MISSILE_H

#include <SDL2/SDL.h>
#include "utils.h"
#include "mobile.h"
#include "missile.h"
#include "context.h"


void display_missiles(SDL_Renderer *renderer, MobileList *missiles_list);
void display_enemies(SDL_Renderer *renderer, MobileList *enemies_list);
void move_missiles(MobileList *missiles_list);
void move_enemies(MobileList *enemies_list);
int add_missile(struct Context *c);
int add_enemy(struct Context *c);

#endif
