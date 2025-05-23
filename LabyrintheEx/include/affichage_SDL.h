#ifndef AFFICHAGE_SDL_H
#define AFFICHAGE_SDL_H

#include <SDL2/SDL.h>

#define taille_f 51
#define LARGEUR_FENETRE 1200
#define HAUTEUR_FENETRE 800

extern SDL_Window *ecran;
extern SDL_Surface *SurfaceBg;
extern SDL_Surface *windowSurface;
extern SDL_Surface *surfaceMur[taille_f][taille_f];

// Fonctions d'affichage
void initFenetre(void);
void affiche_lab(int labyrinthe[taille_f][taille_f]);
void affiche_solution(int labyrinthe[taille_f][taille_f]);
void dessiner_lettre(char lettre, int x, int y, SDL_Color couleur);
void dessiner_texte(const char* texte, int x, int y, SDL_Color couleur);
// Nouvelle fonction pour dessiner les fragments d'histoire
void dessiner_fragments(void);

#endif