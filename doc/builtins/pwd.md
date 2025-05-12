# 📚 Documentation – builtin_pwd

Ce document explique en détail l’implémentation et le fonctionnement de la fonction `builtin_pwd` dans le projet Minishell.

---

## 🏗️ **Fichier concerné**

`src/builtins/pwd.c`

---

## 🎯 **Objectif de la fonction**

La fonction `builtin_pwd` reproduit le comportement de la commande shell `pwd` (print working directory) :

✅ Affiche le chemin absolu du répertoire courant  
✅ Ajoute un retour à la ligne  
✅ Affiche une erreur si le chemin ne peut pas être récupéré

---

## 🔍 **Pourquoi coder `pwd` comme builtin ?**

Dans un shell normal, taper `pwd` exécute `/bin/pwd`.  
Mais **Minishell doit gérer les builtins en interne, sans lancer de processus externe (`execve`)**.

La fonction `builtin_pwd` implémente donc directement l’affichage du chemin dans le shell.

---