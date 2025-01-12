make
mkdir -p generated
./genere-texte 50000 100 > generated/texte3.txt
./genere-mots 5 7 8 100 > generated/mots3.txt
./ac-matrice generated/mots3.txt generated/texte3.txt > generated/res-ac-matrice
./ac-hachage generated/mots3.txt generated/texte3.txt > generated/res-ac-hachage
diff generated/res-ac-matrice generated/res-ac-hachage
