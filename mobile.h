//mobile.h

#ifndef MOBILE_H
#define MOBILE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "utils.h"
#include "sprite.h"
#include "mobile.h"


/**
 * \struct Mobile
 * \brief Structure représentant un sprite
 *
 * Mobile est une structure contenant un sprite,
 * les coordonnées du mobile et sa vitesse.
 */
struct Mobile
{
    struct Sprite *sprite;
    int x, y, dx, dy;
};
 
/**
 * \typedef Une liste de mobile est une liste.
 *
 */
typedef struct List MobileList;
 
/**
 * \fn struct Mobile *create_mobile(struct Sprite *sprite, int x, int y, int dx, int dy)
 * \brief Crée un mobile
 * \param sprite Sprite du mobile
 * \param x abscisse de départ du mobile
 * \param y ordonnée de départ du mobile
 * \param dx vitesse horizontale du mobile
 * \param dy vitesse verticale du mobile
 * \return Un pointeur vers le mobile créé ou NULL en cas d’erreur.
 *
 * Un mobile créé avec create_mobile doit  être libéré avec free_mobile.
 *
 */
struct Mobile *create_mobile(struct Sprite *sprite, int x, int y, int dx, int dy);
 
/**
 * \fn struct Mobile *free_mobile(struct Sprite *sprite, int x, int y, int dx, int dz)
 * \brief Libère un mobile
 * \param mobile Le mobile à libérer
 *
 */
void free_mobile(struct Mobile *mobile);
 
/**
 * \fn MobileList *create_mobile_list(void)
 * \brief Crée une liste vide de mobiles.
 *
 * La liste créée doit être libéré avec free_mobile_list.
 *
 */
MobileList *create_mobile_list(void);
 
/**
 * \fn void free_mobile_list(MobileList *mobile_list)
 * \brief Libère une liste de mobiles.
 * \param mobile_list La liste de mobiles à libérer.
 *
 */
void free_mobile_list(MobileList *mobile_list);
 
/**
 * \fn int append_mobile(MobileList *mobile_list, struct Mobile *mobile)
 * \brief Ajoute un mobile à une liste de mobiles.
 * \param mobile_list La liste de mobiles.
 * \param mobile Le mobile à ajouter à la liste.
 * \return 0 en cas de succès, une valeur négative en cas d’erreur.
 *
 */
int append_mobile(MobileList *mobile_list, struct Mobile *mobile);
 
/**
 * \fn void display_mobile(SDL_Renderer *renderer, struct Mobile *mobile)
 * \brief Affiche un mobile à ses coordonnées.
 * \param renderer Le renderer où afficher le mobile.
 * \param mobile Mobile à afficher.
 */
void display_mobile(SDL_Renderer *renderer, struct Mobile *mobile);
 
/**
 * \fn void display_mobile_list(SDL_Renderer *renderer, MobileList *mobiles_list)
 * \brief Affiche une liste de mobiles.
 * \param renderer Le renderer où afficher le mobile.
 * \param mobiles_list la liste de mobiles à afficher.
 */
void display_mobile_list(SDL_Renderer *renderer, MobileList *mobiles_list);
 
/**
 * \fn SDL_bool has_mobile_collision(struct Mobile *m1, struct Mobile *m2)
 * \brief Vérifie que deux mobiles se touchent
 * \param m1 Le premier mobile
 * \param m2 Le second mobile.
 * \return SDL_TRUE s’il y a collision entre les deux mobiles, sinon SDL_FALSE.
 *
 */
SDL_bool has_mobile_collision(struct Mobile *m1, struct Mobile *m2);
 
/**
 * \fn void move_mobile(struct Mobile *mobile)
 * \brief Déplace un mobile
 * \param mobile Le mobile à déplacer
 *
 * La fonction déplace le mobile grâce à sa vitesse (dx et dy).
 *
 */
void move_mobile(struct Mobile *mobile);
 
/**
 * \fn void display_mobile_list(SDL_Renderer *renderer, MobileList *mobiles_list)
 * \brief Déplace une liste de mobiles.
 * \param mobiles_list la liste de mobiles à afficher.
 */
void move_mobile_list(MobileList *mobiles_list);

#endif
