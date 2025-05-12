# 📝 Documentation détaillée – `executor.c` et gestion des processus

Ce document explique le rôle et le fonctionnement de la fonction `execute_command()` dans le minishell, ainsi que les appels système impliqués (`fork`, `execve`, `waitpid`, `envp`), pour bien comprendre leur logique et leurs interactions.

---

## 📌 Objectif de `execute_command()`

Dans un shell, lorsqu’un utilisateur tape une commande, le shell doit :

1. Créer un **nouveau processus (enfant)** pour exécuter la commande
2. Remplacer ce processus enfant par le programme de la commande
3. Pendant ce temps, le shell (parent) **attend la fin de l’enfant**
4. Une fois fini, le shell **réaffiche le prompt**

La fonction `execute_command()` réalise ces étapes en respectant la norme 42 (≤25 lignes).

---

## 🧠 Pourquoi créer un nouveau processus ?

Si le shell exécute directement la commande, **il remplace son propre programme par celui de la commande**, et donc disparaît.

Créer un **processus enfant** permet :

- Au **parent (le shell)** de continuer d’exister
- À l’**enfant** d’exécuter la commande

Ainsi, **le shell peut revenir et afficher un nouveau prompt** une fois la commande exécutée.

---

## 🔍 Explication des appels système

### 1️⃣ `fork()`

- **Rôle** : créer une copie exacte du processus courant.
- Renvoie :
  - `0` dans l’enfant
  - `>0` (PID de l’enfant) dans le parent
  - `-1` en cas d’erreur

Après `fork()`, **le code continue d’être exécuté à la fois dans le parent et l’enfant**, chacun suivant sa propre logique.

---

### 2️⃣ `execve()`

- **Rôle** : remplacer le processus courant par un nouveau programme.
- Ne retourne jamais si elle réussit.
- Retourne `-1` si échec (et `errno` est défini).

Arguments :

- `pathname` → chemin complet du programme à exécuter (ex : `/bin/ls`)
- `argv` → tableau des arguments (argv[0]=commande, argv[1..n]=arguments)
- `envp` → tableau des variables d’environnement

⚠️ Sans `execve()`, l’enfant continuerait à exécuter le code du shell.

---

### 3️⃣ `envp`

- Tableau contenant les variables d’environnement du shell.
- Chaque entrée est une string `"VARIABLE=valeur"`.
- Transmis à `execve()` pour que la commande ait accès à l’environnement (comme `$PATH`, `$HOME`…).

Exemple de contenu :
    envp[0] = "PATH=/usr/bin:/bin:/usr/local/bin"
    envp[1] = "HOME=/home/user"
    envp[2] = "PWD=/home/user"


✅ Permet au programme exécuté de fonctionner comme s’il était lancé depuis un vrai shell.

---

### 4️⃣ `waitpid()`

- **Rôle** : forcer le parent à attendre la fin de l’enfant.
- Permet de récupérer le code retour de l’enfant.
- Sans `waitpid()`, le shell afficherait un nouveau prompt **avant la fin de la commande.**

> Analogie : un parent attend que son enfant finisse son plat avant de débarrasser.

---

## 🧩 Intégration de `find_command_path()`

Dans `execute_command()`, avant d’appeler `execve()`, on vérifie si la commande entrée contient un `/` :

- Si oui → on exécute directement `argv[0]` comme chemin
- Sinon → on cherche le chemin complet dans `$PATH` via `find_command_path()`
- Si introuvable → on affiche `command not found` et on ne lance pas de processus

Cette logique permet d’accepter à la fois :

✅ `/bin/ls` → chemin absolu  
✅ `ls` → recherche automatique dans `$PATH`

---

## 🔬 Résultat global

| Étape             | Qui (parent/enfant) | Action                                       |
|------------------|--------------------|----------------------------------------------|
| fork              | parent + enfant     | crée un processus enfant                      |
| execve            | enfant              | remplace l’enfant par le programme demandé    |
| waitpid           | parent              | attend la fin de l’enfant                     |
| perror + exit     | enfant (si erreur)  | affiche une erreur et termine proprement      |

---

## 📝 Comportement général

Exemple : utilisateur tape `ls`

1. Le shell appelle `find_command_path("ls", envp)` → retourne `/bin/ls`
2. Le shell appelle `fork()` → crée un enfant
3. **L’enfant appelle `execve("/bin/ls", argv, envp)` → remplace l’enfant par `/bin/ls`**
4. **Le parent appelle `waitpid(pid)` → attend que `/bin/ls` termine avant de redonner le prompt**
5. Si `execve()` échoue, l’enfant affiche l’erreur via `perror()` et termine via `exit(1)`

---

## ⚠️ Pourquoi `exit(1)` est indispensable ?

Sans `exit(1)`, si `execve()` échoue, **l’enfant continuerait d’exécuter le code suivant**, et pourrait se comporter comme un shell secondaire → ce qu’on veut éviter.

C’est pour cela qu’on termine l’enfant explicitement.

---

## 📊 Schéma visuel

```text
[SHELL (parent)]
     |
     |--- fork()
           |
    +------+--------+
    |               |
[parent]        [child]
    |               |
    |           execve()
    |               |
    |         (remplacé par la commande)
waitpid()       programme s'exécute
    |               |
(prompt revient)    (programme fini)

---