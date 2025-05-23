#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "joueur.h"
#include "generateur_labyrinthe.h"
#include "affichage_SDL.h"
#include "themes.h"
#include "score.h"
#include "textes_thematiques.h"



typedef enum {
    TEXTE_NORMAL,
    TEXTE_INTRODUCTION,
    TEXTE_OBJECTIF,
    TEXTE_INSTRUCTIONS,
    TEXTE_CONSEILS,
    TEXTE_ELEMENTS
} TypeTexte;

TypeTexte texte_affiche = TEXTE_NORMAL;

typedef enum {
    MODE_SELECTION_THEME,
    MODE_LABYRINTHE,
    MODE_JEU,
    MODE_SOLUTION
} ModeJeu;

void afficher_instructions(void) {
    SDL_Rect zone_instructions = {LARGEUR_FENETRE - 300, 350, 280, 230};
    SDL_FillRect(windowSurface, &zone_instructions, 
                SDL_MapRGB(windowSurface->format, 30, 30, 30));
    
    // Bordure
    SDL_Rect bordure_inst = {LARGEUR_FENETRE - 302, 348, 284, 234};
    SDL_FillRect(windowSurface, &bordure_inst, 
                SDL_MapRGB(windowSurface->format, 100, 100, 100));
    SDL_FillRect(windowSurface, &zone_instructions, 
                SDL_MapRGB(windowSurface->format, 30, 30, 30));
    
    // TITRE INSTRUCTIONS
    SDL_Rect titre_inst = {LARGEUR_FENETRE - 290, 355, 260, 20};
    SDL_FillRect(windowSurface, &titre_inst, 
                SDL_MapRGB(windowSurface->format, 255, 255, 255));

    // Positions des lignes d'instructions
    int positions_y[] = {385, 410, 435, 460, 485, 510};

    // Noms des thèmes
    const char* noms_themes[6] = {
        "ODYSSEE DHOMERE",
        "TRON LEGACY", 
        "BATMAN GOTHAM",
        "TETRIS BLOCS",
        "AVATAR PANDORA",
        "TOTORO FORET"
    };

    // Afficher les thèmes avec leurs noms
    for(int i = 0; i < 6; i++) {
        SDL_Rect ligne_theme = {
            LARGEUR_FENETRE - 295,
            positions_y[i],  // Utiliser les positions existantes
            270,
            15
        };
        
        // Couleur de fond selon si c'est le thème actuel
        if (i == theme_actuel) {
            SDL_FillRect(windowSurface, &ligne_theme,
                        SDL_MapRGB(windowSurface->format, 
                                  themes[i].couleur_accent.r,
                                  themes[i].couleur_accent.g,
                                  themes[i].couleur_accent.b));
        } else {
            SDL_FillRect(windowSurface, &ligne_theme,
                        SDL_MapRGB(windowSurface->format, 60, 60, 60));
        }
        
        // Petit carré coloré à gauche
        SDL_Rect carre_couleur = {
            LARGEUR_FENETRE - 290,
            positions_y[i] + 2,
            12,
            12
        };
        SDL_FillRect(windowSurface, &carre_couleur, 
                    SDL_MapRGB(windowSurface->format, 
                              themes[i].couleur_accent.r,
                              themes[i].couleur_accent.g,
                              themes[i].couleur_accent.b));
        
        // Nom du thème
        SDL_Color couleur_nom = (i == theme_actuel) ? 
            (SDL_Color){255, 255, 255, 255} : 
            (SDL_Color){200, 200, 200, 255};
        
        dessiner_texte(noms_themes[i], LARGEUR_FENETRE - 275, positions_y[i] + 2, couleur_nom);
    }
}


