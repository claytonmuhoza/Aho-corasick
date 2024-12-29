#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define ALPHABET_SIZE 256

// Structure représentant un trie avec une matrice de transition
typedef struct _trie {
    int maxNode;        // Nombre maximal de nœuds du trie
    int nextNode;       // Indice du prochain nœud disponible
    int **transition;   // Matrice de transition
    int tail;           //      suppléants
    char *finite;       // Tableau indiquant les états terminaux
    int output;         // Indique si un mot se termine ici
} *Trie;

// Structure pour la file utilisée dans le parcours en largeur
typedef struct _queue {
    int *data;
    int front, rear, size;
    int capacity;
} Queue;

Queue *createQueue(int capacity) {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->data = (int *)malloc(capacity * sizeof(int));
    return queue;
}

bool isQueueEmpty(Queue *queue) {
    return queue->size == 0;
}

void enqueue(Queue *queue, int item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue *queue) {
    int item = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Création et initialisation du trie
Trie createTrie(int maxNode) {
    Trie trie = malloc(sizeof(struct _trie));
    trie->maxNode = maxNode;
    trie->nextNode = 1;
    trie->transition = (int **)malloc(maxNode * sizeof(int *));
    trie->suffixLink = (int *)calloc(maxNode, sizeof(int));
    trie->finite = (char *)calloc(maxNode, sizeof(char));

    for (int i = 0; i < maxNode; i++) {
        trie->transition[i] = (int *)calloc(ALPHABET_SIZE, sizeof(int));
        memset(trie->transition[i], -1, ALPHABET_SIZE * sizeof(int));
    }
    return trie;
}

// Ajout d'un mot dans le trie
void insertWord(Trie trie, const char *word) {
    int currentNode = 0;
    for (int i = 0; word[i]; i++) {
        unsigned char c = (unsigned char)word[i];
        if (trie->transition[currentNode][c] == -1) {
            trie->transition[currentNode][c] = trie->nextNode++;
        }
        currentNode = trie->transition[currentNode][c];
    }
    trie->finite[currentNode] = 1;
}

// Construction des liens suppléants
void buildSuffixLinks(Trie trie) {
    Queue *queue = createQueue(trie->maxNode);
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (trie->transition[0][c] != -1) {
            trie->suffixLink[trie->transition[0][c]] = 0;
            enqueue(queue, trie->transition[0][c]);
        } else {
            trie->transition[0][c] = 0;
        }
    }

    while (!isQueueEmpty(queue)) {
        int currentNode = dequeue(queue);
        for (int c = 0; c < ALPHABET_SIZE; c++) {
            int nextNode = trie->transition[currentNode][c];
            if (nextNode != -1) {
                int fallback = trie->suffixLink[currentNode];
                while (trie->transition[fallback][c] == -1) {
                    fallback = trie->suffixLink[fallback];
                }
                fallback = trie->transition[fallback][c];
                trie->suffixLink[nextNode] = fallback;
                trie->finite[nextNode] |= trie->finite[fallback];
                enqueue(queue, nextNode);
            }
        }
    }
    free(queue->data);
    free(queue);
}

// Recherche des occurrences dans le texte
int searchOccurrences(Trie trie, const char *text) {
    int currentNode = 0;
    int occurrences = 0;
    int textLength = strlen(text);
    bool *visited = (bool *)calloc(trie->maxNode, sizeof(bool));

    for (int i = 0; i < textLength; i++) {
        unsigned char c = (unsigned char)text[i];
        while (trie->transition[currentNode][c] == -1) {
            currentNode = trie->suffixLink[currentNode];
        }
        currentNode = trie->transition[currentNode][c];

        // Vérification des états finaux et parcours des suffix links
        int tempNode = currentNode;
        while (tempNode != 0 && !visited[tempNode]) {
            if (trie->finite[tempNode]) {
                occurrences++;
            }
            visited[tempNode] = true; // Marquer comme visité
            tempNode = trie->suffixLink[tempNode];
        }

        // Réinitialiser le tableau `visited` pour la prochaine position du texte
        memset(visited, 0, trie->maxNode * sizeof(bool));
    }

    free(visited);
    return occurrences;
}

