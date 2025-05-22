/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:26:59 by mg                #+#    #+#             */
/*   Updated: 2025/05/22 15:15:15 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static void	print_redir_type(t_redir_type type)
{
	if (type == REDIR_INPUT)
		printf("<");
	else if (type == REDIR_OUTPUT)
		printf(">");
	else if (type == REDIR_APPEND_OUT)
		printf(">>");
	else if (type == REDIR_HEREDOC_OUT)
		printf("<<");
}

static void	print_redirects(t_redirect *redirect)
{
	while (redirect)
	{
		printf(" ");
		print_redir_type(redirect->type);
		printf(" %s", redirect->file_or_delimiter);
		redirect = redirect->next;
	}
}

static void	print_simple_cmd(t_simple_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (i < cmd->arg_count)
	{
		printf("%s", cmd->args[i]);
		if (i < cmd->arg_count - 1)
			printf(" ");
		i++;
	}
	if (cmd->redirects)
		print_redirects(cmd->redirects);
}

void	print_command(t_command *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command with %d parts:\n", cmd->cmd_count);
	i = 0;
	while (i < cmd->cmd_count)
	{
		printf("  %d: ", i + 1);
		print_simple_cmd(cmd->commands[i]);
		if (i < cmd->cmd_count - 1)
			printf(" | ");
		printf("\n");
		i++;
	}
}
*/


/*
 * Fonction pour tester le parser
 * 
 * @param input Ligne de commande à parser
 */


/*
void	test_parser(char *input)
{
	t_token		**tokens;
	t_command	*cmd;

	printf("\n=== Test du Parser ===\n");
	printf("Input: %s\n", input);
	// Tokenisation de l'entrée
	tokens = tokenize_input(input);
	if (!tokens)
	{
		printf("Erreur : Impossible de tokeniser l'entrée.\n");
		return;
	}
	// Affichage des tokens (pour debug)
	printf("\n-- Tokens --\n");
	print_tokens(tokens);
	// Parsing des tokens en structure de commande
	cmd = parse_tokens(tokens);
	if (!cmd)
	{
		printf("\nErreur : Impossible de parser les tokens.\n");
		// Libération des tokens
		int i = 0;
		while (tokens[i])
			free_token(tokens[i++]);
		free(tokens);
		return;
	}
	// Affichage de la structure de commande (à implémenter)
	printf("\n-- Structure de Commande --\n");
	print_command(cmd);
	// Libération de la mémoire
	free_command(cmd);
	int i = 0;
	while (tokens[i])
		free_token(tokens[i++]);
	free(tokens);
}
*/

/*
 * Fonction principale du programme minishell.
 */

/*
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	
	env = init_env_list(envp);
	if (!env)
		return (1);
	init_signals();
	// Tests du parser avec différentes commandes
	test_parser("echo hello");
	test_parser("ls -la | grep .c | wc -l");
	test_parser("cat < input.txt > output.txt");
	test_parser("echo hello > file | grep world");
	test_parser("cat < input > output >> append");
	// Décommenter pour lancer le shell interactif
	// shell_loop(&env);
	free_env_list(env);
	return (g_exit_status);
}
*/