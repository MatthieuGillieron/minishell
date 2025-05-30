#ifndef ENV_H
# define ENV_H

t_env	*init_env_list(char **envp);
char	*env_get(t_env *env, const char *key);
int		env_set(t_env **env, const char *key, const char *value);
int		env_unset(t_env **env, const char *key);
char	**env_to_array(t_env *env);
void	free_env_list(t_env *env);

#endif