#include "themes.h"
#include "generateur_labyrinthe.h"
#include "affichage_SDL.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "textes_thematiques.h"


Theme themes[NB_THEMES];
int theme_actuel = 2; // Gotham par défaut
PointInteret points_interet[20];
int nb_points_interet = 0;
EffetParticule particules[100];
int nb_particules = 0;

void initialiser_themes(void) {
    // Odyssée d'Homère
    strcpy(themes[0].nom, "Odyssée d'Homère");
    themes[0].couleur_mur = (SDL_Color){232, 232, 232, 255};
    themes[0].couleur_chemin = (SDL_Color){13, 67, 119, 255};
    themes[0].couleur_fond = (SDL_Color){26, 53, 85, 255};
    themes[0].couleur_texte = (SDL_Color){255, 255, 255, 255};
    themes[0].couleur_accent = (SDL_Color){90, 205, 255, 255};
    strcpy(themes[0].description, "Naviguez sur la mer Égée, évitez les monstres marins et retrouvez votre chemin vers Ithaque.");
    strcpy(themes[0].elements, "Murs: Colonnes grecques | Chemins: Vagues de la mer | Joueur: Ulysse/Bateau | Ennemis: Sirènes, Cyclope | Objets: Armes divines, Conseils des dieux");
    themes[0].initialiser_theme = initialiser_theme_odyssee;
    themes[0].rendre_theme = rendre_theme_odyssee;
    themes[0].traiter_evenements_theme = traiter_evenements_odyssee;
    
    // TRON Legacy
    strcpy(themes[1].nom, "TRON Legacy");
    themes[1].couleur_mur = (SDL_Color){0, 204, 255, 255};
    themes[1].couleur_chemin = (SDL_Color){0, 17, 34, 255};
    themes[1].couleur_fond = (SDL_Color){0, 8, 17, 255};
    themes[1].couleur_texte = (SDL_Color){0, 204, 255, 255};
    themes[1].couleur_accent = (SDL_Color){255, 62, 62, 255};
    strcpy(themes[1].description, "Explorez la Grille pour trouver la sortie avant d'être déréglé par les forces hostiles du système.");
    strcpy(themes[1].elements, "Murs: Circuits lumineux | Chemins: Noir numérique | Joueur: Programme utilisateur | Ennemis: CLU, Sentinelles | Objets: Disques d'identité, Améliorations");
    themes[1].initialiser_theme = initialiser_theme_tron;
    themes[1].rendre_theme = rendre_theme_tron;
    themes[1].traiter_evenements_theme = traiter_evenements_tron;
    
    // Batman: Gotham City
    strcpy(themes[2].nom, "Batman: Gotham City");
    themes[2].couleur_mur = (SDL_Color){26, 30, 34, 255};
    themes[2].couleur_chemin = (SDL_Color){10, 13, 16, 255};
    themes[2].couleur_fond = (SDL_Color){14, 17, 20, 255};
    themes[2].couleur_texte = (SDL_Color){255, 255, 255, 255};
    themes[2].couleur_accent = (SDL_Color){255, 204, 51, 255};
    strcpy(themes[2].description, "Parcourez les ruelles sombres de Gotham à la recherche de criminels et d'indices pour résoudre l'énigme.");
    strcpy(themes[2].elements, "Murs: Bâtiments gothiques | Chemins: Rues mouillées | Joueur: Batman | Ennemis: Joker, Riddler | Objets: Gadgets, Indices, Bat-signal");
    themes[2].initialiser_theme = initialiser_theme_gotham;
    themes[2].rendre_theme = rendre_theme_gotham;
    themes[2].traiter_evenements_theme = traiter_evenements_gotham;
    
    // Tetris
    strcpy(themes[3].nom, "Tetris");
    themes[3].couleur_mur = (SDL_Color){0, 240, 240, 255};
    themes[3].couleur_chemin = (SDL_Color){17, 17, 17, 255};
    themes[3].couleur_fond = (SDL_Color){0, 0, 0, 255};
    themes[3].couleur_texte = (SDL_Color){255, 255, 255, 255};
    themes[3].couleur_accent = (SDL_Color){240, 160, 0, 255};
    strcpy(themes[3].description, "Naviguez dans un monde de blocs colorés, complétez des lignes pour ouvrir de nouveaux passages.");
    strcpy(themes[3].elements, "Murs: Blocs Tetris | Chemins: Espace vide | Joueur: Bloc mobile | Mécaniques: Rotations, Lignes | Objets: Accélérations, Bonus");
    themes[3].initialiser_theme = initialiser_theme_tetris;
    themes[3].rendre_theme = rendre_theme_tetris;
    themes[3].traiter_evenements_theme = traiter_evenements_tetris;
    
    // Avatar
    strcpy(themes[4].nom, "Forêt d'Avatar");
    themes[4].couleur_mur = (SDL_Color){9, 48, 73, 255};
    themes[4].couleur_chemin = (SDL_Color){6, 21, 48, 255};
    themes[4].couleur_fond = (SDL_Color){5, 16, 32, 255};
    themes[4].couleur_texte = (SDL_Color){77, 240, 255, 255};
    themes[4].couleur_accent = (SDL_Color){255, 153, 51, 255};
    strcpy(themes[4].description, "Traversez la végétation luxuriante de Pandora, connectez-vous à Eywa pour révéler le chemin caché.");
    strcpy(themes[4].elements, "Murs: Végétation bioluminescente | Chemins: Sols forestiers | Joueur: Na'vi | Ennemis: Soldats RDA | Objets: Graines d'Eywa, Ikran");
    themes[4].initialiser_theme = initialiser_theme_avatar;
    themes[4].rendre_theme = rendre_theme_avatar;
    themes[4].traiter_evenements_theme = traiter_evenements_avatar;
    
    // Mon Voisin Totoro
    strcpy(themes[5].nom, "Mon Voisin Totoro");
    themes[5].couleur_mur = (SDL_Color){138, 184, 121, 255};
    themes[5].couleur_chemin = (SDL_Color){212, 233, 255, 255};
    themes[5].couleur_fond = (SDL_Color){142, 197, 252, 255};
    themes[5].couleur_texte = (SDL_Color){33, 107, 60, 255};
    themes[5].couleur_accent = (SDL_Color){121, 85, 72, 255};
    strcpy(themes[5].description, "Explorez la forêt enchantée et découvrez les esprits cachés qui peuvent vous guider vers la sortie.");
    strcpy(themes[5].elements, "Murs: Arbres et buissons | Chemins: Sentiers forestiers | Joueur: Mei | Rencontres: Totoro, Noiraudes | Objets: Graines magiques, Chatbus");
    themes[5].initialiser_theme = initialiser_theme_totoro;
    themes[5].rendre_theme = rendre_theme_totoro;
    themes[5].traiter_evenements_theme = traiter_evenements_totoro;
    
    // Définir les zones de sélection
    int largeur_icone = 120;
    int hauteur_icone = 100;
    int espace = 15;
    int x_debut = (LARGEUR_FENETRE - (3 * largeur_icone + 2 * espace)) / 2;
    int y_ligne1 = HAUTEUR_FENETRE - 220;
    int y_ligne2 = HAUTEUR_FENETRE - 110;
    
    // Ligne 1
    themes[0].zone_selection = (SDL_Rect){x_debut, y_ligne1, largeur_icone, hauteur_icone};
    themes[1].zone_selection = (SDL_Rect){x_debut + largeur_icone + espace, y_ligne1, largeur_icone, hauteur_icone};
    themes[2].zone_selection = (SDL_Rect){x_debut + 2 * (largeur_icone + espace), y_ligne1, largeur_icone, hauteur_icone};
    
    // Ligne 2
    themes[3].zone_selection = (SDL_Rect){x_debut, y_ligne2, largeur_icone, hauteur_icone};
    themes[4].zone_selection = (SDL_Rect){x_debut + largeur_icone + espace, y_ligne2, largeur_icone, hauteur_icone};
    themes[5].zone_selection = (SDL_Rect){x_debut + 2 * (largeur_icone + espace), y_ligne2, largeur_icone, hauteur_icone};
    
    // Marquer le thème actuel comme sélectionné
    for(int i = 0; i < NB_THEMES; i++) {
        themes[i].selectionne = (i == theme_actuel);
    }
}

