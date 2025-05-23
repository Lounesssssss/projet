#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "affichage_SDL.h"
#include "generateur_labyrinthe.h"
#include "themes.h"
#include "joueur.h"
#include "textes_thematiques.h"  // Nouvel include

SDL_Window *ecran = NULL;
SDL_Surface *SurfaceBg = NULL;
SDL_Surface *windowSurface = NULL;
SDL_Surface *surfaceMur[taille_f][taille_f];

void initFenetre() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return;
    }
    
    ecran = SDL_CreateWindow("LabyrintheX - Univers Narratifs",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             LARGEUR_FENETRE,
                             HAUTEUR_FENETRE,
                             SDL_WINDOW_SHOWN);
    
    if(NULL == ecran) {
        fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        return;
    }
    
    SurfaceBg = SDL_GetWindowSurface(ecran);
    SDL_FillRect(SurfaceBg, NULL, SDL_MapRGB(SurfaceBg->format, 0, 0, 0));
    SDL_UpdateWindowSurface(ecran);
    
    windowSurface = SDL_GetWindowSurface(ecran);
}

void affiche_lab(int labyrinthe[taille_f][taille_f]) {
    windowSurface = SDL_GetWindowSurface(ecran);
    
    Theme* theme = &themes[theme_actuel];
    
    int taille_case = 10;
    int offset_x = 50;
    int offset_y = 50;
    
    // Effacer la zone du labyrinthe
    SDL_Rect zone_lab = {offset_x - 5, offset_y - 5, 
                         taille_lab * taille_case + 10, 
                         taille_lab * taille_case + 10};
    SDL_FillRect(windowSurface, &zone_lab, 
                SDL_MapRGB(windowSurface->format, 
                          theme->couleur_fond.r,
                          theme->couleur_fond.g,
                          theme->couleur_fond.b));
    
    // Dessiner le labyrinthe
    for(int i = 0; i < taille_lab; i++) {
        for(int j = 0; j < taille_lab; j++) {
            SDL_Rect position = {
                offset_x + j * taille_case,
                offset_y + i * taille_case,
                taille_case,
                taille_case
            };
            
            Uint32 couleur;
            if(labyrinthe[i][j] == -1) {
                // Mur
                couleur = SDL_MapRGB(windowSurface->format,
                                   theme->couleur_mur.r,
                                   theme->couleur_mur.g,
                                   theme->couleur_mur.b);
            }
            /*
            else if(labyrinthe[i][j] == -2) {
                // Chemin de solution
                couleur = SDL_MapRGB(windowSurface->format,
                                   theme->couleur_accent.r,
                                   theme->couleur_accent.g,
                                   theme->couleur_accent.b);
            }
            */ 
            else {
                // Chemin normal
                couleur = SDL_MapRGB(windowSurface->format,
                                   theme->couleur_chemin.r,
                                   theme->couleur_chemin.g,
                                   theme->couleur_chemin.b);
            }
            
            SDL_FillRect(windowSurface, &position, couleur);
        }
    }
    
    // Dessiner les points d'intérêt
    for(int i = 0; i < nb_points_interet; i++) {
        PointInteret* poi = &points_interet[i];
        if(poi->decouvert) {
            SDL_Rect poi_rect = {
                offset_x + poi->x * taille_case + 2,
                offset_y + poi->y * taille_case + 2,
                taille_case - 4,
                taille_case - 4
            };
            
            Uint32 couleur_poi = SDL_MapRGB(windowSurface->format,
                                          poi->couleur.r,
                                          poi->couleur.g,
                                          poi->couleur.b);
            SDL_FillRect(windowSurface, &poi_rect, couleur_poi);
        }
    }
    
    // Dessiner les fragments d'histoire
    dessiner_fragments();
    
    // Appliquer les effets spécifiques au thème
    if(theme->rendre_theme) {
        theme->rendre_theme();
    }
    
    // Dessiner les particules
    dessiner_particules();
}

