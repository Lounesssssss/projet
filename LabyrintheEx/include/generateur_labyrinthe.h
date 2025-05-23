#ifndef GENERATEUR_LABYRINTHE_H
#define GENERATEUR_LABYRINTHE_H

#define taille_lab 51  // Taille impaire pour l'algorithme de Kruskal

extern int labyrinthe[taille_lab][taille_lab];
extern int lignes;
extern int colonnes;
extern int troue1;
extern int troue2;
extern int distance;

// Fonctions de génération
void creation_grille(void);
void affichage_grille(void);
void remplissage_nb(void);
int terminer(void);
void cassage_mur(void);
void resolution(void);

#endif