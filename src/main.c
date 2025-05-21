/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:05:28 by mg                #+#    #+#             */
/*   Updated: 2025/05/21 15:48:29 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

/**
 * Fonction principale du programme minishell.
 *
 * - Initialise les signaux pour intercepter Ctrl+C / Ctrl+\
 * - Transforme le tableau d’environnement de base `envp` en liste chaînée
 * - Démarre la boucle d'exécution du shell (`shell_loop`)
 * - Nettoie la mémoire à la fin de l'exécution
 *
 * @param argc Nombre d’arguments passés au programme (non utilisé ici)
 * @param argv Tableau des arguments (non utilisé ici)
 * @param envp Tableau de chaînes représentant l’environnement système initial
 * @return Code de sortie global défini dans `g_exit_status`
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
	shell_loop(&env);
	test_lexer("echo hello | grep world > file.txt");
	free_env_list(env);
	return (g_exit_status);
}
*/

//int	g_exit_status = 0;

/**
 * Fonction pour tester le parser
 * 
 * @param input Ligne de commande à parser
 */
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

/**
 * Fonction principale du programme minishell.
 */
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
