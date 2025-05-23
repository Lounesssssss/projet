#ifndef JOUEUR_H
#define JOUEUR_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "generateur_labyrinthe.h"

typedef struct {
    int x, y;           // Position dans le labyrinthe
    int taille_case;    // Taille d'une case
    int offset_x;       // Décalage X du labyrinthe
    int offset_y;       // Décalage Y du labyrinthe
    bool a_gagne;       // Si le joueur a atteint la sortie

    int fragments_collectes;
    bool fragments_trouves[6]; // rouge, vert, jaune, bleu, violet, blanc    
} Joueur;

extern Joueur joueur;

// Initialise le joueur à la position de départ
void initialiser_joueur(void);

// Déplace le joueur si possible
bool deplacer_joueur(int dx, int dy);

// Dessine le joueur
void dessiner_joueur(SDL_Surface* surface);

// Vérifie et collecte les fragments à la position actuelle
void verifier_fragments_a_position(int x, int y);

// Collecte un fragment spécifique
void collecter_fragment(const char* couleur);

// Vérifie si un fragment spécifique a été collecté
bool fragment_est_collecte(const char* couleur);

// Retourne le nombre de fragments collectés
int obtenir_nombre_fragments_collectes(void);

// Vérifie si le joueur a gagné (atteint la sortie)
bool verifier_victoire(void);

#endif