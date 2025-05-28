/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:04:37 by mg                #+#    #+#             */
/*   Updated: 2025/05/28 09:05:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	execute_command(char **argv, t_env **env, t_status *status)
{
    pid_t	pid;
    char	*path;
    int		cmd_status;
    char	**envp;
    char	*dbg_path;
	
    ft_putstr_fd("DEBUG: execute_command appelée avec: ", 2);
    if (argv && argv[0])
	ft_putendl_fd(argv[0], 2);
    else
	ft_putendl_fd("(commande NULL)", 2);
    
    if (!argv || !argv[0] || !argv[0][0])
    {
        ft_putendl_fd("DEBUG: Commande vide ou NULL", 2);
        status->exit_code = 0;
        return;
    }
	
    if (check_builtin(argv, env, status))
    {
        ft_putendl_fd("DEBUG: Commande builtin exécutée", 2);
        return;
    }
    
    dbg_path = env_get(*env, "PATH");
    if (!dbg_path)
	ft_putendl_fd("DEBUG: PATH est NULL", 2);
    else
    {
        ft_putstr_fd("DEBUG: PATH = ", 2);
        ft_putendl_fd(dbg_path, 2);
    }
    
    path = get_command_path(argv[0], *env);
    if (!path)
    {
        ft_putstr_fd("DEBUG: Chemin non trouvé pour: ", 2);
        ft_putendl_fd(argv[0], 2);
        ft_putstr_fd("command not found: ", 2);
        ft_putendl_fd(argv[0], 2);
        status->exit_code = 127;
        return;
    }
    
    ft_putstr_fd("DEBUG: Chemin trouvé: ", 2);
    ft_putendl_fd(path, 2);
    
    handle_signals_parent();
    pid = fork();
    if (pid == 0)
    {
        ft_putendl_fd("DEBUG: Processus enfant créé", 2);
        handle_signals_child();
        envp = env_to_array(*env);
        
        if (!envp)
		ft_putendl_fd("DEBUG: env_to_array a retourné NULL", 2);
        else
        {
            int i = 0;
            while (envp[i] && i < 5) // Afficher seulement les 5 premières variables
            {
                ft_putstr_fd("DEBUG: env[", 2);
                ft_putnbr_fd(i, 2);
                ft_putstr_fd("] = ", 2);
                ft_putendl_fd(envp[i], 2);
                i++;
            }
            ft_putstr_fd("DEBUG: Total env vars: ", 2);
            while (envp[i])
			i++;
            ft_putnbr_fd(i, 2);
            ft_putchar_fd('\n', 2);
        }
        
        ft_putstr_fd("DEBUG: Tentative d'exécution de: ", 2);
        ft_putendl_fd(path, 2);
        
        execve(path, argv, envp);
        
        // Si on arrive ici, execve a échoué
        ft_putstr_fd("DEBUG: execve a échoué avec errno = ", 2);
        ft_putnbr_fd(errno, 2);
        ft_putstr_fd(" (", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putendl_fd(")", 2);
        
        perror("execve");
        free_split(envp);
        free(path);
        exit(126);
    }
    
    ft_putstr_fd("DEBUG: En attente du processus enfant (PID: ", 2);
    ft_putnbr_fd(pid, 2);
    ft_putendl_fd(")", 2);
    
    waitpid(pid, &cmd_status, 0);
    
    ft_putstr_fd("DEBUG: Processus enfant terminé avec status: ", 2);
    ft_putnbr_fd(cmd_status, 2);
    ft_putchar_fd('\n', 2);
    
    set_signal_mode(INTERACTIVE_MODE);
	
    if (WIFEXITED(cmd_status))
    {
        status->exit_code = WEXITSTATUS(cmd_status);
        ft_putstr_fd("DEBUG: Exit code: ", 2);
        ft_putnbr_fd(status->exit_code, 2);
        ft_putchar_fd('\n', 2);
    }
    else if (WIFSIGNALED(cmd_status))
    {
        status->exit_code = 128 + WTERMSIG(cmd_status);
        ft_putstr_fd("DEBUG: Terminé par signal: ", 2);
        ft_putnbr_fd(WTERMSIG(cmd_status), 2);
        ft_putchar_fd('\n', 2);
        
        if (WTERMSIG(cmd_status) == SIGINT)
		write(1, "^C\n", 3);
        else if (WTERMSIG(cmd_status) == SIGQUIT)
		write(1, "^\\Quit\n", 7);
    }
    free(path);
}

*/