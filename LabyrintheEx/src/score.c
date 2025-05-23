// score.c
#include "score.h"
#include "affichage_SDL.h"
#include "themes.h"
#include <stdio.h>
#include <time.h>

// Variable globale du score
ScoreJeu score_jeu;

// Valeurs des points selon les fragments
int points_fragments[6] = {
    50,   // Rouge (joueur) - pas utilisé normalement
    100,  // Vert (origine)
    200,  // Jaune (clé)
    75,   // Bleu (secondaire)
    75,   // Violet (secondaire)
    300   // Blanc (portail)
};

void initialiser_score(void) {
    score_jeu.score_actuel = 0;
    score_jeu.fragments_collectes = 0;
    score_jeu.temps_debut = 0;
    score_jeu.temps_fin = 0;
    score_jeu.bonus_temps = 0;
    score_jeu.bonus_theme = 0;
    score_jeu.malus_collisions = 0;
    score_jeu.collisions_murs = 0;
    score_jeu.partie_terminee = false;
    
    // Charger le meilleur score sauvegardé
    charger_meilleur_score();
    
    printf("Score initialisé. Meilleur score: %d\n", score_jeu.meilleur_score);
}

void commencer_partie(void) {
    // Réinitialiser pour une nouvelle partie
    score_jeu.score_actuel = 0;
    score_jeu.fragments_collectes = 0;
    score_jeu.temps_debut = SDL_GetTicks();
    score_jeu.temps_fin = 0;
    score_jeu.bonus_temps = 0;
    score_jeu.bonus_theme = 0;
    score_jeu.malus_collisions = 0;
    score_jeu.collisions_murs = 0;
    score_jeu.partie_terminee = false;
    
    printf("Nouvelle partie commencée !\n");
}

void terminer_partie(void) {
    score_jeu.temps_fin = SDL_GetTicks();
    score_jeu.partie_terminee = true;
    
    calculer_score_final();
    
    // Vérifier si c'est un nouveau record
    if (score_jeu.score_actuel > score_jeu.meilleur_score) {
        score_jeu.meilleur_score = score_jeu.score_actuel;
        sauvegarder_meilleur_score();
        printf("NOUVEAU RECORD ! Score: %d\n", score_jeu.score_actuel);
    } else {
        printf("Partie terminée. Score: %d (Record: %d)\n", 
               score_jeu.score_actuel, score_jeu.meilleur_score);
    }
    printf("=== TERMINER PARTIE APPELÉE ===\n");
    score_jeu.temps_fin = SDL_GetTicks();
    score_jeu.partie_terminee = true;
    
    calculer_score_final();
}

void ajouter_points_fragment(const char* couleur) {
    int points = 0;
    int index = -1;
    
    // Déterminer l'index et les points selon la couleur
    if (strcmp(couleur, "rouge") == 0) {
        index = 0;
        points = points_fragments[0];
    }
    else if (strcmp(couleur, "vert") == 0) {
        index = 1;
        points = points_fragments[1];
    }
    else if (strcmp(couleur, "jaune") == 0) {
        index = 2;
        points = points_fragments[2];
    }
    else if (strcmp(couleur, "bleu") == 0) {
        index = 3;
        points = points_fragments[3];
    }
    else if (strcmp(couleur, "violet") == 0) {
        index = 4;
        points = points_fragments[4];
    }
    else if (strcmp(couleur, "blanc") == 0) {
        index = 5;
        points = points_fragments[5];
    }
    
    if (index >= 0) {
        score_jeu.score_actuel += points;
        score_jeu.fragments_collectes++;
        
        printf("Fragment %s collecté ! +%d points (Total: %d)\n", 
               couleur, points, score_jeu.score_actuel);
    }
}

void ajouter_collision_mur(void) {
    score_jeu.collisions_murs++;
    score_jeu.malus_collisions += 5; // -5 points par collision
    score_jeu.score_actuel = (score_jeu.score_actuel > 5) ? score_jeu.score_actuel - 5 : 0;
    
    printf("Collision avec un mur ! -5 points (Total: %d)\n", score_jeu.score_actuel);
}

void calculer_score_final(void) {
    if (!score_jeu.partie_terminee) return;
    
    printf("=== DÉBUT CALCUL SCORE ===\n");
    printf("Score avant calcul: %d\n", score_jeu.score_actuel);
    printf("Fragments collectés: %d\n", score_jeu.fragments_collectes);
    
    // Bonus de temps
    int temps_partie = (score_jeu.temps_fin - score_jeu.temps_debut) / 1000;
    printf("Temps de partie: %d secondes\n", temps_partie);
    
    if (temps_partie < 30) {
        score_jeu.bonus_temps = 200;
    } else if (temps_partie < 60) {
        score_jeu.bonus_temps = 100;
    } else if (temps_partie < 120) {
        score_jeu.bonus_temps = 50;
    } else {
        score_jeu.bonus_temps = 0;
    }
    
    printf("Bonus temps calculé: %d\n", score_jeu.bonus_temps);
    
    // Bonus thème (code existant...)
    // ...
    
    printf("Bonus thème calculé: %d\n", score_jeu.bonus_theme);
    printf("Malus collisions: %d\n", score_jeu.malus_collisions);
    
    // Score final
    score_jeu.score_actuel = score_jeu.score_actuel + score_jeu.bonus_temps + score_jeu.bonus_theme;
    
    printf("SCORE FINAL: %d\n", score_jeu.score_actuel);
    printf("=== FIN CALCUL SCORE ===\n");
}

