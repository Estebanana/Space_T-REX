/**
 * \file module_logique.h
 * \author Esteban ROMERA
 * \brief Fichier d'en tete pour le module logique.
*/

#ifndef LOGIQUE_H
#define LOGIQUE_H
#include "constante.h"
#include "sdl2-light.h"


/**
 * \brief Représentation du sprite du jeu
*/
struct sprite_s {
    int h; /*!< Hauteur du sprite. */
    int w; /*!< Largeur du sprite. */
    int posx; /*!< Position x du centre du sprite. */
    int posy; /*!< Position y du centre du sprite. */
};

/**
 * \brief Type qui correspond au sprite
 */
typedef struct sprite_s sprite_t;


/**
 * \brief Représentation du monde du jeu
*/
struct world_s{
    //sprite_t * mur; /*!< Champ du sprite pour le murs. */
    sprite_t * spaceship; /*!< Champ du sprite pour le vaisseau. */
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
    sprite_t * finishline; /*!< Champ du sprite pour la ligne d'arrivée. */
    int vy; /*!< Correspond à la vitesse de déplacement vertical de la ligne d'arrivée. */
    sprite_t * listemur[6]; /*!< Champ du sprite pour le tableau de murs. */
    int make_disappear; /*!< Champ visibilité du sprite. */
};

/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

/**
 * \brief La fonction initialise les données du sprite
 * \param sprite A COMPLETER
 */
void init_sprite(sprite_t * sprite, int x,int y,int w,int h);

void print_sprite(sprite_t *sprite);

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world);

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);

void border_cross(world_t *world);

int sprites_collide(sprite_t *sp1, sprite_t *sp2);

void handle_sprites_collision(world_t* world, sprite_t *sp1, sprite_t *sp2);

void update_walls(world_t *world);

#endif