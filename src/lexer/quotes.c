#include "../../includes/minishell.h"

/**
 * Gère les caractères d'échappement dans les guillemets doubles
 * @param lexer Le lexer contenant l'entrée à analyser
 * @param processed La chaîne de caractères traitée
 * @param p_index Pointeur sur l'index dans la chaîne traitée
 */
static void	handle_escape_char(t_lexer *lexer, char *processed, int *p_index)
{
	if (lexer->current_char == '\\' && lexer->input[lexer->position + 1])
	{
		if (lexer->input[lexer->position + 1] == '"' || 
			lexer->input[lexer->position + 1] == '\\' ||
			lexer->input[lexer->position + 1] == '$')
		{
			advance_lexer(lexer);
			processed[(*p_index)++] = lexer->current_char;
		}
		else
			processed[(*p_index)++] = '\\';
	}
	else
		processed[(*p_index)++] = lexer->current_char;
}

/**
 * Tokenise une chaîne entre guillemets simples
 * @param lexer Le lexer contenant l'entrée à analyser
 * @return Un token de type SQUOTE
 */
t_token	*tokenize_squote(t_lexer *lexer)
{
	size_t	start;
	char	*value;

	start = lexer->position;
	advance_lexer(lexer);  // Avancer après le guillemet ouvrant
	while (lexer->current_char && lexer->current_char != '\'')
		advance_lexer(lexer);
	if (lexer->current_char != '\'')
		return (NULL);  // Guillemet non fermé
	advance_lexer(lexer);  // Avancer après le guillemet fermant
	value = ft_substr(lexer->input, start + 1, lexer->position - start - 2);
	if (!value)
		return (NULL);
	return (create_token(SQUOTE, value, start));
}

/**
 * Tokenise une chaîne entre guillemets doubles
 * @param lexer Le lexer contenant l'entrée à analyser
 * @return Un token de type DQUOTE
 */
t_token	*tokenize_dquote(t_lexer *lexer)
{
	size_t	start;
	char	*processed;
	int		p_index;

	start = lexer->position;
	advance_lexer(lexer);  // Avancer après le guillemet ouvrant
	processed = malloc(ft_strlen(lexer->input) + 1);
	if (!processed)
		return (NULL);
	p_index = 0;
	while (lexer->current_char && lexer->current_char != '"')
	{
		handle_escape_char(lexer, processed, &p_index);
		advance_lexer(lexer);
	}
	if (lexer->current_char != '"')
	{
		free(processed);
		return (NULL);  // Guillemet non fermé
	}
	advance_lexer(lexer);  // Avancer après le guillemet fermant
	processed[p_index] = '\0';
	return (create_token(DQUOTE, processed, start));
}
