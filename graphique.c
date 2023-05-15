/**
 * \file graphique.c
 * \author Esteban ROMERA
 * \brief Pour définir les fonctions graphique.
*/

#include "graphique.h"
#include "logique.h"
#include "constante.h"
#include "sdl2-light.h"

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->spaceship);
    clean_texture(textures->finishline);
    clean_texture(textures->meteorite);
}



/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    textures->spaceship = load_image( "ressources/spaceship.bmp",renderer);
    textures->finishline = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/meteorite.bmp",renderer);
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/

void apply_background(SDL_Renderer *renderer, SDL_Texture *texture){
    if(texture != NULL){
      apply_texture(texture, renderer, 0, 0);
    }
}


/**
 * \brief La fonction applique la texture du sprite sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param texture la texture liée au fond
*/
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t* sprite){
    if(texture != NULL){
        apply_texture(texture, renderer, sprite->posx,sprite->posy);
    }
}


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void apply_wall(SDL_Renderer *renderer, SDL_Texture *textures, sprite_t* sprite){
  int x = sprite->posx;
   int y = sprite->posy;
   for(int i =0; i< (sprite->h/METEORITE_SIZE) ; i++){
        for(int j =0; j< (sprite->w/METEORITE_SIZE); j++){
            if(textures != NULL){
	       apply_texture(textures, renderer, x+j*METEORITE_SIZE, y+i*METEORITE_SIZE);
            }
        }
    }

}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);
    if(world->make_disappear == 0){ //s'il n'y a pas de collision avec le mur
        apply_sprite(renderer,textures->spaceship,world->spaceship);
    }
    apply_sprite(renderer,textures->finishline,world->finishline);
    for(int i = 0; i<6; i++){
        apply_wall(renderer,textures->meteorite, world->listemur[i]);
    }
    
    // on met à jour l'écran
    update_screen(renderer);
}