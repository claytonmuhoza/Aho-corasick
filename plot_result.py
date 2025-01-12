import pandas as pd
import matplotlib.pyplot as plt

# Charger les données à partir du fichier CSV
file_path = 'results/time.csv'
data = pd.read_csv(file_path)

# Fonction pour créer un graphique en fonction de la taille de l'alphabet
def plot_by_alphabet_size(data, output_path='time_by_alphabet_size.png'):
    plt.figure(figsize=(10, 6))
    
    for algorithm in data['Algorithm'].unique():
        subset = data[data['Algorithm'] == algorithm]
        avg_times = subset.groupby('taille_alphabet')['Time'].mean()
        plt.plot(avg_times.index, avg_times.values, label=algorithm, marker='o')
    
    plt.title("Temps d'exécution en fonction de la taille de l'alphabet")
    plt.xlabel("Taille de l'alphabet")
    plt.ylabel("Temps d'exécution (s)")
    plt.legend()
    plt.grid(True)
    plt.savefig(output_path)
    plt.close()
    print(f"Graphique sauvegardé : {output_path}")

# Fonction pour créer un graphique en fonction de la taille des mots
def plot_by_word_size(data, output_path='time_by_word_size.png'):
    plt.figure(figsize=(10, 6))
    
    data['word_size'] =  data['taille_max_mots'].astype(str)
    for algorithm in data['Algorithm'].unique():
        subset = data[data['Algorithm'] == algorithm]
        avg_times = subset.groupby('word_size')['Time'].mean()
        plt.plot(avg_times.index, avg_times.values, label=algorithm, marker='o')
    
    plt.title("Temps d'exécution en fonction de la taille des mots")
    plt.xlabel("Taille des mots (min-max)")
    plt.ylabel("Temps d'exécution (s)")
    plt.xticks(rotation=45)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(output_path)
    plt.close()
    print(f"Graphique sauvegardé : {output_path}")

# Générer les graphiques
plot_by_alphabet_size(data)
plot_by_word_size(data)
