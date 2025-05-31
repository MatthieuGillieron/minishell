#include "../../includes/minishell.h"

// Déclaration de la fonction définie dans e_redir.c
int apply_redirections(t_redirect *redirects);

/**
 * Exécute une commande simple
 * @param cmd Commande simple à exécuter
 * @param env Pointeur vers l'environnement
 * @param status Structure contenant l'état du shell
*/
static void	execute_simple_cmd(t_simple_cmd *cmd, t_env **env, t_status *status)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!cmd || !cmd->args || !cmd->args[0])
		return;
	// Sauvegarder les descripteurs standard pour les restaurer plus tard
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	// Appliquer les redirections si présentes
	if (cmd->redirects)
	{
		if (apply_redirections(cmd->redirects) == -1)
		{
			status->exit_code = 1;
			// Restaurer les descripteurs standard
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
			return ;
		}
	}
	// Exécuter la commande
	execute_command(cmd->args, env, status);
	// Restaurer les descripteurs standard
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
	if (!cmd || !cmd->commands)
		return ;
	
	if (cmd->cmd_count == 1)
	{
		execute_simple_cmd(cmd->commands[0], env, status);
		return ;
	}
	execute_pipeline(cmd, env, status);
}
