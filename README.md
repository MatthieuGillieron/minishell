# Minishell - Projet 42

[![English](https://img.shields.io/badge/English-gray.svg)](./READMEen.md)   [![Français](https://img.shields.io/badge/Français-blue.svg)](./README.md)

Ce projet plonge dans les fondements de la **programmation système en C**, en reproduisant un **mini shell UNIX**. Il met en pratique la gestion des processus, les signaux, et les interactions complexes entre le terminal et l’utilisateur.

<br>

## 🧠 Description du projet

Le projet **Minishell** a pour but d’implémenter une version simplifiée d’un shell en ligne de commande, capable de gérer plusieurs commandes, redirections et pipes, tout en respectant le comportement attendu d’un shell UNIX.

Ce projet aborde des concepts essentiels comme :
- la **création de processus** avec `fork`, `execve` et `wait`
- la gestion des **pipes** (`|`) et **redirections** (`<`, `>`, `>>`)
- la gestion des **signaux** (`SIGINT`, `SIGQUIT`, etc.)
- la **parsing** complexe de l'entrée utilisateur (quotes, variables d’environnement, etc.)
- l'implémentation d'un environnement shell minimal

L’objectif est de recréer un environnement stable, capable de :
- exécuter des commandes internes (`cd`, `export`, `unset`, `env`, etc.)
- gérer la navigation et la manipulation d'environnement
- **gérer correctement les erreurs et signaux** sans faire planter le shell
- respecter le comportement attendu d’un shell Bash (dans les limites du projet)