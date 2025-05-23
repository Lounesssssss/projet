#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generateur_labyrinthe.h"

int labyrinthe[taille_lab][taille_lab];
int lignes;
int colonnes;
int troue1;
int troue2;
int distance;

void creation_grille() {
    for(lignes = 0; lignes < taille_lab; lignes++) {
        if(lignes % 2 == 0) {
            for(colonnes = 0; colonnes < taille_lab; colonnes++) {
                labyrinthe[lignes][colonnes] = -1;
            }
        } else {
            for(colonnes = 0; colonnes < taille_lab; colonnes++) {
                if(colonnes % 2 == 0) {
                    labyrinthe[lignes][colonnes] = -1;
                } else {
                    labyrinthe[lignes][colonnes] = 1;
                }
            }
        }
    }
}

void affichage_grille() {
    for(int i = 0; i < taille_lab; i++) {
        for(int j = 0; j < taille_lab; j++) {
            printf("%d\t", labyrinthe[i][j]);
        }
        putchar('\n');
    }
}

void remplissage_nb() {
    int nb = 0;
    for(lignes = 0; lignes < taille_lab; lignes++) {
        for(colonnes = 0; colonnes < taille_lab; colonnes++) {
            if(labyrinthe[lignes][colonnes] == 1) {
                nb++;
                labyrinthe[lignes][colonnes] = nb;
            }
        }
    }
    // Entrée et sortie
    labyrinthe[1][0] = nb;
    labyrinthe[taille_lab-2][taille_lab-1] = nb;
}

int terminer() {
    for(int i = 1; i < taille_lab; i++) {
        for(int j = 1; j < taille_lab; j++) {
            if(labyrinthe[i][j] != -1) {
                if(labyrinthe[i][j] != troue1) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void cassage_mur() {
    srand(time(NULL));
    while(terminer() == 0) {
        int x = rand() % (taille_lab - 2) + 1;
        int y = rand() % (taille_lab - 2) + 1;
        troue1 = -1;
        troue2 = -1;
        
        if(labyrinthe[x][y] == -1) {
            if(labyrinthe[x + 1][y] == -1) {
                troue1 = labyrinthe[x][y - 1];
                troue2 = labyrinthe[x][y + 1];
            } else {
                troue1 = labyrinthe[x + 1][y];
                troue2 = labyrinthe[x - 1][y];
            }
        }
        
        if(troue1 != troue2 && troue1 != -1 && troue2 != -1) {
            labyrinthe[x][y] = troue1;
            
            for(int i = 0; i < taille_lab; i++) {
                for(int j = 0; j < taille_lab; j++) {
                    if(labyrinthe[i][j] == troue2) {
                        labyrinthe[i][j] = troue1;
                    }
                }
            }
        }
    }
    
    for(int i = 0; i < taille_lab; i++) {
        for(int j = 0; j < taille_lab; j++) {
            if(labyrinthe[i][j] != -1) {
                labyrinthe[i][j] = 0;
            }
        }
    }
}

void resolution() {
    distance = 1;
    labyrinthe[taille_lab-2][taille_lab-1] = 1;
    
    while(labyrinthe[1][0] == 0) {
        distance++;
        for(int i = taille_lab - 2; i > 0; i--) {
            for(int j = taille_lab - 1; j > 0; j--) {
                if(labyrinthe[i][j] == distance - 1) {
                    if(labyrinthe[i + 1][j] == 0) {
                        labyrinthe[i + 1][j] = distance;
                    }
                    if(labyrinthe[i - 1][j] == 0) {
                        labyrinthe[i - 1][j] = distance;
                    }
                    if(labyrinthe[i][j + 1] == 0) {
                        labyrinthe[i][j + 1] = distance;
                    }
                    if(labyrinthe[i][j - 1] == 0) {
                        labyrinthe[i][j - 1] = distance;
                    }
                }
            }
        }
    }
    
    int i = 1;
    int j = 0;
    labyrinthe[1][0] = -2;
    
    while(labyrinthe[taille_lab-2][taille_lab-1] == 1) {
        if(labyrinthe[i + 1][j] == distance - 1) {
            labyrinthe[i + 1][j] = -2;
            i++;
        } else if(labyrinthe[i - 1][j] == distance - 1) {
            labyrinthe[i - 1][j] = -2;
            i--;
        } else if(labyrinthe[i][j + 1] == distance - 1) {
            labyrinthe[i][j + 1] = -2;
            j++;
        } else if(labyrinthe[i][j - 1] == distance - 1) {
            labyrinthe[i][j - 1] = -2;
            j--;
        }
        distance--;
    }
}