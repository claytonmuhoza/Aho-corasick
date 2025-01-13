#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../header/trie_matrice.h"
#define ALPHABET_SIZE 256  // Taille maximale pour un alphabet dynamique



// Initialiser une file
FileNode *createFile() {
    FileNode *file = (FileNode *)malloc(sizeof(FileNode));
    file->head = file->tail = NULL;
    return file;
}

// Enfiler un élément dans la file
void enfiler(FileNode *file, int value) {
    ElementFile *newElement = (ElementFile *)malloc(sizeof(ElementFile));
    newElement->node = value;
    newElement->next = NULL;

    if (file->tail) {
        file->tail->next = newElement;
    } else {
        file->head = newElement;
    }
    file->tail = newElement;
}

// Défiler un élément de la file
int defiler(FileNode *file) {
    if (!file->head) {
        fprintf(stderr, "Erreur : Tentative de défilage dans une file vide.\n");
        exit(EXIT_FAILURE);
    }

    ElementFile *temp = file->head;
    int value = temp->node;
    file->head = file->head->next;

    if (!file->head) {
        file->tail = NULL;
    }

    free(temp);
    return value;
}

// Vérifier si la file est vide
int estVide(FileNode *file) {
    return file->head == NULL;
}

// Libérer la mémoire de la file
void freeFile(FileNode *file) {
    ElementFile *current = file->head;
    while (current) {
        ElementFile *next = current->next;
        free(current);
        current = next;
    }
    free(file);
}



// Création d'un trie
Trie createTrie(int maxNode) {
    Trie trie = (Trie)malloc(sizeof(struct _trie));
    trie->maxNode = maxNode;
    trie->nextNode = 1;
    trie->transition = (int **)malloc(maxNode * sizeof(int *));
    for (int i = 0; i < maxNode; i++) {
        trie->transition[i] = (int *)calloc(ALPHABET_SIZE, sizeof(int));
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            trie->transition[i][j] = -1;
        }
    }
    trie->suffix = (int *)calloc(maxNode, sizeof(int));
    trie->finite = (int *)calloc(maxNode, sizeof(int));
    trie->occurrences = (int *)calloc(maxNode, sizeof(int)); // Initialisation des occurrences à zéro
    return trie;
}

// Insérer un mot dans le trie
void insertWord(Trie trie, const char *word) {
    int node = 0;
    for (int i = 0; word[i]; i++) {
        unsigned char c = (unsigned char)word[i];
        //si la transition n'existe pas, on la crée
        if (trie->transition[node][c] == -1) {
            trie->transition[node][c] = trie->nextNode;// Associer une transition vers un nouveau nœud
            trie->nextNode++; // Incrementer l'indice du prochain nœud disponible
        }
        //on passe au noeud suivant en suivant la transition
        node = trie->transition[node][c];
    }

    trie->finite[node] = 1; // Marquer le nœud final comme terminal
    trie->occurrences[node]++; // Incrémenter le compteur pour ce mot
}

// Construire les liens de suffixe
void buildSuffixLinks(Trie trie) {
    // Créer une file pour le traitement en largeur
    FileNode *file = createFile();

    // Initialiser les liens de suffixe pour les transitions directes depuis la racine
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (trie->transition[0][c] != -1) {
            trie->suffix[trie->transition[0][c]] = 0; // Les suffixes des enfants directs de la racine pointent vers la racine
            enfiler(file, trie->transition[0][c]); // Enfiler ces nœuds pour traitement ultérieur
        } else {
            trie->transition[0][c] = 0; // Les transitions manquantes pointent vers la racine
        }
    }

    // Traiter les nœuds en largeur
    while (!estVide(file)) {
        int node = defiler(file); // Défiler un nœud

        // Traiter toutes les transitions de ce nœud
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (trie->transition[node][c] != -1) {
                int child = trie->transition[node][c]; // Obtenir le nœud enfant
                int suffix = trie->suffix[node]; // Obtenir le suffixe du nœud actuel

                // Trouver le suffixe approprié pour l'enfant
                while (trie->transition[suffix][c] == -1) {
                    suffix = trie->suffix[suffix];
                }
                trie->suffix[child] = trie->transition[suffix][c]; // Définir le suffixe de l'enfant
                // Ajouter les occurrences du suffixe au nœud enfant
                trie->occurrences[child] += trie->occurrences[trie->suffix[child]];
                enfiler(file, child); // Enfiler l'enfant pour traitement ultérieur
            }
        }
    }

    // Libérer la mémoire de la file
    freeFile(file);
}

// Rechercher les occurrences des motifs dans un texte
int searchOccurrences(Trie trie, const char *text) {
    int node = 0;
    int count = 0;

    for (int i = 0; text[i]; i++) {
        unsigned char c = (unsigned char)text[i];
        while (trie->transition[node][c] == -1) {
            node = trie->suffix[node];
        }
        node = trie->transition[node][c];
        
        // Ajouter les occurrences de l'état courant au compteur total
        count += trie->occurrences[node];
    }

    return count;
}

// Libérer la mémoire allouée au trie
void freeTrie(Trie trie) {
    for (int i = 0; i < trie->maxNode; i++) {
        free(trie->transition[i]);
    }
    free(trie->transition);
    free(trie->suffix);
    free(trie->finite);
    free(trie);
}

// Calculer la taille maximale du trie
int calculateTrieSize(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier de mots");
        exit(EXIT_FAILURE);
    }

    int size = 1; // Racine
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        size += strlen(buffer);
    }
    fclose(file);
    return size;
}

// Charger les mots dans le trie
void loadWords(Trie trie, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier de mots");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Supprimer le saut de ligne
        insertWord(trie, buffer);
    }
    fclose(file);
}