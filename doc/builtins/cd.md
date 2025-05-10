# 📝 Documentation – `builtin_cd` (Minishell)

## 📌 Objectif de la commande

La commande **`cd`** (change directory) permet de changer le répertoire courant du shell.

Dans Minishell, la commande `cd` doit reproduire le comportement de Bash, incluant :

✅ `cd` sans argument → aller dans `$HOME`  
✅ `cd ~` → aller dans `$HOME`  
✅ `cd -` → revenir au répertoire précédent (`$OLDPWD`) et afficher ce chemin  
✅ `cd <path>` → aller dans un chemin spécifique

---

## 🎯 Comportements attendus

| Commande       | Comportement attendu                               |
|----------------|---------------------------------------------------|
| `cd`            | Aller dans `$HOME`, ou erreur si non défini       |
| `cd ~`          | Aller dans `$HOME`, ou erreur si non défini       |
| `cd -`          | Aller dans `$OLDPWD` + afficher chemin, ou erreur |
| `cd <path>`     | Aller dans `<path>`, ou erreur si invalide        |

Après chaque changement réussi, il faut :

✅ Mettre à jour la variable d’environnement **`PWD`** (nouveau chemin courant)  
✅ Mettre à jour **`OLDPWD`** (ancien chemin avant le changement)

---

## 🧠 Détails d’implémentation

La fonction principale `builtin_cd` détermine quel cas appliquer selon l’argument fourni.

Elle appelle des fonctions internes :

### 1️⃣ `handle_home_directory`

- Récupère `$HOME`
- Affiche une erreur si `$HOME` non défini (avec `ft_putstr_fd`)
- Tente `chdir(home)`
- Retourne `0` si succès, `1` si échec

---

### 2️⃣ `handle_oldpwd`

- Récupère `$OLDPWD`
- Affiche une erreur si `$OLDPWD` non défini (avec `ft_putstr_fd`)
- Tente `chdir(oldpwd)`
- Affiche le nouveau répertoire courant (comme Bash)
- Met à jour `PWD` et `OLDPWD`
- Retourne `0` si succès, `1` si échec

---

### 3️⃣ `handle_target_directory`

- Tente `chdir(path)` vers le chemin fourni
- Met à jour `PWD` et `OLDPWD`
- Retourne `0` si succès, `1` si échec

---

### 4️⃣ `update_env_vars`

- Met à jour la variable d’environnement `OLDPWD` avec la valeur précédente de `PWD`
- Met à jour `PWD` avec le chemin actuel (via `getcwd`)

---

## 🚩 Restrictions et exigences

✅ Utilise `getenv` et `setenv` pour manipuler les variables d’environnement  
✅ Utilise `perror` pour afficher les erreurs système (`chdir` échoué)  
✅ Remplace `fprintf(stderr, ...)` par `ft_putstr_fd(..., 2)` pour conformité au sujet  
✅ Pas d’utilisation de fonctions interdites  
✅ Respect de la norme (≤25 lignes par fonction, indentation…)

---

## 📚 Notes importantes

- Bash affiche le chemin après `cd -` → reproduit par le `printf("%s\n", old_pwd)` dans `handle_oldpwd`.
- Si `$PWD` ou `$OLDPWD` n’existent pas dans l’environnement, la commande continue mais les mises à jour peuvent échouer silencieusement.
- La fonction **ne gère pas d’options (ex: `cd --help`)** → conforme au sujet.

---

## 📝 Résumé des responsabilités

| Fonction                 | Rôle principal                                |
|-------------------------|----------------------------------------------|
| `builtin_cd`              | Redirige vers les cas HOME, "-", ou chemin   |
| `handle_home_directory`   | Gère `cd` et `cd ~`                         |
| `handle_oldpwd`           | Gère `cd -`                                 |
| `handle_target_directory` | Gère `cd <path>`                            |
| `update_env_vars`         | Met à jour `PWD` et `OLDPWD` après `chdir`  |

---

## 🏆 Pourquoi ce design

Cette structure sépare les responsabilités, limite les fonctions à ≤25 lignes, et respecte le comportement attendu de Bash **tout en restant claire et maintenable**.

Chaque cas est géré dans une fonction spécifique, ce qui simplifie la lecture et permet l’ajout de fonctionnalités si besoin.

