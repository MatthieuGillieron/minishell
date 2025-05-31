#include "../includes/minishell.h"

/**
 * builtin_echo - Affiche les arguments à la suite avec un espace.
 * @argv: Liste des mots à afficher.
 * 
 * Gère l'option -n qui supprime le saut de ligne final.
 * Retourne toujours 0.
 */
int	builtin_echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	// Vérifier l'option -n
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	// Afficher les arguments
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	// Ajouter un saut de ligne sauf si -n est présent
	if (!n_flag)
		printf("\n");
	
	return (0);
}
