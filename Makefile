# Variables de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm

# Noms des exécutables
EXEC_HASH = program_trie_hash
EXEC_MATRICE = program_trie_matrice

# Fichiers sources
SRC_MAIN = ./src/main.c
SRC_HASH = ./src/test_hash.c ./src/trie_hash.c
SRC_MATRICE = ./src/test_matrice.c ./src/trie_matrice.c

# Fichiers objets
OBJ_MAIN = $(SRC_MAIN:.c=.o)
OBJ_HASH = $(SRC_HASH:.c=.o)
OBJ_MATRICE = $(SRC_MATRICE:.c=.o)

# Cible par défaut : créer les deux exécutables
all: $(EXEC_HASH) $(EXEC_MATRICE)

# Compilation de l'exécutable pour le trie avec table de hachage
$(EXEC_HASH): $(OBJ_MAIN) $(OBJ_HASH)
	$(CC) -o $(EXEC_HASH) $(SRC_MAIN) $(OBJ_HASH) $(LDFLAGS) -DUSE_HASH

# Compilation de l'exécutable pour le trie avec matrice de transitions
$(EXEC_MATRICE): $(OBJ_MAIN) $(OBJ_MATRICE)
	$(CC) -o $(EXEC_MATRICE) $(SRC_MAIN) $(OBJ_MATRICE) $(LDFLAGS) -DUSE_MATRICE

# Compilation des fichiers objets pour le programme principal
main.o: $(SRC_MAIN) test_hash.h test_matrice.h
	$(CC) -c $(SRC_MAIN) $(CFLAGS)

# Compilation des fichiers objets pour les tests liés à la table de hachage
test_hash.o: test_hash.c test_hash.h trie_hash.h
	$(CC) -c test_hash.c $(CFLAGS)

trie_hash.o: trie_hash.c trie_hash.h
	$(CC) -c trie_hash.c $(CFLAGS)

# Compilation des fichiers objets pour les tests liés à la matrice de transitions
test_matrice.o: test_matrice.c test_matrice.h trie_matrice.h
	$(CC) -c test_matrice.c $(CFLAGS)

trie_matrice.o: trie_matrice.c trie_matrice.h
	$(CC) -c trie_matrice.c $(CFLAGS)

# Commande pour nettoyer les fichiers objets et les exécutables
clean:
	rm -f *.o $(EXEC_HASH) $(EXEC_MATRICE)
	rm -f *o $(EXEC_HASH) $(EXEC_MATRICE) ./src/*.o
# Commandes pour exécuter les deux programmes
run_hash: $(EXEC_HASH)
	./$(EXEC_HASH)

run_matrice: $(EXEC_MATRICE)
	./$(EXEC_MATRICE)
