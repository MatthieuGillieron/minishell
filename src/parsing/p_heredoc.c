#include "../../includes/minishell.h"

static char	*add_line_to_result(char *result, char *line, t_env *env, t_status *status)
{
	char	*expanded_line;
	char	*temp;

	expanded_line = expand_variables(line, env, status);
	free(line);
	if (!expanded_line)
	{
		free(result);
		return (NULL);
	}
	temp = result;
	result = ft_strjoin(result, expanded_line);
	free(temp);
	free(expanded_line);
	if (!result)
		return (NULL);
	temp = result;
	result = ft_strjoin(result, "\n");
	free(temp);
	return (result);
}

char	*process_heredoc(char *delimiter, t_env *env, t_status *status)
{
	char	*line;
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		result = add_line_to_result(result, line, env, status);
		if (!result)
			return (NULL);
	}
	return (result);
}

