#include "../includes/minishell.h"

/**
 * builtin_echo - Affiche les arguments à la suite avec un espace.
 * @argv: Liste des mots à afficher.
 * 
 * Retourne toujours 0.
 */
int	builtin_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
