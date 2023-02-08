/*
jeu.h
------------

Par OUHAMMI Karim

Rôle: les prototypes des fonctions de jeu.c
*/

#ifndef DEF_JEU
#define DEF_JEU

int jouer(SDL_Surface* ecran, int level);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);

#endif // DEF_JEU
