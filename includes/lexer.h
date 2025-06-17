/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:15 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:16 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

//  *** Forward declarations ***

struct						s_env;
typedef struct s_env		t_env;
struct						s_status;
typedef struct s_status		t_status;
typedef enum e_token_type	t_token_type;

// 	*** Lexer ***
t_lexer	*init_lexer(char *input);
void	advance_lexer(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	**tokenize_input(char *input);

// 	*** Token ***
t_token	*create_token(t_token_type type, char *value, int position);
void	free_token(t_token *token);
void	print_tokens(t_token **tokens);
t_token	*tokenize_word(t_lexer *lexer);
t_token	*tokenize_operator(t_lexer *lexer);
t_token	*tokenize_squote(t_lexer *lexer);
t_token	*tokenize_dquote(t_lexer *lexer);

// 	*** Utils ***
int		is_whitespace(char c);
int		is_special_char(char c);
int		is_quote(char c);
int		is_special_command(char *str, t_status *status);

// 	*** Expansion ***
typedef struct s_expand
{
	char		*str;
	char		*result;
	int			i;
	int			*j;
	t_env		*env;
	t_status	*status;
}	t_expand;

char	*expand_variables(char *str, t_env *env, t_status *status);
char	*extract_var_name(char *str);
void	expand_exit_code(char *result, int *j, t_status *status);
void	expand_env_var(char *result, int *j, char *var_name, t_env *env);
int		process_dollar(t_expand *exp);

#endif