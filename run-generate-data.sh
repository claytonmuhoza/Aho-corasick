#!/bin/bash
make
# Création des dossiers nécessaires
mkdir -p generate

# Générer des textes de longueur 5 000 000 pour les alphabets de taille 2, 4, 20 et 70
for alphabet_size in 2 4 10 20 30 40 50 60 70; do
    echo "Generating text for alphabet size $alphabet_size..."
    ./genere-texte 5000000 $alphabet_size > generate/texte_$alphabet_size.txt
done

# Générer des ensembles de mots pour chaque alphabet
for alphabet_size in 2 4 10 20 30 40 50 60 70; do
    for word_range in "5 15" "15 30" "35 40" "30 60" "80 90" "100 120"; do
        min_len=$(echo $word_range | cut -d' ' -f1)
        max_len=$(echo $word_range | cut -d' ' -f2)
        echo "Generation du mot de l'alphabet $alphabet_size de longeur entre $min_len et $max_len..."
        ./genere-mots 100 $min_len $max_len $alphabet_size > generate/mots_${alphabet_size}_${min_len}_${max_len}.txt
    done
done