void dessiner_lettre(char lettre, int x, int y, SDL_Color couleur) {
    int taille_pixel = 2; // Taille de chaque "pixel" de la lettre
    Uint32 couleur_sdl = SDL_MapRGB(windowSurface->format, couleur.r, couleur.g, couleur.b);
    
    // Tableau de définition des lettres (7x5 pixels)
    // 1 représente un pixel allumé, 0 un pixel éteint
    int lettres[26][7][5] = {
        // A
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}
        },
        // B
        {
            {1,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,0}
        },
        // C
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // D
        {
            {1,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,0}
        },
        // E
        {
            {1,1,1,1,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}
        },
        // F
        {
            {1,1,1,1,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0}
        },
        // G
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,0},
            {1,0,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // H
        {
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}
        },
        // I
        {
            {0,1,1,1,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,1,1,1,0}
        },
        // J
        {
            {0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // K
        {
            {1,0,0,0,1},
            {1,0,0,1,0},
            {1,0,1,0,0},
            {1,1,0,0,0},
            {1,0,1,0,0},
            {1,0,0,1,0},
            {1,0,0,0,1}
        },
        // L
        {
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}
        },
        // M
        {
            {1,0,0,0,1},
            {1,1,0,1,1},
            {1,0,1,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}
        },
        // N
        {
            {1,0,0,0,1},
            {1,1,0,0,1},
            {1,0,1,0,1},
            {1,0,0,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}
        },
        // O
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // P
        {
            {1,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0}
        },
        // Q
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,0,1,0},
            {0,1,1,0,1}
        },
        // R
        {
            {1,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,0},
            {1,0,1,0,0},
            {1,0,0,1,0},
            {1,0,0,0,1}
        },
        // S
        {
            {0,1,1,1,0},
            {1,0,0,0,1},
            {1,0,0,0,0},
            {0,1,1,1,0},
            {0,0,0,0,1},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // T
        {
            {1,1,1,1,1},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}
        },
        // U
        {
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {0,1,1,1,0}
        },
        // V
        {
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {0,1,0,1,0},
            {0,1,0,1,0},
            {0,0,1,0,0}
        },
        // W
        {
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,1,0,1},
            {1,1,0,1,1},
            {1,0,0,0,1}
        },
        // X
        {
            {1,0,0,0,1},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,1,0,1,0},
            {1,0,0,0,1}
        },
        // Y
        {
            {1,0,0,0,1},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}
        },
        // Z
        {
            {1,1,1,1,1},
            {0,0,0,1,0},
            {0,0,1,0,0},
            {0,1,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}
        }
    };
    
    // Si c'est une lettre majuscule
    if (lettre >= 'A' && lettre <= 'Z') {
        int index = lettre - 'A';
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                if (lettres[index][i][j] == 1) {
                    SDL_Rect pixel = {x + j * taille_pixel, y + i * taille_pixel, taille_pixel, taille_pixel};
                    SDL_FillRect(windowSurface, &pixel, couleur_sdl);
                }
            }
        }
    }
    // Si c'est une lettre minuscule, on utilise les mêmes définitions
    else if (lettre >= 'a' && lettre <= 'z') {
        int index = lettre - 'a';
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                if (lettres[index][i][j] == 1) {
                    SDL_Rect pixel = {x + j * taille_pixel, y + i * taille_pixel, taille_pixel, taille_pixel};
                    SDL_FillRect(windowSurface, &pixel, couleur_sdl);
                }
            }
        }
    }
    // Espace - ne rien dessiner
    else if (lettre == ' ') {
        // Ne rien dessiner pour l'espace
    }
    // Deux-points :
    else if (lettre == ':') {
        SDL_Rect point1 = {x + 2 * taille_pixel, y + 2 * taille_pixel, taille_pixel, taille_pixel};
        SDL_Rect point2 = {x + 2 * taille_pixel, y + 4 * taille_pixel, taille_pixel, taille_pixel};
        SDL_FillRect(windowSurface, &point1, couleur_sdl);
        SDL_FillRect(windowSurface, &point2, couleur_sdl);
    }
    // Tiret -
    else if (lettre == '-') {
        SDL_Rect tiret = {x, y + 3 * taille_pixel, 5 * taille_pixel, taille_pixel};
        SDL_FillRect(windowSurface, &tiret, couleur_sdl);
    }
}

void dessiner_texte(const char* texte, int x, int y, SDL_Color couleur) {
    int espacement = 12; // Espacement entre les lettres (5 pixels de largeur + 7 d'espacement)
    
    for (int i = 0; texte[i] != '\0'; i++) {
        dessiner_lettre(texte[i], x + i * espacement, y, couleur);
    }
}

void dessiner_fragments(void) {
    int taille_case = 10;
    int offset_x = 50;
    int offset_y = 50;
    
    // Définir les positions des fragments
    int fragments[5][2] = {
        {3, 3},                       // Fragment vert
        {taille_lab/2, taille_lab/2}, // Fragment jaune  
        {taille_lab/3, 2*taille_lab/3}, // Fragment bleu
        {2*taille_lab/3, taille_lab/3}, // Fragment violet
        {taille_lab-5, taille_lab-5}  // Fragment blanc
    };
    
    // Couleurs des fragments
    Uint32 couleurs[5] = {
        SDL_MapRGB(windowSurface->format, 0, 255, 0),     // Vert
        SDL_MapRGB(windowSurface->format, 255, 255, 0),   // Jaune
        SDL_MapRGB(windowSurface->format, 0, 150, 255),   // Bleu
        SDL_MapRGB(windowSurface->format, 200, 0, 255),   // Violet
        SDL_MapRGB(windowSurface->format, 255, 255, 255)  // Blanc
    };
    
    // Dessiner chaque fragment s'il n'a pas été collecté
    for (int i = 0; i < 5; i++) {
        const char* couleur_noms[5] = {"vert", "jaune", "bleu", "violet", "blanc"};
        
        if (!fragment_est_collecte(couleur_noms[i])) {
            // Effet de lueur/halo
            SDL_Rect halo = {
                offset_x + fragments[i][0] * taille_case - 1,
                offset_y + fragments[i][1] * taille_case - 1,
                taille_case + 2,
                taille_case + 2
            };
            SDL_FillRect(windowSurface, &halo, couleurs[i]);
            
            // Le fragment lui-même
            SDL_Rect fragment = {
                offset_x + fragments[i][0] * taille_case + 1,
                offset_y + fragments[i][1] * taille_case + 1,
                taille_case - 2,
                taille_case - 2
            };
            SDL_FillRect(windowSurface, &fragment, couleurs[i]);
        }
    }
}

void affiche_solution(int labyrinthe[taille_f][taille_f]) {
    affiche_lab(labyrinthe);
    windowSurface = SDL_GetWindowSurface(ecran);
    Theme* theme = &themes[theme_actuel];
    
    int taille_case = 10;
    int offset_x = 50;
    int offset_y = 50;
    
    // Dessiner seulement le chemin de solution
    for(int i = 0; i < taille_lab; i++) {
        for(int j = 0; j < taille_lab; j++) {
            if(labyrinthe[i][j] == -2) {
                SDL_Rect position = {
                    offset_x + j * taille_case,
                    offset_y + i * taille_case,
                    taille_case,
                    taille_case
                };
                
                Uint32 couleur = SDL_MapRGB(windowSurface->format,
                                         theme->couleur_accent.r,
                                         theme->couleur_accent.g,
                                         theme->couleur_accent.b);
                SDL_FillRect(windowSurface, &position, couleur);
            }
        }
    }
}

    
    