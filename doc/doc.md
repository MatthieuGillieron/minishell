
# Fichier pour doc projet 

# 🐚 Minishell – Documentation (état actuel)

## 📖 Introduction

Minishell est un projet de l’école 42 qui consiste à coder un shell Unix simplifié en C.  
Ce projet nous apprend à manipuler les signaux, les processus, les pointeurs, la mémoire dynamique et les bibliothèques comme readline et libft.

Actuellement, notre shell gère l’affichage du prompt, la lecture d’une commande, le découpage de cette commande en tokens, et l’affichage de ces tokens pour debug, tout en respectant la norme 42.

---

## 🚩 Fonctionnalités actuelles

- Gestion de `SIGINT` (Ctrl+C) et `SIGQUIT` (Ctrl+\)
- Affichage d’un prompt interactif avec `readline`
- Lecture d’une ligne entrée par l’utilisateur
- Découpage de la ligne en tokens (mots séparés par espaces)
- Affichage des tokens un par un pour debug
- Libération propre de la mémoire

---

## 📝 Explication du fonctionnement

Lorsqu’on lance le shell, il affiche un prompt (`shell$ `) et attend une commande de l’utilisateur.  
Quand l’utilisateur entre une commande comme `ls -l /tmp` :

1. La commande est lue avec `readline`
2. Elle est ajoutée à l’historique si non vide
3. Elle est découpée en mots grâce à `parse_line`, qui utilise `ft_split`
4. Chaque mot est affiché avec `print_tokens` :
    argv[0]: ls
    argv[1]: -l
    argv[2]: /tmp
5. La mémoire est libérée avec `free_tokens`
6. Le shell redemande une nouvelle commande

Si l’utilisateur tape **Ctrl+D**, le shell quitte proprement en affichant `exit`.

Si l’utilisateur tape **Ctrl+C**, la fonction `sigint_handler` est appelée, elle :
- met à jour `g_exit_status = 130`
- affiche une nouvelle ligne
- efface la ligne en cours
- réaffiche le prompt

Et si l’utilisateur tape **Ctrl+\**, le shell ignore cette commande grâce à `signal(SIGQUIT, SIG_IGN)`.

---

## 💬 Exemple d’utilisation
    $ ./minishell
    shell$ ls -l
    argv[0]: ls
    argv[1]: -l
    shell$

---

## 🚀 Prochaines étapes

La prochaine fonctionnalité sera d’exécuter la commande entrée, en remplaçant l’affichage des tokens par un appel à une fonction `execute_command`, qui utilisera `fork` et `execve`.

Ensuite, nous ajouterons la recherche de l’exécutable dans le PATH, la gestion des redirections, des pipes et des builtins.

---

## 🏗️ Concepts appris jusqu’ici

- Gestion des signaux (`SIGINT`, `SIGQUIT`)
- Utilisation de `readline` et `add_history`
- Manipulation de tableaux de pointeurs (`char **argv`)
- Découpage d’une chaîne en tokens avec `ft_split`
- Libération de mémoire dynamique

---

## 🧠 Comprendre les signaux Unix

Un **signal Unix** est un mécanisme de communication entre le système d’exploitation et un processus, ou entre processus.  
C’est comme un message envoyé pour dire : "attention, il s’est passé quelque chose !"

Quand un signal est reçu par un processus :
- soit il applique le **comportement par défaut** (exemple : arrêter le process)
- soit il intercepte le signal avec une **fonction handler personnalisée**
- soit il ignore le signal

---

### 📋 Quelques signaux importants

| Signal   | Numéro | Nom complet   | Comportement par défaut      | Provoqué par              |
|----------|--------|---------------|------------------------------|--------------------------|
| SIGINT    | 2      | Interrupt     | Arrêter le processus          | **Ctrl+C** dans terminal  |
| SIGQUIT   | 3      | Quit          | Arrêter + créer un core dump  | **Ctrl+\\**               |
| SIGTERM   | 15     | Terminate     | Arrêter le processus          | `kill pid`                |
| SIGKILL   | 9      | Kill          | Forcer l’arrêt (non interceptable) | `kill -9 pid`         |
| SIGSTOP   | 19     | Stop          | Suspendre (non interceptable) | `kill -STOP pid` ou Ctrl+Z |

---

## 🚩 Les signaux gérés actuellement

Notre minishell gère **SIGINT** et **SIGQUIT**.

### 🔧 SIGINT (Ctrl+C)

Quand l’utilisateur tape **Ctrl+C**, le terminal envoie **SIGINT (signal numéro 2)** au shell.  
Par défaut, ce signal **tue le processus en cours.**

Mais dans notre minishell, on intercepte ce signal grâce à :

```c
signal(SIGINT, sigint_handler);

---