void sauvegarder_meilleur_score(void) {
    FILE* fichier = fopen("meilleur_score.txt", "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d", score_jeu.meilleur_score);
        fclose(fichier);
        printf("Meilleur score sauvegardé: %d\n", score_jeu.meilleur_score);
    } else {
        printf("Erreur: impossible de sauvegarder le score\n");
    }
}

void charger_meilleur_score(void) {
    FILE* fichier = fopen("meilleur_score.txt", "r");
    if (fichier != NULL) {
        fscanf(fichier, "%d", &score_jeu.meilleur_score);
        fclose(fichier);
        printf("Meilleur score chargé: %d\n", score_jeu.meilleur_score);
    } else {
        score_jeu.meilleur_score = 0;
        printf("Aucun score sauvegardé trouvé. Meilleur score: 0\n");
    }
}

void afficher_score(SDL_Surface* surface) {
    // Zone d'affichage du score en temps réel (coin supérieur droit)
    SDL_Rect zone_score = {LARGEUR_FENETRE - 200, 10, 190, 30};
    SDL_FillRect(surface, &zone_score, 
                SDL_MapRGB(surface->format, 0, 0, 0));
    
    // Bordure
    SDL_Rect bordure_score = {zone_score.x - 2, zone_score.y - 2, zone_score.w + 4, zone_score.h + 4};
    SDL_FillRect(surface, &bordure_score, 
                SDL_MapRGB(surface->format, 
                          themes[theme_actuel].couleur_accent.r,
                          themes[theme_actuel].couleur_accent.g,
                          themes[theme_actuel].couleur_accent.b));
    SDL_FillRect(surface, &zone_score, 
                SDL_MapRGB(surface->format, 0, 0, 0));
    
    // Afficher "SCORE:" et la valeur
    SDL_Color couleur_score = {255, 255, 255, 255};
    dessiner_texte("SCORE:", zone_score.x + 5, zone_score.y + 5, couleur_score);
    
    // Convertir le score en chaîne pour l'afficher
    char score_str[20];
    sprintf(score_str, "%d", score_jeu.score_actuel);
    dessiner_texte(score_str, zone_score.x + 5, zone_score.y + 18, couleur_score);
    
    // Afficher le nombre de fragments collectés
    char fragments_str[20];
    sprintf(fragments_str, "FRAG: %d/6", score_jeu.fragments_collectes);
    
    SDL_Rect zone_fragments = {LARGEUR_FENETRE - 200, 45, 190, 20};
    SDL_FillRect(surface, &zone_fragments, 
                SDL_MapRGB(surface->format, 20, 20, 20));
    
    SDL_Color couleur_fragments = {200, 200, 200, 255};
    dessiner_texte(fragments_str, zone_fragments.x + 5, zone_fragments.y + 3, couleur_fragments);
}

