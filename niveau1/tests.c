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
}

/**
 *  \brief fonction principale en charge de lancer les tests
*/
int main( int argc, char* args[] ){
    
    test_init_sprite();
    return 0;
}
