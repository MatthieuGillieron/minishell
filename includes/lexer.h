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
t_token *tokenize_squote(t_lexer *lexer);
t_token *tokenize_dquote(t_lexer *lexer);

// 	*** Utils ***

int		is_whitespace(char c);
int		is_special_char(char c);
int		is_quote(char c);
int		is_special_command(char *str, t_status *status);

// 	*** Expansion ***

char	*expand_variables(char *str, t_env *env, t_status *status);
char	*extract_var_name(char *str);
void	expand_exit_code(char *result, int *j, t_status *status);
void	expand_env_var(char *result, int *j, char *var_name, t_env *env);
int		process_dollar(char *str, int i, char *result, int *j,
						t_env *env, t_status *status);

#endif