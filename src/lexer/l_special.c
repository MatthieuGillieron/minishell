#include "../../includes/minishell.h"

int	is_special_command(char *str, t_status *status)
{
	// Désactiver complètement le traitement spécial des variables d'environnement
	(void)str;
	(void)status;
	return (0);
}