void changer_theme(int index) {
    if(index < 0 || index >= NB_THEMES) return;
    
    // Désélectionner l'ancien thème
    themes[theme_actuel].selectionne = false;
    
    // Changer le thème actuel
    theme_actuel = index;
    
    // Sélectionner le nouveau thème
    themes[theme_actuel].selectionne = true;
    initialiser_textes_thematiques(); // Réinitialiser les textes pour le nouveau thème


    
    // Réinitialiser les points d'intérêt
    nb_points_interet = 0;
    nb_particules = 0;
    
    // Initialiser le nouveau thème
    if(themes[theme_actuel].initialiser_theme) {
        themes[theme_actuel].initialiser_theme();
    }
    
    printf("Thème changé: %s\n", themes[theme_actuel].nom);
}

void afficher_selecteur_themes(void) {
    // Fond pour la zone de sélection
    SDL_Rect zone_selecteur = {0, HAUTEUR_FENETRE - 240, LARGEUR_FENETRE, 240};
    SDL_FillRect(windowSurface, &zone_selecteur, 
                SDL_MapRGB(windowSurface->format, 15, 15, 25));
    
    // Titre du sélecteur
    SDL_Rect zone_titre = {(LARGEUR_FENETRE - 400) / 2, HAUTEUR_FENETRE - 235, 400, 25};
    SDL_FillRect(windowSurface, &zone_titre, 
                SDL_MapRGB(windowSurface->format, 255, 255, 255));
    
    // Afficher chaque thème avec son nom
    for(int i = 0; i < NB_THEMES; i++) {
        afficher_icone_theme_avec_nom(i);
    }
    
    // Afficher l'aperçu du thème sélectionné (à gauche)
    afficher_apercu_theme(theme_actuel);
}

// Nouvelle fonction pour afficher les icônes avec les noms
void afficher_icone_theme_avec_nom(int index) {
    Theme* theme = &themes[index];
    
    // Définir la couleur de bordure
    Uint32 couleur_bordure = theme->selectionne ? 
        SDL_MapRGB(windowSurface->format, theme->couleur_accent.r, theme->couleur_accent.g, theme->couleur_accent.b) :
        SDL_MapRGB(windowSurface->format, 51, 51, 85);
    
    // Dessiner la bordure
    SDL_Rect bordure = {
        theme->zone_selection.x - 3,
        theme->zone_selection.y - 3,
        theme->zone_selection.w + 6,
        theme->zone_selection.h + 6
    };
    SDL_FillRect(windowSurface, &bordure, couleur_bordure);
    
    // Dessiner le fond de l'icône
    Uint32 couleur_fond = SDL_MapRGB(windowSurface->format, 
        theme->couleur_fond.r, theme->couleur_fond.g, theme->couleur_fond.b);
    SDL_FillRect(windowSurface, &theme->zone_selection, couleur_fond);
   
    // Dessiner la représentation visuelle du thème (plus petite)
    dessiner_representation_theme_reduite(index);
   
    // Afficher le nom du thème avec notre fonction de texte pixelisé
    SDL_Color couleur_nom = {theme->couleur_texte.r, theme->couleur_texte.g, theme->couleur_texte.b, 255};
    
    // Position du texte (en bas de chaque icône)
    int x_texte = theme->zone_selection.x + 5;
    int y_texte = theme->zone_selection.y + theme->zone_selection.h - 25;
    
    // Noms courts pour qu'ils tiennent dans l'espace
    switch(index) {
        case 0:
            dessiner_texte("ODYSSEE", x_texte, y_texte, couleur_nom);
            dessiner_texte("DHOMERE", x_texte, y_texte + 12, couleur_nom);
            break;
        case 1:
            dessiner_texte("TRON", x_texte, y_texte, couleur_nom);
            dessiner_texte("LEGACY", x_texte, y_texte + 12, couleur_nom);
            break;
        case 2:
            dessiner_texte("BATMAN", x_texte, y_texte, couleur_nom);
            dessiner_texte("GOTHAM", x_texte, y_texte + 12, couleur_nom);
            break;
        case 3:
            dessiner_texte("TETRIS", x_texte, y_texte, couleur_nom);
            dessiner_texte("BLOCS", x_texte, y_texte + 12, couleur_nom);
            break;
        case 4:
            dessiner_texte("AVATAR", x_texte, y_texte, couleur_nom);
            dessiner_texte("PANDORA", x_texte, y_texte + 12, couleur_nom);
            break;
        case 5:
            dessiner_texte("TOTORO", x_texte, y_texte, couleur_nom);
            dessiner_texte("FORET", x_texte, y_texte + 12, couleur_nom);
            break;
    }
}