void afficher_informations_theme(void) {
    Theme* theme = &themes[theme_actuel];
    
    SDL_Rect zone_info = {LARGEUR_FENETRE - 300, 50, 280, 280};
    SDL_FillRect(windowSurface, &zone_info, 
                SDL_MapRGB(windowSurface->format, 
                          theme->couleur_fond.r * 0.8f,
                          theme->couleur_fond.g * 0.8f,
                          theme->couleur_fond.b * 0.8f));
    
    // Bordure avec couleur d'accent du thème
    SDL_Rect bordure_info = {LARGEUR_FENETRE - 302, 48, 284, 284};
    SDL_FillRect(windowSurface, &bordure_info, 
                SDL_MapRGB(windowSurface->format, 
                          theme->couleur_accent.r,
                          theme->couleur_accent.g,
                          theme->couleur_accent.b));
    SDL_FillRect(windowSurface, &zone_info, 
                SDL_MapRGB(windowSurface->format, 
                          theme->couleur_fond.r * 0.8f,
                          theme->couleur_fond.g * 0.8f,
                          theme->couleur_fond.b * 0.8f));
    
    // Titre du thème
    SDL_Rect titre_theme = {LARGEUR_FENETRE - 290, 60, 260, 25};
    SDL_FillRect(windowSurface, &titre_theme, 
                SDL_MapRGB(windowSurface->format, 
                          theme->couleur_texte.r,
                          theme->couleur_texte.g,
                          theme->couleur_texte.b));
    
    // Zone de texte - NE PAS la remplir si on affiche un texte spécial
    SDL_Rect desc_theme = {LARGEUR_FENETRE - 290, 100, 260, 80};
    if (texte_affiche == TEXTE_NORMAL) {
        SDL_FillRect(windowSurface, &desc_theme, 
                    SDL_MapRGB(windowSurface->format, 60, 60, 60));
    } else {
        // Fond sombre pour le texte
        SDL_FillRect(windowSurface, &desc_theme, 
                    SDL_MapRGB(windowSurface->format, 20, 20, 20));
        
        // Afficher le texte selon l'état
        switch(texte_affiche) {
            case TEXTE_INTRODUCTION:
                {
                    SDL_Color couleur_titre = {255, 255, 0, 255};
                    SDL_Color couleur_texte = {200, 200, 200, 255};
                    
                    dessiner_texte("INTRODUCTION", LARGEUR_FENETRE - 285, 105, couleur_titre);
                    dessiner_texte("BIENVENUE DANS", LARGEUR_FENETRE - 285, 120, couleur_texte);
                    dessiner_texte("LABYRINTHEX", LARGEUR_FENETRE - 285, 135, couleur_texte);
                    dessiner_texte("UNIVERS NARRATIFS", LARGEUR_FENETRE - 285, 150, couleur_texte);
                    dessiner_texte("COLLECTEZ FRAGMENTS", LARGEUR_FENETRE - 285, 165, couleur_texte);
                }
                break;
                
            case TEXTE_OBJECTIF:
                {
                    SDL_Color couleur_titre = {255, 100, 100, 255};
                    SDL_Color couleur_texte = {200, 200, 200, 255};
                    
                    dessiner_texte("OBJECTIF", LARGEUR_FENETRE - 285, 105, couleur_titre);
                    dessiner_texte("EXPLOREZ LABYRINTHE", LARGEUR_FENETRE - 285, 120, couleur_texte);
                    dessiner_texte("TROUVEZ FRAGMENTS", LARGEUR_FENETRE - 285, 135, couleur_texte);
                    dessiner_texte("RECONSTITUEZ", LARGEUR_FENETRE - 285, 150, couleur_texte);
                    dessiner_texte("LE RECIT COMPLET", LARGEUR_FENETRE - 285, 165, couleur_texte);
                }
                break;
                
            case TEXTE_INSTRUCTIONS:
                {
                    SDL_Color couleur_titre = {100, 255, 100, 255};
                    SDL_Color couleur_texte = {200, 200, 200, 255};
                    
                    dessiner_texte("INSTRUCTIONS", LARGEUR_FENETRE - 285, 105, couleur_titre);
                    dessiner_texte("FLECHES: DEPLACER", LARGEUR_FENETRE - 285, 120, couleur_texte);
                    dessiner_texte("J: MODE JEU", LARGEUR_FENETRE - 285, 135, couleur_texte);
                    dessiner_texte("S: SOLUTION", LARGEUR_FENETRE - 285, 150, couleur_texte);
                    dessiner_texte("R: REGENERER", LARGEUR_FENETRE - 285, 165, couleur_texte);
                }
                break;
                
            case TEXTE_CONSEILS:
                {
                    SDL_Color couleur_titre = {100, 100, 255, 255};
                    SDL_Color couleur_texte = {200, 200, 200, 255};
                    
                    dessiner_texte("CONSEILS", LARGEUR_FENETRE - 285, 105, couleur_titre);
                    dessiner_texte("ATTENTION AUX", LARGEUR_FENETRE - 285, 120, couleur_texte);
                    dessiner_texte("CHEMINS CHANGEANTS", LARGEUR_FENETRE - 285, 135, couleur_texte);
                    dessiner_texte("EXPLOREZ CHAQUE", LARGEUR_FENETRE - 285, 150, couleur_texte);
                    dessiner_texte("RECOIN DU LABYRINTHE", LARGEUR_FENETRE - 285, 165, couleur_texte);
                }
                break;
                
            case TEXTE_ELEMENTS:
                {
                    SDL_Color couleur_titre = {255, 150, 0, 255};
                    SDL_Color couleur_texte = {200, 200, 200, 255};
                    
                    dessiner_texte("ELEMENTS", LARGEUR_FENETRE - 285, 105, couleur_titre);
                    
                    // Texte selon le thème comme dans votre code précédent
                    switch(theme_actuel) {
                        case 1: // TRON
                            dessiner_texte("ROUGE: PROGRAMME", LARGEUR_FENETRE - 285, 120, couleur_texte);
                            dessiner_texte("VERT: ENTREE", LARGEUR_FENETRE - 285, 135, couleur_texte);
                            dessiner_texte("JAUNE: DISQUE", LARGEUR_FENETRE - 285, 150, couleur_texte);
                            dessiner_texte("BLEU: GRILLE", LARGEUR_FENETRE - 285, 165, couleur_texte);
                            break;
                        // Autres thèmes...
                        default:
                            dessiner_texte("ROUGE: JOUEUR", LARGEUR_FENETRE - 285, 120, couleur_texte);
                            dessiner_texte("VERT: ORIGINE", LARGEUR_FENETRE - 285, 135, couleur_texte);
                            dessiner_texte("JAUNE: CLE", LARGEUR_FENETRE - 285, 150, couleur_texte);
                            dessiner_texte("BLEU: FRAGMENT", LARGEUR_FENETRE - 285, 165, couleur_texte);
                            break;
                    }
                }
                break;
                
            default:
                break;
        }
    }
    
    // Éléments (simulés) - seulement si affichage normal
    if (texte_affiche == TEXTE_NORMAL) {
        SDL_Rect elem_theme = {LARGEUR_FENETRE - 290, 200, 260, 110};
        SDL_FillRect(windowSurface, &elem_theme, 
                    SDL_MapRGB(windowSurface->format, 40, 40, 40));
    }
    // Garder aussi la palette de couleurs originale en bas (optionnel)
    SDL_Color palette[] = {
        themes[theme_actuel].couleur_mur,
        themes[theme_actuel].couleur_chemin,
        themes[theme_actuel].couleur_fond,
        themes[theme_actuel].couleur_texte,
        themes[theme_actuel].couleur_accent
    };
    
    for(int i = 0; i < 5; i++) {
        SDL_Rect color_rect = {
            LARGEUR_FENETRE - 280 + i * 50,
            290,
            40, 30
        };
        SDL_FillRect(windowSurface, &color_rect, 
                    SDL_MapRGB(windowSurface->format, 
                              palette[i].r, palette[i].g, palette[i].b));
    }
}

