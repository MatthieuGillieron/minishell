# 📁 Documentation – Recherche de commande dans $PATH (`find_command_path`)

Ce document décrit le fonctionnement des fonctions suivantes :

- `get_path_env(char **envp)`
- `free_split(char **split)`
- `find_command_path(char *cmd, char **envp)`

Ces fonctions permettent à un shell de rechercher **le chemin absolu** d'une commande (comme `ls`) à partir de la variable d'environnement `$PATH`.

---

## 📌 Objectif

Quand un utilisateur tape une commande simple (ex: `ls`) sans chemin (`/bin/ls`), le shell doit :

1. Chercher la variable d’environnement `PATH`
2. La découper en plusieurs chemins (ex: `/usr/local/bin`, `/usr/bin`, `/bin`)
3. Tester dans chaque dossier si un exécutable portant le nom de la commande existe
4. Retourner le chemin complet vers cet exécutable
5. Sinon, indiquer que la commande est introuvable

---

## 🔧 Fonction `get_path_env(char **envp)`

### 🎯 Rôle

Cette fonction parcourt le tableau `envp` (l’environnement du shell) et retourne **le contenu de la variable `PATH`** (sans le `PATH=`).

### 📤 Exemple

Si `envp` contient :
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
PWD=/home/user/projet
Elle retournera la string :
"/usr/local/bin:/usr/bin:/bin"

---

## 🔧 Fonction `free_split(char **split)`

### 🎯 Rôle

Libère un tableau de chaînes alloué par `ft_split()`.

Quand on découpe `PATH` avec `ft_split(path, ':')`, on obtient un tableau de strings.  
Chacune est allouée dynamiquement, il faut donc les `free` **une par une**, puis le tableau lui-même.

---

## 🔧 Fonction `find_command_path(char *cmd, char **envp)`

### 🎯 Rôle

Cette fonction utilise la variable d’environnement `PATH` pour **trouver un chemin absolu vers une commande donnée**, comme `ls`.

### 🧠 Étapes détaillées

1. Elle appelle `get_path_env()` pour récupérer le contenu de `PATH`
2. Elle découpe ce contenu avec `ft_split(..., ':')` pour obtenir un tableau de dossiers
3. Pour chaque dossier, elle construit un chemin complet :
/bin/ls
/usr/bin/ls
...

4. Elle utilise la fonction `access(path, X_OK)` pour vérifier si le fichier existe et est exécutable
5. Si trouvé → elle retourne le chemin
6. Sinon → elle retourne `NULL` (commande non trouvée)

---

## 🔍 Fonctionnement de `access(path, X_OK)`

- `access()` est une fonction système qui teste les permissions sur un fichier.
- `X_OK` signifie “est-ce exécutable ?”
- Si le chemin est correct **et exécutable**, `access()` retourne `0`.

---

## 🧼 Gestion mémoire

- Chaque chemin est alloué dynamiquement avec `ft_strjoin`
- Si un chemin est invalide → on le `free` tout de suite
- Le tableau `char **paths` est libéré avec `free_split`

---

## 📤 Exemple pratique

Si `cmd = "ls"`  
et que `PATH = "/usr/local/bin:/usr/bin:/bin"`

Alors `find_command_path("ls", envp)` va essayer successivement :

- `/usr/local/bin/ls`
- `/usr/bin/ls`
- `/bin/ls`

et retourner **le premier chemin correct** détecté par `access(path, X_OK)`.

---

## ❌ Si rien n’est trouvé

La fonction retourne `NULL`.  
Cela permet au shell de répondre :  
`command not found: ls`

---

## ✅ Résumé

| Fonction           | Rôle                                              |
|--------------------|---------------------------------------------------|
| `get_path_env`     | Trouve et retourne la valeur de `$PATH`           |
| `free_split`       | Libère un tableau de strings (`char **`)          |
| `find_command_path`| Cherche où se trouve une commande dans `$PATH`    |

---

## 🧠 Intégration dans le Shell

Avant d’appeler `execve()`, il faut :

1. Vérifier si `argv[0]` contient un `/`
2. Si non → appeler `find_command_path(argv[0], envp)`
3. Si `NULL` → afficher `command not found`
4. Sinon → exécuter avec le chemin trouvé

Cela permet à l’utilisateur de taper :
shell$ ls
au lieu de :
shell$ /bin/ls

---




