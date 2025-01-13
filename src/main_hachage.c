#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../header/trie_hachage.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_mots.txt> <fichier_text.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *wordFile = argv[1];
    const char *textFile = argv[2];

    int trieSize = calculateTrieSize(wordFile);
    Trie trie = createTrie(1000*trieSize);
    loadWords(trie,wordFile);
    
    buildSuffixLinks(trie);
     FILE *textFp = fopen(textFile, "r");
    if (!textFp) {
        perror("Erreur d'ouverture du fichier texte");
        // freeTrie(trie);
        exit(EXIT_FAILURE);
    }

    char *text = NULL;
    size_t textLen = 0;
    getline(&text, &textLen, textFp);
    fclose(textFp);

    
    printf("%d",searchOccurrences(trie, text));

    free(text);

    return 0;
}
