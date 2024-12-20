#ifndef TRIE_HASH_H
#define TRIE_HASH_H

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
    char *finite;
};

// Fonction pour créer un trie avec un nombre maximum de nœuds
Trie createTrie(int maxNode);

// Fonction pour insérer un mot dans le trie
void insertInTrie(Trie trie, unsigned char *w);

// Fonction pour vérifier si un mot est présent dans le trie
int isInTrie(Trie trie, unsigned char *w);

// Fonction pour insérer les préfixes d'un mot dans le trie
void insertPrefixes(Trie trie, unsigned char *word);

// Fonction pour insérer les suffixes d'un mot dans le trie
void insertSufixes(Trie trie, unsigned char *word);

// Fonction pour insérer tous les facteurs (sous-chaînes) d'un mot dans le trie
void insertFactors(Trie trie, unsigned char *w);

// Fonction pour calculer la taille du tableau de hachage nécessaire en fonction du nombre de nœuds maximum
int hashSize(int maxNode);

#endif
