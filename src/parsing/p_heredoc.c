#include "../../includes/minishell.h"

char *process_heredoc(char *delimiter, t_env *env, t_status *status)
{
    char *line;
    char *result;
    char *expanded_line;
    char *temp;
    
    result = ft_strdup("");
    if (!result)
        return NULL;
        
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // Appliquer l'expansion des variables sur la ligne
        expanded_line = expand_variables(line, env, status);
        free(line);
        
        if (!expanded_line)
        {
            free(result);
            return NULL;
        }
        
        // Ajouter la ligne au résultat
        temp = result;
        result = ft_strjoin(result, expanded_line);
        free(temp);
        free(expanded_line);
        
        if (!result)
            return NULL;
            
        // Ajouter un saut de ligne
        temp = result;
        result = ft_strjoin(result, "\n");
        free(temp);
        
        if (!result)
            return NULL;
    }
    
    return result;
}

