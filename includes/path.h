#ifndef PATH_H
# define PATH_H

char	*get_path_env(t_env *env);
char	*get_command_path(char *cmd, t_env *env);
void	free_split(char **split);
char	*get_command_path(char *cmd, t_env *env);
char *join_path(char *path, char *cmd);

#endif
