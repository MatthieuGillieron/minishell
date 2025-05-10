/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:45:04 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 16:14:51 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_exit_char(char c, int pos)
{
	return (ft_isdigit(c) || (pos == 0 && (c == '-' || c == '+')));
}

/**
 * Implémentation de la commande builtin `exit`
 *
 * Comporte uniquement le comportement standard attendu par Bash :
 * - Affiche "exit" sur la sortie standard avant de quitter (même cas d'erreur)
 * - Si aucun argument : quitte avec code 0
 * - Si un argument numérique valide : quitte avec ce code
 * - Si un argument non numérique : affiche une erreur et quitte avec code 2
 * - Si plus d'un argument : affiche "too many arguments" et NE quitte PAS
 *
 * Restrictions respectées :
 * - Utilise uniquement printf et ft_putstr_fd/ft_putendl_fd pour stderr
 * - Conforme au comportement de Bash
 *
 * @param argv Tableau des arguments (argv[0] = "exit", argv[1] = value option)
 * @return 1 si trop d'arguments et le shell ne quitte pas, rien sinon
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
