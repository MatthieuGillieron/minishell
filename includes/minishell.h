/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaramar <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:02:48 by mg                #+#    #+#             */
/*   Updated: 2025/05/08 17:53:54 by mtaramar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_exit_status;

/*
	Bibliotheque
*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include "signals.h"
# include "loop.h"
# include "parsing.h"
# include "executor.h"
# include "path.h"
# include "../libft/includes/libft.h"


/*
	Colors
*/

# define RST		"\033[0m"		
# define RED		"\033[1;31m"	
# define GREEN		"\033[1;32m"	
# define YELLOW		"\033[1;33m"	
# define BLUE		"\033[1;34m"	
# define MAGENTA	"\033[1;35m"	
# define CYAN		"\033[1;36m"	
# define WHITE		"\033[1;37m"

#endif