// Fonction pour dessiner une représentation réduite du thème (pour laisser place au texte)
void dessiner_representation_theme_reduite(int index) {
    Theme* theme = &themes[index];
    SDL_Rect zone = theme->zone_selection;
    
    // Zone pour la représentation visuelle (plus petite pour laisser place au texte)
    SDL_Rect zone_visuelle = {
        zone.x + 10,
        zone.y + 10,
        zone.w - 20,
        zone.h - 50  // Réduire la hauteur pour laisser place au texte
    };
    
    // Couleurs
    Uint32 couleur_mur = SDL_MapRGB(windowSurface->format,
        theme->couleur_mur.r, theme->couleur_mur.g, theme->couleur_mur.b);
    Uint32 couleur_chemin = SDL_MapRGB(windowSurface->format,
        theme->couleur_chemin.r, theme->couleur_chemin.g, theme->couleur_chemin.b);
    Uint32 couleur_accent = SDL_MapRGB(windowSurface->format,
        theme->couleur_accent.r, theme->couleur_accent.g, theme->couleur_accent.b);
    
    // Dessiner selon le thème spécifique (versions simplifiées)
    switch(index) {
        case 0: // Odyssée
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Quelques colonnes grecques simplifiées
            for(int i = 0; i < 4; i++) {
                SDL_Rect colonne = {zone_visuelle.x + i * 20, zone_visuelle.y + 5, 6, 20};
                SDL_FillRect(windowSurface, &colonne, couleur_mur);
            }
            // Bateau
            SDL_Rect bateau = {zone_visuelle.x + 10, zone_visuelle.y + 25, 8, 4};
            SDL_FillRect(windowSurface, &bateau, couleur_accent);
            break;
            
        case 1: // TRON
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Grille simple
            for(int x = zone_visuelle.x; x < zone_visuelle.x + zone_visuelle.w; x += 15) {
                SDL_Rect ligne_v = {x, zone_visuelle.y, 1, zone_visuelle.h};
                SDL_FillRect(windowSurface, &ligne_v, couleur_mur);
            }
            // Circuit
            SDL_Rect circuit = {zone_visuelle.x + 10, zone_visuelle.y + 15, 30, 2};
            SDL_FillRect(windowSurface, &circuit, couleur_mur);
            break;
            
        case 2: // Gotham
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Skyline simplifié
            for(int i = 0; i < 5; i++) {
                SDL_Rect building = {zone_visuelle.x + i * 15, zone_visuelle.y + 10, 10, 20};
                SDL_FillRect(windowSurface, &building, couleur_mur);
            }
            // Bat-signal
            SDL_Rect signal = {zone_visuelle.x + 60, zone_visuelle.y + 5, 8, 8};
            SDL_FillRect(windowSurface, &signal, couleur_accent);
            break;
            
        case 3: // Tetris
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Quelques blocs Tetris
            SDL_Rect bloc1 = {zone_visuelle.x + 10, zone_visuelle.y + 10, 6, 6};
            SDL_Rect bloc2 = {zone_visuelle.x + 25, zone_visuelle.y + 15, 6, 6};
            SDL_Rect bloc3 = {zone_visuelle.x + 40, zone_visuelle.y + 5, 6, 6};
            SDL_FillRect(windowSurface, &bloc1, couleur_mur);
            SDL_FillRect(windowSurface, &bloc2, couleur_accent);
            SDL_FillRect(windowSurface, &bloc3, couleur_mur);
            break;
            
        case 4: // Avatar
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Arbres bioluminescents
            for(int i = 0; i < 4; i++) {
                SDL_Rect arbre = {zone_visuelle.x + i * 20, zone_visuelle.y + 10, 12, 12};
                SDL_FillRect(windowSurface, &arbre, couleur_mur);
                // Points lumineux
                SDL_Rect point = {zone_visuelle.x + i * 20 + 6, zone_visuelle.y + 16, 2, 2};
                SDL_FillRect(windowSurface, &point, couleur_accent);
            }
            break;
            
        case 5: // Totoro
            SDL_FillRect(windowSurface, &zone_visuelle, couleur_chemin);
            // Buissons et arbres
            for(int i = 0; i < 3; i++) {
                SDL_Rect buisson = {zone_visuelle.x + i * 25, zone_visuelle.y + 15, 15, 10};
                SDL_FillRect(windowSurface, &buisson, couleur_mur);
            }
            // Nuage
            SDL_Rect nuage = {zone_visuelle.x + 50, zone_visuelle.y + 5, 20, 6};
            Uint32 blanc = SDL_MapRGB(windowSurface->format, 255, 255, 255);
            SDL_FillRect(windowSurface, &nuage, blanc);
            break;
    }
}


void dessiner_apercu_odyssee(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond mer
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Colonnes grecques (murs)
   SDL_Rect colonne1 = {zone.x + 10, zone.y + 5, 8, 30};
   SDL_Rect colonne2 = {zone.x + 30, zone.y + 10, 8, 25};
   SDL_Rect colonne3 = {zone.x + 50, zone.y + 8, 8, 27};
   SDL_Rect colonne4 = {zone.x + 70, zone.y + 12, 8, 23};
   
   SDL_FillRect(windowSurface, &colonne1, couleur_mur);
   SDL_FillRect(windowSurface, &colonne2, couleur_mur);
   SDL_FillRect(windowSurface, &colonne3, couleur_mur);
   SDL_FillRect(windowSurface, &colonne4, couleur_mur);
   
   // Vagues (chemins)
   for(int x = zone.x; x < zone.x + zone.w; x += 10) {
       SDL_Rect vague = {x, zone.y + zone.h - 8, 8, 3};
       SDL_FillRect(windowSurface, &vague, couleur_accent);
   }
   
   // Bateau (joueur)
   SDL_Rect bateau = {zone.x + 15, zone.y + zone.h - 15, 8, 6};
   SDL_FillRect(windowSurface, &bateau, couleur_accent);
}

void dessiner_apercu_tron(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond sombre
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Grille
   for(int x = zone.x; x < zone.x + zone.w; x += 10) {
       SDL_Rect ligne_v = {x, zone.y, 1, zone.h};
       SDL_FillRect(windowSurface, &ligne_v, couleur_mur);
   }
   for(int y = zone.y; y < zone.y + zone.h; y += 10) {
       SDL_Rect ligne_h = {zone.x, y, zone.w, 1};
       SDL_FillRect(windowSurface, &ligne_h, couleur_mur);
   }
   
   // Circuits lumineux
   SDL_Rect circuit1 = {zone.x + 10, zone.y + 15, 40, 3};
   SDL_Rect circuit2 = {zone.x + 25, zone.y + 10, 3, 30};
   SDL_Rect circuit3 = {zone.x + 60, zone.y + 25, 30, 3};
   
   SDL_FillRect(windowSurface, &circuit1, couleur_mur);
   SDL_FillRect(windowSurface, &circuit2, couleur_mur);
   SDL_FillRect(windowSurface, &circuit3, couleur_mur);
   
   // Disque (joueur)
   SDL_Rect disque = {zone.x + 30, zone.y + 30, 8, 8};
   SDL_FillRect(windowSurface, &disque, couleur_accent);
}

