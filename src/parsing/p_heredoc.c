/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:47 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:11:47 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_heredoc_data
{
	char	*result;
	int		is_first;
	int		has_content;
}	t_heredoc_data;

static char	*expand_line(char *line, t_env *env, t_status *status)
{
	char	*expanded_line;

	expanded_line = expand_variables(line, env, status);
	free(line);
	return (expanded_line);
}

static char	*add_line_to_result(char *result, char *expanded_line, int is_first)
{
	char	*temp;

	if (!is_first)
	{
		temp = result;
		result = ft_strjoin(result, "\n");
		free(temp);
		if (!result)
			return (NULL);
	}
	temp = result;
	result = ft_strjoin(result, expanded_line);
	free(temp);
	return (result);
}

static char	*read_heredoc_lines(t_heredoc_data *data,
						char *delimiter, t_env *env, t_status *status)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		data->has_content = 1;
		expanded_line = expand_line(line, env, status);
		if (!expanded_line)
			return (NULL);
		data->result = add_line_to_result(data->result,
				expanded_line, data->is_first);
		free(expanded_line);
		if (!data->result)
			return (NULL);
		data->is_first = 0;
	}
	return (data->result);
}

char	*process_heredoc(char *delimiter, t_env *env, t_status *status)
{
	t_heredoc_data	data;
	char			*result;

	data.result = ft_strdup("");
	if (!data.result)
		return (NULL);
	data.is_first = 1;
	data.has_content = 0;
	result = read_heredoc_lines(&data, delimiter, env, status);
	if (!result || !data.has_content)
	{
		free(data.result);
		return (ft_strdup(""));
	}
	return (result);
}
