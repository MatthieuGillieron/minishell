#ifndef EXECUTOR_H
# define EXECUTOR_H

void	execute_command(char **argv, t_env **env, t_status *status);
void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status);

#endif