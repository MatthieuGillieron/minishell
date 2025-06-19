# Minishell - Projet 42

[![Français](https://img.shields.io/badge/Français-blue.svg)](./README.md)
[![English](https://img.shields.io/badge/English-gray.svg)](./READMEen.md)

## 📋 Table des matières

- [Présentation](#-présentation)
- [Fonctionnalités](#-fonctionnalités)
- [Architecture](#-architecture)
- [Installation](#-installation)
- [Utilisation](#-utilisation)
- [Commandes supportées](#-commandes-supportées)
- [Gestion des signaux](#-gestion-des-signaux)
- [Exemples](#-exemples)
- [Dépendances](#-dépendances)
- [Développement](#-développement)
- [Tests](#-tests)
- [Documentation](#-documentation)
- [Contributeurs](#-contributeurs)
- [Licence](#-licence)

## 🚀 Présentation

Minishell est une implémentation simplifiée d'un shell Unix, développée dans le cadre du cursus de l'école 42. Ce projet met en pratique des concepts avancés de programmation système en C, notamment la gestion des processus, les signaux, les redirections et les pipes.

Ce shell permet d'exécuter des commandes, de gérer l'environnement système, et d'utiliser des fonctionnalités essentielles comme les redirections et les pipes, tout en offrant une expérience utilisateur similaire à celle des shells Unix standards.

## ✨ Fonctionnalités

- **Prompt interactif** avec affichage personnalisé
- **Historique des commandes** (navigation avec flèches haut/bas)
- **Exécution de commandes** avec recherche dans le PATH
- **Commandes internes (builtins)** : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Redirections** : `<` (entrée), `>` (sortie), `>>` (ajout), `<<` (heredoc)
- **Pipes** (`|`) pour chaîner plusieurs commandes
- **Variables d'environnement** (expansion avec `$VAR`)
- **Gestion des signaux** : SIGINT (Ctrl+C), SIGQUIT (Ctrl+\\)
- **Gestion des quotes** (simples et doubles) avec respect des règles de parsing
- **Code de retour** (`$?`) pour connaître le statut de la dernière commande

## 🏗 Architecture

Le projet est organisé selon une architecture modulaire pour faciliter la maintenance et l'évolution du code :

```
minishell/
├── src/                # Code source
│   ├── builtins/       # Commandes internes (cd, echo, etc.)
│   ├── execution/      # Exécution des commandes et processus
│   ├── lexer/          # Analyse lexicale de l'entrée utilisateur
│   ├── parsing/        # Analyse syntaxique et construction de l'AST
│   ├── signals/        # Gestion des signaux
│   ├── utils/          # Fonctions utilitaires
│   └── main.c          # Point d'entrée du programme
├── includes/           # Fichiers d'en-tête
├── libft/              # Bibliothèque de fonctions standard
├── doc/                # Documentation technique
└── Makefile            # Compilation du projet
```

### Flux d'exécution

1. **Lecture** : Capture de l'entrée utilisateur via readline
2. **Lexer** : Découpage de l'entrée en tokens (mots, opérateurs, etc.)
3. **Parser** : Analyse syntaxique et construction de l'arbre de commandes
4. **Expansion** : Traitement des variables d'environnement et quotes
5. **Exécution** : Exécution des commandes avec gestion des redirections et pipes
6. **Attente** : Attente de la fin des processus enfants
7. **Retour** : Affichage du prompt pour une nouvelle commande

## 📥 Installation

### Prérequis

- GCC ou Clang
- Make
- Bibliothèque Readline

### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/MatthieuGillieron/minishell.git
cd minishell

# Compiler le projet
make

# Vérifier les fuites mémoire (optionnel)
make leaks
```

Le Makefile détecte automatiquement votre système d'exploitation et configure les chemins pour la bibliothèque Readline.

## 🖥 Utilisation

```bash
# Lancer le shell
./minishell
```

Une fois lancé, le shell affiche un prompt et attend vos commandes.

## 📝 Commandes supportées

### Commandes internes (builtins)

| Commande | Description | Options |
|----------|-------------|---------|
| `echo` | Affiche du texte | `-n` (sans retour à la ligne) |
| `cd` | Change de répertoire | Chemin relatif ou absolu |
| `pwd` | Affiche le répertoire courant | Aucune |
| `export` | Définit des variables d'environnement | `VAR=value` |
| `unset` | Supprime des variables d'environnement | Nom de variable |
| `env` | Affiche l'environnement | Aucune |
| `exit` | Quitte le shell | Code de sortie (optionnel) |

### Opérateurs et redirections

| Opérateur | Description | Exemple |
|-----------|-------------|---------|
| `|` | Pipe (redirection de sortie vers entrée) | `ls \| grep .c` |
| `<` | Redirection d'entrée | `cat < file.txt` |
| `>` | Redirection de sortie (écrase) | `ls > output.txt` |
| `>>` | Redirection de sortie (ajoute) | `echo "text" >> log.txt` |
| `<<` | Heredoc (entrée multi-lignes) | `cat << EOF` |

## 🚦 Gestion des signaux

| Signal | Combinaison | Comportement |
|--------|-------------|-------------|
| SIGINT | Ctrl+C | Interrompt la commande en cours, affiche un nouveau prompt |
| SIGQUIT | Ctrl+\\ | Ignoré dans le shell interactif, termine les processus enfants |
| EOF | Ctrl+D | Quitte le shell proprement si la ligne est vide |

## 📋 Exemples

```bash
# Commandes simples
echo "Hello, World!"
pwd
cd Documents

# Variables d'environnement
export NAME=value
echo $NAME
echo "Current path: $PATH"

# Redirections
echo "content" > file.txt
cat < file.txt
ls -la >> log.txt

# Pipes
ls -la | grep .c | wc -l

# Heredoc
cat << EOF
This is a multi-line
text input
$USER
EOF

# Combinaisons complexes
cat < input.txt | grep "pattern" > output.txt
```

## 📚 Dépendances

- **Readline** : Gestion de l'interface utilisateur et de l'historique
- **Libft** : Bibliothèque personnelle de fonctions standard

## 🛠 Développement

### Structure du code

- **Lexer** : Analyse lexicale de l'entrée utilisateur
  - Tokenisation de l'entrée
  - Gestion des quotes et caractères spéciaux
  
- **Parser** : Construction de l'arbre syntaxique
  - Vérification de la syntaxe
  - Organisation des commandes et opérateurs
  
- **Executor** : Exécution des commandes
  - Création de processus
  - Gestion des redirections et pipes
  - Exécution des builtins

### Normes de codage

Le code suit la norme de l'école 42 :
- Maximum 25 lignes par fonction
- Maximum 5 fonctions par fichier
- Maximum 4 paramètres par fonction
- Déclaration des variables en début de fonction
- Utilisation de préfixes pour les noms de fichiers

## 🧪 Tests

Le projet inclut des tests pour vérifier le bon fonctionnement des différentes fonctionnalités :

```bash
# Vérifier les fuites mémoire
make leaks

# Tests manuels recommandés
./minishell
> echo $PATH
> ls -la | grep .c | wc -l
> cat << EOF > file.txt
```

## 📖 Documentation

Une petite documentation détaillée est disponible dans le répertoire `doc/` :

- `doc/doc.md` : Vue d'ensemble du projet
- `doc/builtins/` : Documentation des commandes internes
- `doc/lexer.md` : Fonctionnement de l'analyse lexicale
- `doc/parser.md` : Fonctionnement de l'analyse syntaxique
- `doc/pipes.md` : Implémentation des pipes
- `doc/redirections.md` : Gestion des redirections
- `doc/environnement.md` : Gestion des variables d'environnement

## 👥 Contributeurs

- [Matthieu Gillieron](https://github.com/MatthieuGillieron) - Développeur
- [Mathieu Taramarcaz](https://github.com/PalmaSkry) - Développeur

## 📄 Licence

Ce projet est distribué sous licence MIT. Voir le fichier `LICENSE` pour plus d'informations.

---

© 2025 Minishell - Projet École 42
