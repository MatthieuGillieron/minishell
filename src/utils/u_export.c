/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:14:56 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:57 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * print_export_var - Affiche une variable au format de export.
 * @key: Nom de la variable.
 * @value: Valeur de la variable (peut être NULL).
 */
static void	print_export_var(char *key, char *value)
{
	printf("declare -x %s", key);
	if (value)
		printf("=\"%s\"", value);
	printf("\n");
}

/**
 * count_env - Compte le nombre de variables dans l'environnement.
 * @env: Liste d'environnement.
 * 
 * Retourne le nombre d'entrées.
 */
static int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/**
 * create_env_array - Crée un tableau de chaînes à partir de la liste env.
 * @env: Liste d'environnement.
 * 
 * Retourne un tableau de chaînes (à libérer par l'appelant).
 */
static char	**create_env_array(t_env *env)
{
	char	**array;
	int		count;
	int		i;

	count = count_env(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

/**
 * sort_env_array - Trie le tableau d'environnement par ordre alphabétique.
 * @array: Tableau à trier.
 */
static void	sort_env_array(char **array)
{
	int		i;
	int		j;
	char	*temp;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * print_sorted_env - Affiche les variables triées au format export.
 * @env: Liste des variables d'environnement.
 */
void	print_sorted_env(t_env *env)
{
	char	**keys;
	int		i;
	t_env	*current;

	keys = create_env_array(env);
	if (!keys)
		return ;
	sort_env_array(keys);
	i = 0;
	while (keys[i])
	{
		current = env;
		while (current && ft_strcmp(current->key, keys[i]) != 0)
			current = current->next;
		if (current)
			print_export_var(current->key, current->value);
		i++;
	}
	i = 0;
	while (keys[i])
	{
		free(keys[i]);
		i++;
	}
	free(keys);
}
