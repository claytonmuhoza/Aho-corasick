#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Vérifier si le bon nombre de paramètres a été passé
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <nombre de mots> <longueur minimale> <longueur maximale> <taille de l'alphabet>\n", argv[0]);
        return 1;
    }

    // Récupérer les arguments
    int nombre_mots = atoi(argv[1]);
    int longueur_min = atoi(argv[2]);
    int longueur_max = atoi(argv[3]);
    int taille_alphabet = atoi(argv[4]);

    // Vérifier la validité des arguments
    if (nombre_mots <= 0 || longueur_min <= 0 || longueur_max < longueur_min || taille_alphabet <= 0 || taille_alphabet > 256) {
        fprintf(stderr, "Erreur : tous les paramètres doivent être des entiers positifs.\n");
        fprintf(stderr, "La longueur maximale doit être >= à la longueur minimale.\n");
        fprintf(stderr, "La taille de l'alphabet ne peut pas dépasser 256.\n");
        return 1;
    }

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Générer les mots pseudo-aléatoires
    for (int i = 0; i < nombre_mots; i++) {
        // Déterminer la longueur aléatoire du mot
        int longueur_mot = longueur_min + (rand() % (longueur_max - longueur_min + 1));

        // Générer un mot de la longueur déterminée
        for (int j = 0; j < longueur_mot; j++) {
            char lettre = (taille_alphabet < 256-48)? 48+(rand() % taille_alphabet) : (rand() % taille_alphabet);
            // char lettre = (rand() % taille_alphabet);
            putchar(lettre);
        }

        // Passer à la ligne suivante après chaque mot
        putchar('\n');
    }

    return 0;
}
