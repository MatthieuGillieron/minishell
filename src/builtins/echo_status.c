#include "../../includes/minishell.h"

/**
 * builtin_echo_status - Affiche le code de sortie de la dernière commande
 * @status: Structure contenant l'état du shell
 * 
 * Retourne toujours 0.
 */
int	builtin_echo_status(t_status *status)
{
	printf("%d\n", status->exit_code);
	return (0);
}