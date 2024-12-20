#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../header/trie_hash.h"

/**
 * Fonction pour calculer la taille du tableau de hachage.
 * Elle multiplie le nombre maximal de nœuds par 11 pour avoir une taille
 * adaptée à la structure du trie.
 */
int hashSize(int maxNode) {
    return maxNode * 11;
}

/**
 * Fonction de hachage.
 * Elle prend en entrée un état `state`, une lettre `letter` et le nombre 
 * maximal de nœuds `maxNode`. Elle retourne la position dans le tableau de
 * hachage en utilisant une formule basée sur l'addition du nœud courant et 
 * de la lettre, modulo la taille du tableau de hachage.
 */
unsigned int hashFunction(int state, unsigned char letter, int maxNode) {
    int HASH_SIZE = hashSize(maxNode);
    return (state + letter) % HASH_SIZE;
}

/**
 * Fonction pour créer un trie.
 * Elle alloue dynamiquement un nouveau trie avec un nombre maximal de nœuds.
 * Le tableau des transitions est initialisé avec des listes chaînées, et 
 * les états terminaux sont initialisés à zéro.
 */
Trie createTrie(int maxNode) {
    Trie trie = (Trie)malloc(sizeof(struct _trie)); // Allocation de mémoire pour la structure _trie
    trie->maxNode = maxNode; // Initialisation du nombre maximal de nœuds
    trie->nextNode = 1;      // Le nœud initial est toujours le nœud 0
    int HASH_SIZE = hashSize(trie->maxNode); // Calcul de la taille du tableau de hachage
    trie->transition = (List *)calloc(HASH_SIZE, sizeof(List)); // Initialisation du tableau de transitions
    trie->finite = (char *)calloc(maxNode, sizeof(char)); // Initialisation du tableau des états terminaux
    return trie;
}

/**
 * Fonction pour insérer un mot dans le trie.
 * Le mot est parcouru caractère par caractère, et chaque transition est insérée 
 * dans le tableau de hachage. Si la transition n'existe pas, elle est créée.
 */
void insertInTrie(Trie trie, unsigned char *w) {
    int currentNode = 0; // Commence par le nœud initial

    // Parcourt chaque caractère du mot `w`
    for (int i = 0; w[i] != '\0'; i++) {
        // Calcule la position dans le tableau de hachage pour l'état courant et la lettre
        unsigned int h = hashFunction(currentNode, w[i], trie->maxNode);
        List entry = trie->transition[h]; // Récupère la liste de transitions pour cette clé hachée

        // Parcourt la liste chaînée à la recherche de la transition correspondante
        while (entry != NULL && !(entry->startNode == currentNode && entry->letter == w[i])) {
            entry = entry->next;
        }

        // Si la transition n'existe pas, on la crée
        if (entry == NULL) {
            entry = (List)malloc(sizeof(struct _list)); // Allocation pour une nouvelle transition
            entry->startNode = currentNode;             // Définition du nœud de départ
            entry->letter = w[i];                       // Définition de la lettre de transition
            entry->targetNode = trie->nextNode++;       // Le nœud cible devient le suivant disponible
            entry->next = trie->transition[h];          // Insertion en tête de la liste chaînée
            trie->transition[h] = entry;                // Mise à jour de la table de hachage
        }
        currentNode = entry->targetNode; // Passe au nœud suivant
    }
    trie->finite[currentNode] = 1; // Marque le dernier nœud comme terminal
}

/**
 * Fonction pour vérifier si un mot est présent dans le trie.
 * Elle parcourt le mot et suit les transitions dans le tableau de hachage.
 * Si une transition est manquante, le mot n'est pas dans le trie.
 */
int isInTrie(Trie trie, unsigned char *w) {
    int currentNode = 0; // Commence par le nœud initial

    // Parcourt chaque caractère du mot `w`
    for (int i = 0; w[i] != '\0'; i++) {
        // Calcule la position dans le tableau de hachage
        unsigned int h = hashFunction(currentNode, w[i], trie->maxNode);
        List entry = trie->transition[h]; // Récupère la liste de transitions pour cette clé hachée

        // Parcourt la liste chaînée pour trouver la transition
        while (entry != NULL && !(entry->startNode == currentNode && entry->letter == w[i])) {
            entry = entry->next;
        }

        // Si la transition n'existe pas, le mot n'est pas dans le trie
        if (entry == NULL) {
            return 0;
        }

        currentNode = entry->targetNode; // Passe au nœud suivant
    }
    return trie->finite[currentNode]; // Retourne si le nœud courant est terminal ou non
}

/**
 * Fonction pour insérer tous les préfixes d'un mot dans le trie.
 * on insert tout le mot et on marque les nœuds comme terminaux au fur et à mesure qu'on avance
 */
void insertPrefixes(Trie trie, unsigned char *word) {
      int currentNode = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        unsigned int h = hashFunction(currentNode, word[i], trie->maxNode);
        List entry = trie->transition[h];
        
        // Recherche si la transition existe déjà
        while (entry != NULL && !(entry->startNode == currentNode && entry->letter == word[i])) {
            entry = entry->next;
        }

        // Si la transition n'existe pas, on la crée
        if (entry == NULL) {
            entry = (List)malloc(sizeof(struct _list));
            entry->startNode = currentNode;
            entry->letter = word[i];
            entry->targetNode = trie->nextNode++;
            entry->next = trie->transition[h];
            trie->transition[h] = entry;
        }

        currentNode = entry->targetNode;
        
        // On marque les nœuds comme terminaux au fur et à mesure qu'on avance
        trie->finite[currentNode] = 1;
    }
}

/**
 * Fonction pour insérer tous les suffixes d'un mot dans le trie.
 * Elle parcourt le mot de la fin au début et insère chaque suffixe.
 */
void insertSufixes(Trie trie, unsigned char *word) {
    int sizeOfWord = strlen((const char *)word);
    char *suffixe = (char*)malloc((sizeOfWord + 1) * sizeof(char)); // Allocation pour le suffixe
    int i = sizeOfWord - 1;
    for (i = sizeOfWord - 1; i >= 0; i--) {
        strncpy(suffixe, (const char *)(word + i), sizeOfWord - i); // Copie le suffixe
        suffixe[sizeOfWord - i] = '\0'; // Ajoute la fin de chaîne
        printf("Suffixe %s \n", suffixe); // Affiche le suffixe
        insertInTrie(trie, (unsigned char *)suffixe); // Insère le suffixe dans le trie
    }
    free(suffixe); // Libère la mémoire
    printf("\n");
}

/**
 * Fonction pour insérer tous les facteurs (sous-chaînes) d'un mot dans le trie.
 * Elle parcourt toutes les sous-chaînes possibles et les insère dans le trie.
 */
void insertFactors(Trie trie, unsigned char *word) {
    int len = strlen((char *)word);
    printf("Insertion des facteurs du mot %s\n", word);

    // Parcourt toutes les sous-chaînes possibles
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            unsigned char facteur[j - i + 1];
            strncpy((char *)facteur, (char *)(word + i), j - i); // Copie la sous-chaîne
            facteur[j - i] = '\0'; // Ajoute la fin de chaîne
            printf("facteur: %s\n", facteur); // Affiche le facteur
            insertInTrie(trie, facteur); // Insère le facteur dans le trie
        }
    }
}
