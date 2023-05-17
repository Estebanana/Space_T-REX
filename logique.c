/**
 * \file logique.c
 * \author Esteban ROMERA
 * \brief Pour implémenter les fonctions du monde.
*/

#include "graphique.h"
#include "logique.h"
#include "constante.h"
#include "sdl2-light.h"
#include <SDL2/SDL_mixer.h>
#include <time.h>



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


void init_walls(world_t* world, sprite_t *listemur[]){

    listemur[0]->posx = 0;
    listemur[0]->posy = 0;
    listemur[0]->h = 6*METEORITE_SIZE;
    listemur[0]->w = 3*METEORITE_SIZE;

    listemur[1]->posx = 204;
    listemur[1]->posy = 0;
    listemur[1]->h = 6*METEORITE_SIZE;
    listemur[1]->w = 3*METEORITE_SIZE;

    listemur[2]->posx = 0;
    listemur[2]->posy = -352;
    listemur[2]->h = 5*METEORITE_SIZE;
    listemur[2]->w = METEORITE_SIZE;

    listemur[3]->posx = 140;
    listemur[3]->posy = -352;
    listemur[3]->h = 5*METEORITE_SIZE;
    listemur[3]->w = 7*METEORITE_SIZE;

    listemur[4]->posx = 0;
    listemur[4]->posy = -672;
    listemur[4]->h = 6*METEORITE_SIZE;
    listemur[4]->w = 3*METEORITE_SIZE;

    listemur[5]->posx = 204;
    listemur[5]->posy = -672;
    listemur[5]->h = 6*METEORITE_SIZE;
    listemur[5]->w = 3*METEORITE_SIZE;

    listemur[6]->posx = 0;
    listemur[6]->posy = -1000;
    listemur[6]->h = 2*METEORITE_SIZE;
    listemur[6]->w = 2*METEORITE_SIZE;

    listemur[7]->posx = 128;
    listemur[7]->posy = -1000;
    listemur[7]->h = 2*METEORITE_SIZE;
    listemur[7]->w = 7*METEORITE_SIZE;

    listemur[8]->posx = 0;
    listemur[8]->posy = -1300;
    listemur[8]->h = 3*METEORITE_SIZE;
    listemur[8]->w = 6*METEORITE_SIZE;

    listemur[9]->posx = 108;
    listemur[9]->posy = -1600;
    listemur[9]->h = 3*METEORITE_SIZE;
    listemur[9]->w = 6*METEORITE_SIZE;

    int k,j;
    for (int i = 10; i < world->nb_mur; i++) {
        listemur[i] = malloc(sizeof(sprite_t));
        do {
        k = rand() % (SCREEN_WIDTH - SHIP_SIZE);
        j = rand() % (SCREEN_WIDTH - SHIP_SIZE);
        } while (abs(k - j) <= 32);
        init_sprite(listemur[i], k, -2000 - (i - 10) * 100, METEORITE_SIZE, METEORITE_SIZE);
        init_sprite(listemur[i], j, -2000 - (i - 10) * 100, METEORITE_SIZE, METEORITE_SIZE);
    }
}

void print_sprite(sprite_t *sprite){
    printf("Sprite : coords |%d|%d| Hauteur|%d| Largeur|%d|\n", sprite->posx, sprite->posy, sprite->h, sprite->w);
}

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t *world) {
    srand(time(NULL));

    // on n'est pas à la fin du jeu
    world->quit = 0;
    world->gameover = 0;
    world->finishtime = 0;
    world->closing_time = 0;
    world->nb_mur = 50;

    // Initialiser SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur lors de l'initialisation de SDL_mixer: %s\n", Mix_GetError());
    }

    world->spaceship = malloc(sizeof(sprite_t));
    init_sprite(world->spaceship, (SCREEN_WIDTH - SHIP_SIZE) / 2, 417 - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE);

    world->finishline = malloc(sizeof(sprite_t));
    init_sprite(world->finishline, 0, -1700, SCREEN_WIDTH, FINISH_LINE_HEIGHT);

    world->vy = INITIAL_SPEED;
    world->make_noise = 0;

    // Initialisation des murs de météorites
    for (int i = 0; i < 10; i++) {
        world->listemur[i] = malloc(sizeof(sprite_t));
    }

    init_walls(world, world->listemur);
}


void play_sound(Mix_Music *son) {
    if (son == NULL) {
        printf("Erreur lors du chargement du son: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(son, 1) == -1) {
        printf("Erreur lors de la lecture du son: %s\n", Mix_GetError());
    }
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->spaceship);
    free(world->finishline);
    for (int i = 0; i < world->nb_mur; i++) {
        free(world->listemur[i]);
    }
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 */

void border_cross(world_t *world){
    //limite à droite
    if (world->spaceship->posx + world->spaceship->w/2 > SCREEN_WIDTH){
        world->spaceship->posx = 0;
    }
    //limite à gauche
    if (world->spaceship->posx + world->spaceship->w/2 < 0){
        world->spaceship->posx = SCREEN_WIDTH - world->spaceship->w/2;
    }
    //print_sprite(world->spaceship);
}

/**
 * \brief La fonction  indique si les deux sprites sp1 et sp2 passés en paramètres sont en collision
 * \param sp1 le premier sprite
 * \param sp2 le deuxième sprite
 * \return 1 si collision ou 0 sinon
 */
int sprites_collide(sprite_t *sp1, sprite_t *sp2){
    if(abs((sp1->posx + sp1->w/2) - (sp2->posx + sp2->w/2)) <= (sp1->w + sp2->w)/2 && abs((sp1->posy + sp1->h/2) - (sp2->posy + sp2->h/2)) <= (sp1->h + sp2->h)/2){
        return 1;
    }
    return 0;
}

void handle_sprites_collision(world_t* world, sprite_t *sp1, sprite_t *sp2){
    if(sprites_collide(sp1, sp2)){
        world->vy = 0;
        world->make_noise =1;
        world->gameover = 1;
    }
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->quit;
}


/**
 * \brief La fonction met à jour les données des murs
 * \param world données du monde
 */
void update_walls(world_t *world) {
    for (int i = 0; i < world->nb_mur; i++) {
        world->listemur[i]->posy += world->vy;
    }
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */
void update_data(world_t *world) {
    world->finishline->posy += world->vy;
    
    border_cross(world);
    update_walls(world);
    for (int i = 0; i < world->nb_mur; i++) {
        handle_sprites_collision(world, world->spaceship, world->listemur[i]);
    }
    if (sprites_collide(world->spaceship, world->finishline) && world->finishtime == 0) {
        world->finishtime = SDL_GetTicks();
    }
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
            world->quit = 1;
        }

        //si une touche est appuyée
        if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est 'ESC'
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->quit = 1;
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