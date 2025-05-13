/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:16:12 by mg                #+#    #+#             */
/*   Updated: 2025/05/13 16:33:11 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// juste pour test !!!

void test_lexer(char *input)
{
    t_token **tokens;

    printf("Input: %s\n", input);
    tokens = tokenize_input(input);
    if (!tokens)
    {
        printf("Erreur : Impossible de tokeniser l'entrée.\n");
        return;
    }
    print_tokens(tokens);

    int i = 0;
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