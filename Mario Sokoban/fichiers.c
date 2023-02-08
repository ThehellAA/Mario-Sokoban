/*
fichiers.c
------------

Par OUHAMMI Karim

Rôle: les fonctions de gestion des fichiers de niveau
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int lvl){
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 10] = {0};
    int i = 0, j = 0;

    if( lvl == 0)
        fichier = fopen("mesNiveaux.txt", "r");
    else
        fichier = fopen("niveaux.txt", "r");

    if(fichier == NULL)
        return 0;

    if(lvl == 0)
        fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 10, fichier);
    else
        for(i = 0 ; i < lvl ; i++)
            fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 10, fichier);

    for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++){
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++){
            switch(ligneFichier[(i * NB_BLOCS_LARGEUR) + j]){
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
                case '5':
                    niveau[j][i] = 5;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]){
    FILE* fichier = NULL;
    int i = 0, j = 0;

    fichier = fopen("mesNiveaux.txt", "w");

    if(fichier == NULL)
        return 0;

    for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            fprintf(fichier, "%d", niveau[j][i]);

    fclose(fichier);
    return 1;
}
