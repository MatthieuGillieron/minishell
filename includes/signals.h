/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:12:30 by mtaramar          #+#    #+#             */
/*   Updated: 2025/05/26 14:17:39 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef enum	e_signal_mode
{
	INTERACTIVE_MODE,
	EXECUTION_MODE,
	HEREDOC_MODE,
}	t_signal_mode;

//		*** PROTOTYPES ***

void	init_signals(void);
void	set_signal_mode(t_signal_mode mode);
void	handle_signals_parent(void);
void	handle_signals_child(void);

#endif