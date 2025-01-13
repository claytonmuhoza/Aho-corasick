#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../header/trie_hachage.h"

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
    return (state *256 + letter) % HASH_SIZE;
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
    trie->suffix = (int *)calloc(maxNode, sizeof(int)); // Initialisation du tableau des suffixes
    trie->occurrences = (int *)calloc(maxNode, sizeof(int)); // Initialisation des occurrences à 0
    return trie;
}
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

/**
 * Fonction pour insérer un mot dans le trie.
 * Le mot est parcouru caractère par caractère, et chaque transition est insérée 
 * dans le tableau de hachage. Si la transition n'existe pas, elle est créée.
 */
void insertInTrie(Trie trie, const char *mot) {
    unsigned char *w = (unsigned char *)mot;
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
    trie->occurrences[currentNode]++; // Incrémente le nombre d'occurrences
}

void buildSuffixLinks(Trie trie) {
    FileNode *file = createFile(trie->maxNode);

    // Initialisation des liens suffixes
    for (int i = 0; i < 256; i++) {
        unsigned int h = hashFunction(0, i, trie->maxNode);
        List entry = trie->transition[h];
        while (entry) {
            // queue[rear++] = entry->targetNode;
            enfiler(file, entry->targetNode);
            trie->suffix[entry->targetNode] = 0; // Pas de suffixe pour les nœuds de niveau 1
            entry = entry->next;
        }
    }
    while (!estVide(file)) {
        int currentNode = defiler(file);
        for (int i = 0; i < 256; i++) {
            unsigned int h = hashFunction(currentNode, i, trie->maxNode);
            List entry = trie->transition[h];

            while (entry) {
                int target = entry->targetNode;
                int suffix = trie->suffix[currentNode];

                // Recherche d'un suffixe valide
                while (suffix && !trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]) {
                    suffix = trie->suffix[suffix];
                }

                if (trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]) {
                    suffix = trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]->targetNode;
                }

                trie->suffix[target] = suffix;
                // Propagation des occurrences
                trie->occurrences[target] += trie->occurrences[suffix];
                enfiler(file,target);
                entry = entry->next;
            }
        }
    }

    freeFile(file);
}
/**
 * Fonction pour rechercher les occurrences des mots du trie dans un texte.
 * 
 */
int searchOccurrences(Trie trie, const char *text) {
    int currentNode = 0;
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        // Recherche d'une transition valide
        while (currentNode && !trie->transition[hashFunction(currentNode, c, trie->maxNode)]) {
            currentNode = trie->suffix[currentNode];
        }
        // Si la transition existe, on passe au nœud suivant
        if (trie->transition[hashFunction(currentNode, c, trie->maxNode)]) {
            currentNode = trie->transition[hashFunction(currentNode, c, trie->maxNode)]->targetNode;
        }

        count += trie->occurrences[currentNode]; // Incrémente le nombre d'occurrences
    }

    return count; // Retourne le nombre total d'occurrences
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
void loadWords(Trie trie,const char *filename){ 
    FILE* fichier = fopen(filename, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : Le fichier est nul.\n");
        return;
    }
    int MAX_LINE_LENGTH  = 1024;
    unsigned char ligne[MAX_LINE_LENGTH]; // Buffer pour stocker chaque ligne
    while (fgets((char*)ligne, MAX_LINE_LENGTH, fichier) != NULL) {
        // Supprimer le caractère de fin de ligne '\n' si présent
        size_t longueur = strlen((char*)ligne);
        if (longueur > 0 && ligne[longueur - 1] == '\n') {
            ligne[longueur - 1] = '\0';
        }

        // Appeler la fonction pour insérer dans le trie
        insertInTrie(trie,(char*)ligne);
    }

    if (ferror(fichier)) {
        perror("Erreur lors de la lecture du fichier");
    }
}
