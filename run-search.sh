#!/bin/bash
#executer le makefile
make
# Création du dossier pour les résultats
mkdir -p results
mkdir -p search-results
# Initialiser le fichier CSV
echo "Text,Words,Algorithm,Time" > results/times.csv
echo "Words,taille_alphabet,taille_min_mots,taille_max_mots,Algorithm,Time" > results/time.csv

# Effectuer les recherches
for alphabet_size in in 2 4 20 70; do
    for word_range in "5 15" "15 30" "30 60"; do
        min_len=$(echo $word_range | cut -d' ' -f1)
        max_len=$(echo $word_range | cut -d' ' -f2)
        mots_file="generate/mots_${alphabet_size}_${min_len}_${max_len}.txt"
        texte_file="generate/texte_${alphabet_size}.txt"

        for algo in ac-matrice ac-hachage; do
            echo "Recherche avec $algo dans le texte d'alphabet $alphabet_size des mots de longeur entre [$min_len, $max_len]..."
            start_time=$(date +%s.%N)
            ./$algo $mots_file $texte_file > search-results/${algo}_${alphabet_size}_${min_len}_${max_len}.txt
            end_time=$(date +%s.%N)
            elapsed_time=$(echo "$end_time - $start_time" | bc)
            echo "$texte_file,$mots_file,$algo,$elapsed_time" >> results/times.csv
            echo "$mots_file,$alphabet_size,$min_len,$max_len,$algo,$elapsed_time" >> results/time.csv
        done
        diff search-results/ac-matrice_${alphabet_size}_${min_len}_${max_len}.txt search-results/ac-hachage_${alphabet_size}_${min_len}_${max_len}.txt >> search-results/diff.txt
    done
done
