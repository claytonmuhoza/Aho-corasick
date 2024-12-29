#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256  // Taille maximale pour un alphabet dynamique

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

// Structure représentant un trie
typedef struct _trie {
    int maxNode;
    int nextNode;
    int **transition;
    int *suffix;
    int *finite;
} *Trie;

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
    return trie;
}

// Insérer un mot dans le trie
void insertWord(Trie trie, const char *word) {
    int node = 0;
    for (int i = 0; word[i]; i++) {
        unsigned char c = (unsigned char)word[i];
        if (trie->transition[node][c] == -1) {
            trie->transition[node][c] = trie->nextNode++;
        }
        node = trie->transition[node][c];
    }
    trie->finite[node] = 1;
}

// Construire les liens de suffixe
void buildSuffixLinks(Trie trie) {
    FileNode *file = createFile();

    for (int c = 0; c < ALPHABET_SIZE; c++) {
        if (trie->transition[0][c] != -1) {
            trie->suffix[trie->transition[0][c]] = 0;
            enfiler(file, trie->transition[0][c]);
        } else {
            trie->transition[0][c] = 0;
        }
    }

    while (!estVide(file)) {
        int node = defiler(file);

        for (int c = 0; c < ALPHABET_SIZE; c++) {
            if (trie->transition[node][c] != -1) {
                int child = trie->transition[node][c];
                int suffix = trie->suffix[node];
                while (trie->transition[suffix][c] == -1) {
                    suffix = trie->suffix[suffix];
                }
                trie->suffix[child] = trie->transition[suffix][c];
                enfiler(file, child);
            }
        }
    }

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

        int temp = node;
        while (temp != 0) {
            if (trie->finite[temp]) {
                count++;
            }
            temp = trie->suffix[temp];
        }
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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_mots.txt> <fichier_text.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *wordFile = argv[1];
    const char *textFile = argv[2];

    int trieSize = calculateTrieSize(wordFile);
    Trie trie = createTrie(trieSize);

    loadWords(trie, wordFile);
    buildSuffixLinks(trie);

    FILE *textFp = fopen(textFile, "r");
    if (!textFp) {
        perror("Erreur d'ouverture du fichier texte");
        freeTrie(trie);
        exit(EXIT_FAILURE);
    }
    //afficher les suppleant pour chaque noeud
    for (int i = 0; i < trie->maxNode; i++) {
        printf("suppleant[%d] = %d\n", i, trie->suffix[i]);
    }

    char *text = NULL;
    size_t textLen = 0;
    getline(&text, &textLen, textFp);
    fclose(textFp);

    int occurrences = searchOccurrences(trie, text);
    printf("Nombre total de motifs trouvés : %d\n", occurrences);

    free(text);
    freeTrie(trie);

    return EXIT_SUCCESS;
}
