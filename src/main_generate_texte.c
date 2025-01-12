#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Vérifier si le bon nombre de paramètres a été passé
    if (argc != 3) {
        fprintf(stderr, "Utilisation: %s <longueur du texte> <taille de l'alphabet>\n", argv[0]);
        return 1;
    }

    // Récupérer les arguments
    int longueur = atoi(argv[1]);
    int taille_alphabet = atoi(argv[2]);

    // Vérifier la validité des arguments
    if (longueur <= 0 || taille_alphabet <= 0 || taille_alphabet > 256) {
        fprintf(stderr, "Erreur : longueur du texte et taille de l'alphabet doivent être des entiers positifs.\n");
        fprintf(stderr, "La taille de l'alphabet ne peut pas dépasser 256.\n");
        return 1;
    }

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Générer et afficher le texte pseudo-aléatoire
    for (int i = 0; i < longueur; i++) {
        char lettre =  (taille_alphabet < 256-48)? 48+(rand() % taille_alphabet) : (rand() % taille_alphabet);
        // char lettre =  (rand() % taille_alphabet);
        putchar(lettre);
    }


    return 0;
}
