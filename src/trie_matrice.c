#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../header/trie_matrice.h"

// Fonction pour créer le trie
Trie createTrie(int max_node)
{
    // Allocation memoire pour le trie
    Trie trie = malloc(sizeof(struct _trie));

    // Verification si l'allocation a reussi, sinon afficher un message d'erreur
    if (trie == NULL) {
        fprintf(stderr, "Erreur d'allocation memoire pour le trie.\n");
        exit(EXIT_FAILURE); // Sortie en cas d'echec
    }

    // Initialisation de la valeur du nombre maximal de nœuds
    trie->maxNode = (int)max_node;

    trie->nextNode = 1; // Le premier nœud disponible sera 1, car l'etat initial est 0

    // Allocation memoire pour la matrice de transition
    trie->transition = (int**)malloc(max_node * sizeof(int*));
    trie->suffixLink = calloc(max_node, sizeof(int)); // Allocation pour les liens de suffixe (initialises à 0)
    trie->finite = (char*)calloc(max_node, sizeof(char)); // Allocation pour les etats terminaux (initialises à 0)

    if (trie->transition == NULL) {
        // Si l'allocation echoue, liberer la memoire et quitter
        free(trie->transition);
        exit(EXIT_FAILURE);
    }

    // Initialisation de chaque ligne de la matrice de transition
    for (int i = 0; i < max_node; i++) {
        // Allocation de memoire pour chaque nœud de la matrice de transition (pour chaque lettre possible)
        trie->transition[i] = (int *)calloc(UCHAR_MAX, sizeof(int));
        if (trie->transition[i] == NULL) {
            // Si l'allocation echoue, quitter
            exit(EXIT_FAILURE);
        }

        // Initialisation des transitions à -1 (aucune transition par defaut)
        memset(trie->transition[i], -1, UCHAR_MAX * sizeof(int));
    }
    return trie; // Retourne le trie cree
}

// Fonction pour afficher les etats terminaux du trie
void displayFiniteState(Trie trie)
{
    printf("Liste des etats terminaux:");
    for (int i = 0; i < trie->maxNode; i++) {
        if (trie->finite[i]) {
            printf(" %d ", i); // Affichage de l'indice des etats terminaux
        }
    }
    printf("\n");
}

// Fonction pour afficher la table de transition du trie
void afficherTrie(Trie trie)
{
    int max_node = trie->maxNode;
    printf("Table de transition\n");
    
    // Parcourt chaque nœud du trie
    for (int i = 0; i < max_node; i++) {
        printf("%d:", i); // Affichage du nœud actuel
        for (int j = 0; j < UCHAR_MAX; j++) {
            if (trie->transition[i][j] != -1) {
                printf(" %c->%d", j, trie->transition[i][j]); // Affichage des transitions valides
            }
        }
        printf("\n");
    }
}

// Fonction pour inserer un mot dans le trie
void insertInTrie(Trie trie, unsigned char* word)
{
    int sizeOfWord = strlen((const char *)word); // Taille du mot à inserer
    int currentNode = 0; // Commence à partir du nœud racine (0)

    // Parcourt chaque lettre du mot
    for (int i = 0; i < sizeOfWord; i++) {
        unsigned letter = word[i];

        // Si aucune transition pour cette lettre, ajouter un nouveau nœud
        if (trie->transition[currentNode][letter] == -1) {
            trie->transition[currentNode][letter] = trie->nextNode; // Associer une transition vers un nouveau nœud
            currentNode = trie->nextNode; // Passer au nœud suivant
            trie->nextNode++; // Incrementer l'indice du prochain nœud disponible
        } else {
            // Si la transition existe dejà, suivre la transition
            currentNode = trie->transition[currentNode][letter];
        }
    }
    trie->finite[currentNode] = 1; // Marquer le nœud final comme terminal
}
// int get_link(Trie t,int v) {

//     if (t[v].fail == -1) {
//         if (v == 0 || t[v].fail == 0)
//             t[v].fail = 0;
//         else
//             t[v].fail= 0;//go(get_link(t,t[v].fail), t[v].fail);
//     }
//     return t[v].fail;
// }

// Fonction pour verifier si un mot est present dans le trie
int isInTrie(Trie trie, unsigned char *word)
{
    int currentNode = 0; // Commence à partir de la racine
    int sizeOfWord = strlen((const char *)word);

    // Parcourt chaque lettre du mot
    for (int i = 0; i < sizeOfWord; i++) {
        unsigned char letter = word[i];
        // Si aucune transition pour cette lettre, le mot n'est pas present
        if (trie->transition[currentNode][letter] == -1) {
            return 0; // Mot non trouve
        }
        // Suivre la transition
        currentNode = trie->transition[currentNode][letter];
    }
    return trie->finite[currentNode]; // Retourne si le mot se termine à un etat terminal
}

/**
 * Fonction pour inserer tous les prefixes d'un mot dans le trie
 * On inserer tout le mot dans le trie puis on rend tout les etat terminaux
*/
void insertPrefixes(Trie trie, unsigned char *word)
{
    int currentNode = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        
        if (trie->transition[currentNode][word[i]] == -1) {
            trie->transition[currentNode][word[i]] = trie->nextNode++;
        }
        
        currentNode = trie->transition[currentNode][word[i]];
        
        // On marque les nœuds comme terminaux au fur et à mesure qu'on avance
        trie->finite[currentNode] = 1;
    }
    printf("\n");
    
}

