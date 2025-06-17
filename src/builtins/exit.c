/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:09:01 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:09:01 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * is_valid_exit_char - Vérifie si le caractère est valide pour un nombre.
 * @c: caractère à tester.
 * @pos: position dans la chaîne (utile pour '+' ou '-').
 * 
 * Retourne 1 si c’est un caractère valide, 0 sinon.
 */
static int	is_valid_exit_char(char c, int pos)
{
	return (ft_isdigit(c) || (pos == 0 && (c == '-' || c == '+')));
}

/**
 * builtin_exit - Gère le comportement du builtin exit.
 * @argv: Arguments. Peut inclure un code de sortie.
 * 
 * Quitte le programme ou affiche erreur si trop d’arguments.
 * Retourne 1 si trop d’arguments (ne quitte pas).
 */
int	builtin_exit(char **argv)
{
	int	exit_code;
	int	i;

	printf("exit\n");
	if (!argv[1])
		exit(0);
	i = 0;
	while (argv[1][i])
	{
		if (!is_valid_exit_char(argv[1][i], i))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		i++;
	}
	exit_code = ft_atoi(argv[1]);
	if (argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	exit(exit_code);
}
