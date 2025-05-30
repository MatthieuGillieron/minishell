#ifndef BUILTINS_H
# define BUILTINS_H

int		check_builtin(char **argv, t_env **env, t_status *status);
int		builtin_cd(char **argv, t_env **env);
int		builtin_exit(char **argv);
int		builtin_unset(char **argv, t_env **env);
int		builtin_env(t_env *env);
int		builtin_pwd(void);
int		builtin_echo(char **argv);

/* Commande export et fonctions associées */
int		builtin_export(char **argv, t_env **env);
void	print_sorted_env(t_env *env);

#endif