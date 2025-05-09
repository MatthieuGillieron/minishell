# 📚 Documentation – Builtins Minishell

Ce document explique les fichiers et fonctions liés aux builtins du Minishell, pour bien comprendre leur rôle et leur fonctionnement.

---

## 🏗️ `builtins.c`

Le fichier `src/builtins/builtins.c` contient la fonction `check_builtin()`.

### ✅ Objectif

- Vérifie si la commande entrée par l’utilisateur est un **builtin**
- Si OUI, appelle la fonction builtin correspondante
- Sinon, retourne `0` pour indiquer qu’il faut lancer `execve`

### ✅ Fonction

```c
#include "../../includes/builtins.h"
#include "../../libft/libft.h"

int	check_builtin(char **argv)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
	{
		builtin_pwd();
		return (1);
	}
	if (ft_strncmp(argv[0], "echo", 5) == 0)
	{
		builtin_echo(argv);
		return (1);
	}
	if (ft_strncmp(argv[0], "env", 4) == 0)
	{
		builtin_env();
		return (1);
	}
	return (0);
}
