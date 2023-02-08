/*
animation.c
------------

Par OUHAMMI Karim

Rôle: création du gif d'intro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "animation.h"

int animation(SDL_Surface* ecran){
    SDL_Surface *background = NULL, *help[48] = {NULL};
    SDL_Rect position, positionHelp;
    SDL_Event event;
    int continuer = 1, i = 0, tempsAct = 0, tempsPrec = 0, quit = 1;

    background = IMG_Load("images/bgAnimation.jpg");

    help[0] = IMG_Load("images/1.jpg");
    help[1] = IMG_Load("images/2-0.jpg");
    help[2] = IMG_Load("images/2-1.jpg");
    help[3] = IMG_Load("images/2-2.jpg");
    help[4] = IMG_Load("images/2-3.jpg");
    help[5] = IMG_Load("images/2-4.jpg");
    help[6] = IMG_Load("images/2-5.jpg");
    help[7] = IMG_Load("images/2-6.jpg");
    help[8] = IMG_Load("images/2-7.jpg");
    help[9] = IMG_Load("images/2-8.jpg");
    help[10] = IMG_Load("images/2-9.jpg");
    help[11] = IMG_Load("images/2-10.jpg");
    help[12] = IMG_Load("images/2-11.jpg");
    help[13] = IMG_Load("images/2-12.jpg");
    help[14] = IMG_Load("images/2-13.jpg");
    help[15] = IMG_Load("images/2-14.jpg");
    help[16] = IMG_Load("images/2-15.jpg");
    help[17] = IMG_Load("images/2-16.jpg");
    help[18] = IMG_Load("images/2-17.jpg");
    help[19] = IMG_Load("images/2-18.jpg");
    help[20] = IMG_Load("images/2-19.jpg");
    help[21] = IMG_Load("images/2-20.jpg");
    help[22] = IMG_Load("images/2-21.jpg");
    help[23] = IMG_Load("images/2-22.jpg");
    help[24] = IMG_Load("images/2-23.jpg");
    help[25] = IMG_Load("images/2-24.jpg");
    help[26] = IMG_Load("images/2-25.jpg");
    help[27] = IMG_Load("images/2-26.jpg");
    help[28] = IMG_Load("images/2-27.jpg");
    help[29] = IMG_Load("images/3.jpg");
    help[30] = IMG_Load("images/4.jpg");
    help[31] = IMG_Load("images/5.jpg");
    help[32] = IMG_Load("images/6.jpg");
    help[33] = IMG_Load("images/7.jpg");
    help[34] = IMG_Load("images/8.jpg");
    help[35] = IMG_Load("images/8.jpg");
    help[36] = IMG_Load("images/9-0.jpg");
    help[37] = IMG_Load("images/9-1.jpg");
    help[38] = IMG_Load("images/9-2.jpg");
    help[39] = IMG_Load("images/9-3.jpg");
    help[40] = IMG_Load("images/9-4.jpg");
    help[41] = IMG_Load("images/9-5.jpg");
    help[42] = IMG_Load("images/9-6.jpg");
    help[43] = IMG_Load("images/9-7.jpg");
    help[44] = IMG_Load("images/9-8.jpg");
    help[45] = IMG_Load("images/9-9.jpg");
    help[46] = IMG_Load("images/9-10.jpg");
    help[47] = IMG_Load("images/9-11.jpg");

    position.x = 0;
    position.y = 0;
    positionHelp.x = 51;
    positionHelp.y = 169;

    while(continuer){
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = 0;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                continuer = 0;
                break;
        }

        tempsAct = SDL_GetTicks();
        if(tempsAct - tempsPrec > 150 && i < 48){
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            SDL_BlitSurface(background, NULL, ecran, &position);
            SDL_BlitSurface(help[i], NULL, ecran, &positionHelp);
            tempsPrec = tempsAct;
            i++;
        }
        if(i >= 48) SDL_BlitSurface(help[47], NULL, ecran, &positionHelp);

        SDL_Flip(ecran);
    }

    for(i = 0 ; i < 48 ; i++)
        SDL_FreeSurface(help[i]);
    SDL_FreeSurface(background);

    return quit;
}
