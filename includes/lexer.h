/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:11:47 by mg                #+#    #+#             */
/*   Updated: 2025/05/13 16:32:20 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type t_token_type;
typedef struct s_token t_token;
typedef struct s_lexer t_lexer;

// 	*** Lexer ***

t_lexer *init_lexer(char *input);
void	advance_lexer(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
t_token *get_next_token(t_lexer *lexer);
t_token **tokenize_input(char *input);

// 	*** Token ***

t_token *create_token(t_token_type type, char *value, int position);
void	free_token(t_token *token);
void	print_tokens(t_token **tokens);
t_token *tokenize_word(t_lexer *lexer);
t_token *tokenize_operator(t_lexer *lexer);

// 	*** Utils ***

int		is_whitespace(char c);
int		is_special_char(char c);
int		is_quote(char c);

#endif