# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ_matrice = ./src/main_matrice.o 
OBJ_hash = ./src/main_hash.o 
OBJ_hash_v2 = ./src/main_hash_v2.o 
TARGET_matrice = ac-matrice
TARGET_hash = ac-hash
TARGET_hash_v2 = ac-hachage
TARGET_GENERATEUR_TEXTE = genere-texte
TARGET_GENERATEUR_MOTS = genere-mots
# Règle par défaut
all: $(TARGET_matrice) $(TARGET_hash) $(TARGET_hash_v2) $(TARGET_GENERATEUR_TEXTE) $(TARGET_GENERATEUR_MOTS)
# Compilation du programme
$(TARGET_matrice): $(OBJ_matrice)
	$(CC) $(CFLAGS) -o $(TARGET_matrice) $(OBJ_matrice)
$(TARGET_hash): $(OBJ_hash)
	$(CC) $(CFLAGS) -o $(TARGET_hash) $(OBJ_hash)
$(TARGET_hash_v2): $(OBJ_hash_v2)
	$(CC) $(CFLAGS) -o $(TARGET_hash_v2) $(OBJ_hash_v2)
$(TARGET_GENERATEUR_TEXTE): ./src/main_generate_texte.c
	$(CC) $(CFLAGS) -o $(TARGET_GENERATEUR_TEXTE) ./src/main_generate_texte.c
$(TARGET_GENERATEUR_MOTS): ./src/main_generate_mots.o
	$(CC) $(CFLAGS) -o $(TARGET_GENERATEUR_MOTS) ./src/main_generate_mots.o
main_generate_texte.o: ./src/main_generate_texte.c
	$(CC) $(CFLAGS) -c ./src/main_generate_texte.c
main_generate_mots.o: ./src/main_generate_mots.c
	$(CC) $(CFLAGS) -c ./src/main_generate_mots.c
trie_matrice.o: ./src/trie_matrice.c ./header/trie_matrice.h
	$(CC) $(CFLAGS) -c ./src/trie_matrice.c
main_matrice.o: ./src/main_matrice.c 
	$(CC) $(CFLAGS) -c ./src/main_matrice.c
trie_hash.o: ./src/trie_hash.c ./header/trie_hash.h
	$(CC) $(CFLAGS) -c ./src/trie_hash.c
main_hash.o: ./src/main_hash.c ./header/trie_hash.h
	$(CC) $(CFLAGS) -c ./src/main_hash.c
trie_hash_v2.o: ./src/trie_hash_v2.c ./header/trie_hash_v2.h
	$(CC) $(CFLAGS) -c ./src/trie_hash_v2.c
# Compilation des fichiers objets du generateur de mon
generateur_mots.o: generateur_mots.c generateur_mots.h
	$(CC) $(CFLAGS) -c generateur_mots.c
# Compilation des fichiers objets de main
main.o: main.c algorithme_recherche_naif.h
	$(CC) $(CFLAGS) -c main.c 
# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(TARGET_matrice) $(TARGET_hash) $(TARGET_GENERATEUR_MOTS) $(TARGET_GENERATEUR_TEXTE) generate/ results/ search-results/ *.o src/*.o 
