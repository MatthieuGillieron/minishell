# 📚 Documentation – builtin_echo

Ce document explique en détail l’implémentation et le fonctionnement de la fonction `builtin_echo` dans le projet Minishell.

---

## 🏗️ **Fichier concerné**

`src/builtins/echo.c`

---

## 🎯 **Objectif de la fonction**

La fonction `builtin_echo` reproduit le comportement de la commande `echo` dans un shell classique :

✅ Affiche les arguments passés en paramètre, séparés par des espaces  
✅ Termine par un saut de ligne (sauf si option `-n` prise en compte plus tard)

---

## 🔍 **Pourquoi coder `echo` comme builtin ?**

Dans un shell normal, `echo` est souvent un builtin.  
Minishell doit gérer les commandes internes sans lancer de processus externe (`execve`).

La fonction `builtin_echo` permet d’exécuter `echo` directement dans le shell.

---

## 📝 **Comportement attendu**

Quand l’utilisateur tape :

```bash
shell$ echo Hello World
La fonction doit afficher :
Hello World