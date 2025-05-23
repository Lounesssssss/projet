#include "joueur.h"
#include "affichage_SDL.h"
#include "themes.h"
#include "textes_thematiques.h"
#include "score.h"


Joueur joueur;

void initialiser_joueur(void) {
    // Position de départ à l'entrée du labyrinthe
    joueur.x = 1;
    joueur.y = 1;
    joueur.taille_case = 10;
    joueur.offset_x = 50;
    joueur.offset_y = 50;
    joueur.a_gagne = false;

    // Initialiser le suivi des fragments
    joueur.fragments_collectes = 0;
    for (int i = 0; i < 6; i++) {
        joueur.fragments_trouves[i] = false;
    }
}

bool deplacer_joueur(int dx, int dy) {
    int nouvelle_x = joueur.x + dx;
    int nouvelle_y = joueur.y + dy;

    printf("Tentative déplacement: (%d,%d) -> (%d,%d)\n", 
           joueur.x, joueur.y, nouvelle_x, nouvelle_y);
    
    // Vérifier si la nouvelle position est valide (pas un mur)
    if(nouvelle_x >= 0 && nouvelle_x < taille_lab && 
       nouvelle_y >= 0 && nouvelle_y < taille_lab) {
       
        printf("Case cible: %d\n", labyrinthe[nouvelle_y][nouvelle_x]);
        
        if(labyrinthe[nouvelle_y][nouvelle_x] != -1) {
            joueur.x = nouvelle_x;
            joueur.y = nouvelle_y;
            
            // Vérifier les fragments à cette position
            verifier_fragments_a_position(nouvelle_x, nouvelle_y);
            
            // Vérifier si le joueur a atteint la sortie
            if(nouvelle_x == taille_lab - 2 && nouvelle_y == taille_lab - 2) {
                joueur.a_gagne = true;
                terminer_partie(); // Terminer la partie et calculer le score
                printf("VICTOIRE!\n");
            }
            
            return true;
        } else {
            // Collision avec un mur - ajouter malus
            ajouter_collision_mur();
        }
    }
    
    return false;
}

void dessiner_joueur(SDL_Surface* surface) {
    // Position à l'écran
    SDL_Rect joueur_rect = {
        joueur.offset_x + joueur.x * joueur.taille_case, 
        joueur.offset_y + joueur.y * joueur.taille_case,
        joueur.taille_case,
        joueur.taille_case
    };
    
    // Couleur du joueur (rouge vif pour être bien visible)
    Uint32 couleur_joueur = SDL_MapRGB(surface->format, 255, 0, 0);
    SDL_FillRect(surface, &joueur_rect, couleur_joueur);
    
    // Ajouter un contour pour plus de visibilité
    SDL_Rect contour = {
        joueur_rect.x - 1,
        joueur_rect.y - 1,
        joueur_rect.w + 2,
        joueur_rect.h + 2
    };
    SDL_FillRect(surface, &contour, 
                SDL_MapRGB(surface->format, 255, 255, 255));
    SDL_FillRect(surface, &joueur_rect, couleur_joueur);
}

// Vérifier les fragments à une position donnée
void verifier_fragments_a_position(int x, int y) {
    // Utiliser les MÊMES positions que dans dessiner_fragments()
    typedef struct {
        int x, y;
        const char* couleur;
    } Position_Fragment;
    
    Position_Fragment fragments[5] = {
        {3, 3, "vert"},                       // Fragment vert
        {taille_lab/2, taille_lab/2, "jaune"}, // Fragment jaune
        {taille_lab/3, 2*taille_lab/3, "bleu"}, // Fragment bleu
        {2*taille_lab/3, taille_lab/3, "violet"}, // Fragment violet
        {taille_lab-5, taille_lab-5, "blanc"}  // Fragment blanc
    };
    
    // Vérifier si le joueur est sur un fragment
    for (int i = 0; i < 5; i++) {
        if (x == fragments[i].x && y == fragments[i].y) {
            collecter_fragment(fragments[i].couleur);
        }
    }
}

// Collecter un fragment
void collecter_fragment(const char* couleur) {
    int index = -1;
    
    if (strcmp(couleur, "rouge") == 0) index = 0;
    else if (strcmp(couleur, "vert") == 0) index = 1;
    else if (strcmp(couleur, "jaune") == 0) index = 2;
    else if (strcmp(couleur, "bleu") == 0) index = 3;
    else if (strcmp(couleur, "violet") == 0) index = 4;
    else if (strcmp(couleur, "blanc") == 0) index = 5;
    
    if (index >= 0 && !joueur.fragments_trouves[index]) {
        joueur.fragments_trouves[index] = true;
        joueur.fragments_collectes++;
        
        // Ajouter les points au score
        ajouter_points_fragment(couleur);
        
        // Afficher le texte thématique pour ce fragment
        afficher_texte_fragment(couleur);
        
        // Mettre à jour la progression
        mettre_a_jour_progression(joueur.fragments_collectes, 6);
        
        printf("Fragment %s collecté! Total: %d/6\n", couleur, joueur.fragments_collectes);
    }
}

// Vérifier si un fragment est collecté
bool fragment_est_collecte(const char* couleur) {
    int index = -1;
    
    // Si c'est une chaîne de caractères
    if (couleur) {
        if (strcmp(couleur, "rouge") == 0) index = 0;
        else if (strcmp(couleur, "vert") == 0) index = 1;
        else if (strcmp(couleur, "jaune") == 0) index = 2;
        else if (strcmp(couleur, "bleu") == 0) index = 3;
        else if (strcmp(couleur, "violet") == 0) index = 4;
        else if (strcmp(couleur, "blanc") == 0) index = 5;
    }
    
    return (index >= 0 && index < 6) ? joueur.fragments_trouves[index] : false;
}

// Obtenir le nombre de fragments collectés
int obtenir_nombre_fragments_collectes(void) {
    return joueur.fragments_collectes;
}

bool verifier_victoire(void) {
    return joueur.a_gagne;
}