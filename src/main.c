#include <stdio.h>
#include <stdlib.h>

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
    
    return 0;
}
