#ifndef TEST_HASH_H
#define TEST_HASH_H
#include "trie_hash.h"

//fonction qui contient les instructions pour tester le trie utilisant la fonction de hachage
void testHash();
//affiche si un mot est dans le trie
void afficherIsInTrie(Trie trie,unsigned char* word);
//affiche si les prefixes d'un mot sont dans le trie ou pas
void showPrefixeIsInTrie(Trie trie, unsigned char *word);
//affiche si les suffixes d'un mot sont dans le trie ou pas
void showSuffixeIsInTrie(Trie trie,unsigned char *word);
//affiche si les facteurs d'un mot sont dans le trie ou pas
void showFacteurIsInTrie(Trie trie, unsigned char *word);
#endif