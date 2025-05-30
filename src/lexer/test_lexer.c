#include "../../includes/minishell.h"

// juste pour test !!!

/**
 * Affiche tous les tokens pour le débogage.
 */
void	print_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("Token[%d]: Type=%d, Value=%s\n",
			i, tokens[i]->type, tokens[i]->value);
		i++;
	}
}

void	test_lexer(char *input)
{
	t_token	**tokens;
	int		i;

	printf("Input: %s\n", input);
	tokens = tokenize_input(input);
	if (!tokens)
	{
		printf("Erreur : Impossible de tokeniser l'entrée.\n");
		return ;
	}
	print_tokens(tokens);
	i = 0;
	while (tokens[i])
		free_token(tokens[i++]);
	free(tokens);
}

/*
int	main(int argc, char **argv, char **envp)
	{
		(void)argc;
		(void)argv;
		(void)envp;
	
		// Exemple de test du lexer
		test_lexer("echo hello | grep world > file.txt");
	
		return (0);
	}
*/
