/*
editeur.c
------------

Par OUHAMMI Karim

Rôle: les fonctions de mode editeur
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "editeur.h"

int editeur(SDL_Surface* ecran){
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL, *caisseOK = NULL, *background = NULL;
    SDL_Rect position, positionEditeur;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    int marioExiste = 0;
    int tabMolette[] = {MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};
    int quit = 1;

    //Sprites
    background = IMG_Load("images/bgEditor.jpg");
    mur = IMG_Load("images/mur.jpg");
    caisse = IMG_Load("images/caisse.png");
    caisseOK = IMG_Load("images/caisse_ok.png");
    objectif = IMG_Load("images/objectif.png");
    mario = IMG_Load("images/mario_bas.gif");

    if(!chargerNiveau(carte, 0))
        exit(EXIT_FAILURE);

    // Boucle PRINCIPALE
    while(continuer){
        SDL_WaitEvent(&event);
        marioExiste = 0;
        switch(event.type){
            case SDL_QUIT:
                quit = 0;
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y < TAILLE_BLOC * NB_BLOCS_HAUTEUR){
                    if(event.button.button == SDL_BUTTON_LEFT){
                        if(carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] == OBJECTIF && objetActuel == CAISSE)
                            carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = CAISSE_OK;
                        else if(objetActuel == MARIO){
                            for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
                                for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
                                    if(carte[i][j] == MARIO)
                                        marioExiste = 1;
                            if(!marioExiste)
                                carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = MARIO;
                        }
                        else
                            carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                        clicGaucheEnCours = 1;
                    }
                    else if(event.button.button == SDL_BUTTON_RIGHT){
                        carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
                        clicDroitEnCours = 1;
                    }
                }
                //Gestion des evenement de la molette
                if(event.button.button == SDL_BUTTON_WHEELUP){
                    objetActuel = gestionMoletteUp(objetActuel, tabMolette);
                }
                if(event.button.button == SDL_BUTTON_WHEELDOWN){
                    objetActuel = gestionMoletteDown(objetActuel, tabMolette);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if(event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                positionEditeur.x = event.motion.x + 10;
                positionEditeur.y = event.motion.y + 20;
                if(event.motion.y < TAILLE_BLOC * NB_BLOCS_HAUTEUR){
                    if(clicGaucheEnCours){
                        if(objetActuel != MARIO)
                            carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                    }
                    else if(clicDroitEnCours)
                        carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_l:
                        chargerNiveau(carte, 0);
                        break;
                }
                break;
        } // Fin waitevent !

        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(background, NULL, ecran, &position);

        for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
            for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j]){
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        if(carte[i][j] == OBJECTIF)
                            SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        else
                            SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                    case MARIO:
                        SDL_BlitSurface(mario, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                }
            }
        }

        for( i = 0 ; i < 5 ; i++){
            position.x = positionEditeur.x;
            position.y = positionEditeur.y + i * TAILLE_BLOC;
            switch(tabMolette[i]){
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
                    SDL_BlitSurface(objectif, NULL, ecran, &position);
                    break;
                case MARIO:
                    SDL_BlitSurface(mario, NULL, ecran, &position);
                    break;
            }
        }

        SDL_Flip(ecran);
    } // Boucle PRINCIPALE

    SDL_FreeSurface(background);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);

    return quit;
}

int gestionMoletteUp(int objetActuel, int tabMolette[]){
    int i = 0;

    if(objetActuel == 5)
        tabMolette[0] = 1;
    else
        tabMolette[0] = objetActuel + 1;

    for(i = 1 ; i < 5 ; i++){
        if(tabMolette[0] + i <= 5)
            tabMolette[i] = tabMolette[0] + i;
        else
            tabMolette[i] = (tabMolette[0] + i) % 5;
    }
    return tabMolette[0];
}

int gestionMoletteDown(int objetActuel, int tabMolette[]){
    int i = 0;

    if(objetActuel == 1)
        tabMolette[0] = 5;
    else
        tabMolette[0] = objetActuel - 1;

    for(i = 1 ; i < 5 ; i++){
        if(tabMolette[0] + i <= 5)
            tabMolette[i] = tabMolette[0] + i;
        else
            tabMolette[i] = (tabMolette[0] + i) % 5;
    }
    return tabMolette[0];
}
