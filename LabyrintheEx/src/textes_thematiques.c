// textes_thematiques.c
#include "textes_thematiques.h"
#include "affichage_SDL.h"
#include "themes.h"
#include <string.h>
#include <stdio.h>

// Variable globale pour stocker les textes
TextesThematiques textes_theme;

// Fonction d'initialisation
void initialiser_textes_thematiques(void) {
    // Textes généraux
    strcpy(textes_theme.introduction, "Bienvenue dans LabyrinthEX, un voyage à travers des univers narratifs entrelacés. "
                             "Votre mission est de naviguer à travers ce labyrinthe dimensionnel pour collecter les fragments d'histoire dispersés.");
    
    strcpy(textes_theme.objectif, "Objectif : Explorez le labyrinthe pour trouver tous les fragments d'histoire (points colorés) "
                         "et reconstituez le récit complet avant que le temps ne s'écoule.");
    
    strcpy(textes_theme.elements, "• Point rouge : Votre position actuelle dans le multivers narratif.\n"
                         "• Point vert : Fragment d'origine - le début de votre quête.\n"
                         "• Point jaune : Fragment clé - élément essentiel à l'intrigue.\n"
                         "• Point blanc : Portail dimensionnel - passage à un autre niveau.\n"
                         "• Points bleus/violets : Fragments secondaires - enrichissent l'histoire.");
    
    strcpy(textes_theme.instructions, "Utilisez les touches directionnelles pour vous déplacer. "
                              "Chaque fragment collecté révèle une partie de l'histoire dans ce panneau. "
                              "Complétez le récit pour débloquer le prochain univers narratif.");
    
    strcpy(textes_theme.conseil, "Attention : Certains chemins peuvent changer au fil de votre progression, "
                        "représentant les différentes possibilités narratives qui s'ouvrent à vous.");
    
    // Textes pour les fragments adaptés au thème actuel
    // Odyssée d'Homère
    if (theme_actuel == 0) {
        strcpy(textes_theme.fragment_vert, "Vous avez trouvé le début de l'Odyssée ! L'histoire du retour d'Ulysse à Ithaque commence ici...");
        strcpy(textes_theme.fragment_jaune, "Fragment clé découvert ! La rencontre avec les sirènes marque un tournant dans le voyage.");
        strcpy(textes_theme.fragment_bleu, "Le cyclope Polyphème apparaît dans votre récit. Un souvenir douloureux du périple d'Ulysse.");
        strcpy(textes_theme.fragment_violet, "La magicienne Circé entre en scène. Ses sortilèges transformeront les compagnons d'Ulysse.");
        strcpy(textes_theme.fragment_blanc, "Portail vers le royaume d'Hadès ! Ulysse devra consulter l'ombre du devin Tirésias.");
        strcpy(textes_theme.fragment_rouge, "Vous êtes revenu au navire d'Ulysse. Un nouveau chapitre de l'Odyssée commence.");
    }
    // Tron Legacy
    else if (theme_actuel == 1) {
        strcpy(textes_theme.fragment_vert, "Connexion à la Grille établie ! Vous entrez dans le système informatique...");
        strcpy(textes_theme.fragment_jaune, "Disque d'identité récupéré ! Cet élément crucial contient votre code source.");
        strcpy(textes_theme.fragment_bleu, "Programme de sécurité neutralisé. Une nouvelle partie de la Grille s'ouvre à vous.");
        strcpy(textes_theme.fragment_violet, "Mémoire système récupérée. Des souvenirs de l'Ancien Réseau apparaissent.");
        strcpy(textes_theme.fragment_blanc, "Portail ISO activé ! Préparez-vous à explorer une zone du système encore inconnue.");
        strcpy(textes_theme.fragment_rouge, "Retour au point d'entrée. Un nouveau cycle système commence.");
    }
    // Batman: Gotham
    else if (theme_actuel == 2) {
        strcpy(textes_theme.fragment_vert, "Premier indice découvert ! L'enquête de Batman dans les rues de Gotham commence...");
        strcpy(textes_theme.fragment_jaune, "Informateur clé localisé ! Il révèle des informations cruciales sur les plans du criminel.");
        strcpy(textes_theme.fragment_bleu, "Radio de police interceptée. Un nouveau crime a été signalé dans un autre quartier.");
        strcpy(textes_theme.fragment_violet, "Journal intime trouvé. Il contient des informations sur les motivations du criminel.");
        strcpy(textes_theme.fragment_blanc, "Bat-signal activé ! Une urgence requiert votre présence immédiate ailleurs dans Gotham.");
        strcpy(textes_theme.fragment_rouge, "Retour à la Batcave. Un nouveau dossier d'enquête vous attend.");
    }
    // Tetris
    else if (theme_actuel == 3) {
        strcpy(textes_theme.fragment_vert, "Pièce S récupérée ! Le puzzle commence à prendre forme...");
        strcpy(textes_theme.fragment_jaune, "Pièce carrée obtenue ! Un élément stable pour votre construction.");
        strcpy(textes_theme.fragment_bleu, "Pièce J ajoutée à votre inventaire. Un nouveau motif se dessine.");
        strcpy(textes_theme.fragment_violet, "Pièce T découverte. Parfaite pour combler les espaces difficiles.");
        strcpy(textes_theme.fragment_blanc, "Pièce ligne trouvée ! L'élément parfait pour réaliser un Tetris complet.");
        strcpy(textes_theme.fragment_rouge, "Retour à la pièce Z. Une nouvelle séquence de blocs commence.");
    }
    // Avatar
    else if (theme_actuel == 4) {
        strcpy(textes_theme.fragment_vert, "Connexion à l'Arbre des Voix établie ! Vous commencez à entendre Eywa...");
        strcpy(textes_theme.fragment_jaune, "Graine sacrée d'Eywa trouvée ! Elle révèle des chemins cachés dans la forêt.");
        strcpy(textes_theme.fragment_bleu, "Esprit animal découvert. Il vous offre sa protection dans la forêt dangereuse.");
        strcpy(textes_theme.fragment_violet, "Mémoire Na'vi récupérée. D'anciens secrets de Pandora se dévoilent à vous.");
        strcpy(textes_theme.fragment_blanc, "Portail vers les Montagnes Flottantes activé ! Un nouveau territoire s'ouvre à vous.");
        strcpy(textes_theme.fragment_rouge, "Retour au clan. Un nouveau cycle de la lune de Pandora commence.");
    }
    // Totoro
    else if (theme_actuel == 5) {
        strcpy(textes_theme.fragment_vert, "Premier gland magique trouvé ! La forêt commence à révéler ses secrets...");
        strcpy(textes_theme.fragment_jaune, "Parapluie de Totoro découvert ! Un objet essentiel pour rencontrer l'esprit de la forêt.");
        strcpy(textes_theme.fragment_bleu, "Petit Totoro blanc aperçu. Il vous guide plus profondément dans la forêt.");
        strcpy(textes_theme.fragment_violet, "Noiraudes rassemblées. Elles transportent vos graines vers un lieu spécial.");
        strcpy(textes_theme.fragment_blanc, "Arrêt du Chat-bus trouvé ! Préparez-vous à voyager vers un endroit magique.");
        strcpy(textes_theme.fragment_rouge, "Retour à la maison. Un nouveau jour d'aventure commence près de la forêt.");
    }
    // Textes par défaut si aucun thème spécifique
    else {
        strcpy(textes_theme.fragment_vert, "Vous avez trouvé le fragment d'origine ! L'histoire commence...");
        strcpy(textes_theme.fragment_jaune, "Fragment clé découvert ! Un élément crucial vient d'être révélé.");
        strcpy(textes_theme.fragment_bleu, "Fragment secondaire collecté. Une nouvelle perspective s'ouvre à vous.");
        strcpy(textes_theme.fragment_violet, "Fragment secondaire ajouté à votre collection. L'intrigue s'épaissit.");
        strcpy(textes_theme.fragment_blanc, "Portail dimensionnel activé ! Préparez-vous à explorer un nouveau niveau narratif.");
        strcpy(textes_theme.fragment_rouge, "Vous êtes revenu à votre point de départ. Un nouveau cycle commence.");
    }
    
    // Initialiser le texte actuel
    textes_theme.texte_actuel = textes_theme.introduction;
    textes_theme.timer_affichage = 0;
    textes_theme.duree_affichage = 5000; // 5 secondes par défaut
    textes_theme.fragmentsCollectes = 0;
    textes_theme.totalFragments = 5; // Ajustez selon votre jeu
    
    printf("Textes thématiques initialisés pour le thème: %s\n", themes[theme_actuel].nom);
}

