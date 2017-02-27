#include <SDL2/SDL.h>
#include "utils.h"
#include "mobile.h"
#include "missile.h"
#include "context.h"

#define SCREEN_WIDTH  700
#define SCREEN_HEIGHT 700

// Ajout de missile, mouvement des missiles ...

void display_missiles(SDL_Renderer *renderer, MobileList *missiles_list)
{
    display_mobile_list(renderer, missiles_list);
}
 
void display_enemies(SDL_Renderer *renderer, MobileList *enemies_list)
{
    display_mobile_list(renderer, enemies_list);
}
 
void move_missiles(MobileList *missiles_list)
{
    move_mobile_list(missiles_list);
}
 
void move_enemies(MobileList *enemies_list)
{
    move_mobile_list(enemies_list);
}
 
int add_missile(struct Context *c)
{
    struct Sprite *sprite = c->s_missile;
    int x = c->spaceship->x + c->spaceship->sprite->w / 2 - sprite->w / 2, y = c->spaceship->y, dx, dy;
    if(c->direction == NOTHING)
    {
        dx = 0;
        dy = -randint(2, 5);
    }
    else
    {
        dy = -randint(3, 7);
        if(c->direction == RIGHT)
            dx = 1;
        else
            dx = -1;
    }
    struct Mobile *missile = create_mobile(sprite, x, y, dx, dy);
    if(NULL == missile)
        return -1;
    if(append_mobile(c->missiles_list, missile) < 0)
    {
        free_mobile(missile);
        return -1;
    }
    return 0;
}

int add_enemy(struct Context *c)
{
    struct Sprite *sprite = c->s_enemy;
    int x = randint(0, SCREEN_WIDTH - sprite->w), y = -sprite->h, dx = 0, dy = randint(3, 5);
    struct Mobile *enemy = create_mobile(sprite, x, y, dx, dy);
    if(NULL == enemy)
        return -1;
    if(append_mobile(c->enemies_list, enemy) < 0)
    {
        free_mobile(enemy);
        return -1;
    }
    return 0;
}