// Libération de la mémoire allouée au trie
void freeTrie(Trie trie) {
    for (int i = 0; i < trie->maxNode; i++) {
        free(trie->transition[i]);
    }
    free(trie->transition);
    free(trie->suffixLink);
    free(trie->finite);
    free(trie);#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Assumons des caractères en minuscules anglais.

typedef struct Node {
    int next[ALPHABET_SIZE]; // Transitions.
    int fail;                // Lien de suppléance.
    int output;              // Indique si un mot se termine ici.
} Node;

#define MAX_STATES 1000

Node trie[MAX_STATES];
int stateCount = 1;

// Fonction pour convertir un caractère en indice.
int charToIndex(char c) {
    return c - 'a';
}

// Ajouter un mot dans le trie.
void insert(const char *word) {
    int currentState = 0;
    for (int i = 0; word[i]; i++) {
        int ch = charToIndex(word[i]);
        if (trie[currentState].next[ch] == -1) {
            trie[currentState].next[ch] = stateCount++;
        }
        currentState = trie[currentState].next[ch];
    }
    trie[currentState].output++;
}

// Construire les suppléants.
void buildFailureLinks() {
    int queue[MAX_STATES];
    int head = 0, tail = 0;

    // Initialiser les liens de suppléance pour le niveau 1.
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (trie[0].next[i] != -1) {
            trie[trie[0].next[i]].fail = 0;
            queue[tail++] = trie[0].next[i];
        } else {
            trie[0].next[i] = 0; // Liens vers l'état initial.
        }
    }

    // Parcours en largeur pour construire les liens.
    while (head < tail) {
        int state = queue[head++];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (trie[state].next[i] != -1) {
                int fail = trie[state].fail;
                while (trie[fail].next[i] == -1) {
                    fail = trie[fail].fail;
                }
                fail = trie[fail].next[i];
                trie[trie[state].next[i]].fail = fail;

                // Ajouter les sorties du nœud de suppléance.
                trie[trie[state].next[i]].output += trie[fail].output;

                queue[tail++] = trie[state].next[i];
            }
        }
    }
}

// Rechercher des mots dans le texte.
int search(const char *text) {
    int currentState = 0;
    int totalMatches = 0;

    for (int i = 0; text[i]; i++) {
        int ch = charToIndex(text[i]);
        while (trie[currentState].next[ch] == -1) {
            currentState = trie[currentState].fail;
        }
        currentState = trie[currentState].next[ch];
        totalMatches += trie[currentState].output;
    }

    return totalMatches;
}

int main() {
    // Initialiser le trie.
    memset(trie, -1, sizeof(trie));

    // Ajouter des mots au trie.
    insert("he");
    insert("she");
    insert("his");
    insert("hers");

    // Construire les liens de suppléance.
    buildFailureLinks();

    // Chercher des mots dans le texte.
    const char *text = "ahishers";
    printf("Nombre total d'occurrences : %d\n", search(text));

    return 0;
}

}

int main() {
    Trie trie = createTrie(5000); // Crée un trie avec une taille maximale de 5000 nœuds

    // Liste des mots à rechercher
    const char *words[] = {
        "cbbabc", "abb", "bcbbc", "cbbac", "cccb",
        "abba", "bba", "aacb", "aba", "ccabac"
    };
    int numWords = sizeof(words) / sizeof(words[0]);

    // Insertion des mots dans le trie
    for (int i = 0; i < numWords; i++) {
        insertWord(trie, words[i]);
    }

    // Construction des liens suppléants
    buildSuffixLinks(trie);

    // Texte dans lequel rechercher les mots
    const char *text = "abacbbccbbbbaaccababaababacccbbbabbbbacbaccccabaaacccbbaacbabaaaacbaaacbbbbcaababbcbcccbaccccabbcbbbbacacbccababbcbcccccaaccbaaaccaaacbacabcccabcabcaacbabbabbccbccbaabbacbaaaaaacacacbabbabbbabcbbbbabaaacbabcabacbcbaaacbabaaccbabaabccbaaabcbbcacbacbcccbcbbcababccaaabcbcbabbcaaaacabaacccccccbbcaacbbbbbbaccccabcaaccaabacacbcbcaaababccacaaabcbbccabbabcbbcccbbbabbcccabaaaaacacbacbbbccaacaacaaacccaaccaabbaaaacaccbcabaacbcaaccacaacabbcacabaaabccbabaabbbaaaaabcbccbacbcccaccbabaccaabcbcbcbabcaabbaabacbaa";

    // Recherche des occurrences
    int result = searchOccurrences(trie, text);

    printf("Nombre d'occurrences : %d\n", result);

    freeTrie(trie);
    return 0;
}
