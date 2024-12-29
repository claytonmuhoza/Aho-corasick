#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hashSize(maxNode) (maxNode * 256)

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
    char *suffix; // Suppleant
    char *finite;
};

// Fonction de hachage
unsigned int hashFunction(int startNode, unsigned char letter, int maxNode) {
    return (startNode * 256 + letter) % hashSize(maxNode);
}

Trie createTrie(int maxNode) {
    Trie trie = (Trie)malloc(sizeof(struct _trie));
    trie->maxNode = maxNode;
    trie->nextNode = 1; // Le nœud initial est toujours le nœud 0
    int HASH_SIZE = hashSize(trie->maxNode);
    trie->transition = (List *)calloc(HASH_SIZE, sizeof(List));
    trie->finite = (char *)calloc(maxNode, sizeof(char));
    trie->suffix = (char *)calloc(maxNode, sizeof(char));
    return trie;
}

void insertInTrie(Trie trie, unsigned char *w) {
    int currentNode = 0;

    for (int i = 0; w[i] != '\0'; i++) {
        unsigned int h = hashFunction(currentNode, w[i], trie->maxNode);
        List entry = trie->transition[h];

        while (entry != NULL && !(entry->startNode == currentNode && entry->letter == w[i])) {
            entry = entry->next;
        }

        if (entry == NULL) {
            entry = (List)malloc(sizeof(struct _list));
            entry->startNode = currentNode;
            entry->letter = w[i];
            entry->targetNode = trie->nextNode++;
            entry->next = trie->transition[h];
            trie->transition[h] = entry;
        }
        currentNode = entry->targetNode;
    }
    trie->finite[currentNode] = 1;
}

void buildSuffixLinks(Trie trie) {
    int *queue = (int *)malloc(trie->maxNode * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < 256; i++) {
        unsigned int h = hashFunction(0, i, trie->maxNode);
        List entry = trie->transition[h];
        while (entry) {
            queue[rear++] = entry->targetNode;
            trie->suffix[entry->targetNode] = 0;
            entry = entry->next;
        }
    }

    while (front < rear) {
        int currentNode = queue[front++];

        for (int i = 0; i < 256; i++) {
            unsigned int h = hashFunction(currentNode, i, trie->maxNode);
            List entry = trie->transition[h];

            while (entry) {
                int target = entry->targetNode;
                int suffix = trie->suffix[currentNode];

                while (suffix && !trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]) {
                    suffix = trie->suffix[suffix];
                }

                if (trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]) {
                    suffix = trie->transition[hashFunction(suffix, entry->letter, trie->maxNode)]->targetNode;
                }

                trie->suffix[target] = suffix;
                queue[rear++] = target;
                entry = entry->next;
            }
        }
    }

    free(queue);
}

int searchOccurrences(Trie trie, unsigned char *text) {
    int currentNode = 0;
    int count = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        while (currentNode && !trie->transition[hashFunction(currentNode, text[i], trie->maxNode)]) {
            currentNode = trie->suffix[currentNode];
        }

        if (trie->transition[hashFunction(currentNode, text[i], trie->maxNode)]) {
            currentNode = trie->transition[hashFunction(currentNode, text[i], trie->maxNode)]->targetNode;
        }

        int tempNode = currentNode;
        while (tempNode) {
            if (trie->finite[tempNode]) {
                count++;
            }
            tempNode = trie->suffix[tempNode];
        }
    }

    return count;
}

int main() {
    Trie trie = createTrie(1000);
    insertInTrie(trie, (unsigned char *)"cbbabc");
    insertInTrie(trie, (unsigned char *)"abb");
    insertInTrie(trie,(unsigned char *)"bcbbc");
    insertInTrie(trie, (unsigned char *)"cbbac");
    insertInTrie(trie, (unsigned char *)"cccb");
    insertInTrie(trie, (unsigned char *)"abba");
    insertInTrie(trie, (unsigned char *)"bba");
    insertInTrie(trie, (unsigned char *)"aacb");
    insertInTrie(trie,(unsigned char *)"aba");
    insertInTrie(trie, (unsigned char *)"ccabac");
    buildSuffixLinks(trie);

    unsigned char text[] = "abacbbccbbbbaaccababaababacccbbbabbbbacbaccccabaaacccbbaacbabaaaacbaaacbbbbcaababbcbcccbaccccabbcbbbbacacbccababbcbcccccaaccbaaaccaaacbacabcccabcabcaacbabbabbccbccbaabbacbaaaaaacacacbabbabbbabcbbbbabaaacbabcabacbcbaaacbabaaccbabaabccbaaabcbbcacbacbcccbcbbcababccaaabcbcbabbcaaaacabaacccccccbbcaacbbbbbbaccccabcaaccaabacacbcbcaaababccacaaabcbbccabbabcbbcccbbbabbcccabaaaaacacbacbbbccaacaacaaacccaaccaabbaaaacaccbcabaacbcaaccacaacabbcacabaaabccbabaabbbaaaaabcbccbacbcccaccbabaccaabcbcbcbabcaabbaabacbaa";
    printf("Number of occurrences: %d\n", searchOccurrences(trie, text));

    return 0;
}
