#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute_command(char **argv, t_env **env, t_status *status);
void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status);
int		apply_redirections(t_redirect *redirects);
int		apply_output_redirection(char *file_path);
int		apply_append_redirection(char *file_path);

#endif