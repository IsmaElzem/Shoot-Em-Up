#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"
#include "mobile.h"
#include "missile.h"
#include "animation.h"
#include "context.h"

#define SCREEN_WIDTH  700
#define SCREEN_HEIGHT 700

// Permet de charger la fenêtre, les textures, le renderer, etc.

void display_score(struct Context *c)
{
    int width_number = c->s_score->w / 10, height_number = c->s_score->h;
    int x = SCREEN_WIDTH - width_number - 10, y = 10;
    int score = c->points;
    do
    {
        int number = score % 10;
        SDL_Rect src = {number * width_number, 0, width_number, height_number};
        display_cliped_sprite(c->renderer, c->s_score, x, y, &src);
        x -= width_number;
        score = score / 10;
    }while(score);
}
 
void display_life(struct Context *c)
{
    int x = 10, y = 10, i = 0;
    struct Sprite *sprite = c->s_heart;
    for(i = 0; i < c->life_points; i++, x += sprite->w)
        display_sprite(c->renderer, sprite, x, y);
}
   
int init_context(struct Context *c)
{
    if(init_SDL(&c->window, &c->renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "My shoot ’em up") < 0)
        return -1;
    SDL_Color black = {0, 0, 0, 0}, write = {255, 255, 255, 0};
    c->s_menu = load_sprite("images/menu.bmp", c->renderer, &write);
    c->s_spaceship = load_sprite("images/vaisseau.bmp", c->renderer, NULL);
    c->s_enemy = load_sprite("images/vaisseauEnnemi.png", c->renderer, &black);
    c->s_missile = load_sprite("images/missile2.png", c->renderer, &black);
    c->s_background = load_sprite("images/Fond.bmp", c->renderer, NULL);
    c->s_heart = load_sprite("images/coeur.png", c->renderer, &black);
    c->s_score = load_sprite("images/chiffre.png", c->renderer, &black);
    c->s_explosion = load_sprite("images/explosion.bmp", c->renderer, &write);
    if(!c->s_background || !c->s_spaceship || !c->s_missile|| !c->s_enemy || !c->s_score || !c->s_heart || !c->s_explosion)
        return -1;
   
    c->enemies_list = create_mobile_list();
    c->missiles_list = create_mobile_list();
    c->animation_list = create_animation_list();
    if(!c->enemies_list || !c->missiles_list || !c->animation_list)
        return -1;
   
    c->spaceship = create_mobile(c->s_spaceship, SCREEN_WIDTH / 2 - c->s_spaceship->w / 2,
                                 SCREEN_HEIGHT - c->s_spaceship->h, 10, 0);
    if(!c->spaceship)
        return -1;
   
    c->direction = NOTHING;
    c->enemy_time = 2000;
    c->shoot_time = 500;
    c->points = 0;
    c->life_points = 5;
    return 0;
}
 
void display_context(struct Context *c)
{
    set_background_sprite(c->renderer, c->s_background);
    display_sprite(c->renderer, c->spaceship->sprite, c->spaceship->x, c->spaceship->y);
    display_enemies(c->renderer, c->enemies_list);
    display_missiles(c->renderer, c->missiles_list);
    display_score(c);
    display_life(c);
    display_animation_list(c->renderer, c->animation_list);
    SDL_RenderPresent(c->renderer);
}
 
void destroy_context(struct Context *c)
{
    free_sprite(c->s_missile);
    free_sprite(c->s_enemy);
    free_sprite(c->s_background);
    free_sprite(c->s_spaceship);
    free_sprite(c->s_score);
    free_sprite(c->s_heart);
    free_sprite(c->s_explosion);
   
    free_animation_list(c->animation_list);
    free_mobile_list(c->enemies_list);
    free_mobile_list(c->missiles_list);
    free_mobile(c->spaceship);
   
    SDL_DestroyRenderer(c->renderer);
    SDL_DestroyWindow(c->window);
    SDL_Quit();
}
 
int manage_collision(struct Context *c)
{
    struct Node *enemy_node = c->enemies_list->first;
    struct Mobile *spaceship = c->spaceship;
    while(enemy_node)
    {
        SDL_bool enemy_alive = SDL_TRUE;
        struct Node *next_enemy_node = enemy_node->next, *missile_node = c->missiles_list->first;
        struct Mobile *enemy = enemy_node->data;
        if(has_mobile_collision(enemy, spaceship) || enemy->y > SCREEN_HEIGHT)
        {
            if(add_animation(c->animation_list, c->s_explosion, enemy->x, enemy->y, 8, 50, SDL_FALSE) < 0)
                return -1;
            free_mobile(enemy);
            free_node(enemy_node);
            enemy_alive = SDL_FALSE;
            c->life_points--;
        }
        while(missile_node && enemy_alive)
        {
            struct Node *next_missile_node = missile_node->next;
            struct Mobile *missile = missile_node->data;
            if(has_mobile_collision(enemy, missile))
            {
                if(add_animation(c->animation_list, c->s_explosion, enemy->x, enemy->y, 8, 50, SDL_FALSE) < 0)
                    return -1;
                free_mobile(enemy);
                free_node(enemy_node);
                free_mobile(missile);
                free_node(missile_node);
                update_level(c);
                enemy_alive = SDL_FALSE;
                c->points++;
            }
            else if(missile->y + missile->sprite->h < 0)
            {
                free_mobile(missile);
                free_node(missile_node);
            }
            missile_node = next_missile_node;
        }
        enemy_node = next_enemy_node;
    }
    return 0;
}
 
void update_level(struct Context *c)
{
    c->enemy_time = SDL_max(c->enemy_time - 5 * c->points, 800);
}
