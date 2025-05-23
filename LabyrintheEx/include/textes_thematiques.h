// textes_thematiques.h
#ifndef TEXTES_THEMATIQUES_H
#define TEXTES_THEMATIQUES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_TEXTE_THEMATIQUE 512

typedef struct {
    char introduction[MAX_TEXTE_THEMATIQUE];
    char objectif[MAX_TEXTE_THEMATIQUE];
    char elements[MAX_TEXTE_THEMATIQUE];
    char instructions[MAX_TEXTE_THEMATIQUE];
    char conseil[MAX_TEXTE_THEMATIQUE];
    
    // Textes pour les fragments collectés
    char fragment_vert[MAX_TEXTE_THEMATIQUE];
    char fragment_jaune[MAX_TEXTE_THEMATIQUE];
    char fragment_rouge[MAX_TEXTE_THEMATIQUE];
    char fragment_bleu[MAX_TEXTE_THEMATIQUE];
    char fragment_violet[MAX_TEXTE_THEMATIQUE];
    char fragment_blanc[MAX_TEXTE_THEMATIQUE];
    
    // Texte actuel à afficher
    char* texte_actuel;
    
    // Timer pour changer de texte
    Uint32 timer_affichage;
    int duree_affichage;
    int fragmentsCollectes;
    int totalFragments;
} TextesThematiques;

// Fonction pour initialiser les textes thématiques
void initialiser_textes_thematiques(void);

// Fonction pour afficher le texte thématique dans l'interface
void afficher_textes_thematiques(SDL_Surface* surface);

// Fonction pour changer le texte à afficher
void changer_texte_thematique(const char* cle);

// Fonction pour afficher un texte lié à un fragment collecté
void afficher_texte_fragment(const char* couleur);

// Fonction pour mettre à jour la progression
void mettre_a_jour_progression(int fragmentsCollectes, int totalFragments);

// Fonction de nettoyage pour libérer la mémoire
void liberer_textes_thematiques(void);

// Variable globale pour les textes thématiques
extern TextesThematiques textes_theme;

#endif // TEXTES_THEMATIQUES_H