void afficher_score_final(SDL_Surface* surface) {
    // Zone d'affichage du score final
    SDL_Rect zone_score_final = {
        (LARGEUR_FENETRE - 400) / 2,
        150,
        400,
        200
    };
    
    // Fond et bordure
    SDL_FillRect(surface, &zone_score_final, 
                SDL_MapRGB(surface->format, 0, 0, 0));
    
    SDL_Rect bordure_finale = {
        zone_score_final.x - 3,
        zone_score_final.y - 3,
        zone_score_final.w + 6,
        zone_score_final.h + 6
    };
    SDL_FillRect(surface, &bordure_finale, 
                SDL_MapRGB(surface->format, 
                          themes[theme_actuel].couleur_accent.r,
                          themes[theme_actuel].couleur_accent.g,
                          themes[theme_actuel].couleur_accent.b));
    SDL_FillRect(surface, &zone_score_final, 
                SDL_MapRGB(surface->format, 0, 0, 0));
    
    // Couleurs
    SDL_Color couleur_titre = {255, 255, 0, 255};
    SDL_Color couleur_texte = {255, 255, 255, 255};
    SDL_Color couleur_valeur = {100, 255, 100, 255};
    SDL_Color couleur_record = {255, 100, 100, 255};
    
    int x_base = zone_score_final.x + 20;
    int y_base = zone_score_final.y + 20;
    
    // Titre
    dessiner_texte("SCORE FINAL", x_base + 80, y_base, couleur_titre);
    
    // SOLUTION : Fonction pour convertir un nombre en texte
    
    // Fragments
    dessiner_texte("FRAGMENTS:", x_base, y_base + 30, couleur_texte);
    if (score_jeu.fragments_collectes == 0) dessiner_texte("0", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 1) dessiner_texte("1", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 2) dessiner_texte("2", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 3) dessiner_texte("3", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 4) dessiner_texte("4", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 5) dessiner_texte("5", x_base + 150, y_base + 30, couleur_valeur);
    else if (score_jeu.fragments_collectes == 6) dessiner_texte("6", x_base + 150, y_base + 30, couleur_valeur);
    else dessiner_texte("PLUS", x_base + 150, y_base + 30, couleur_valeur);
    
    // Bonus temps
    dessiner_texte("BONUS TEMPS:", x_base, y_base + 50, couleur_texte);
    if (score_jeu.bonus_temps == 0) dessiner_texte("0", x_base + 150, y_base + 50, couleur_valeur);
    else if (score_jeu.bonus_temps == 50) dessiner_texte("50", x_base + 150, y_base + 50, couleur_valeur);
    else if (score_jeu.bonus_temps == 100) dessiner_texte("100", x_base + 150, y_base + 50, couleur_valeur);
    else if (score_jeu.bonus_temps == 200) dessiner_texte("200", x_base + 150, y_base + 50, couleur_valeur);
    else dessiner_texte("AUTRE", x_base + 150, y_base + 50, couleur_valeur);
    
    // Bonus thème
    dessiner_texte("BONUS THEME:", x_base, y_base + 70, couleur_texte);
    if (score_jeu.bonus_theme == 0) dessiner_texte("0", x_base + 150, y_base + 70, couleur_valeur);
    else if (score_jeu.bonus_theme == 25) dessiner_texte("25", x_base + 150, y_base + 70, couleur_valeur);
    else if (score_jeu.bonus_theme == 50) dessiner_texte("50", x_base + 150, y_base + 70, couleur_valeur);
    else if (score_jeu.bonus_theme == 75) dessiner_texte("75", x_base + 150, y_base + 70, couleur_valeur);
    else if (score_jeu.bonus_theme == 100) dessiner_texte("100", x_base + 150, y_base + 70, couleur_valeur);
    else dessiner_texte("AUTRE", x_base + 150, y_base + 70, couleur_valeur);
    
    // Malus (plus flexible)
    dessiner_texte("MALUS:", x_base, y_base + 90, couleur_texte);
    if (score_jeu.malus_collisions == 0) dessiner_texte("0", x_base + 150, y_base + 90, couleur_valeur);
    else if (score_jeu.malus_collisions <= 10) dessiner_texte("FAIBLE", x_base + 150, y_base + 90, couleur_valeur);
    else if (score_jeu.malus_collisions <= 30) dessiner_texte("MOYEN", x_base + 150, y_base + 90, couleur_valeur);
    else if (score_jeu.malus_collisions <= 50) dessiner_texte("ELEVE", x_base + 150, y_base + 90, couleur_valeur);
    else dessiner_texte("TRES ELEVE", x_base + 150, y_base + 90, couleur_valeur);
    
    // Total (plages)
    dessiner_texte("TOTAL:", x_base, y_base + 120, couleur_titre);
    if (score_jeu.score_actuel == 0) dessiner_texte("0", x_base + 150, y_base + 120, couleur_titre);
    else if (score_jeu.score_actuel < 100) dessiner_texte("FAIBLE", x_base + 150, y_base + 120, couleur_titre);
    else if (score_jeu.score_actuel < 300) dessiner_texte("MOYEN", x_base + 150, y_base + 120, couleur_titre);
    else if (score_jeu.score_actuel < 500) dessiner_texte("BON", x_base + 150, y_base + 120, couleur_titre);
    else if (score_jeu.score_actuel < 700) dessiner_texte("TRES BON", x_base + 150, y_base + 120, couleur_titre);
    else dessiner_texte("EXCELLENT", x_base + 150, y_base + 120, couleur_titre);
    
    // Record
    dessiner_texte("RECORD:", x_base, y_base + 150, couleur_record);
    if (score_jeu.score_actuel >= score_jeu.meilleur_score) {
        dessiner_texte("NOUVEAU !", x_base + 100, y_base + 150, couleur_record);
        dessiner_texte("FELICITATIONS", x_base + 40, y_base + 170, couleur_record);
    } else if (score_jeu.meilleur_score == 0) {
        dessiner_texte("AUCUN", x_base + 150, y_base + 150, couleur_record);
    } else if (score_jeu.meilleur_score < 300) {
        dessiner_texte("FAIBLE", x_base + 150, y_base + 150, couleur_record);
    } else if (score_jeu.meilleur_score < 500) {
        dessiner_texte("MOYEN", x_base + 150, y_base + 150, couleur_record);
    } else {
        dessiner_texte("ELEVE", x_base + 150, y_base + 150, couleur_record);
    }

}
