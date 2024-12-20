# Description du projet
Implementation d'une structure de données de type *RETRIEVAL ALGORITHM*
On utilise deux methodes d'implementation:
1. Une matrice de transition
2. Une Table de hachage
## Instruction pour lancer les executables
Le makefile va generer deux fichiers executable `program_trie_matrice` et `program_trie_hash`

```bash
#on lancer la commande make sans argument  pour generer les deux executable
make
# Pour lancer le programme de test pour le trie utilisant une matrice de transition
make run_matrice
# Pour lancer le programme de test pour le trie utilisant une fonction de hachage
make run_hash
# pour supprimer les fichiers object .o et les executables
make clean


```
## Liste des fichiers

### Pour le program_trie_matrice
1. trie_matrice.c : Implémentation des fonctions du trie utilisant une matrice de transition
2. trie_matrice.h : Fichier d'en-tête correspondant à trie_matrice.c 
3. test_matrice.c : contient les fonctions de test pour le trie basé sur matrice.
3. test_matrice.h : Fichier d'en-tête pour les fonctions de test.
### Pour le program_trie_hash
1. trie_hash.c : Implémentation des fonctions du trie utilisant une fonction de hachage
2. trie_hash.h : Fichier d'en-tête correspondant à trie_hash.c
3. test_hash.c : contient les fonctions de test pour le trie basé sur hachage
4. test_hash.h : Fichier d'en-tête pour les fonctions de test.
