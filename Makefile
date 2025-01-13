# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ_matrice = ./src/main_matrice.o ./src/trie_matrice.o
OBJ_hachage = ./src/main_hachage.o  ./src/trie_hachage.o
TARGET_matrice = ac-matrice
TARGET_hachage = ac-hachage
TARGET_GENERATEUR_TEXTE = genere-texte
TARGET_GENERATEUR_MOTS = genere-mots
# Règle par défaut
all: $(TARGET_matrice) $(TARGET_hachage)  $(TARGET_GENERATEUR_TEXTE) $(TARGET_GENERATEUR_MOTS)
# Compilation du programme
$(TARGET_matrice): $(OBJ_matrice)
	$(CC) $(CFLAGS) -o $(TARGET_matrice) $(OBJ_matrice)
$(TARGET_hachage): $(OBJ_hachage)
	$(CC) $(CFLAGS) -o $(TARGET_hachage) $(OBJ_hachage)
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
main_matrice.o: ./src/main_matrice.c ./header/trie_matrice.h
	$(CC) $(CFLAGS) -c ./src/main_matrice.c
trie_hachage.o: ./src/trie_hachage.c ./header/trie_hachage.h
	$(CC) $(CFLAGS) -c ./src/trie_hachage.c
main_hachage.o: ./src/main_hachage.c ./header/trie_hachage.h
	$(CC) $(CFLAGS) -c ./src/hachage.c
# Compilation des fichiers objets du generateur de mon
generateur_mots.o: generateur_mots.c generateur_mots.h
	$(CC) $(CFLAGS) -c generateur_mots.c
# Nettoyage des fichiers objets et exécutables
clean:
	rm -rf $(TARGET_matrice) $(TARGET_hachage) $(TARGET_GENERATEUR_MOTS) $(TARGET_GENERATEUR_TEXTE) generate/ results/ search-results/ *.o src/*.o 
