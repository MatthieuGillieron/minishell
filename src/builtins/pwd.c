#include "../includes/minishell.h"

/**
 * builtin_pwd - Affiche le répertoire courant.
 * 
 * Retourne 0 si succès, 1 sinon.
 */
int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
