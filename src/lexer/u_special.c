#include "../../includes/minishell.h"

/**
 * is_special_command - Vérifie si une chaîne est une commande spéciale
 * @str: La chaîne à vérifier
 * @status: Structure contenant l'état du shell
 * 
 * Retourne 1 si la commande est spéciale et a été traitée, 0 sinon
 */
int	is_special_command(char *str, t_status *status)
{
	if (ft_strcmp(str, "$?") == 0)
	{
		builtin_echo_status(status);
		return (1);
	}
	return (0);
}