void dessiner_apercu_gotham(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond sombre
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Skyline de Gotham
   SDL_Rect building1 = {zone.x + 5, zone.y + 15, 12, 30};
   SDL_Rect building2 = {zone.x + 25, zone.y + 10, 15, 35};
   SDL_Rect building3 = {zone.x + 50, zone.y + 20, 10, 25};
   SDL_Rect building4 = {zone.x + 70, zone.y + 5, 12, 40};
   SDL_Rect building5 = {zone.x + 90, zone.y + 18, 10, 27};
   
   SDL_FillRect(windowSurface, &building1, couleur_mur);
   SDL_FillRect(windowSurface, &building2, couleur_mur);
   SDL_FillRect(windowSurface, &building3, couleur_mur);
   SDL_FillRect(windowSurface, &building4, couleur_mur);
   SDL_FillRect(windowSurface, &building5, couleur_mur);
   
   // Effets de pluie
   for(int i = 0; i < 15; i++) {
       SDL_Rect goutte = {
           zone.x + (i * 7) % zone.w,
           zone.y + (i * 3) % (zone.h - 5),
           1, 3
       };
       SDL_FillRect(windowSurface, &goutte, couleur_accent);
   }
   
   // Bat-signal
   SDL_Rect signal = {zone.x + 20, zone.y + 5, 10, 10};
   SDL_FillRect(windowSurface, &signal, couleur_accent);
   
   // Batman (joueur)
   SDL_Rect batman = {zone.x + 35, zone.y + zone.h - 10, 8, 8};
   SDL_FillRect(windowSurface, &batman, couleur_accent);
}

void dessiner_apercu_tetris(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond noir
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Différents blocs Tetris avec couleurs variées
   // I-piece (cyan)
   SDL_Rect i1 = {zone.x + 10, zone.y + 10, 8, 8};
   SDL_Rect i2 = {zone.x + 10, zone.y + 18, 8, 8};
   SDL_Rect i3 = {zone.x + 10, zone.y + 26, 8, 8};
   SDL_Rect i4 = {zone.x + 10, zone.y + 34, 8, 8};
   SDL_FillRect(windowSurface, &i1, couleur_mur);
   SDL_FillRect(windowSurface, &i2, couleur_mur);
   SDL_FillRect(windowSurface, &i3, couleur_mur);
   SDL_FillRect(windowSurface, &i4, couleur_mur);
   
   // T-piece (violet)
   Uint32 violet = SDL_MapRGB(windowSurface->format, 160, 0, 240);
   SDL_Rect t1 = {zone.x + 30, zone.y + 10, 8, 8};
   SDL_Rect t2 = {zone.x + 38, zone.y + 10, 8, 8};
   SDL_Rect t3 = {zone.x + 46, zone.y + 10, 8, 8};
   SDL_Rect t4 = {zone.x + 38, zone.y + 18, 8, 8};
   SDL_FillRect(windowSurface, &t1, violet);
   SDL_FillRect(windowSurface, &t2, violet);
   SDL_FillRect(windowSurface, &t3, violet);
   SDL_FillRect(windowSurface, &t4, violet);
   
   // O-piece (jaune)
   Uint32 jaune = SDL_MapRGB(windowSurface->format, 240, 240, 0);
   SDL_Rect o1 = {zone.x + 70, zone.y + 15, 8, 8};
   SDL_Rect o2 = {zone.x + 78, zone.y + 15, 8, 8};
   SDL_Rect o3 = {zone.x + 70, zone.y + 23, 8, 8};
   SDL_Rect o4 = {zone.x + 78, zone.y + 23, 8, 8};
   SDL_FillRect(windowSurface, &o1, jaune);
   SDL_FillRect(windowSurface, &o2, jaune);
   SDL_FillRect(windowSurface, &o3, jaune);
   SDL_FillRect(windowSurface, &o4, jaune);
   
   // Bloc en mouvement (rouge)
   SDL_Rect moving = {zone.x + 50, zone.y + zone.h - 15, 8, 8};
   SDL_FillRect(windowSurface, &moving, couleur_accent);
}

void dessiner_apercu_avatar(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond forêt
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Arbres bioluminescents (circulaires)
   SDL_Rect arbre1 = {zone.x + 15, zone.y + 10, 20, 20};
   SDL_Rect arbre2 = {zone.x + 45, zone.y + 15, 15, 15};
   SDL_Rect arbre3 = {zone.x + 70, zone.y + 8, 25, 25};
   SDL_Rect arbre4 = {zone.x + 20, zone.y + 35, 18, 18};
   
   SDL_FillRect(windowSurface, &arbre1, couleur_mur);
   SDL_FillRect(windowSurface, &arbre2, couleur_mur);
   SDL_FillRect(windowSurface, &arbre3, couleur_mur);
   SDL_FillRect(windowSurface, &arbre4, couleur_mur);
   
   // Points bioluminescents
   for(int i = 0; i < 20; i++) {
       SDL_Rect point = {
           zone.x + (i * 5) % zone.w,
           zone.y + (i * 7) % zone.h,
           2, 2
       };
       SDL_FillRect(windowSurface, &point, couleur_accent);
   }
   
   // Connexions (lignes entre arbres simulées par des rectangles)
   SDL_Rect connexion1 = {zone.x + 35, zone.y + 20, 10, 2};
   SDL_Rect connexion2 = {zone.x + 60, zone.y + 22, 15, 2};
   SDL_FillRect(windowSurface, &connexion1, couleur_accent);
   SDL_FillRect(windowSurface, &connexion2, couleur_accent);
   
   // Na'vi (joueur)
   SDL_Rect navi = {zone.x + 25, zone.y + zone.h - 12, 8, 8};
   SDL_FillRect(windowSurface, &navi, couleur_accent);
}

