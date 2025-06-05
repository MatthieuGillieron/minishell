# 📝 Documentation – Redirections dans Minishell

## 📌 Introduction

Les redirections sont un élément fondamental des shells Unix, permettant de rediriger l'entrée et la sortie standard des commandes. Notre implémentation dans Minishell gère les quatre types de redirections standards.

---

## 🔄 Types de redirections supportés

| Symbole | Nom | Description | Fonction |
|---------|-----|-------------|----------|
| `<` | Redirection d'entrée | Lit l'entrée depuis un fichier | `apply_input_redirection` |
| `>` | Redirection de sortie | Écrit la sortie dans un fichier (écrase) | `apply_output_redirection` |
| `>>` | Redirection en append | Écrit la sortie à la fin d'un fichier | `apply_append_redirection` |
| `<<` | Heredoc | Lit l'entrée depuis le terminal jusqu'à un délimiteur | `apply_heredoc_redirection` |

---

## 🧠 Architecture du code

Notre implémentation est divisée en plusieurs fichiers pour respecter la norme 42 :

- `e_redir.c` : Gère les redirections d'entrée (`<` et `<<`)
- `e_redir2.c` : Gère les redirections de sortie (`>` et `>>`)

### Fonctions principales

1. **`apply_redirections`** : Fonction principale qui parcourt toutes les redirections d'une commande et les applique.

2. **`process_redirection`** : Détermine le type de redirection et appelle la fonction appropriée.

3. **Fonctions spécifiques** :
   - `apply_input_redirection` : Ouvre un fichier en lecture et redirige STDIN vers ce fichier
   - `apply_output_redirection` : Ouvre un fichier en écriture (écrase) et redirige STDOUT vers ce fichier
   - `apply_append_redirection` : Ouvre un fichier en mode append et redirige STDOUT vers ce fichier
   - `apply_heredoc_redirection` : Crée un pipe, lit l'entrée jusqu'au délimiteur, et redirige STDIN vers ce pipe

---

## 🔧 Fonctionnement technique

### Redirection d'entrée (`<`)

```c
fd = open(file_path, O_RDONLY);
dup2(fd, STDIN_FILENO);
```

### Redirection de sortie (`>`)

```c
fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);
```

### Redirection en append (`>>`)

```c
fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
dup2(fd, STDOUT_FILENO);
```

### Heredoc (`<<`)

1. Crée un pipe avec `pipe(pipe_fd)`
2. Lit l'entrée ligne par ligne avec `readline`
3. Écrit chaque ligne dans le pipe jusqu'à rencontrer le délimiteur
4. Redirige STDIN vers le côté lecture du pipe

---

## 🚩 Gestion des erreurs

Chaque fonction de redirection vérifie :
- Si l'ouverture du fichier a réussi
- Si la redirection avec `dup2` a réussi

En cas d'erreur :
- Un message d'erreur est affiché avec `perror`
- La fonction retourne `-1`
- La commande n'est pas exécutée

---

## 📊 Exemple d'utilisation

```bash
# Redirection d'entrée
cat < input.txt

# Redirection de sortie
ls > output.txt

# Redirection en append
echo "hello" >> log.txt

# Heredoc
cat << EOF
Ceci est un texte
sur plusieurs lignes
EOF
```

---

## 🔍 Points techniques importants

1. Toutes les redirections sont appliquées **avant** l'exécution de la commande
2. Les descripteurs de fichiers originaux (STDIN/STDOUT) sont sauvegardés et restaurés après l'exécution
3. Les fichiers ouverts sont fermés après la redirection pour éviter les fuites de descripteurs
4. Le heredoc utilise un pipe pour transmettre les données, pas un fichier temporaire