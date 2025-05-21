/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:26:59 by mg                #+#    #+#             */
/*   Updated: 2025/05/21 16:03:35 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_redir_type(t_redir_type type)
{
	if (type == REDIR_INPUT)
		printf("<");
	else if (type == REDIR_OUTPUT)
		printf(">");
	else if (type == REDIR_APPEND_OUT)
		printf(">>");
	else if (type == REDIR_HEREDOC_OUT)
		printf("<<");
}

static void	print_redirects(t_redirect *redirect)
{
	while (redirect)
	{
		printf(" ");
		print_redir_type(redirect->type);
		printf(" %s", redirect->file_or_delimiter);
		redirect = redirect->next;
	}
}

static void	print_simple_cmd(t_simple_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (i < cmd->arg_count)
	{
		printf("%s", cmd->args[i]);
		if (i < cmd->arg_count - 1)
			printf(" ");
		i++;
	}
	if (cmd->redirects)
		print_redirects(cmd->redirects);
}

void	print_command(t_command *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("Command is NULL\n");
		return ;
	}
	printf("Command with %d parts:\n", cmd->cmd_count);
	i = 0;
	while (i < cmd->cmd_count)
	{
		printf("  %d: ", i + 1);
		print_simple_cmd(cmd->commands[i]);
		if (i < cmd->cmd_count - 1)
			printf(" | ");
		printf("\n");
		i++;
	}
}
