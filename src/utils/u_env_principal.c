#include "../includes/minishell.h"

t_env	*init_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;
	t_env	*last;
	int		i;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (node)
		{
			if (!head)
				head = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}	
	if (!head)
	{
		env_set(&head, "TERM", "xterm-256color");
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)))
			env_set(&head, "PWD", cwd);
	}
	return (head);
}


char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
	return (0);
}

int	env_unset(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
