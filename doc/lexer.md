# Documentation : Gestion du Lexer et des Tokens dans Minishell

## Introduction

Dans le projet Minishell, le **lexer** et la **tokenisation** sont des étapes fondamentales pour analyser une ligne de commande saisie par l'utilisateur. Ces étapes permettent de découper l'entrée en unités lexicales appelées **tokens**, qui seront ensuite utilisées par le parser pour construire une structure syntaxique.

Cette documentation explique en détail comment le lexer et la gestion des tokens ont été implémentés, en décrivant les structures, les fonctions, et les étapes principales.

---

## 1. Objectifs du Lexer

Le rôle du lexer est de :
1. Lire une ligne de commande saisie par l'utilisateur.
2. Découper cette ligne en **tokens** (unités lexicales) en fonction des caractères spéciaux (`|`, `<`, `>`, etc.), des mots, et des espaces.
3. Préparer ces tokens pour qu'ils soient utilisés par le parser.

---

## 2. Structures et Types

### 2.1. `t_lexer`

Représente l'état du lexer pendant l'analyse de l'entrée.

```c
typedef struct s_lexer
{
    char	*input;          // Ligne d'entrée à analyser
    size_t 	position;        // Position actuelle dans la ligne
    char	current_char;    // Caractère actuel
}	
```

### 2.2. `t_token`

Représente un token extrait par le lexer.

```c
typedef struct s_token
{
    t_token_type	type;       // Type du token (ex: WORD, PIPE, etc.)
    char			*value;     // Valeur du token (ex: "echo", "|", etc.)
    int				position;   // Position dans la ligne d'entrée
    struct s_token	*next;      // Pointeur vers le token suivant (non utilisé ici)
}	
```

### 2.3. t_token_type

Énumération des différents types de tokens

```c
typedef enum e_token_type
{
    WORD,           // Un mot ou argument (ex: "ls", "hello")
    PIPE,           // Le caractère `|`
    REDIR_IN,       // Le caractère `<`
    REDIR_OUT,      // Le caractère `>`
    REDIR_APPEND,   // Le caractère `>>`
    HEREDOC,        // Le caractère `<<`
    ENV_VAR,        // Une variable d'environnement (ex: "$HOME")
    QUOTE,          // Un guillemet simple ou double
    WHITESPACE,     // Un espace ou une tabulation
    END_OF_INPUT    // Fin de l'entrée
}	
```




### 3. Fonctionnement du Lexer

3.1. Initialisation

Le lexer est initialisé avec la ligne d'entrée à analyser. La structure `t_lexer` est allouée dynamiquement et configurée avec les valeurs initiales.

```c
t_lexer *init_lexer(char *input)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->input = input;
    lexer->position = 0;
    lexer->current_char = input[0];
    return (lexer);
}
```

### 3.2. Avancement dans l'entrée

Le lexer avance caractère par caractère dans la ligne d'entrée grâce à la fonction `advance_lexer`.

```c
void advance_lexer(t_lexer *lexer)
{
    lexer->position++;
    if (lexer->input[lexer->position])
        lexer->current_char = lexer->input[lexer->position];
    else
        lexer->current_char = '\0';
}
```

### 3.3. Ignorer les espaces

Les espaces et tabulations sont ignorés grâce à la fonction `skip_whitespace`.

```c
void skip_whitespace(t_lexer *lexer)
{
    while (lexer->current_char && is_whitespace(lexer->current_char))
        advance_lexer(lexer);
}
```

### 3.4. Extraction des tokens

La fonction principale du lexer est get_next_token, qui extrait le prochain token de l'entrée.

1. Ignore les espaces avec skip_whitespace.
2. Vérifie si la fin de l'entrée est atteinte.
3. Identifie les caractères spéciaux (|, <, >, etc.).
4. Traite les mots ou arguments.