void afficher_message_victoire(void) {
    // Zone de message de victoire centrée
    SDL_Rect zone_message = {
        (LARGEUR_FENETRE - 300) / 2,  // Centrée horizontalement dans la fenêtre
        200,                          // Position Y fixe, pas trop bas
        300, 
        100
    };
    
    
    // Fond semi-transparent
    SDL_FillRect(windowSurface, &zone_message, 
                SDL_MapRGB(windowSurface->format, 0, 0, 0));
    
    // Bordure colorée selon le thème actuel
    SDL_Rect bordure = {
        zone_message.x - 3, 
        zone_message.y - 3, 
        zone_message.w + 6, 
        zone_message.h + 6
    };
                        
    SDL_FillRect(windowSurface, &bordure, 
                SDL_MapRGB(windowSurface->format, 
                          themes[theme_actuel].couleur_accent.r,
                          themes[theme_actuel].couleur_accent.g,
                          themes[theme_actuel].couleur_accent.b));
                          
    // Re-remplir la zone interne pour effacer la bordure
    SDL_FillRect(windowSurface, &zone_message, 
                SDL_MapRGB(windowSurface->format, 0, 0, 0));
    
    // Ligne de titre "VICTOIRE !"
    SDL_Rect ligne_titre = {
        zone_message.x + 50, 
        zone_message.y + 20, 
        200, 
        20
    };

    SDL_FillRect(windowSurface, &ligne_titre, 
                SDL_MapRGB(windowSurface->format, 255, 255, 255));
    
    // Ligne de félicitations
    SDL_Rect ligne_texte = {
        zone_message.x + 30, 
        zone_message.y + 50, 
        240, 
        15
    };

    SDL_FillRect(windowSurface, &ligne_texte, 
                SDL_MapRGB(windowSurface->format, 200, 200, 200));
    
    // Ligne d'instructions
    SDL_Rect ligne_instruction = {
        zone_message.x + 50, 
        zone_message.y + 75, 
        200, 
        10
    };

    SDL_FillRect(windowSurface, &ligne_instruction, 
                SDL_MapRGB(windowSurface->format, 150, 150, 150));
}

