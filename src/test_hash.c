#include <stdio.h>
#include <stdlib.h>
#include "../header/trie_hash.h"  // Inclusion du fichier d'en-tête contenant les fonctions pour gérer le trie basé sur hash
#include "../header/test_hash.h"  // Inclusion du fichier d'en-tête spécifique aux tests sur le trie
#include <string.h>     // Inclusion de la bibliothèque pour la gestion des chaînes de caractères

// Fonction principale pour tester le trie basé sur hash
void testHash() {
    // Déclaration et création d'un trie avec une capacité de 100 nœuds
    Trie trie = createTrie(100);

    // Définition de plusieurs mots à insérer dans le trie
    unsigned char word1[] = "acagt";
    unsigned char word2[] = "acgt";
    unsigned char word3[] = "gat";
    unsigned char word4[] = "cagt";

    // Insertion des mots dans le trie et vérification de leur présence
    insertInTrie(trie, word1);
    afficherIsInTrie(trie, word1);

    insertInTrie(trie, word2);
    afficherIsInTrie(trie, word2);

    insertInTrie(trie, word3);
    afficherIsInTrie(trie, word3);

    insertInTrie(trie, word4);
    afficherIsInTrie(trie, word4);

    // Test avec un mot qui n'a pas été inséré dans le trie
    unsigned char notInTrieWord[] = "test";
    printf("\nTest sur un mot qui n'a pas ete insere dans le trie\n");
    afficherIsInTrie(trie, notInTrieWord);

    // Insertion des préfixes d'un mot dans le trie
    unsigned char motPrefixe[] = "bonjour";
    printf("\nInsertion des prefixes du mot %s dans le trie\n", motPrefixe);
    insertPrefixes(trie, motPrefixe);

    // Vérification des préfixes dans le trie
    showPrefixeIsInTrie(trie, motPrefixe);

    // Insertion des suffixes d'un autre mot dans le trie
    unsigned char motSuffixe[] = "hello";
    printf("\nInsertion des suffixes du mot %s dans le trie\n", motSuffixe);
    insertSufixes(trie, motSuffixe);

    // Vérification des suffixes dans le trie
    showSuffixeIsInTrie(trie, motSuffixe);

    // Insertion des facteurs d'un mot dans le trie
    unsigned char motFacteur[] = "abaabab";
    insertFactors(trie, motFacteur);

    // Vérification des facteurs dans le trie
    showFacteurIsInTrie(trie, motFacteur);
}

// Fonction qui affiche si un mot est présent dans le trie
void afficherIsInTrie(Trie trie, unsigned char* word) {
    printf("Le mot %s est dans le trie? ", word);
    isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
}

// Fonction qui affiche si les préfixes d'un mot sont présents dans le trie
void showPrefixeIsInTrie(Trie trie, unsigned char *word) {
    int sizeOfWord = strlen((const char *)word);
    char *prefixe = (char*)malloc((sizeOfWord + 1) * sizeof(char));  // Allocation mémoire pour stocker le préfixe

    // Boucle pour tester chaque préfixe du mot
    for (int i = 0; i <= sizeOfWord; i++) {
        strncpy(prefixe, (const char *)word, i);  // Copie du préfixe actuel
        prefixe[i] = '\0';  // Ajout du caractère de fin de chaîne
        printf("Prefixe %s\n", prefixe);
        printf("Le prefixe %s est dans le trie? ", prefixe);
        isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
    }

    free(prefixe);  // Libération de la mémoire allouée
    printf("\n");
}

// Fonction qui affiche si les suffixes d'un mot sont présents dans le trie
void showSuffixeIsInTrie(Trie trie, unsigned char *word) {
    int sizeOfWord = strlen((const char *)word);
    char *suffixe = (char*)malloc((sizeOfWord + 1) * sizeof(char));  // Allocation mémoire pour stocker le suffixe

    printf("Test si les suffixes du mot %s sont dans le trie\n", word);

    // Boucle pour tester chaque suffixe du mot
    for (int i = sizeOfWord - 1; i >= 0; i--) {
        strncpy(suffixe, (const char *)(word + i), sizeOfWord - i);  // Copie du suffixe actuel
        suffixe[sizeOfWord - i] = '\0';  // Ajout du caractère de fin de chaîne
        printf("Le suffixe %s est dans le trie? ", suffixe);
        isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
    }

    free(suffixe);  // Libération de la mémoire allouée
    printf("\n");
}

// Fonction qui affiche si les facteurs (sous-chaînes) d'un mot sont présents dans le trie
void showFacteurIsInTrie(Trie trie, unsigned char *word) {
    int len = strlen((char *)word);
    printf("Test si les facteurs du mot %s sont dans le trie\n", word);

    // Boucle pour tester toutes les sous-chaînes possibles (facteurs) du mot
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            unsigned char facteur[j - i + 1];
            strncpy((char *)facteur, (char *)(word + i), j - i);  // Copie du facteur actuel
            facteur[j - i] = '\0';  // Ajout du caractère de fin de chaîne
            printf("Le facteur %s est dans le trie? ", facteur);
            isInTrie(trie, word) ? printf("oui\n") : printf("non\n");
        }
    }
}