void dessiner_apercu_totoro(SDL_Rect zone, Uint32 couleur_mur, Uint32 couleur_chemin, Uint32 couleur_accent) {
   // Fond ciel
   SDL_FillRect(windowSurface, &zone, couleur_chemin);
   
   // Arbres et buissons
   SDL_Rect buisson1 = {zone.x + 10, zone.y + 15, 20, 15};
   SDL_Rect arbre = {zone.x + 40, zone.y + 10, 25, 25};
   SDL_Rect buisson2 = {zone.x + 75, zone.y + 18, 15, 12};
   SDL_Rect buisson3 = {zone.x + 20, zone.y + 35, 18, 10};
   
   SDL_FillRect(windowSurface, &buisson1, couleur_mur);
   SDL_FillRect(windowSurface, &arbre, couleur_mur);
   SDL_FillRect(windowSurface, &buisson2, couleur_mur);
   SDL_FillRect(windowSurface, &buisson3, couleur_mur);
   
   // Nuages
   SDL_Rect nuage1 = {zone.x + 5, zone.y + 5, 25, 8};
   SDL_Rect nuage2 = {zone.x + 60, zone.y + 8, 30, 6};
   Uint32 blanc = SDL_MapRGB(windowSurface->format, 255, 255, 255);
   SDL_FillRect(windowSurface, &nuage1, blanc);
   SDL_FillRect(windowSurface, &nuage2, blanc);
   
   // Noiraudes (petits esprits)
   SDL_Rect noiraude1 = {zone.x + 25, zone.y + 28, 4, 4};
   SDL_Rect noiraude2 = {zone.x + 55, zone.y + 32, 4, 4};
   SDL_Rect noiraude3 = {zone.x + 80, zone.y + 25, 4, 4};
   SDL_FillRect(windowSurface, &noiraude1, couleur_accent);
   SDL_FillRect(windowSurface, &noiraude2, couleur_accent);
   SDL_FillRect(windowSurface, &noiraude3, couleur_accent);
   
   // Sentier
   SDL_Rect sentier = {zone.x + 15, zone.y + zone.h - 5, zone.w - 30, 3};
   SDL_FillRect(windowSurface, &sentier, couleur_accent);
   
   // Mei (joueur)
   SDL_Rect mei = {zone.x + 30, zone.y + zone.h - 12, 8, 8};
   SDL_FillRect(windowSurface, &mei, couleur_accent);
}

void afficher_apercu_theme(int index) {
   if(index < 0 || index >= NB_THEMES) return;
   
   Theme* theme = &themes[index];
   
   // Zone d'aperçu principal (à gauche)
   SDL_Rect zone_apercu = {20, 20, 350, 300};
   
   // Bordure
   SDL_Rect bordure_apercu = {18, 18, 354, 304};
   Uint32 couleur_bordure = SDL_MapRGB(windowSurface->format,
       theme->couleur_accent.r, theme->couleur_accent.g, theme->couleur_accent.b);
   SDL_FillRect(windowSurface, &bordure_apercu, couleur_bordure);
   
   // Fond de l'aperçu
   Uint32 couleur_fond = SDL_MapRGB(windowSurface->format,
       theme->couleur_fond.r, theme->couleur_fond.g, theme->couleur_fond.b);
   SDL_FillRect(windowSurface, &zone_apercu, couleur_fond);
   
   // Titre (simulé avec un rectangle)
   SDL_Rect zone_titre = {30, 30, 330, 25};
   Uint32 couleur_titre = SDL_MapRGB(windowSurface->format,
       theme->couleur_texte.r, theme->couleur_texte.g, theme->couleur_texte.b);
   SDL_FillRect(windowSurface, &zone_titre, couleur_titre);
   
   // Mini-labyrinthe avec le thème
   afficher_mini_labyrinthe_theme(index);
   
   // Zone de description (simulée)
   SDL_Rect zone_description = {30, 250, 330, 60};
   Uint32 couleur_desc = SDL_MapRGB(windowSurface->format, 40, 40, 40);
   SDL_FillRect(windowSurface, &zone_description, couleur_desc);
   
   // Zone d'éléments (simulée)
   SDL_Rect zone_elements = {390, 20, 300, 300};
   SDL_FillRect(windowSurface, &zone_elements, couleur_desc);
}

void afficher_points_interet_demo(int index, int offset_x, int offset_y, int taille_case) {
   // Positions des points d'intérêt dans le mini-labyrinthe
   int poi_positions[][2] = {
       {4, 5}, {8, 3}, {12, 8}, {6, 11}, {10, 13}
   };
   
   // Couleurs selon le thème
   SDL_Color couleurs[5];
   
   switch(index) {
       case 0: // Odyssée
           couleurs[0] = (SDL_Color){255, 51, 102, 255};   // Sirènes
           couleurs[1] = (SDL_Color){170, 136, 255, 255};  // Circé
           couleurs[2] = (SDL_Color){255, 215, 0, 255};    // Trésor
           couleurs[3] = (SDL_Color){255, 102, 51, 255};   // Cyclope
           couleurs[4] = (SDL_Color){51, 255, 51, 255};    // Ithaque
           break;
       case 1: // TRON
           couleurs[0] = (SDL_Color){255, 170, 0, 255};    // Portal
           couleurs[1] = (SDL_Color){255, 51, 102, 255};   // CLU
           couleurs[2] = (SDL_Color){51, 255, 51, 255};    // Programme allié
           couleurs[3] = (SDL_Color){255, 255, 51, 255};   // Disque
           couleurs[4] = (SDL_Color){51, 51, 255, 255};    // Sortie
           break;
       case 2: // Gotham
           couleurs[0] = (SDL_Color){51, 170, 51, 255};    // Poison Ivy
           couleurs[1] = (SDL_Color){204, 68, 34, 255};    // Joker
           couleurs[2] = (SDL_Color){170, 170, 170, 255};  // Commissaire Gordon
           couleurs[3] = (SDL_Color){255, 204, 51, 255};   // Bat-signal
           couleurs[4] = (SDL_Color){68, 68, 68, 255};     // Wayne Tower
           break;
       case 3: // Tetris
           couleurs[0] = (SDL_Color){0, 240, 0, 255};      // S-piece
           couleurs[1] = (SDL_Color){160, 0, 240, 255};    // T-piece
           couleurs[2] = (SDL_Color){240, 160, 0, 255};    // L-piece
           couleurs[3] = (SDL_Color){240, 240, 0, 255};    // O-piece
           couleurs[4] = (SDL_Color){240, 0, 0, 255};      // Z-piece
           break;
       case 4: // Avatar
           couleurs[0] = (SDL_Color){255, 153, 51, 255};   // Arbre des âmes
           couleurs[1] = (SDL_Color){255, 51, 102, 255};   // Site humain
           couleurs[2] = (SDL_Color){51, 255, 153, 255};   // Ikran
           couleurs[3] = (SDL_Color){153, 255, 51, 255};   // Graines
           couleurs[4] = (SDL_Color){51, 153, 255, 255};   // Connexion Eywa
           break;
       case 5: // Totoro
           couleurs[0] = (SDL_Color){102, 102, 102, 255};  // Totoro
           couleurs[1] = (SDL_Color){116, 185, 255, 255};  // Chatbus
           couleurs[2] = (SDL_Color){34, 34, 34, 255};     // Noiraudes
           couleurs[3] = (SDL_Color){255, 193, 7, 255};    // Graines magiques
           couleurs[4] = (SDL_Color){76, 175, 80, 255};    // Tunnel secret
           break;
   }
   
   // Dessiner les points d'intérêt
   for(int i = 0; i < 5; i++) {
       SDL_Rect poi_rect = {
           offset_x + poi_positions[i][0] * taille_case + 3,
           offset_y + poi_positions[i][1] * taille_case + 3,
           taille_case - 6,
           taille_case - 6
       };
       
       Uint32 couleur_poi = SDL_MapRGB(windowSurface->format,
                                      couleurs[i].r, couleurs[i].g, couleurs[i].b);
       SDL_FillRect(windowSurface, &poi_rect, couleur_poi);
   }
}

