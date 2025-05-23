// score.h
#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    int score_actuel;
    int fragments_collectes;
    int temps_debut;
    int temps_fin;
    int bonus_temps;
    int bonus_theme;
    int malus_collisions;
    int collisions_murs;
    bool partie_terminee;
    int meilleur_score;
} ScoreJeu;

// Variable globale du score
extern ScoreJeu score_jeu;

// Fonctions de gestion du score
void initialiser_score(void);
void commencer_partie(void);
void terminer_partie(void);
void ajouter_points_fragment(const char* couleur);
void ajouter_collision_mur(void);
void calculer_score_final(void);
void sauvegarder_meilleur_score(void);
void charger_meilleur_score(void);
void afficher_score(SDL_Surface* surface);
void afficher_score_final(SDL_Surface* surface);

#endif // SCORE_H