```c
t_token *get_next_token(t_lexer *lexer)
{
    skip_whitespace(lexer);

    if (lexer->current_char == '\0')
        return (create_token(END_OF_INPUT, NULL, lexer->position));
    if (is_special_char(lexer->current_char))
        return (tokenize_operator(lexer));
    if (!is_whitespace(lexer->current_char))
        return (tokenize_word(lexer));
    return (NULL);
}
```

### 4. Gestion des Tokens

4.1. Création d'un token

Les tokens sont créés dynamiquement avec la fonction `create_token`.
Chaque token est associé à un type, une valeur, et une position.

```c
t_token *create_token(t_token_type type, char *value, int position)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value ? ft_strdup(value) : NULL;
    token->position = position;
    return (token);
}
```

### 4.2. Libération de la mémoire

Les tokens sont libérés avec la fonction `free_token`.

```c
void free_token(t_token *token)
{
    if (token)
    {
        free(token->value);
        free(token);
    }
}
```

### 4.3. Affichage des tokens

Pour le débogage, les tokens peuvent être affichés avec print_tokens.

```c
void print_tokens(t_token **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        printf("Token[%d]: Type=%d, Value=%s\n", i, tokens[i]->type, tokens[i]->value);
        i++;
    }
}
```

### 5. Tokenisation

5.1. Tokenisation des mots
Les mots ou arguments sont extraits avec `tokenize_word`. La fonction avance dans l'entrée jusqu'à rencontrer un caractère spécial ou un espace.

```c
t_token *tokenize_word(t_lexer *lexer)
{
    size_t start = lexer->position;

    while (lexer->current_char && !is_whitespace(lexer->current_char) && !is_special_char(lexer->current_char))
        advance_lexer(lexer);
    char *value = ft_substr(lexer->input, start, lexer->position - start);
    return (create_token(WORD, value, start));
}
```

### 5.2. Tokenisation des opérateurs
Les opérateurs spéciaux `(|, <, >, >>, <<)` sont extraits avec `tokenize_operator`.

```c
t_token *tokenize_operator(t_lexer *lexer)
{
    char op = lexer->current_char;

    advance_lexer(lexer);
    if (op == '>' && lexer->current_char == '>')
    {
        advance_lexer(lexer);
        return (create_token(REDIR_APPEND, ">>", lexer->position - 2));
    }
    else if (op == '<' && lexer->current_char == '<')
    {
        advance_lexer(lexer);
        return (create_token(HEREDOC, "<<", lexer->position - 2));
    }
    else if (op == '>')
        return (create_token(REDIR_OUT, ">", lexer->position - 1));
    else if (op == '<')
        return (create_token(REDIR_IN, "<", lexer->position - 1));
    else if (op == '|')
        return (create_token(PIPE, "|", lexer->position - 1));
    return (NULL);
}
```

### 6. Utilitaires

6.1. Vérification des caractères
Les fonctions utilitaires permettent de vérifier si un caractère est un espace, un caractère spécial, ou un guillemet.

```c
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}
```

### 7. Test du Lexer

Une fonction de test `(test_lexer)` permet de vérifier le fonctionnement du lexer en affichant les tokens extraits.

```c
void test_lexer(char *input)
{
    t_token **tokens;

    printf("Input: %s\n", input);
    tokens = tokenize_input(input);
    if (!tokens)
    {
        printf("Erreur : Impossible de tokeniser l'entrée.\n");
        return;
    }
    print_tokens(tokens);

    int i = 0;
    while (tokens[i])
        free_token(tokens[i++]);
    free(tokens);
}
```
### 8. Conclusion

Le lexer et la tokenisation dans Minishell sont conçus pour analyser efficacement une ligne de commande et extraire des tokens. Cette architecture modulaire permet de gérer facilement les différents types de tokens et de préparer les données pour le parser.

Points forts :
- Gestion claire des tokens avec des types bien définis.
- Modularité grâce à la séparation des fonctions dans différents fichiers.
- Facilité de débogage avec des fonctions comme print_tokens.

Améliorations possibles :

- Ajouter la gestion des guillemets `(' et ")` pour les arguments complexes.
- Gérer les variables d'environnement `($VAR)` directement dans le lexer.