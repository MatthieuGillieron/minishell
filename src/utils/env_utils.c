/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:53:08 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/10 17:15:16 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Crée une copie dynamique du tableau d'environnement.
 * Alloue et duplique chaque entrée de envp.
 *
 * @param envp Le tableau d'environnement original (fourni par main).
 * @return Un tableau nouvellement alloué contenant les mêmes variables,
	ou NULL en cas d'erreur.
 */
char	**copy_env(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/**
 * Libère proprement un tableau d'environnement dynamique.
 *
 * @param env Le tableau à libérer.
 */
void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
