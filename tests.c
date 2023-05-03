/**
 * \file tests.c
 * \author Esteban ROMERA
 * \brief Fichier d'en tete pour le module de test.
*/

#include "logique.h"
#include "constante.h"
#include "sdl2-light.h"

/**
 *  \brief fonction qui initialise et affiche un sprite donné en paramètre avec les fonctions init_sprite et print_sprite
*/
void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h){
    init_sprite(sprite, x, y, w, h);
    print_sprite(sprite);
}

void test_init_sprite(){
    world_t *world = malloc(sizeof(world));
    world->spaceship = malloc(sizeof(sprite_t));
    test_init_sprite_param(world->spaceship ,(SCREEN_WIDTH - SHIP_SIZE)/2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE,SHIP_SIZE);
    test_init_sprite_param(world->spaceship ,0, 0, 20,20);
    test_init_sprite_param(world->spaceship , 10-10,0-10,10,10);
    test_init_sprite_param(world->spaceship ,10,10, -2, 2);
    //clean_data(world);
}

/**
 *  \brief fonction qui initialise et affiche un sprite donné en paramètre avec les fonctions init_sprite et print_sprite
*/
void test_sprites_collide_param(sprite_t *sp1, sprite_t *sp2, int x, int y, int w, int h, int x2, int y2, int w2, int h2){
    init_sprite(sp1, x, y, w, h);
    init_sprite(sp2, x2, y2, w2, h2);
    printf("collision ? %d\n",sprites_collide(sp1,sp2));
}

void test_sprites_collide(){
    world_t *world = malloc(sizeof(world));
    world->spaceship = malloc(sizeof(sprite_t));
    world->mur = malloc(sizeof(sprite_t));
    test_sprites_collide_param(world->spaceship, world->mur, 50,50,10,10,50,50,10,10);
    test_sprites_collide_param(world->spaceship, world->mur, 50,50,10,20,150,50,20,10);
    //clean_data(world);
}

/**
 *  \brief fonction principale en charge de lancer les tests
*/
int main( int argc, char* args[] ){
    test_init_sprite();
    test_sprites_collide();
       
    return 0;
}
