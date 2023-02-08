/*
next.c
------------

Par OUHAMMI Karim

Rôle: la gestion de fin du parti 
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "next.h"

int next(SDL_Surface* ecran, int level){
    SDL_Surface *next = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1;

    next = IMG_Load("images/next.png");
    position.x = (TAILLE_BLOC*NB_BLOCS_LARGEUR)/2 - (next->w)/2;
    position.y = (TAILLE_BLOC*NB_BLOCS_HAUTEUR)/2 - (next->h)/2;;

    SDL_BlitSurface(next, NULL, ecran, &position);
    SDL_Flip(ecran);

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                level = -1;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    level = 0;
                    continuer = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.x >= position.x + 63 && event.button.x <= position.x + 88 && event.button.y >= position.y + 52 && event.button.y <= position.y + 77){
                    if(level != 1)
                        level--;
                    continuer = 0;
                }
                if(event.button.x >= position.x + 103 && event.button.x <= position.x + 128 && event.button.y >= position.y + 52 && event.button.y <= position.y + 77){
                    continuer = 0;
                }
                if(event.button.x >= position.x + 143 && event.button.x <= position.x + 168 && event.button.y >= position.y + 52 && event.button.y <= position.y + 77){
                    level++;
                    continuer = 0;
                }
                break;
        }
    }

    return level;
}
