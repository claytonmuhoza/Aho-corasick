#include <stdio.h>
#include <stdlib.h>
#include "../header/file.h"
// Inclure les bons fichiers de test en fonction de la compilation
#ifdef USE_HASH
    #include "../header/test_hash.h"
#elif defined(USE_MATRICE)
    #include "../header/test_matrice.h"
#endif

int main()
{
#ifdef USE_HASH
    testHash();
#elif defined(USE_MATRICE)
    testMatrice();
    
#endif
    printf("test\n");
    FileNode *file = (FileNode *)malloc(sizeof(FileNode));
    enfiler(file, 12);
    enfiler(file, 14);
    enfiler(file, 17);
    enfiler(file, 19);
    enfiler(file, 21);
    enfiler(file, 23);
    enfiler(file, 25);
    enfiler(file, 27);
    printf("defile\n");
    for(int i = 0; i < 8; i++){
        printf("%d\n",defiler(file));
    }
    return 0;
}
