# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ_matrice = ./src/main_matrice.o 
OBJ_hash = ./src/main_hash.o 
TARGET_matrice = ac-matrice
TARGET_hash = ac-hash
# Règle par défaut
all: $(TARGET_matrice) $(TARGET_hash)
# Compilation du programme
$(TARGET_matrice): $(OBJ_matrice)
	$(CC) $(CFLAGS) -o $(TARGET_matrice) $(OBJ_matrice)
$(TARGET_hash): $(OBJ_hash)
	$(CC) $(CFLAGS) -o $(TARGET_hash) $(OBJ_hash)


trie_matrice.o: ./src/trie_matrice.c ./header/trie_matrice.h
	$(CC) $(CFLAGS) -c ./src/trie_matrice.c
main_matrice.o: ./src/main_matrice.c 
	$(CC) $(CFLAGS) -c ./src/main_matrice.c
trie_hash.o: ./src/trie_hash.c ./header/trie_hash.h
	$(CC) $(CFLAGS) -c ./src/trie_hash.c
main_hash.o: ./src/main_hash.c ./header/trie_hash.h
	$(CC) $(CFLAGS) -c ./src/main_hash.c
# Compilation des fichiers objets du generateur de mon
generateur_mots.o: generateur_mots.c generateur_mots.h
	$(CC) $(CFLAGS) -c generateur_mots.c
# Compilation des fichiers objets de main
main.o: main.c algorithme_recherche_naif.h
	$(CC) $(CFLAGS) -c main.c 
# Nettoyage des fichiers objets et exécutables
clean:
	rm -f $(TARGET_matrice) $(TARGET_hash) *.o src/*.o 
