/*
select.c
------------

Par OUHAMMI Karim

Rôle: la gestion de selection du niveau
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "select.h"

int selectLevel(SDL_Surface* ecran){
    SDL_Surface* bgLvl = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1, level = 0, i = 0, j = 0;

    bgLvl = IMG_Load("images/bgLvl.jpg");

    position.x = 0;
    position.y = 0;

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                level = -1;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                for(i = 0 ; i < 5 ; i++){
                    for(j = 0 ; j < 5 ; j++){
                        if(event.button.x >= 87+34*j+16*j && event.button.x <= 87+34*j+16*j+34 && event.button.y >= 87+34*i+16*i && event.button.y <= 87+34*i+16*i+34){
                            level = i * 5 + j + 1;
                            continuer = 0;
                        }
                    }
                }
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(bgLvl, NULL, ecran, &position);
        SDL_Flip(ecran);

    }

    SDL_FreeSurface(bgLvl);

    return level;
}
