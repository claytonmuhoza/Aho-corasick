# Algorithme aho-corasick
##  Compilation des executable
la commande `make` va générer les exécutables suivant
1. ac-matrice
2. ac-hachage
3. genere-mots
4. genere-texte

La commande make n'a pas besoin d'être lancée manuellement, car elle est déjà appelée dans le script pour générer les fichiers nécessaires ainsi que pour exécuter les tests.
##  Génération des fichiers
pour générer les mots et les textes qui vont nous servir dans les tests, on lancer le script bash contenu dans le fichier `run-generate-data.sh` 
```
bash run-generate-data.sh
```
les fichiers générés sont enregistrés dans le dossier `generer/`

## Tests de recherche

Pour faire les tests de recherche avec les fichiers générés, on va utiliser le fichier bash `run-search.sh`
```
bash run-search.sh
```
* l'exécution du script va relever les temps d'exécution de la recherche en utilisant les deux méthodes sur les fichiers générés et ces temps seront enregistrés dans un fichier csv nommé `results/time.csv`
* nombres d'occurrence résultats de la recherche seront écrits dans des fichiers se trouvant dans le dossier `search-results`. 
* Dans ce même dossier (search-results), on y retrouvera également un fichier nommé `diff.txt` qui contient la différence des résultats si les deux méthodes de recherche on retourne un fichier différent, normalement ce fichier est vide si tout fonctionne correctement.
## Visualisation des résultats
Pour tracer les courbes représentant les résultats obtenu lors de la recherche, on utilise un script python qu’on a nommé `plot_result.py`
```
python3 plot_result.py
```
ce script python va générer
deux fichiers time_by_alphabet_size.png 
time_by_word_size.png 
ces deux fichiers seront écrit à la racine du projet