// Fonction pour afficher le texte thématique dans l'interface
// Dans textes_thematiques.c

void afficher_textes_thematiques(SDL_Surface* surface) {
    if (!textes_theme.texte_actuel) return;
    
    // Zone de texte (se positionne dans la zone de description du thème)
    SDL_Rect zone_texte = {LARGEUR_FENETRE - 290, 100, 260, 80};
    
    // Couleurs adaptées au thème actuel
    SDL_Color* couleur_fond = &themes[theme_actuel].couleur_fond;
    SDL_Color* couleur_texte = &themes[theme_actuel].couleur_texte;
    SDL_Color* couleur_accent = &themes[theme_actuel].couleur_accent;
    
    // Titre mieux mis en évidence
    SDL_Rect titre_texte = {zone_texte.x, zone_texte.y - 25, zone_texte.w, 20};
    SDL_FillRect(surface, &titre_texte, 
                SDL_MapRGB(surface->format, 
                          couleur_accent->r,
                          couleur_accent->g,
                          couleur_accent->b));

    // Texte simulé pour le titre (en attendant SDL_ttf)
    SDL_Rect ligne_titre = {
        titre_texte.x + 5,
        titre_texte.y + 5,
        titre_texte.w - 10,
        10
    };

    SDL_FillRect(surface, &ligne_titre, 
                SDL_MapRGB(surface->format, 
                          couleur_texte->r,
                          couleur_texte->g,
                          couleur_texte->b));
    
    // Dessiner le fond de la zone de texte
    SDL_FillRect(surface, &zone_texte, 
                SDL_MapRGB(surface->format, 
                          couleur_fond->r * 0.7f, 
                          couleur_fond->g * 0.7f, 
                          couleur_fond->b * 0.7f));
    
    // Bordure décorative
    SDL_Rect bordure_texte = {zone_texte.x - 2, zone_texte.y - 2, zone_texte.w + 4, zone_texte.h + 4};
    SDL_FillRect(surface, &bordure_texte, 
                SDL_MapRGB(surface->format, 
                          couleur_accent->r,
                          couleur_accent->g,
                          couleur_accent->b));
    SDL_FillRect(surface, &zone_texte, 
                SDL_MapRGB(surface->format, 
                          couleur_fond->r * 0.7f,
                          couleur_fond->g * 0.7f,
                          couleur_fond->b * 0.7f));
    
    // Simuler l'affichage du texte par des lignes
    int longueur_texte = strlen(textes_theme.texte_actuel);
    int nb_lignes = longueur_texte / 30 + 1; // Estimation grossière
    
    for (int i = 0; i < nb_lignes && i < 5; i++) {
        SDL_Rect ligne = {
            zone_texte.x + 5,
            zone_texte.y + 5 + i * 15,
            zone_texte.w - 10,
            10
        };
        
        // Ajuster la largeur de la ligne en fonction de la longueur estimée du texte
        int longueur_ligne = longueur_texte > 30 ? 30 : longueur_texte;
        ligne.w = (ligne.w * longueur_ligne) / 30;
        longueur_texte -= longueur_ligne;
        
        // Dessiner la ligne
        SDL_FillRect(surface, &ligne, 
                    SDL_MapRGB(surface->format, 
                              couleur_texte->r,
                              couleur_texte->g,
                              couleur_texte->b));
    }
    
    // Vérifier si c'est le moment de changer de texte
    if (textes_theme.timer_affichage > 0 && 
    (int)(SDL_GetTicks() - textes_theme.timer_affichage) > textes_theme.duree_affichage) {
        // Revenir au texte d'objectif après un temps défini
        textes_theme.texte_actuel = textes_theme.objectif;
        textes_theme.timer_affichage = 0;
    }
    
    // Afficher la progression des fragments
    SDL_Rect barre_fond = {zone_texte.x, zone_texte.y + zone_texte.h + 10, zone_texte.w, 15};
    SDL_FillRect(surface, &barre_fond, 
                SDL_MapRGB(surface->format, 40, 40, 40));
    
    // Barre de progression remplie en fonction des fragments collectés
    if (textes_theme.fragmentsCollectes > 0) {
        float proportion = (float)textes_theme.fragmentsCollectes / textes_theme.totalFragments;
        int largeur_barre = (int)(proportion * zone_texte.w);
        
        SDL_Rect barre_remplie = {zone_texte.x, zone_texte.y + zone_texte.h + 10, largeur_barre, 15};
        SDL_FillRect(surface, &barre_remplie, 
                    SDL_MapRGB(surface->format, 
                              couleur_accent->r,
                              couleur_accent->g,
                              couleur_accent->b));
    }
}

