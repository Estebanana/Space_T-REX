/**
 * \file module_logique.c
 * \author Esteban ROMERA
 * \brief Pour implémenter les fonctions du monde.
*/

#include "graphique.h"
#include "logique.h"
#include "constante.h"
#include "sdl2-light.h"


/**
 * \brief La fonction initialise les données du sprite
 * \param sprite A COMPLETER
 */
void init_sprite(sprite_t * sprite, int x,int y,int w,int h){
    sprite->posx = x;
    sprite->posy = y;
    sprite->h = h;
    sprite->w = w;
}

void print_sprite(sprite_t *sprite){
    printf("Sprite : coords |%d|%d| Hauteur|%d| Largeur|%d|\n", sprite->posx, sprite->posy, sprite->h, sprite->w);
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    world->spaceship = malloc(sizeof(sprite_t));
    init_sprite(world->spaceship, (SCREEN_WIDTH - SHIP_SIZE)/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE,SHIP_SIZE);
    print_sprite(world->spaceship);
    world->finishline = malloc(sizeof(sprite_t));
    init_sprite(world->finishline, 0, FINISH_LINE_HEIGHT,SCREEN_WIDTH,FINISH_LINE_HEIGHT);
    world->vy = INITIAL_SPEED;
    world->mur = malloc(sizeof(sprite_t));
    init_sprite(world->mur, (SCREEN_WIDTH/2)-(METEORITE_SIZE*1.5), METEORITE_SIZE, 3*METEORITE_SIZE, 7*METEORITE_SIZE);
    print_sprite(world->mur);
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->finishline->posy += world->vy;
    world->mur->posy += world->vy;
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while(SDL_PollEvent(event)){
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'ESC'
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'flèche droite'
            if(event->key.keysym.sym == SDLK_RIGHT){
                world->spaceship->posx += MOVING_STEP;
            }
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'flèche gauche'
            if(event->key.keysym.sym == SDLK_LEFT){
                world->spaceship->posx -= MOVING_STEP;
            }
        }

       
        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'flèche haut'
            if(event->key.keysym.sym == SDLK_UP){
                world->vy += INITIAL_SPEED;
            }
        }
        
        //si une touche est relachée
        if(event->type == SDL_KEYUP){
            //si la touche relachée est 'flèche haut'
            if(event->key.keysym.sym == SDLK_UP){
                world->vy -= INITIAL_SPEED;
            }
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'flèche bas'
            if(event->key.keysym.sym == SDLK_DOWN){
                world->vy -= INITIAL_SPEED;
            }
        }
        
        //si une touche est relachée
        if(event->type == SDL_KEYUP){
            //si la touche relachée est 'flèche bas'
            if(event->key.keysym.sym == SDLK_DOWN){
                world->vy += INITIAL_SPEED;
            }
        }
    }
}