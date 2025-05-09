# 📚 Documentation – builtin_env

Ce document explique en détail l’implémentation et le fonctionnement de la fonction `builtin_env` dans le projet Minishell.

---

## 🏗️ **Fichier concerné**

`src/builtins/env.c`

---

## 🎯 **Objectif de la fonction**

La fonction `builtin_env` reproduit le comportement de la commande `env` d’un shell classique :

✅ Affiche toutes les variables d’environnement actuellement définies  
✅ Chaque variable est affichée sur une ligne au format `VARIABLE=VALEUR`

---

## 🔍 **Pourquoi coder `env` comme builtin ?**

Dans un shell normal, `env` est souvent un programme externe (`/usr/bin/env`) mais peut aussi être intégré en builtin.

Minishell doit gérer les commandes internes sans lancer de processus externe (`execve`).

La fonction `builtin_env` permet d’afficher l’environnement directement dans le shell, sans processus enfant.

---

## 📝 **Comportement attendu**

Quand l’utilisateur tape :

```bash
shell$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
PWD=/home/user/projet
...