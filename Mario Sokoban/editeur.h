/*
editeur.h
------------

Par OUHAMMI Karim

Rôle: les prototypes des fonction d'editeur.c
*/

#ifndef DEF_EDITEUR
#define DEF_EDITEUR

int editeur(SDL_Surface* ecran);
int gestionMoletteUp(int objetActuel, int tabMolette[]);
int gestionMoletteDown(int objetActuel, int tabMolette[]);

#endif // DEF_EDITEUR
