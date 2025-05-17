/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:18:40 by mg                #+#    #+#             */
/*   Updated: 2025/05/16 14:36:02 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Convertir un type de token en type de redirection
static t_redir_type token_to_redir_type(t_token_type token_type)
{
    if (token_type == REDIR_IN)
        return (REDIR_INPUT);
    else if (token_type == REDIR_OUT)
        return (REDIR_OUTPUT);
    else if (token_type == REDIR_APPEND)
        return (REDIR_APPEND);
    else if (token_type == HEREDOC)
        return (REDIR_HEREDOC);
    return (REDIR_INPUT); // Par défaut
}

// Parser une redirection (< fichier, > fichier, etc.)
t_redirect *parse_redirection(t_token ***tokens_ptr, t_token_type redir_type)
{
    t_redirect *redirect;

    // Vérifier qu'il y a un token après la redirection
    if (!**tokens_ptr || (***tokens_ptr).type != WORD)
        return (NULL); // Erreur: redirection sans fichier/délimiteur
    
    // Créer la structure de redirection
    redirect = (t_redirect *)malloc(sizeof(t_redirect));
    if (!redirect)
        return (NULL);
    
    // Initialiser la redirection
    redirect->type = token_to_redir_type(redir_type);
    redirect->file_or_delimiter = (***tokens_ptr).value;
    redirect->next = NULL;
    
    // Avancer au token suivant
    (*tokens_ptr)++;
    
    return (redirect);
}
