#ifndef TRIE_H
#define TRIE_H

// Structure représentant un trie avec une matrice de transition
struct _trie {
    int maxNode;       /* Nombre maximal de nœuds du trie */
    int nextNode;      /* Indice du prochain nœud disponible */
    int **transition;  /* Matrice de transition où chaque nœud peut avoir plusieurs transitions vers d'autres nœuds */
    int fail; 
    int *suffixLink;   /* Tableau des suppléants */       
    char *finite;      /* Tableau indiquant les états terminaux (où un mot peut se terminer) */
};



// Structure pour les éléments de la file
typedef struct _ElementFile ElementFile;
struct _ElementFile{
    int node;
    ElementFile *next;
};
// Structure de la file
typedef struct _FileNode FileNode;
struct _FileNode{
    ElementFile *head;
    ElementFile *tail;
};
// Fonction pour enfiler un élément dans la file
void enfiler(FileNode *file, int node);
// Foncton pour defiler un element de la file
int defiler(FileNode *file);

FileNode* creerFile();


// Définition du type Trie comme un pointeur vers la structure _trie

typedef struct _trie *Trie;
//construction des liens de suppleance
void calculSuppleant(Trie trie);
// Fonction pour créer un trie avec un nombre maximal de nœuds donné
Trie createTrie(int max_node);

// Fonction pour insérer un mot dans un trie
void insertInTrie(Trie trie, unsigned char* word);

// Fonction pour afficher la structure du trie (transitions et états)
void afficherTrie(Trie trie);

// Fonction pour afficher les états terminaux d'un trie
void displayFiniteState(Trie trie);

// Fonction pour vérifier si un mot est contenu dans un trie
int isInTrie(Trie trie, unsigned char *word);

// Fonction pour insérer les préfixes d'un mot dans un trie
void insertPrefixes(Trie trie, unsigned char *word);

// Fonction pour insérer les suffixes d'un mot dans un trie
void insertSufixes(Trie trie, unsigned char *word);

// Fonction pour insérer tous les facteurs d'un mot dans un trie
void insertFactors(Trie trie, unsigned char *word);
// calculer le fail
void calculFail(Trie trie);
// Fonction pour calculer et retourner le suppléant d'un nœud donné
int findSuffixLink(Trie trie, int node);
#endif // TRIE_H
