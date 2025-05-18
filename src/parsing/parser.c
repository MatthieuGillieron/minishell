/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:19:01 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/18 16:11:53 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../../includes/parser.h"

/**
 * Découpe une ligne de commande en tokens.
 * Utilise un simple split par espaces.
 *
 * @param line Ligne entrée par l'utilisateur.
 * @return Un tableau de chaînes représentant les tokens.
 */
char	**parse_line(char *line)
{
	if (!line)
		return (NULL);
	return (ft_split(line, ' '));
}

/**
 * Libère un tableau de tokens généré par parse_line.
 *
 * @param argv Le tableau à libérer.
 */

void	free_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
