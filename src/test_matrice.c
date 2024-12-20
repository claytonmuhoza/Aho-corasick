#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/test_matrice.h"
#include "../header/test_matrice.h"

/**
 * Fonction principale de test pour la matrice du trie.
 * Elle teste l'insertion de mots, de préfixes, de suffixes et de facteurs dans le trie.
 */
void testMatrice() {
    // Création d'un trie avec 60 nœuds maximum
    Trie trie = createTrie(60);
    printf("Trie créé avec succès\n");

    // Mots à insérer dans le trie
    unsigned char word1[] = "acagt";
    unsigned char word2[] = "acgt";
    unsigned char word3[] = "cagt";
    unsigned char motPrefixe[] = "bonjour";
    unsigned char motSuffixe[] = "hello";

    // Insertion des mots dans le trie et affichage du résultat
    printf("Insertion du mot %s dans le trie\n", word1);
    insertInTrie(trie, word1);
    afficherIsInTrie(trie, word1);

    printf("Insertion du mot %s dans le trie\n", word2);
    insertInTrie(trie, word2);
    afficherIsInTrie(trie, word2);

    printf("Insertion du mot %s dans le trie\n", word3);
    insertInTrie(trie, word3);
    afficherIsInTrie(trie, word3);

    // Test sur un mot qui n'a pas encore été inséré dans le trie
    unsigned char notInTrieWord[] = "test";
    printf("\nTest sur un mot qui n'a pas été inséré dans le trie\n");
    afficherIsInTrie(trie, notInTrieWord);

    // Insertion des préfixes d'un mot dans le trie
    printf("\nInsertion des préfixes du mot %s dans le trie\n", motPrefixe);
    insertPrefixes(trie, motPrefixe);

    // Test des préfixes
    showPrefixeIsInTrie(trie, motPrefixe);

    // Insertion des suffixes d'un mot dans le trie
    printf("\nInsertion des suffixes du mot %s dans le trie\n", motSuffixe);
    insertSufixes(trie, motSuffixe);

    // Test des suffixes
    showSuffixeIsInTrie(trie, motSuffixe);

    // Insertion et test des facteurs d'un mot
    unsigned char motFacteur[] = "abaabab";
    insertFactors(trie, motFacteur);
    showFacteurIsInTrie(trie, motFacteur);

    // Affichage des données du trie
    afficherTrie(trie);
    displayFiniteState(trie);
}

/**
 * Fonction qui affiche si un mot donné est dans le trie.
 * Elle prend en paramètre le trie et le mot à vérifier.
 */
void afficherIsInTrie(Trie trie, unsigned char* word) {
    printf("Le mot %s est dans le trie: ", word);
    isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
}

/**
 * Fonction qui affiche si les préfixes d'un mot sont dans le trie.
 * Elle parcourt tous les préfixes possibles du mot et les vérifie dans le trie.
 */
void showPrefixeIsInTrie(Trie trie, unsigned char *word) {
    int sizeOfWord = strlen((const char *)word);
    char *prefixe = (char*)malloc((sizeOfWord + 1) * sizeof(char)); // Allocation mémoire pour le préfixe

    for (int i = 0; i <= sizeOfWord; i++) {
        strncpy(prefixe, (const char *)word, i); // Copie le préfixe actuel
        prefixe[i] = '\0'; // Ajoute la fin de chaîne
        printf("Le préfixe %s\n est dans le trie ? ", prefixe);
        isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
    }

    free(prefixe); // Libération de la mémoire
    printf("\n");
}

/**
 * Fonction qui affiche si les suffixes d'un mot sont dans le trie.
 * Elle parcourt tous les suffixes possibles du mot et les vérifie dans le trie.
 */
void showSuffixeIsInTrie(Trie trie, unsigned char *word) {
    int sizeOfWord = strlen((const char *)word);
    char *suffixe = (char*)malloc((sizeOfWord + 1) * sizeof(char)); // Allocation mémoire pour le suffixe

    printf("Test si les suffixes du mot %s sont dans le trie\n", word);
    for (int i = sizeOfWord - 1; i >= 0; i--) {
        strncpy(suffixe, (const char *)(word + i), sizeOfWord - i); // Copie le suffixe actuel
        suffixe[sizeOfWord - i] = '\0'; // Ajoute la fin de chaîne
        printf("Le suffixe %s est dans le trie ? ", suffixe);
        isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
    }

    free(suffixe); // Libération de la mémoire
    printf("\n");
}

/**
 * Fonction qui affiche si les facteurs (sous-chaînes) d'un mot sont dans le trie.
 * Elle parcourt toutes les sous-chaînes du mot et les vérifie dans le trie.
 */
void showFacteurIsInTrie(Trie trie, unsigned char *word) {
    int len = strlen((char *)word);
    printf("Test si les facteurs du mot %s sont dans le trie\n", word);

    // Parcourt toutes les sous-chaînes du mot
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            unsigned char facteur[j - i + 1];
            strncpy((char *)facteur, (char *)(word + i), j - i); // Copie le facteur actuel
            facteur[j - i] = '\0'; // Ajoute la fin de chaîne
            printf("Le facteur %s \nest dans le trie ? ", facteur);
            isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
        }
    }
}
