#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"
#include "mobile.h"
#include "list.h"

struct Mobile *create_mobile(struct Sprite *sprite, int x, int y, int dx, int dy)
{
    struct Mobile *mobile = malloc(sizeof(struct Mobile));
    if(NULL == mobile)
    {
        perror("Error creating mobile : ");
        return NULL;
    }
    mobile->sprite = sprite;
    mobile->x = x;
    mobile->y = y;
    mobile->dx = dx;
    mobile->dy = dy;
    return mobile;
}
 
MobileList *create_mobile_list(void)
{
    return create_list();
}
 
int append_mobile(MobileList *mobile_list, struct Mobile *mobile)
{
    return list_append(mobile_list, mobile);
}
 
void free_mobile_list(MobileList *mobile_list)
{
    struct Node *node = mobile_list->first;
    while(node)
    {
        struct Node *next = node->next;
        free_mobile(node->data);
        free(node);
        node = next;
    }
    free(mobile_list);
}
 
void display_mobile(SDL_Renderer *renderer, struct Mobile *mobile)
{
    display_sprite(renderer, mobile->sprite, mobile->x, mobile->y);
}
 
SDL_bool has_mobile_collision(struct Mobile *m1, struct Mobile *m2)
{
    SDL_Rect r1 ={m1->x, m1->y, m1->sprite->w, m1->sprite->h}, r2 = {m2->x, m2->y, m2->sprite->w, m2->sprite->h};
    return SDL_HasIntersection(&r1, &r2);
}
 
void move_mobile(struct Mobile *mobile)
{
    mobile->x += mobile->dx;
    mobile->y += mobile->dy;
}
 
void free_mobile(struct Mobile *mobile)
{
    free(mobile);
}
 
void display_mobile_list(SDL_Renderer *renderer, MobileList *mobiles_list)
{
    struct Node *node = mobiles_list->first;
    while(NULL != node)
    {
        struct Mobile *mobile = node->data;
        display_mobile(renderer, mobile);
        node = node->next;
    }
}
 
void move_mobile_list(MobileList *mobiles_list)
{
    struct Node *node = mobiles_list->first;
    while(NULL != node)
    {
        struct Mobile *mobile = node->data;
        move_mobile(mobile);
        node = node->next;
    }
}
