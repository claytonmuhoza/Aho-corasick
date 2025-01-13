#ifndef TRIE_HACHAGE_H
#define TRIE_HACHAGE_H


typedef struct _list *List;

struct _list {
    int startNode, targetNode;
    unsigned char letter;
    struct _list *next;
};

typedef struct _trie *Trie;

struct _trie {
    int maxNode; 
    int nextNode;
    List *transition; 
    char *finite; //tableau pour stocker les états terminaux
    int *suffix; //tableau pour stocker les suppleants
    int *occurrences; //tableau pour stocker les occurrences
};
// Fonction pour créer un trie avec un nombre maximum de nœuds
Trie createTrie(int maxNode);

// Fonction pour insérer un mot dans le trie
void insertInTrie(Trie trie, const char *w);

// Fonction pour calculer la taille du tableau de hachage nécessaire en fonction du nombre de nœuds maximum
int hashSize(int maxNode);
/**
 * Fonction pour calculer la taille du tableau de hachage.
 * Elle multiplie le nombre maximal de nœuds par 11 pour avoir une taille
 * adaptée à la structure du trie.
 */
int hashSize(int maxNode);
/**
 * Fonction de hachage.
 * Elle prend en entrée un état `state`, une lettre `letter` et le nombre 
 * maximal de nœuds `maxNode`. Elle retourne la position dans le tableau de
 * hachage en utilisant une formule basée sur l'addition du nœud courant et 
 * de la lettre, modulo la taille du tableau de hachage.
 */
unsigned int hashFunction(int state, unsigned char letter, int maxNode);

/**
 * Fonction pour créer un trie.
 * Elle alloue dynamiquement un nouveau trie avec un nombre maximal de nœuds.
 * Le tableau des transitions est initialisé avec des listes chaînées, et 
 * les états terminaux sont initialisés à zéro.
 */
Trie createTrie(int maxNode);
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
// fonction pour insérer un mot dans le trie
void insertInTrie(Trie trie, const char *mot);
// fonction pour construire les liens de suppléance
void buildSuffixLinks(Trie trie);
// Fonction pour rechercher les occurrences des mots du trie dans un texte. 
int searchOccurrences(Trie trie, const char *text);
// Calculer la taille maximale du trie
int calculateTrieSize(const char *filename);
// Charger les mots du fichier dans le trie
void loadWords(Trie trie,const char *filename);
#endif