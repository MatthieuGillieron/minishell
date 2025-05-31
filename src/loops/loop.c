#include "../includes/minishell.h"

/**
 * @brief Boucle principale de l'interpréteur Minishell.
 *
 * Cette boucle lit une ligne de commande de l'utilisateur via readline,
 * la stocke dans l'historique si elle n'est pas vide,
 * la parse en tokens (arguments), exécute la commande,
 * puis libère toute la mémoire allouée.
 *
 * Elle continue jusqu'à ce que l'utilisateur entre EOF (Ctrl+D),
 * auquel cas "exit" est affiché et la boucle se termine.
 *
 * @param env Structure chaînée contenant l'environnement courant.
 */


/**
 * Traite les tokens et exécute la commande
 * @param tokens Les tokens à traiter
 * @param status Structure contenant l'état du shell
 */
static void	process_tokens(t_token **tokens, t_status *status)
{
	t_command	*cmd;
	int			i;

	expand_tokens(tokens, status->env, status);
	cmd = parse_tokens(tokens);
	if (cmd)
	{
		execute_parsed_command(cmd, &status->env, status);
		free_command(cmd);
	}
	i = 0;
	while (tokens[i])
		free_token(tokens[i++]);
	free(tokens);
}

/**
 * Lit une ligne de commande et la traite
 * @param status Structure contenant l'état du shell
 * @return 1 pour continuer, 0 pour quitter
 */
static int	read_and_process_line(t_status *status)
{
	char		*line;
	t_token		**tokens;

	line = readline(MAGENTA"MNM$ "RST);
	if (!line)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (*line)
		add_history(line);
	
	// Vérifier si c'est une commande spéciale
	if (is_special_command(line, status))
	{
		free(line);
		return (1);
	}
	
	tokens = tokenize_input(line);
	if (tokens)
		process_tokens(tokens, status);
	free(line);
	return (1);
}

/**
 * Boucle principale de l'interpréteur Minishell
 * @param status Structure contenant l'état du shell
 */
void	shell_loop(t_status *status)
{
	while (status->running)
	{
		set_signal_mode(INTERACTIVE_MODE);
		g_sig_received = 0;
		if (!read_and_process_line(status))
			break;
	}
}