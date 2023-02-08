/*
jeu.c
------------

Par OUHAMMI Karim

Rôle: les fonctions de gestion du jeu lui-même
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeu.h"


int jouer(SDL_Surface* ecran, int level){
    SDL_Surface *mario[4] = {NULL};
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL, *background = NULL;
    SDL_Rect position, positionJoueur, positionHelp;
    SDL_Event event;

    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    //Sprites
    background = IMG_Load("images/bgPlay.jpg");
    mur = IMG_Load("images/mur.jpg");
    caisse = IMG_Load("images/caisse.png");
    caisseOK = IMG_Load("images/caisse_ok.png");
    objectif = IMG_Load("images/objectif.png");
    mario[BAS] = IMG_Load("images/mario_bas.gif");
    mario[HAUT] = IMG_Load("images/mario_haut.gif");
    mario[DROITE] = IMG_Load("images/mario_droite.gif");
    mario[GAUCHE] = IMG_Load("images/mario_gauche.gif");
    marioActuel = mario[BAS];



    if(!chargerNiveau(carte, level))
        exit(EXIT_FAILURE);

    // Recuperation de la position initiale de MARIO.
    for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){
            if(carte[i][j] == MARIO){
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    SDL_EnableKeyRepeat(100, 100);

    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                level = -1;
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        level = 0;
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        marioActuel = mario[HAUT];
                        deplacerJoueur(carte, &positionJoueur, HAUT);
                        break;
                    case SDLK_DOWN:
                        marioActuel = mario[BAS];
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;
                    case SDLK_RIGHT:
                        marioActuel = mario[DROITE];
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;
                    case SDLK_LEFT:
                        marioActuel = mario[GAUCHE];
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;
                    case SDLK_r:
                        continuer = 0;
                        break;
                }
                break;
        }

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(background, NULL, ecran, &position);

        objectifsRestants = 0;

        for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
            for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j]){
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        objectifsRestants = 1;
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                }
            }
        }

        if(!objectifsRestants){
            level = next(ecran, level);
            continuer = 0;
        }


        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);

        SDL_Flip(ecran);
    }

    // Désactivation de la répétition des touches (remise à 0)
    SDL_EnableKeyRepeat(0, 0);
    //Libiration des Surfaces
    SDL_FreeSurface(background);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    for(i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(mario[i]);

    return level;
} // Jouer()

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction){
    switch(direction){
        case HAUT:
            if(pos->y - 1 < 0)
                break;
            if(carte[pos->x][pos->y - 1] == MUR)
                break;
            if((carte[pos->x][pos->y-1]==CAISSE||carte[pos->x][pos->y-1]==CAISSE_OK)&&(pos->y-2<0||carte[pos->x][pos->y-2]==MUR||carte[pos->x][pos->y-2]==CAISSE||carte[pos->x][pos->y-2]==CAISSE_OK))
                break;
            deplacerCaisse(&carte[pos->x][pos->y-1], &carte[pos->x][pos->y-2]);
            pos->y--;
            break;
        case BAS:
            if(pos->y + 1 >= NB_BLOCS_HAUTEUR)
                break;
            if(carte[pos->x][pos->y + 1] == MUR)
                break;
            if((carte[pos->x][pos->y+1]==CAISSE||carte[pos->x][pos->y+1]==CAISSE_OK)&&(pos->y+2>=NB_BLOCS_HAUTEUR||carte[pos->x][pos->y+2]==MUR||carte[pos->x][pos->y+2]==CAISSE||carte[pos->x][pos->y+2]==CAISSE_OK))
                break;
            deplacerCaisse(&carte[pos->x][pos->y+1], &carte[pos->x][pos->y+2]);
            pos->y++;
            break;
        case DROITE:
            if(pos->x + 1 >= NB_BLOCS_LARGEUR)
                break;
            if(carte[pos->x+1][pos->y] == MUR)
                break;
            if((carte[pos->x+1][pos->y]==CAISSE||carte[pos->x+1][pos->y]==CAISSE_OK)&&(pos->x+2>=NB_BLOCS_LARGEUR||carte[pos->x+2][pos->y]==MUR||carte[pos->x+2][pos->y]==CAISSE||carte[pos->x+2][pos->y]==CAISSE_OK))
                break;
            deplacerCaisse(&carte[pos->x+1][pos->y], &carte[pos->x+2][pos->y]);
            pos->x++;
            break;
        case GAUCHE:
            if(pos->x - 1 < 0)
                break;
            if(carte[pos->x-1][pos->y] == MUR)
                break;
            if((carte[pos->x-1][pos->y]==CAISSE||carte[pos->x-1][pos->y]==CAISSE_OK)&&(pos->x-2<0||carte[pos->x-2][pos->y]==MUR||carte[pos->x-2][pos->y]==CAISSE||carte[pos->x-2][pos->y]==CAISSE_OK))
                break;
            deplacerCaisse(&carte[pos->x-1][pos->y], &carte[pos->x-2][pos->y]);
            pos->x--;
            break;
    }
} // deplacerJoueur()

void deplacerCaisse(int *premiereCase, int *secondeCase){
    if(*premiereCase == CAISSE || *premiereCase == CAISSE_OK){
        if(*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;

        if(*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
} // deplacerCaisse()
