/**
 * \file graphique.c
 * \author Esteban ROMERA
 * \brief Pour définir les fonctions graphique.
*/

#include "graphique.h"
#include "logique.h"
#include "constante.h"
#include "sdl2-light.h"
#include "sdl2-ttf-light.h"

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/
void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->spaceship);
    clean_texture(textures->finishline);
    clean_texture(textures->meteorite);
    clean_font(textures->font);
    Mix_FreeMusic(textures->point); // Libérer la musique chargée
    Mix_CloseAudio(); // Fermer SDL_mixer
}

/**
 * \brief La fonction initialise les textures nécessaires à l'affichage graphique du jeu
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/
void init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/background.bmp",renderer);
    textures->spaceship = load_image( "ressources/dino.bmp",renderer);
    textures->finishline = load_image( "ressources/finish_line.bmp",renderer);
    textures->meteorite = load_image( "ressources/cactus.bmp",renderer);
    textures->font = load_font("ressources/arial.ttf", 14);
    textures->point = Mix_LoadMUS("ressources/point.mp3");
    textures->die = Mix_LoadMUS("ressources/die.mp3");
    textures->jump = Mix_LoadMUS("ressources/jump.mp3");

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
 * \brief 
 * \param 
*/
void time_counter(SDL_Renderer *renderer, world_t* world,textures_t *textures){
    static int x = 0;
    if(world->finishtime != 0){
        x = 1;
    }
    if (world->gameover == 0) {
        // Afficher le temps écoulé en haut à gauche de l'écran
        char time_str[20];
        Uint32 current_time = SDL_GetTicks();
        
        if(x ==1){
            current_time -= 3000; // on enlève le temps passé à l'arret
        }
        if(world->finishtime == 0){
            float elapsed_seconds = current_time / 1000.0f;
            sprintf(time_str, "Time: %.2f s", elapsed_seconds);
            apply_text(renderer, 10, 10, 200, 30, time_str, textures->font);
        }
    }
}

/**
 * \brief 
 * \param world les données du monde
 * \return 
 */
void end_game(world_t *world, SDL_Renderer *renderer, textures_t *textures) {
    static int audio_point = 0;
    static int audio_die = 0;

    if ((world->gameover == 1 || world->finishtime != 0) && world->closing_time == 0) {
        world->closing_time = SDL_GetTicks();
    }
    
    if (world->gameover == 1) {
        if(audio_die == 0){
            play_sound(textures->die);
            audio_die++;
        }
        char msg_gameover[20];
        sprintf(msg_gameover, "You lost !");
        apply_text(renderer, 45, 140, 210, 60, msg_gameover, textures->font);
    }
    
    if (world->finishtime != 0) {
        float elapsed_seconds = (world->finishtime) / 1000.0f;
        if(audio_point == 0){
            play_sound(textures->point);
            audio_point++;
        }
        // Afficher le message de fin avec le temps écoulé
        char msg_finish[40];
        sprintf(msg_finish, "You finished in %.2f s !", elapsed_seconds);
        apply_text(renderer, 45, 140, 210, 60, msg_finish, textures->font);
    }
}

/**
 * \brief 
 * \param world données du monde
 */
void check_closing_time(world_t *world, textures_t *textures) {

    if (world->closing_time != 0) {
        Uint32 current_time = SDL_GetTicks();
        Uint32 elapsed_time = current_time - world->closing_time;
        world->vy = 0;


        // Définir la durée souhaitée avant de fermer l'application (ici 3 secondes)
        Uint32 closing_duration = 3000;  // 3 secondes
        if (elapsed_time >= closing_duration) {
            if(world->gameover == 1){
                exit(0);
            }
            // Fermer l'application
            world->finishtime = 0;
            world->vy = INITIAL_SPEED;
            world->finishline->posy = -4050;
            world->closing_time = 0;
        }
    }
}

/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer le renderer lié à l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */
void apply_walls(SDL_Renderer *renderer, SDL_Texture *textures, sprite_t* sprite){
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
    int x = 0;

    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures->background);
    if(world->make_noise == 0){ //s'il n'y a pas de collision avec le mur
        apply_sprite(renderer,textures->spaceship,world->spaceship);
    }
    apply_sprite(renderer,textures->finishline,world->finishline);
    for(int i = 0; i< world->nb_mur; i++){
        apply_walls(renderer,textures->meteorite, world->listemur[i]);
        if(world->spaceship->posy < world->listemur[i]->posy && world->spaceship->posy + INITIAL_SPEED > world->listemur[i]->posy && x == 0){
            play_sound(textures->jump);
            x = i;
        }
    }
    
    time_counter(renderer, world, textures);
    end_game(world, renderer, textures);

    //verification de la fermeture du jeu
    check_closing_time(world, textures);    

    // on met à jour l'écran
    update_screen(renderer);
}