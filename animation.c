#include <SDL2/SDL.h>
#include "sprite.h"
#include "list.h"
#include "animation.h"
#include <stdio.h>

// Tout ce qui concerne les animations

struct Animation *create_animation(struct Sprite *sprite, int x, int y, int nb_image, int delay, SDL_bool loop)
{
    struct Animation *animation = malloc(sizeof(struct Animation));
    if(animation == NULL)
    {
        perror("Error creating animation : ");
        return NULL;
    }
    animation->sprite = sprite;
    animation->nb_image = nb_image;
    animation->actual_image = 0;
    animation->loop = loop;
    animation->x = x;
    animation->y = y;
    animation->last_time = 0;
    animation->delay = delay;
    return animation;
}
 
void free_animation(struct Animation *animation)
{
    free(animation);
}
 
SDL_bool update_animation(struct Animation *animation, int actual_time)
{
    if(actual_time - animation->last_time > animation->delay)
    {
        animation->actual_image++;
        animation->last_time = actual_time;
        if(animation->actual_image >= animation->nb_image && animation->loop)
            animation->actual_image = 0;
    }
    return animation->actual_image < animation->nb_image;
}
 
void display_animation(SDL_Renderer *renderer, struct Animation *animation)
{
    int w = animation->sprite->w / animation->nb_image, h = animation->sprite->h;
    int x = animation->x, y = animation->y;
    SDL_Rect src = {w * animation->actual_image, 0, w, h};
    display_cliped_sprite(renderer, animation->sprite, x, y, &src);
}
 
AnimationList *create_animation_list(void)
{
    return create_list();
}
 
void free_animation_list(AnimationList *animation_list)
{
    struct Node *node = animation_list->first;
    while(node)
    {
        struct Node *next = node->next;
        free_animation(node->data);
        free(node);
        node = next;
    }
    free(animation_list);
}
 
int append_animation(AnimationList *animation_list, struct Animation *animation)
{
    return list_append(animation_list, animation);
}
 
void display_animation_list(SDL_Renderer *renderer, AnimationList *animation_list)
{
    struct Node *node = animation_list->first;
    while(NULL != node)
    {
        struct Animation *animation = node->data;
        display_animation(renderer, animation);
        node = node->next;
    }
}
 
 
void update_animation_list(AnimationList *animation_list, int actual_time)
{
    struct Node *node = animation_list->first;
    while(NULL != node)
    {
        struct Node *next_node = node->next;
        struct Animation *animation = node->data;
        if(!update_animation(animation, actual_time))
        {
            free_animation(animation);
            free_node(node);
        }
        node = next_node;
    }
}
 
int add_animation(AnimationList *animation_list, struct Sprite *sprite, int x, int y, int nb_image, int delay, SDL_bool loop)
{
    struct Animation *animation = create_animation(sprite, x, y, nb_image, delay, loop);
    if(NULL == animation)
        return -1;
    if(append_animation(animation_list, animation) < 0)
    {
        free_animation(animation);
        return -1;
    }
    return 0;
}