// Fonction pour changer le texte à afficher
void changer_texte_thematique(const char* cle) {
    if (strcmp(cle, "introduction") == 0) {
        textes_theme.texte_actuel = textes_theme.introduction;
    }
    else if (strcmp(cle, "objectif") == 0) {
        textes_theme.texte_actuel = textes_theme.objectif;
    }
    else if (strcmp(cle, "elements") == 0) {
        textes_theme.texte_actuel = textes_theme.elements;
    }
    else if (strcmp(cle, "instructions") == 0) {
        textes_theme.texte_actuel = textes_theme.instructions;
    }
    else if (strcmp(cle, "conseil") == 0) {
        textes_theme.texte_actuel = textes_theme.conseil;
    }
    
    // Réinitialiser le timer
    textes_theme.timer_affichage = 0;
}

// Fonction pour afficher un texte lié à un fragment collecté
void afficher_texte_fragment(const char* couleur) {
    if (strcmp(couleur, "vert") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_vert;
    }
    else if (strcmp(couleur, "jaune") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_jaune;
    }
    else if (strcmp(couleur, "bleu") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_bleu;
    }
    else if (strcmp(couleur, "violet") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_violet;
    }
    else if (strcmp(couleur, "blanc") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_blanc;
    }
    else if (strcmp(couleur, "rouge") == 0) {
        textes_theme.texte_actuel = textes_theme.fragment_rouge;
    }
    
    // Démarrer le timer pour changer automatiquement de texte après un délai
    textes_theme.timer_affichage = SDL_GetTicks();
    
    // Afficher un message dans la console pour débug
    printf("Fragment %s collecté! Texte thématique affiché.\n", couleur);
}

// Fonction pour mettre à jour la progression
void mettre_a_jour_progression(int fragmentsCollectes, int totalFragments) {
    textes_theme.fragmentsCollectes = fragmentsCollectes;
    textes_theme.totalFragments = totalFragments;
    
    printf("Progression mise à jour: %d/%d fragments collectés.\n", 
          fragmentsCollectes, totalFragments);
}

// Fonction de nettoyage
void liberer_textes_thematiques(void) {
    // Rien à faire dans cette implémentation simple,
    // car nous n'allouons pas de mémoire dynamiquement
    printf("Nettoyage des textes thématiques terminé.\n");
}