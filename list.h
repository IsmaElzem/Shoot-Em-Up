// list.h

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * \struct Node
 * \brief Objet représentant un élément d’une liste
 *
 * Node est une structure contenant un pointeur sur les données contenues,
 * un pointeur sur l’élément précédent (nul s’il s’agit du premier élément),
 * un pointeur sur l’élément suivant (nul s’il s’agit du dernier élément) et
 * un pointeur sur la liste à laquelle il appartient.
 */
struct Node
{
    void *data;
    struct Node *next;
    struct Node *previous;
    struct List *list;
};
 
/**
 * \struct List
 * \brief Objet représentant une liste
 *
 * List est une structure contenant un pointeur sur le premier élément de la liste,
 * un pointeur sur son dernier élément et sa taille.
 */
struct List
{
    size_t size;
    struct Node *first;
    struct Node *last;
};
 
/**
 * \fn int list_is_empty(struct List *list)
 * \brief Vérifie si une liste est vide.
 * \param list Liste dont on veut vérifier la vacuité.
 *
 * \return Un booléen valant `true` si la list est vide, `false` sinon.
 *
 */
int list_is_empty(struct List *list);
 
/**
 * \fn struct List *create_list(void)
 * \brief Crée une nouvelle liste
 * \return Un pointeur sur la liste créée et `NULL` en cas d’erreur.
 *
 * La fonction crée une nouvelle liste vide. Elle met sa taille à zéro,
 * et les pointeurs vers les premier et dernier élément à `NULL`.
 * Attention : une liste doit être détruite avec la fonction `free_list`.
 */
struct List *create_list(void);
 
/**
 * \fn struct List *free_list(struct List *list);
 * \brief Libère une liste.
 *
 */
void free_list(struct List *list);
 
/**
 * \fn struct Node *list_get_element(struct List *list, size_t i)
 * \brief Renvoie le i-ème élément d’une liste.
 * \param list Liste dont on veut l’élément.
 * \param i Indice de l’élément à renvoyer
 * \return Pointeur sur le i-ème élément de la liste. NULL en cas d’erreur.
 *
 * Les indices d’une liste sont numérotées de 0 à list.size - 1.
 */
struct Node *list_get_element(struct List const * const list, size_t i);
 
/**
 * \fn void *list_get_element(struct List const * const list, size_t i)
 * \brief Renvoie les données du i-ième élément d’une liste.
 * \param list Liste dont on veut les données.
 * \param i Indice de l’élément dont on veut les données.
 * \return Données du i-ème élément de la liste. NULL en cas d’erreur.
 *
 * Les indices d’une liste sont numérotées de 0 à list.size - 1.
 */
void *list_get(struct List const * const list, const size_t i);
 
/**
 * \fn void *list_pop_index(struct List * const list, const size_t i)
 * \brief Supprime et renvoie le dernier élément d’une liste.
 * \param list Liste dont on veut supprimer le dernier élément.
 * \param i Indice de l’élément dont on veut les données.
 * \return Les données du dernier élément de la liste
 *
 */
void *list_pop_index(struct List * const list, const size_t i);
 
/**
 * \fn void *list_pop(struct List * const list)
 * \brief Supprime et renvoie le dernier élément d’une liste.
 * \param list Liste dont on veut supprimer le dernier élément.
 * \return Les données du dernier élément de la liste
 *
 */
void *list_pop(struct List * const list);
 
/**
 * \fn void *list_pop_first(struct List * const list)
 * \brief Supprime et renvoie le premier élément d’une liste.
 * \param list Liste dont on veut supprimer le premier élément.
 * \return Les données du premier élément de la liste
 *
 */
void *list_pop_first(struct List * const list);
 
/**
 * \fn int list_append(struct List *list, void *data)
 * \brief Ajoute un nouvel élément à la fin d’une liste
 * \param list Liste à laquelle ajouter l’élément
 * \param data Pointeur sur les données correspondant à l’élément
 * \return 0 en cas de succès et -1 en cas d’erreur.
 *
 */
int list_append(struct List *list, void *data);
 
/**
 * \fn int list_append_first(struct List *list, void *data)
 * \brief Ajoute un nouvel élément au début d’une liste
 * \param list Liste à laquelle ajouter l’élément
 * \param data Pointeur sur les données correspondant à l’élément
 * \return 0 en cas de succès et -1 en cas d’erreur.
 *
 */
int list_append_first(struct List *list, void *data);
 
/**
 * \fn int list_insert(struct List *list, size_t i, void *data)
 * \brief Ajoute un nouvel élément à une liste à la place i
 * \param list Liste à laquelle ajouter l’élément
 * \param data Pointeur sur les données correspondant à l’élément
 * \return 0 en cas de succès et -1 en cas d’erreur.
 *
 * Les places vont de 0 à `list.size`. Essayer d’insérer un élément à
 * une position plus grande que `list.size` donne une erreur.
 */
int list_insert(struct List *list, size_t i, void *data);
 
/**
 * \fn void free_node(struct Node *node)
 * \brief Supprime un élément d’une liste
 * \param node Nœud à supprimer de la liste.
 * \return 0 en cas de succès et -1 en cas d’erreur.
 *
 */
void free_node(struct Node *node);

#endif
