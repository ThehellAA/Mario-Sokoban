/*
main.c
------------

Par OUHAMMI Karim

Rôle: la fonction principal (main) du jeu
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

int main(int argc, char** argv){
    int continuer = 1, level = 0, button = 0;
    SDL_Surface *ecran = NULL, *background = NULL, *bgPlay = NULL, *bgEditor = NULL;
    SDL_Rect position;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetIcon(IMG_Load("images/icon.ico"), NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban", NULL);

    continuer = animation(ecran);

    background = IMG_Load("images/background.jpg");
    bgPlay = IMG_Load("images/background_button_play.jpg");
    bgEditor = IMG_Load("images/background_button_editor.jpg");

    position.x = 0;
    position.y = 0;

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(event.button.x >= 16 && event.button.x <= 126 && event.button.y >= 426 && event.button.y <= 485){
                        level = selectLevel(ecran);
                        if(level == -1)
                            continuer = 0;
                        else if(level >= 1){
                            do{
                                level = jouer(ecran, level);
                                if(level == -1)
                                    continuer = 0;
                                else if(level == 0)
                                    break;
                            }while(continuer > 0);
                        }
                    }
                    else if(event.button.x >= 16 && event.button.x <= 274 && event.button.y >= 465 && event.button.y <= 497)
                        continuer = editeur(ecran);
                }
                break;
            case SDL_MOUSEMOTION:
                if(event.motion.x >= 16 && event.motion.x <= 126 && event.motion.y >= 426 && event.motion.y <= 485)
                    button = 1;
                else if(event.motion.x >= 16 && event.motion.x <= 274 && event.motion.y >= 465 && event.motion.y <= 497)
                    button = 2;
                else
                    button = 0;
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(background, NULL, ecran, &position);
        if(button == 1)
            SDL_BlitSurface(bgPlay, NULL, ecran, &position);
        if(button == 2)
            SDL_BlitSurface(bgEditor, NULL, ecran, &position);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(background);
    SDL_FreeSurface(bgPlay);
    SDL_FreeSurface(bgEditor);
    SDL_Quit();

    return EXIT_SUCCESS;
}
