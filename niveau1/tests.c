/**
 * \file tests.c
 * \author Esteban ROMERA
 * \brief Fichier d'en tete pour le module de test.
*/

#include "module_logique.h"
#include "constante.h"
#include "sdl2-light.h"

/**
 *  \brief fonction qui initialise et affiche un sprite donné en paramètre avec les fonctions init_sprite et print_sprite
*/
void test_init_sprite_param(sprite_t *sprite, int x, int y, int w, int h){
    init_sprite(world->sprite, x, y, w, h);
    print_sprite(sprite);
}

/**
 *  \brief fonction principale en charge de lancer les tests
*/
int main( int argc, char* args[] ){
    world->sprite = malloc(sizeof(sprite_t));
    test_init_sprite_param();
    return 0;
}