void afficher_mini_labyrinthe_theme(int index) {
   Theme* theme = &themes[index];
   
   // Labyrinthe simplifié pour la démo
   int mini_lab[15][15] = {
       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
       {1,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
       {1,0,1,0,1,0,1,1,0,1,0,1,1,0,1},
       {1,0,1,0,0,0,0,1,0,0,0,1,0,0,1},
       {1,0,1,1,1,1,0,1,0,1,1,1,0,1,1},
       {1,0,0,0,0,1,0,1,0,0,0,0,0,1,1},
       {1,1,1,1,0,1,0,1,1,1,1,1,0,0,1},
       {1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
       {1,0,1,1,1,1,1,1,1,1,0,1,1,0,1},
       {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
       {1,1,1,0,1,1,1,1,0,1,1,1,1,0,1},
       {1,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
       {1,0,1,1,1,0,1,1,1,1,1,0,1,0,1},
       {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
       {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
   };
   
   int taille_case = 12;
   int offset_x = 45;
   int offset_y = 70;
   
   // Couleurs
   Uint32 couleur_mur = SDL_MapRGB(windowSurface->format,
       theme->couleur_mur.r, theme->couleur_mur.g, theme->couleur_mur.b);
   Uint32 couleur_chemin = SDL_MapRGB(windowSurface->format,
       theme->couleur_chemin.r, theme->couleur_chemin.g, theme->couleur_chemin.b);
   Uint32 couleur_accent = SDL_MapRGB(windowSurface->format,
       theme->couleur_accent.r, theme->couleur_accent.g, theme->couleur_accent.b);
   
   // Dessiner le mini-labyrinthe
   for(int y = 0; y < 15; y++) {
       for(int x = 0; x < 15; x++) {
           SDL_Rect case_rect = {
               offset_x + x * taille_case,
               offset_y + y * taille_case,
               taille_case,
               taille_case
           };
           
           if(mini_lab[y][x] == 1) {
               SDL_FillRect(windowSurface, &case_rect, couleur_mur);
           } else {
               SDL_FillRect(windowSurface, &case_rect, couleur_chemin);
           }
       }
   }
   
   // Position du joueur
   SDL_Rect joueur = {
       offset_x + 1 * taille_case + 2,
       offset_y + 1 * taille_case + 2,
       taille_case - 4,
       taille_case - 4
   };
   SDL_FillRect(windowSurface, &joueur, couleur_accent);
   
   // Points d'intérêt adaptés au thème
   afficher_points_interet_demo(index, offset_x, offset_y, taille_case);
}

bool traiter_clic_selecteur_themes(int x, int y) {
   for(int i = 0; i < NB_THEMES; i++) {
       SDL_Rect zone = themes[i].zone_selection;
       
       // Vérifier si le clic est dans la zone de ce thème
       if(x >= zone.x && x <= zone.x + zone.w &&
          y >= zone.y && y <= zone.y + zone.h) {
           
           // Changer vers ce thème
           changer_theme(i);
           return true; // Clic traité
       }
   }
   
   return false; // Aucun thème cliqué
}

void adapter_labyrinthe_au_theme(void) {
   // Cette fonction adapte l'affichage du labyrinthe existant
   // au nouveau thème sans le régénérer complètement
   
   // Appliquer les effets spécifiques au thème
   if(themes[theme_actuel].rendre_theme) {
       themes[theme_actuel].rendre_theme();
   }
   
   // Redessiner le labyrinthe avec les nouvelles couleurs
   affiche_lab(labyrinthe);
   
   // Mettre à jour l'affichage
   SDL_UpdateWindowSurface(ecran);
}

// Fonctions utilitaires pour les effets
void ajouter_particule(int x, int y, int type) {
    (void)type;
       if(nb_particules < 100) {
       particules[nb_particules].x = x;
       particules[nb_particules].y = y;
       particules[nb_particules].opacity = 1.0f;
       particules[nb_particules].speed = 1.0f + (float)(rand() % 3);
       nb_particules++;
   }
}

void mettre_a_jour_particules(void) {
   for(int i = 0; i < nb_particules; i++) {
       particules[i].y += particules[i].speed;
       particules[i].opacity -= 0.02f;
       
       // Supprimer les particules qui ont disparu
       if(particules[i].opacity <= 0 || particules[i].y > HAUTEUR_FENETRE) {
           // Déplacer la dernière particule à cette position
           particules[i] = particules[nb_particules - 1];
           nb_particules--;
           i--; // Réévaluer cette position
       }
   }
}

void dessiner_particules(void) {
   for(int i = 0; i < nb_particules; i++) {
       if(particules[i].opacity > 0) {
           SDL_Rect part = {
               (int)particules[i].x,
               (int)particules[i].y,
               2, 4
           };
           
           // Couleur avec transparence simulée
           Uint32 couleur = SDL_MapRGB(windowSurface->format, 
                                     200, 200, 255); // Bleu clair pour la pluie
           
           SDL_FillRect(windowSurface, &part, couleur);
       }
   }
}

void ajouter_point_interet(int x, int y, int type, const char* nom, const char* description, SDL_Color couleur) {
   if(nb_points_interet < 20) {
       points_interet[nb_points_interet].x = x;
       points_interet[nb_points_interet].y = y;
       points_interet[nb_points_interet].type = type;
       strcpy(points_interet[nb_points_interet].nom, nom);
       strcpy(points_interet[nb_points_interet].description, description);
       points_interet[nb_points_interet].couleur = couleur;
       points_interet[nb_points_interet].decouvert = true; // Pour la démo
       nb_points_interet++;
   }
}

// Fonctions d'initialisation spécifiques par thème
void initialiser_theme_odyssee(void) {
   printf("Initialisation du thème Odyssée d'Homère\n");
   
   // Ajouter des points d'intérêt spécifiques à l'Odyssée
   ajouter_point_interet(10, 15, 1, "Île des Sirènes", 
                        "Vous entendez des chants envoûtants. Résistez à la tentation!", 
                        (SDL_Color){255, 51, 102, 255});
   
   ajouter_point_interet(25, 8, 1, "Antre de Circé", 
                        "La magicienne propose de vous aider... pour un prix.", 
                        (SDL_Color){170, 136, 255, 255});
   
   ajouter_point_interet(35, 30, 2, "Port d'Ithaque", 
                        "Enfin! Votre patrie est en vue!", 
                        (SDL_Color){255, 215, 0, 255});
   
   ajouter_point_interet(20, 25, 0, "Épée divine", 
                        "Une arme bénie par Athéna vous aidera dans votre quête.", 
                        (SDL_Color){255, 255, 255, 255});
}

void initialiser_theme_tron(void) {
   printf("Initialisation du thème TRON Legacy\n");
   
   // Points d'intérêt TRON
   ajouter_point_interet(12, 18, 3, "Portal d'accès", 
                        "Un portail menant vers une autre section de la Grille.", 
                        (SDL_Color){255, 170, 0, 255});
   
   ajouter_point_interet(28, 12, 1, "Agent de CLU", 
                        "Programme hostile détecté. Évitez ou combattez.", 
                        (SDL_Color){255, 51, 102, 255});
   
   ajouter_point_interet(40, 35, 2, "Sortie système", 
                        "Point d'extraction vers le monde réel.", 
                        (SDL_Color){51, 255, 51, 255});
   
   ajouter_point_interet(15, 30, 0, "Disque d'identité", 
                        "Améliore vos capacités dans la Grille.", 
                        (SDL_Color){0, 204, 255, 255});
}

void initialiser_theme_gotham(void) {
   printf("Initialisation du thème Batman: Gotham City\n");
   
   // Points d'intérêt Gotham
   ajouter_point_interet(8, 20, 1, "Repaire de Poison Ivy", 
                        "Des plantes toxiques bloquent le passage.", 
                        (SDL_Color){51, 170, 51, 255});
   
   ajouter_point_interet(30, 10, 1, "Piège du Joker", 
                        "Attention! Un piège explosif a été posé ici.", 
                        (SDL_Color){204, 68, 34, 255});
   
   ajouter_point_interet(42, 25, 0, "Commissaire Gordon", 
                        "Gordon a des informations cruciales sur l'affaire.", 
                        (SDL_Color){170, 170, 170, 255});
   
   ajouter_point_interet(35, 5, 3, "Bat-Signal", 
                        "Le signal est activé. Gotham a besoin de vous!", 
                        (SDL_Color){255, 204, 51, 255});
   
   ajouter_point_interet(45, 40, 2, "Wayne Tower", 
                        "Votre base d'opérations vous attend.", 
                        (SDL_Color){68, 68, 68, 255});
}

void initialiser_theme_tetris(void) {
   printf("Initialisation du thème Tetris\n");
   
   // Points d'intérêt Tetris
   ajouter_point_interet(10, 12, 3, "Ligne complète", 
                        "Complétez cette ligne pour gagner des points!", 
                        (SDL_Color){255, 255, 255, 255});
   
   ajouter_point_interet(25, 20, 0, "Pièce T", 
                        "Une pièce T peut s'insérer ici parfaitement.", 
                        (SDL_Color){160, 0, 240, 255});
   
   ajouter_point_interet(38, 28, 0, "Pièce I", 
                        "La pièce idéale pour faire un Tetris!", 
                        (SDL_Color){0, 240, 240, 255});
   
   ajouter_point_interet(30, 35, 3, "Zone de danger", 
                        "Attention! Les blocs s'accumulent dangereusement.", 
                        (SDL_Color){240, 0, 0, 255});
}

void initialiser_theme_avatar(void) {
   printf("Initialisation du thème Forêt d'Avatar\n");
   
   // Points d'intérêt Avatar
   ajouter_point_interet(15, 18, 3, "Arbre des Âmes", 
                        "L'arbre sacré pulse d'une énergie mystique.", 
                        (SDL_Color){255, 153, 51, 255});
   
   ajouter_point_interet(32, 22, 1, "Avant-poste RDA", 
                        "Des soldats humains patrouillent dans la zone.", 
                        (SDL_Color){255, 51, 102, 255});
   
   ajouter_point_interet(28, 8, 0, "Ikran sauvage", 
                        "Un dragon volant pourrait devenir votre monture.", 
                        (SDL_Color){51, 255, 153, 255});
   
   ajouter_point_interet(40, 30, 0, "Graines d'Eywa", 
                        "Ces graines brillantes révèlent des chemins cachés.", 
                        (SDL_Color){153, 255, 51, 255});
   
   ajouter_point_interet(20, 35, 3, "Connexion Eywa", 
                        "Connectez-vous au réseau de la vie de Pandora.", 
                        (SDL_Color){51, 153, 255, 255});
}

void initialiser_theme_totoro(void) {
   printf("Initialisation du thème Mon Voisin Totoro\n");
   
   // Points d'intérêt Totoro
   ajouter_point_interet(18, 15, 3, "Grand Totoro", 
                        "Le roi de la forêt vous observe avec bienveillance.", 
                        (SDL_Color){102, 102, 102, 255});
   
   ajouter_point_interet(35, 25, 3, "Arrêt Chatbus", 
                        "Le Chatbus peut vous emmener ailleurs instantanément.", 
                        (SDL_Color){116, 185, 255, 255});
   
   ajouter_point_interet(12, 30, 0, "Noiraudes", 
                        "De petits esprits noirs vous guident gentiment.", 
                        (SDL_Color){34, 34, 34, 255});
   
   ajouter_point_interet(40, 10, 0, "Graines magiques", 
                        "Ces graines peuvent faire pousser un arbre géant!", 
                        (SDL_Color){255, 193, 7, 255});
   
   ajouter_point_interet(25, 35, 2, "Tunnel secret", 
                        "Un passage caché mène vers la maison.", 
                        (SDL_Color){76, 175, 80, 255});
}

// Fonctions de rendu spécifiques par thème
void rendre_theme_odyssee(void) {
   // Effet de vagues
   static int vague_offset = 0;
   vague_offset = (vague_offset + 1) % 20;
   
   // Dessiner des vagues sur les chemins
   for(int i = 0; i < taille_lab; i++) {
       for(int j = 0; j < taille_lab; j++) {
           if(labyrinthe[i][j] == 0) { // Chemin
               if((i + j + vague_offset) % 10 == 0) {
                   SDL_Rect vague = {
                       50 + j * 10 + 2,
                       50 + i * 10 + 7,
                       6, 2
                   };
                   SDL_FillRect(windowSurface, &vague, 
                               SDL_MapRGB(windowSurface->format, 90, 205, 255));
               }
           }
       }
   }
}

void rendre_theme_tron(void) {
   // Effet de grille clignotante
   static int grid_pulse = 0;
   grid_pulse = (grid_pulse + 1) % 60;
   
   if(grid_pulse < 30) {
       // Dessiner une grille subtile
       for(int x = 50; x < 50 + taille_lab * 10; x += 20) {
           SDL_Rect ligne_v = {x, 50, 1, taille_lab * 10};
           SDL_FillRect(windowSurface, &ligne_v, 
                       SDL_MapRGB(windowSurface->format, 0, 102, 128));
       }
       for(int y = 50; y < 50 + taille_lab * 10; y += 20) {
           SDL_Rect ligne_h = {50, y, taille_lab * 10, 1};
           SDL_FillRect(windowSurface, &ligne_h, 
                       SDL_MapRGB(windowSurface->format, 0, 102, 128));
       }
   }
}

void rendre_theme_gotham(void) {
   // Effet de pluie
   static int frame_count = 0;
   frame_count++;
   
   if(frame_count % 3 == 0) {
       // Ajouter des gouttes de pluie
       for(int i = 0; i < 5; i++) {
           ajouter_particule(
               50 + (rand() % (taille_lab * 10)),
               40,
               0 // Type pluie
           );
       }
   }
   
   mettre_a_jour_particules();
   dessiner_particules();
   
   // Bat-signal dans le ciel
   SDL_Rect signal = {LARGEUR_FENETRE - 100, 30, 60, 60};
   SDL_FillRect(windowSurface, &signal, 
               SDL_MapRGB(windowSurface->format, 255, 255, 170));
   
   // Symbole Batman simplifié
   SDL_Rect bat_symbol = {LARGEUR_FENETRE - 85, 45, 30, 15};
   SDL_FillRect(windowSurface, &bat_symbol, 
               SDL_MapRGB(windowSurface->format, 0, 0, 0));
}

void rendre_theme_tetris(void) {
   // Effet de blocs qui tombent occasionnellement
   static int drop_timer = 0;
   drop_timer++;
   
   if(drop_timer % 120 == 0) { // Toutes les 2 secondes environ
       // Animer un bloc qui tombe
       static int bloc_y = 50;
       static int bloc_x = 60;
       
       if(bloc_y < 50 + taille_lab * 10) {
           SDL_Rect bloc = {bloc_x, bloc_y, 20, 20};
           SDL_FillRect(windowSurface, &bloc, 
                       SDL_MapRGB(windowSurface->format, 240, 160, 0));
           bloc_y += 10;
       } else {
           bloc_y = 50;
           bloc_x = 60 + (rand() % (taille_lab * 10 - 40));
       }
   }
}

void rendre_theme_avatar(void) {
   // Effet de bioluminescence pulsante
   static int pulse = 0;
   pulse = (pulse + 1) % 120;
   
   float intensity = 0.5f + 0.5f * sin(pulse * 3.14159f / 60.0f);
   
   // Points bioluminescents autour des murs
   for(int i = 0; i < nb_points_interet; i++) {
       if(points_interet[i].decouvert) {
           SDL_Rect glow = {
               50 + points_interet[i].x * 10 - 2,
               50 + points_interet[i].y * 10 - 2,
               14, 14
           };
           
           // Effet de lueur (simulé)
           for(int r = 0; r < 3; r++) {
               SDL_Rect glow_ring = {
                   glow.x - r,
                   glow.y - r,
                   glow.w + 2*r,
                   glow.h + 2*r
               };
               Uint32 couleur = SDL_MapRGB(windowSurface->format, 
                                         (Uint8)(77 * intensity),
                                         (Uint8)(240 * intensity),
                                         (Uint8)(255 * intensity));
               SDL_FillRect(windowSurface, &glow_ring, couleur);
           }
       }
   }
}

void rendre_theme_totoro(void) {
   // Particules magiques flottantes
   static int magic_timer = 0;
   magic_timer++;
   
   if(magic_timer % 60 == 0) {
       // Ajouter des particules magiques
       for(int i = 0; i < 3; i++) {
           ajouter_particule(
               50 + (rand() % (taille_lab * 10)),
               50 + (rand() % (taille_lab * 10)),
               1 // Type magie
           );
       }
   }
   
   // Dessiner des particules magiques (différentes de la pluie)
   for(int i = 0; i < nb_particules; i++) {
       if(particules[i].opacity > 0) {
           SDL_Rect part = {
               (int)particules[i].x + (int)(sin(magic_timer * 0.1f + i) * 2),
               (int)particules[i].y + (int)(cos(magic_timer * 0.1f + i) * 2),
               3, 3
           };
           
           Uint32 couleur = SDL_MapRGB(windowSurface->format, 
                                      255, 215, 0); // Doré
           SDL_FillRect(windowSurface, &part, couleur);
       }
   }
   
   // Nuages qui bougent
   static int cloud_offset = 0;
   cloud_offset = (cloud_offset + 1) % 200;
   
   SDL_Rect nuage1 = {LARGEUR_FENETRE - 150 + cloud_offset/4, 20, 80, 30};
   SDL_Rect nuage2 = {LARGEUR_FENETRE - 250 + cloud_offset/3, 40, 100, 35};
   
   SDL_FillRect(windowSurface, &nuage1, 
               SDL_MapRGB(windowSurface->format, 255, 255, 255));
   SDL_FillRect(windowSurface, &nuage2, 
               SDL_MapRGB(windowSurface->format, 245, 245, 245));
}

// Fonctions de gestion d'événements par thème
void traiter_evenements_odyssee(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Ulysse utilise sa ruse légendaire!\n");
               break;
           case SDLK_s:
               printf("Vous résistez au chant des sirènes...\n");
               break;
       }
   }
}

void traiter_evenements_tron(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Lancement du disque d'identité!\n");
               break;
           case SDLK_r:
               printf("Reconfiguration du programme en cours...\n");
               break;
       }
   }
}

void traiter_evenements_gotham(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Batman lance un batarang!\n");
               break;
           case SDLK_d:
               printf("Mode détective activé...\n");
               break;
           case SDLK_g:
               printf("Utilisation du grappin!\n");
               break;
       }
   }
}

void traiter_evenements_tetris(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Rotation de la pièce!\n");
               break;
           case SDLK_DOWN:
               printf("Descente rapide activée!\n");
               break;
       }
   }
}

void traiter_evenements_avatar(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Connexion à Eywa...\n");
               break;
           case SDLK_c:
               printf("Communication avec la faune locale...\n");
               break;
       }
   }
}

void traiter_evenements_totoro(SDL_Event* event) {
   if(event->type == SDL_KEYDOWN) {
       switch(event->key.keysym.sym) {
           case SDLK_SPACE:
               printf("Mei cherche des glands magiques!\n");
               break;
           case SDLK_t:
               printf("Appel à Totoro... Il vous entend peut-être...\n");
               break;
       }
   }
}