// Fonction pour inserer tous les suffixes d'un mot dans le trie
void insertSufixes(Trie trie, unsigned char *word)
{
    
    int sizeOfWord = strlen((const char *)word);
    char *suffixe = (char*)malloc((sizeOfWord + 1) * sizeof(char));

    // Pour chaque suffixe de longueur croissante, l'inserer dans le trie
    for (int i = sizeOfWord - 1; i >= 0; i--) {
        // Copier le suffixe dans la variable suffixe
        strncpy(suffixe, (const char *)(word + i), sizeOfWord - i);
        suffixe[sizeOfWord - i] = '\0'; // Terminer la chaîne avec '\0'

        printf("Suffixe %s \n", suffixe); // Afficher le suffixe
        insertInTrie(trie, (unsigned char *)suffixe); // Inserer dans le trie
    }
    free(suffixe); // Liberer la memoire allouee
    printf("\n");
}

// Fonction pour inserer tous les facteurs (sous-chaînes) d'un mot dans le trie
void insertFactors(Trie trie, unsigned char *word)
{
    int len = strlen((char *)word);
    printf("Insertion des facteurs du mot %s\n", word);

    // Pour chaque sous-chaîne, de longueur croissante, l'inserer dans le trie
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            unsigned char facteur[j - i + 1];
            strncpy((char *)facteur, (char *)(word + i), j - i); // Copier la sous-chaîne
            facteur[j - i] = '\0'; // Terminer la sous-chaîne avec '\0'
            printf("Facteur: %s\n", facteur); // Afficher le facteur
            insertInTrie(trie, facteur); // Inserer dans le trie
        }
    }
}
FileNode* creerFile()
{
    FileNode* file = (FileNode*)malloc(sizeof(FileNode));
    file->head = NULL;
    file->tail = NULL;
    return file;
}
//fonction pour enfiler un element dans la file
void enfiler(FileNode *file, int node)
{
   
    ElementFile *element = (ElementFile *)malloc(sizeof(ElementFile));
    element->node = node;
    element->next = NULL;
    if (file->head == NULL) {
        file->head = element;
        file->tail = element;
    } else {
        file->tail->next = element;
        file->tail = element;
    }
}
//fonction pour defiler un element de la file
int defiler(FileNode *file)
{
    
    if (file == NULL || file->head == NULL) {
        return -1;
    }
    int node = file->head->node;
    ElementFile *element = file->head;
    file->head = file->head->next;
    if (file->head == NULL) {
        file->tail = NULL;
    }
    free(element);
    return node;
}


// Fonction pour trouver le mot correspondant jusqu'à un nœud donné
char *findWord(Trie trie, int node) {
    if (node >= trie->nextNode) {
        fprintf(stderr, "Erreur : Nœud invalide %d.\n", node);
        return NULL;
    }

    char *word = malloc(trie->maxNode * sizeof(char));
    if (word == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le mot.\n");
        return NULL;
    }
    int index = 0;
    while (node != 0) { // Remonter jusqu'à la racine
        int parent = -1;
        char c = '\0';
        for (int i = 0; i < trie->maxNode; i++) {
            for (int ch = 0; ch < UCHAR_MAX; ch++) {
                if (trie->transition[i][ch] == node) {
                    parent = i;
                    c = (char)ch;
                    break;
                }
            }
            if (parent != -1) break;
        }
        if (parent == -1) {
            fprintf(stderr, "Erreur : Nœud parent non trouvé pour %d.\n", node);
            free(word);
            return NULL;
        }
        word[index++] = c; // Ajouter le caractère
        node = parent;     // Monter au parent
    }
    word[index] = '\0';
    // Inverser le mot
    for (int i = 0; i < index / 2; i++) {
        char temp = word[i];
        word[i] = word[index - i - 1];
        word[index - i - 1] = temp;
    }
    return word;
}

// Fonction pour calculer et retourner le suppléant d'un nœud donné
int findSuffixLink(Trie trie, int node) {
    if (node == 0) return 0; // Le suppléant de la racine est elle-même

    // Si le suppléant est déjà calculé, le retourner
    if (trie->suffixLink[node] != 0) {
        return trie->suffixLink[node];
    }

    // Récupérer le suppléant du parent
    int parent = 0;
    char charToParent = '\0';

    // Trouver le parent du nœud courant et l’arête (caractère) qui mène à ce nœud
    for (int i = 0; i < trie->maxNode; i++) {
        for (int ch = 0; ch < UCHAR_MAX; ch++) {
            if (trie->transition[i][ch] == node) {
                parent = i;
                charToParent = (char)ch;
                break;
            }
        }
        if (parent != 0) break;
    }

    if (parent == 0) {
        fprintf(stderr, "Erreur : Impossible de trouver le parent du nœud %d.\n", node);
        return 0; // Défaut : retourner 0 si le parent n'est pas trouvé
    }

    // Récursivement calculer le suppléant du parent
    int parentSuffixLink = findSuffixLink(trie, parent);

    // Chercher le nœud correspondant au caractère via le suppléant du parent
    while (parentSuffixLink != 0 && trie->transition[parentSuffixLink][(unsigned char)charToParent] == -1) {
        parentSuffixLink = trie->suffixLink[parentSuffixLink];
    }

    // Déterminer le suppléant final
    if (trie->transition[parentSuffixLink][(unsigned char)charToParent] != -1) {
        trie->suffixLink[node] = trie->transition[parentSuffixLink][(unsigned char)charToParent];
    } else {
        trie->suffixLink[node] = 0;
    }

    return trie->suffixLink[node];
}