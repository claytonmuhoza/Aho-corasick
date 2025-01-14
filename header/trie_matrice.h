#ifndef TRIE_MATRICE_H
#define TRIE_MATRICE_H

// Structure pour les éléments de la file
typedef struct _ElementFile {
    int node;
    struct _ElementFile *next;
} ElementFile;

// Structure de la file
typedef struct _FileNode {
    ElementFile *head;
    ElementFile *tail;
} FileNode;

// Initialiser une file
FileNode *createFile();

// Enfiler un élément dans la file
void enfiler(FileNode *file, int value);

// Défiler un élément de la file
int defiler(FileNode *file);

// Vérifier si la file est vide
int estVide(FileNode *file);

// Libérer la mémoire de la file
void freeFile(FileNode *file);

// Structure représentant un trie
typedef struct _trie {
    int maxNode;
    int nextNode;
    int **transition;
    int *suffix;
    int *finite;
    int *occurrences;
} *Trie;

// Création d'un trie
Trie createTrie(int maxNode);
// Insérer un mot dans le trie
void insertWord(Trie trie, const char *word);
// Construire les liens de suffixe
void buildSuffixLinks(Trie trie);

// Rechercher les occurrences des motifs dans un texte
int searchOccurrences(Trie trie, const char *text);

// Libérer la mémoire allouée au trie
void freeTrie(Trie trie);
// Calculer la taille maximale du trie
int calculateTrieSize(const char *filename);

// Charger les mots dans le trie
void loadWords(Trie trie, const char *filename);
#endif