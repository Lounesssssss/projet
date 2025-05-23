#ifndef THEMES_H
#define THEMES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define NB_THEMES 6
#define MAX_DESCRIPTION 300
#define MAX_NOM 50
#define MAX_ELEMENTS 200

typedef struct {
    char nom[MAX_NOM];
    SDL_Color couleur_mur;
    SDL_Color couleur_chemin;
    SDL_Color couleur_fond;
    SDL_Color couleur_texte;
    SDL_Color couleur_accent;
    char description[MAX_DESCRIPTION];
    char elements[MAX_ELEMENTS];
    
    // Fonctions spécifiques au thème
    void (*initialiser_theme)(void);
    void (*rendre_theme)(void);
    void (*traiter_evenements_theme)(SDL_Event*);
    
    // Zone cliquable et état
    SDL_Rect zone_selection;
    bool selectionne;
} Theme;

typedef struct {
    int x, y;
    int type; // 0=item, 1=enemy, 2=exit, 3=special
    char nom[50];
    char description[150];
    bool decouvert;
    SDL_Color couleur;
} PointInteret;

typedef struct {
    int x, y;
    float opacity;
    float speed;
} EffetParticule;

extern Theme themes[NB_THEMES];
extern int theme_actuel;
extern PointInteret points_interet[20];
extern int nb_points_interet;
extern EffetParticule particules[100];
extern int nb_particules;

// Fonctions de gestion des thèmes
void initialiser_themes(void);
void changer_theme(int index);
void afficher_selecteur_themes(void);
bool traiter_clic_selecteur_themes(int x, int y);
void adapter_labyrinthe_au_theme(void);

// Fonctions de rendu thématique
void afficher_icone_theme(int index);
void dessiner_representation_theme(int index);
void afficher_apercu_theme(int index);
void afficher_mini_labyrinthe_theme(int index);

// Fonctions spécifiques par thème - initialisation
void initialiser_theme_odyssee(void);
void initialiser_theme_tron(void);
void initialiser_theme_gotham(void);
void initialiser_theme_tetris(void);
void initialiser_theme_avatar(void);
void initialiser_theme_totoro(void);

// Fonctions spécifiques par thème - rendu
void rendre_theme_odyssee(void);
void rendre_theme_tron(void);
void rendre_theme_gotham(void);
void rendre_theme_tetris(void);
void rendre_theme_avatar(void);
void rendre_theme_totoro(void);

// Fonctions spécifiques par thème - événements
void traiter_evenements_odyssee(SDL_Event* event);
void traiter_evenements_tron(SDL_Event* event);
void traiter_evenements_gotham(SDL_Event* event);
void traiter_evenements_tetris(SDL_Event* event);
void traiter_evenements_avatar(SDL_Event* event);
void traiter_evenements_totoro(SDL_Event* event);

// Fonctions d'aperçu par thème
void dessiner_apercu_odyssee(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);
void dessiner_apercu_tron(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);
void dessiner_apercu_gotham(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);
void dessiner_apercu_tetris(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);
void dessiner_apercu_avatar(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);
void dessiner_apercu_totoro(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent);

void afficher_points_interet_demo(int index, int offset_x, int offset_y, int taille_case);
void afficher_icone_theme_avec_nom(int index);
void dessiner_representation_theme_reduite(int index);

// Fonctions d'effets spéciaux
void ajouter_particule(int x, int y, int type);
void mettre_a_jour_particules(void);
void dessiner_particules(void);
void ajouter_point_interet(int x, int y, int type, const char* nom, const char* description, SDL_Color couleur);
void afficher_points_interet_demo(int index, int offset_x, int offset_y, int taille_case);

#endif