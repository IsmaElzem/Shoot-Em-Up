#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include "missile.h"
#include "animation.h"
#include "context.h"
#include "event.h"


#define SCREEN_WIDTH  700
#define SCREEN_HEIGHT 700
 

// Main du projet, c'est le coeur, ce qui fais battre le jeu!

int menu(struct Context *c); 
int play(struct Context *c);
 
int play(struct Context *c)
{
    struct Input in = {{SDL_FALSE}, SDL_FALSE};
    int last_shoot = 0, last_enemy = 0;
    while(!in.quit&& c->life_points > 0)
    {
        int actual_time = SDL_GetTicks();
        c->direction = NOTHING;
        update_event(&in);
        if(in.key[SDL_SCANCODE_RIGHT] && c->spaceship->x < SCREEN_WIDTH - c->spaceship->sprite->w / 2)
        {
            c->direction = RIGHT;
            c->spaceship->x += c->spaceship->dx;
        }
        if(in.key[SDL_SCANCODE_LEFT] && c->spaceship->x > - c->spaceship->sprite->w / 2)
        {
            c->direction = LEFT;
            c->spaceship->x -= c->spaceship->dx;
        }
        if(in.key[SDL_SCANCODE_SPACE]  && actual_time - last_shoot > c->shoot_time)
        {
            last_shoot = actual_time;
            if(add_missile(c) < 0)
                return -1;
        }
        if(actual_time - last_enemy > c->enemy_time)
        {
            last_enemy = actual_time;
            if(add_enemy(c) < 0)
                return -1;
        }
        if(in.quit)
        {
            return 3;
        }
        update_animation_list(c->animation_list, actual_time);
        move_missiles(c->missiles_list);
        move_enemies(c->enemies_list);
        if(manage_collision(c) < 0)
            return -1;
        display_context(c);
        SDL_Delay(20);
    }
    return 0;
}


int menu(struct Context *c)
{  
    int choix = 0;
    struct Input in = {{SDL_FALSE}, SDL_FALSE};
    set_background_sprite(c->renderer, c->s_menu);
    SDL_RenderPresent(c->renderer);
    while(choix != 1 && choix != 2 && choix != 3)
    {
        update_event(&in);
        if(in.key[SDL_SCANCODE_1] || in.key[SDL_SCANCODE_KP_1])
            choix = 1;
        else if(in.key[SDL_SCANCODE_2] || in.key[SDL_SCANCODE_KP_2])
            choix = 2;
        else if(in.key[SDL_SCANCODE_3] || in.key[SDL_SCANCODE_KP_3] || in.quit)
            choix = 3;
    }
    return choix;
} 

int main(void)
{
    struct Context c = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    srand(time(NULL));
    if(init_context(&c) == 0)
    {
        int choix = 0;
        while(choix != 3)
        {
           choix = menu(&c);
            if(choix == 1)
                choix = play(&c);
            else if(choix == 2)
                printf("La fonctionnalité score n’est pas encore disponible.\n");
       }
    }
    destroy_context(&c);
    return 0;
}
