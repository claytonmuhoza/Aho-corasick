#ifndef FILE_H
#define FILE_H
// Structure pour les éléments de la file
typedef struct _ElementFile ElementFile;
struct _ElementFile{
    int node;
    ElementFile *next;
};
// Structure de la file
typedef struct _FileNode FileNode;
struct _FileNode{
    ElementFile *head;
    ElementFile *tail;
};
void enfiler(FileNode *file, int node);
int defiler(FileNode *file);
// Fonction pour enfiler un élément dans la file
void enfiler(FileNode *file, int node);
// Foncton pour defiler un element de la file
int defiler(FileNode *file);
#endif