#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26 // Supposons un alphabet anglais en minuscules
#define CHAR_TO_INDEX(c) ((c) - 'a')

// Structure représentant un triee avec une matrice de transition
struct _triee {
    int maxNode;       /* Nombre maximal de nœuds du triee */
    int nextNode;      /* Indice du prochain nœud disponible */
    int **transition;  /* Matrice de transition */
    int *fail;         /* Tableau des suppléants */
    char *finite;      /* États terminaux */
};

typedef struct _triee Triee;

// Initialisation d'un triee
Triee *createTriee(int maxNode) {
    Triee *triee = (Triee *)malloc(sizeof(Triee));
    triee->maxNode = maxNode;
    triee->nextNode = 1; // Le nœud 0 est la racine
    
    // Allocation de la matrice de transition
    triee->transition = (int **)malloc(maxNode * sizeof(int *));
    for (int i = 0; i < maxNode; i++) {
        triee->transition[i] = (int *)malloc(ALPHABET_SIZE * sizeof(int));
        memset(triee->transition[i], -1, ALPHABET_SIZE * sizeof(int));
    }

    triee->fail = (int *)malloc(maxNode * sizeof(int));
    memset(triee->fail, 0, maxNode * sizeof(int));

    triee->finite = (char *)calloc(maxNode, sizeof(char));
    return triee;
}

// Insertion d'un mot dans le triee
void insert(Triee *triee, const char *word) {
    int currentNode = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = CHAR_TO_INDEX(word[i]);
        if (triee->transition[currentNode][index] == -1) {
            triee->transition[currentNode][index] = triee->nextNode++;
        }
        currentNode = triee->transition[currentNode][index];
    }
    triee->finite[currentNode] = 1;
}

// Construction des liens de suppléance
void buildFailLinks(Triee *triee) {
    int *queue = (int *)malloc(triee->maxNode * sizeof(int));
    int front = 0, back = 0;

    // Initialisation des suppléants pour les enfants directs de la racine
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (triee->transition[0][i] != -1) {
            queue[back++] = triee->transition[0][i];
            triee->fail[triee->transition[0][i]] = 0;
        }
    }

    // Construction des suppléants pour les autres nœuds
    while (front < back) {
        int currentNode = queue[front++];
        printf("parcours des noueds %d\n", currentNode);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int child = triee->transition[currentNode][i];
            if (child != -1) {
                int failNode = triee->fail[currentNode];
                while (failNode != 0 && triee->transition[failNode][i] == -1) {
                    failNode = triee->fail[failNode];
                }
                if (triee->transition[failNode][i] != -1) {
                    failNode = triee->transition[failNode][i];
                }
                triee->fail[child] = failNode;
                triee->finite[child] |= triee->finite[failNode]; // Marquer si c'est un état terminal
                queue[back++] = child;
            }
        }
    }
    free(queue);
}

// Recherche des motifs dans un texte
void search(Triee *triee, const char *text) {
    int currentNode = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        int index = CHAR_TO_INDEX(text[i]);
        while (currentNode != 0 && triee->transition[currentNode][index] == -1) {
            currentNode = triee->fail[currentNode];
        }
        if (triee->transition[currentNode][index] != -1) {
            currentNode = triee->transition[currentNode][index];
        }
        if (triee->finite[currentNode]) {
            printf("Mot trouvé à l'indice %d\n", i);
        }
    }
}

// Libération de la mémoire allouée pour le triee
void freeTriee(Triee *triee) {
    for (int i = 0; i < triee->maxNode; i++) {
        free(triee->transition[i]);
    }
    free(triee->transition);
    free(triee->fail);
    free(triee->finite);
    free(triee);
}

int testMatrice() {
    // Exemple d'utilisation
    Triee *triee = createTriee(1000); // Capacité maximale de 1000 nœuds
    
    insert(triee, "he");
    insert(triee, "she");
    insert(triee, "hers");
    insert(triee, "his");

    buildFailLinks(triee);

    const char *text = "ahishers";
    search(triee, text);

    freeTriee(triee);
    return 0;
}
