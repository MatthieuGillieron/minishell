#ifndef SIGNALS_H
# define SIGNALS_H

typedef enum e_signal_mode
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