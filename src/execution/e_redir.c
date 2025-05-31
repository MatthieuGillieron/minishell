#include "../../includes/minishell.h"

/**
 * Applique une redirection d'entrée (<)
 * @param file_path Chemin du fichier à ouvrir en lecture
 * @return 0 si succès, -1 si erreur
 */
static int	apply_input_redirection(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/**
 * Lit l'entrée jusqu'au délimiteur pour un heredoc
 * @param pipe_fd Descripteur de fichier du pipe
 * @param delimiter Le délimiteur qui termine la saisie
 */
static void	read_heredoc_input(int pipe_fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, delimiter) == 0))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
}

/**
 * Applique une redirection de type heredoc (<<)
 * @param delimiter Le délimiteur qui termine la saisie
 * @return 0 si succès, -1 si erreur
 */
static int	apply_heredoc_redirection(char *delimiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	set_signal_mode(HEREDOC_MODE);
	read_heredoc_input(pipe_fd[1], delimiter);
	set_signal_mode(INTERACTIVE_MODE);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

/**
 * Traite une redirection spécifique
 * @param current Redirection à traiter
 * @return 0 si succès, -1 si erreur
 */
static int	process_redirection(t_redirect *current)
{
	if (current->type == REDIR_INPUT)
		return (apply_input_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_OUTPUT)
		return (apply_output_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_APPEND_OUT)
		return (apply_append_redirection(current->file_or_delimiter));
	else if (current->type == REDIR_HEREDOC_OUT)
		return (apply_heredoc_redirection(current->file_or_delimiter));
	return (0);
}

/**
 * Applique toutes les redirections d'une commande
 * @param redirects Liste des redirections à appliquer
 * @return 0 si succès, -1 si erreur
 */
int	apply_redirections(t_redirect *redirects)
{
	t_redirect	*current;

	current = redirects;
	while (current)
	{
		if (process_redirection(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