#undef main
int main(int argc, char** argv) {
    (void)argc; // Éviter le warning de variable non utilisée
    (void)argv;
    
    // Initialisation
    srand(time(NULL));
    
    initFenetre();
    if(ecran == NULL) {
        printf("Erreur d'initialisation SDL\n");
        return 1;
    }
    
    initialiser_themes();
    initialiser_textes_thematiques();
    initialiser_score();


    
    // Générer le labyrinthe initial
    creation_grille();
    remplissage_nb();
    cassage_mur();
    resolution();
    
    printf("=== LabyrintheX: Univers Narratifs ===\n");
    printf("Utilisation:\n");
    printf("- TAB: Basculer entre sélection de thème et labyrinthe\n");
    printf("- 1-6: Changer de thème directement\n");
    printf("- Clic: Sélectionner un thème\n");
    printf("- S: Afficher/cacher la solution\n");
    printf("- R: Régénérer le labyrinthe\n");
    printf("- ESC: Quitter\n");
    printf("Thème actuel: %s\n", themes[theme_actuel].nom);
    
    // Variables du jeu
    ModeJeu mode_actuel = MODE_SELECTION_THEME;
    bool solution_visible = false;
    bool running = true;

    // Initialiser le joueur
    initialiser_joueur();

    // Boucle principale
    while(running) {
        SDL_Event event;
        
        // Gestion des événements
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            else if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                        
                    case SDLK_TAB:
                        // Changer de mode
                        if(mode_actuel == MODE_SELECTION_THEME) {
                            mode_actuel = MODE_LABYRINTHE;
                        } else {
                            mode_actuel = MODE_SELECTION_THEME;
                        }
                        break;
                        
                    case SDLK_s:
                        // Basculer la solution
                        solution_visible = !solution_visible;
                        printf("Solution %s\n", solution_visible ? "visible" : "cachée");
                        break;
                        
                    case SDLK_r:
                        // Régénérer le labyrinthe
                        creation_grille();
                        remplissage_nb();
                        cassage_mur();
                        resolution();
                        printf("Nouveau labyrinthe généré!\n");
                        break;
                        
                    case SDLK_j:
                        // Basculer en mode jeu
                        mode_actuel = MODE_JEU;
                        initialiser_joueur();
                        commencer_partie(); // Commencer une nouvelle partie avec score
                        changer_texte_thematique("objectif");
                        printf("Mode jeu activé. Utilisez les flèches pour déplacer le joueur.\n"); 
                        break;      

                    case SDLK_i:
                        texte_affiche = TEXTE_INTRODUCTION;
                        printf("Affichage du texte d'introduction.\n");
                        break;

                    case SDLK_o:
                        texte_affiche = TEXTE_OBJECTIF;
                        printf("Affichage des objectifs.\n");
                        break;

                    case SDLK_e:
                        texte_affiche = TEXTE_ELEMENTS;
                        printf("Affichage des descriptions des éléments.\n");
                        break;

                    case SDLK_h:
                        texte_affiche = TEXTE_INSTRUCTIONS;
                        printf("Affichage des instructions.\n");
                        break;

                    case SDLK_c:
                        texte_affiche = TEXTE_CONSEILS;
                        printf("Affichage des conseils.\n");
                        break;


                    case SDLK_UP:
                        if(mode_actuel == MODE_JEU) {
                            if(deplacer_joueur(0, -1)) {
                                printf("Déplacement vers le haut\n");
                            }

                        }
                        break;


                    case SDLK_DOWN:
                        if(mode_actuel == MODE_JEU) {
                            if(deplacer_joueur(0, 1)) {
                                printf("Déplacement vers le bas\n");
                            }
                        }
                        break;

                    case SDLK_LEFT:
                        if(mode_actuel == MODE_JEU) {
                            if(deplacer_joueur(-1, 0)) {
                                printf("Déplacement vers la gauche\n");
                            }
                        }
                        break;

                    case SDLK_RIGHT:
                        if(mode_actuel == MODE_JEU) {
                            if(deplacer_joueur(1, 0)) {
                                printf("Déplacement vers la droite\n");
                            }
                        }
                        break;
                    
                    case SDLK_1:
                    case SDLK_2:
                    case SDLK_3:
                    case SDLK_4:
                    case SDLK_5:
                    case SDLK_6:
                        // Changer de thème directement
                        changer_theme(event.key.keysym.sym - SDLK_1);
                        break;
                        
                    default:
                        // Transmettre l'événement au thème actuel
                        if(themes[theme_actuel].traiter_evenements_theme) {
                            themes[theme_actuel].traiter_evenements_theme(&event);
                        }
                        break;
                    
                    
                }
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN) {
                if(mode_actuel == MODE_SELECTION_THEME) {
                    // Gérer les clics sur le sélecteur de thèmes
                    if(traiter_clic_selecteur_themes(event.button.x, event.button.y)) {
                        printf("Nouveau thème sélectionné: %s\n", themes[theme_actuel].nom);
                    }
                }
            }
        }
        
        // Rendu
        // Effacer l'écran
        SDL_FillRect(windowSurface, NULL, 
                    SDL_MapRGB(windowSurface->format, 0, 0, 0));
        
        if(mode_actuel == MODE_SELECTION_THEME) {
            // Afficher le sélecteur de thèmes
            afficher_selecteur_themes();
        } else {
            // Afficher le labyrinthe
            if(solution_visible) {
                affiche_solution(labyrinthe);
            } else {
                affiche_lab(labyrinthe);
            }
            
            if(mode_actuel == MODE_JEU) {
                dessiner_joueur(windowSurface);
                afficher_score(windowSurface);

                if(verifier_victoire()) {
                    static bool score_affiche = false;
                    if (!score_affiche) {
                        printf("Victoire ! Affichage du score final.\n");
                        printf("=== DEBUG AFFICHAGE SCORE (UNE FOIS) ===\n");
                        printf("Fragments: %d\n", score_jeu.fragments_collectes);
                        printf("Bonus temps: %d\n", score_jeu.bonus_temps);
                        printf("Bonus thème: %d\n", score_jeu.bonus_theme);
                        printf("Malus: %d\n", score_jeu.malus_collisions);
                        printf("Total: %d\n", score_jeu.score_actuel);
                        printf("Record: %d\n", score_jeu.meilleur_score);
                        printf("========================================\n");
                        score_affiche = true;
                    }
                    afficher_score_final(windowSurface);
                }
            }
            // Afficher les informations du thème actuel
            afficher_informations_theme();
            
            // Afficher les instructions
            afficher_instructions();
        }
        
        // Mettre à jour l'affichage
        SDL_UpdateWindowSurface(ecran);
        // Petit délai pour maintenir ~60 FPS
       SDL_Delay(16);
   }
   
   // Nettoyage
   printf("Fermeture du programme...\n");
   liberer_textes_thematiques();
   SDL_Quit();
   return 0;
}