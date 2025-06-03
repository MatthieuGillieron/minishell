#include "../includes/minishell.h"

t_env	*create_env_node(const char *entry)
{
	t_env	*node;
	char	*equal;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_substr(entry, 0, equal - entry);
	node->value = ft_strdup(equal + 1);
	node->next = NULL;
	return (node);
}

void	add_default_path_if_missing(t_env **head)
{
	t_env	*node;
	t_env	*last;

	if (env_get(*head, "PATH"))
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->key = ft_strdup("PATH");
	node->value = ft_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	node->next = NULL;
	if (!*head)
		*head = node;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}
