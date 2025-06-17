/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:32 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:32 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

//  *** Forward declarations ***
struct						s_token;
typedef struct s_token		t_token;
struct						s_env;
typedef struct s_env		t_env;
struct						s_lexer;
typedef struct s_lexer		t_lexer;
struct						s_redirect;
typedef struct s_redirect	t_redirect;
struct						s_simple_cmd;
typedef struct s_simple_cmd	t_simple_cmd;
struct						s_command;
typedef struct s_command	t_command;
struct						s_status;
typedef struct s_status		t_status;
struct						s_expand;
typedef struct s_expand		t_expand;

typedef enum e_signal_mode
{
	INTERACTIVE_MODE,
	EXECUTION_MODE,
	HEREDOC_MODE,
}	t_signal_mode;

//		*** PROTOTYPES ***

void	sigint_interactive_handler(int sig);
void	sigint_execution_handler(int sig);
void	sigint_heredoc_handler(int sig);

void	init_signals(void);
void	set_signal_mode(t_signal_mode mode);
void	handle_signals_parent(void);
void	handle_signals_child(void);

#endif