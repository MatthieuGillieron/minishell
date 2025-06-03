## Documentation Détaillée du Parser de Minishell**

### **Table des Matières**

1. Architecture Globale
2. Structures de Données
3. Flux de Traitement
4. Analyse Détaillée des Fichiers
5. Cas d'Utilisation
6. Gestion des Erreurs
7. Conformité à la Norme 42

### **Architecture Globale**

Le parser de Minishell est responsable de transformer une série de tokens générés par le lexer en une structure de données hiérarchique représentant une commande shell. Cette structure peut ensuite être exécutée par le module d'exécution.

## Organisation des Fichiers

Le parser est divisé en plusieurs fichiers pour respecter la norme 42:

- **p_core.c**: Fonctions centrales du parser (initialisation et parsing principal)
- **p_simple.c**: Gestion des commandes simples
- **p_redir.c**: Gestion des redirections
- **p_test.c**: Fonctions d'affichage pour le débogage
- **u_parse.c**: Fonctions utilitaires pour la libération de mémoire

## **Structures de Données**

### Énumération des Types de Redirection

```c

typedef *enum* e_redir_type

{

    REDIR_INPUT,         *// Redirection d'entrée (<)*

    REDIR_OUTPUT,        *// Redirection de sortie (>)*

    REDIR_APPEND_OUT,    *// Redirection de sortie en mode append (>>)*

    REDIR_HEREDOC_OUT    *// Heredoc (<<)*

} t_redir_type;

```

Cette énumération définit les différents types de redirections que le shell peut gérer, permettant une représentation claire et typée dans le code.

## Structure de Redirection

```c

typedef *struct* s_redirect

{

    t_redir_type        type;                *// Type de redirection*

    *char*                *file_or_delimiter;  *// Fichier ou délimiteur*

    *struct* s_redirect   *next;               *// Pointeur vers la redirection suivante*

} t_redirect;
```

Cette structure représente une redirection individuelle avec:

- Un type (entrée, sortie, etc.)
- Un nom de fichier ou un délimiteur
- Un pointeur vers la redirection suivante, permettant de créer une liste chaînée

## Structure de Commande Simple

```c

typedef *struct* s_simple_cmd

{

    *char*        **args;       *// Tableau d'arguments (args[0] est la commande)*

    *int*         arg_count;    *// Nombre d'arguments*

    t_redirect  *redirects;   *// Liste chaînée de redirections*

} t_simple_cmd;
```

Cette structure représente une commande shell simple (avant ou après un pipe) avec:

- Un tableau d'arguments (le premier étant la commande elle-même)
- Un compteur d'arguments
- Une liste de redirections associées à cette commande

## Structure de Commande Complète|

```c

typedef *struct* s_command

{

    t_simple_cmd    **commands;  *// Tableau de commandes simples*

    *int*             cmd_count;   *// Nombre de commandes dans le pipeline*

} t_command;
```

Cette structure représente un pipeline complet de commandes avec:

- Un tableau de commandes simples
- Le nombre de commandes dans le pipeline (séparées par des pipes)

## **Flux de Traitement**

Le flux de traitement du parser suit les étapes suivantes:

1. **Tokenisation**: L'entrée utilisateur est d'abord tokenisée par le lexer
2. **Parsing global**: La fonction `parse_tokens` identifie les commandes séparées par des pipes
3. **Parsing des commandes simples**: Chaque segment entre pipes est parsé par `parse_simple_command`
4. **Parsing des redirections**: Les redirections sont détectées et parsées par `parse_redirection`
5. **Construction de la structure**: Une structure hiérarchique est créée pour représenter la commande complète

## **Analyse Détaillée des Fichiers**

##p_core.c - Fonctions Centrales

### initialize_command

```c

t_command *initialize_command(*int* cmd_count)

{

    t_command *cmd;

    *int*       i;   

    cmd = (t_command *)malloc(sizeof(t_command));

    if (!cmd)
        return (NULL);

    cmd->cmd_count = cmd_count;
    cmd->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd_count);

    if (!cmd->commands)
    {
    free(cmd);
    return (NULL);
    }

    i = 0;

    while (i < cmd->cmd_count)
    {
        cmd->commands[i] = NULL;
        i++;
    }

return (cmd);

}
```

**Analyse**:

- Alloue la mémoire pour la structure `t_command`
- Alloue un tableau de pointeurs vers des commandes simples
- Initialise tous les pointeurs à NULL
- Gère proprement les erreurs d'allocation mémoire

## count_commands

```c

static *int* count_commands(t_token **tokens)

{

    *int*     count;

    t_token **current;
    count = 1; *// Au moins une commande*

    current = tokens;

    while (*current)
    {
        if ((*current)->type == PIPE)
            count++;
    current++;
    }

return (count);

}
```

**Analyse**:

- Fonction auxiliaire marquée comme `static` car utilisée uniquement dans ce fichier
- Compte le nombre de commandes dans un pipeline en comptant les tokens PIPE + 1
- Implémentation simple et efficace

### parse_tokens

```c
t_command *parse_tokens(t_token **tokens)

{

    t_command *cmd;
    t_token   **current;

    *int*       i;
    *int*       cmd_count;

    if (!tokens || !tokens[0])
        return (NULL);
    cmd_count = count_commands(tokens);
    cmd = initialize_command(cmd_count);
    if (!cmd)
        return (NULL);
    current = tokens;
    i = 0;
    while (i < cmd->cmd_count)
    {
        cmd->commands[i] = parse_simple_command(&current);
        if (!cmd->commands[i])
        {
            free_command(cmd);
            return (NULL);
        }
        if (*current && (*current)->type == PIPE)
            current++;
        i++;
    }
return (cmd);

}

```

**Analyse**:

- Fonction principale du parser qui:
    1. Vérifie la validité des tokens d'entrée
    2. Compte le nombre de commandes séparées par des pipes
    3. Initialise la structure de commande
    4. Parse chaque commande simple
    5. Gère proprement les erreurs et libère la mémoire en cas d'échec
- Passe un pointeur vers le pointeur de token (`&current`) pour permettre à `parse_simple_command` de faire avancer le pointeur

## p_simple.c - Parsing des Commandes Simples

### add_arg

```c

static *int* add_arg(t_simple_cmd *cmd, *char* *arg)
{

    *char* **new_args;
    *int*   i;

    new_args = (*char* **)malloc(sizeof(*char* *) * (cmd->arg_count + 2));
    if (!new_args)
        return (0);
    i = 0;

    while (i < cmd->arg_count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[cmd->arg_count] = arg;
    new_args[cmd->arg_count + 1] = NULL;

    if (cmd->args)
        free(cmd->args);
    cmd->args = new_args;
    cmd->arg_count++;
return (1);

}
```

**Analyse**:

- Fonction helper qui ajoute un argument à une commande simple
- Réalloue le tableau d'arguments pour accommoder le nouvel argument
- Termine le tableau par NULL pour respecter la convention POSIX
- Gère correctement la libération de l'ancien tableau
- Note: Les chaînes individuelles ne sont pas dupliquées mais référencées directement depuis les tokens

### add_redirect

```c

static *int* add_redirect(t_simple_cmd *cmd, t_redirect *redirect)
{

    t_redirect *current;

    if (!cmd->redirects)
        cmd->redirects = redirect;
    else
    {
        current = cmd->redirects;
    while (current->next)
        current = current->next;
    current->next = redirect;
    }

return (1);

}

```

**Analyse**:

- Ajoute une redirection à la fin de la liste chaînée de redirections d'une commande
- Gère le cas spécial où c'est la première redirection
- Implémentation classique d'ajout à une liste chaînée

### process_token

```c
static *int* process_token(t_simple_cmd *cmd, t_token ***tokens_ptr)

{

t_token_type redir_type;

t_redirect   *redirect;

if ((***tokens_ptr).type == WORD)

{

if (!add_arg(cmd, (***tokens_ptr).value))

return (0);

(*tokens_ptr)++;

}

else if ((***tokens_ptr).type == REDIR_IN || (***tokens_ptr).type == REDIR_OUT

|| (***tokens_ptr).type == REDIR_APPEND || (***tokens_ptr).type == HEREDOC)

{

redir_type = (***tokens_ptr).type;

(*tokens_ptr)++;

redirect = parse_redirection(tokens_ptr, redir_type);

if (!redirect)

return (0);

if (!add_redirect(cmd, redirect))

return (0);

}

else

return (0);

return (1);

}
```c

**#### Analyse**:

- Fonction centrale qui traite un token selon son type
- Gère deux cas principaux:
    1. Token WORD: ajoute l'argument à la commande
    2. Tokens de redirection: parse la redirection et l'ajoute à la commande
- Avance le pointeur de token après traitement
- Retourne 0 en cas d'erreur, ce qui permet à `parse_simple_command` de détecter et gérer les échecs

### ### parse_simple_command

```c

t_simple_cmd *parse_simple_command(t_token ***tokens_ptr)

{

t_simple_cmd *cmd;

cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));

if (!cmd)

return (NULL);

cmd->args = NULL;

cmd->arg_count = 0;

cmd->redirects = NULL;

while (**tokens_ptr && (***tokens_ptr).type != PIPE

&& (***tokens_ptr).type != END_OF_INPUT)

{

if (!process_token(cmd, tokens_ptr))

return (NULL);

}

if (**tokens_ptr && (***tokens_ptr).type == END_OF_INPUT)

(*tokens_ptr)++;

return (cmd);

}

```

**#### Analyse**:

- Fonction principale pour parser une commande simple
- Initialise la structure de commande
- Traite les tokens séquentiellement jusqu'à rencontrer un pipe ou la fin de l'entrée
- Délègue le traitement de chaque token à `process_token`
- Gère spécifiquement le token END_OF_INPUT pour éviter qu'il ne soit traité à nouveau
- Optimisé pour respecter la limite de 25 lignes de la norme 42

### ## p_redir.c - Gestion des Redirections

### ### token_to_redir_type

```c
t_redir_type token_to_redir_type(t_token_type token_type)

{

if (token_type == REDIR_IN)

return (REDIR_INPUT);

else if (token_type == REDIR_OUT)

return (REDIR_OUTPUT);

else if (token_type == REDIR_APPEND)

return (REDIR_APPEND_OUT);

else if (token_type == HEREDOC)

return (REDIR_HEREDOC_OUT);

return (REDIR_INPUT); *// Par défaut*

}
```

**#### Analyse**:

- Convertit un type de token de redirection en type de redirection interne
- Permet une séparation claire entre les types utilisés par le lexer et ceux utilisés par le parser
- Inclut une valeur par défaut pour la sécurité

### ### parse_redirection

```c
t_redirect *parse_redirection(t_token ***tokens_ptr, t_token_type redir_type)

{

t_redirect *redirect;

*// Vérifier qu'il y a un token après la redirection*

if (!**tokens_ptr || (***tokens_ptr).type != WORD)

return (NULL); *// Erreur: redirection sans fichier/délimiteur*

*// Créer la structure de redirection*

redirect = (t_redirect *)malloc(sizeof(t_redirect));

if (!redirect)

return (NULL);

*// Initialiser la redirection*

redirect->type = token_to_redir_type(redir_type);

redirect->file_or_delimiter = (***tokens_ptr).value;

redirect->next = NULL;

*// Avancer au token suivant*

(*tokens_ptr)++;

return (redirect);

}
```

**#### Analyse**:

- Parse une redirection spécifique
- Vérifie qu'il y a bien un token WORD après l'opérateur de redirection
- Crée et initialise la structure de redirection
- Avance le pointeur de token
- Retourne NULL en cas d'erreur (par ex. si la redirection n'est pas suivie d'un nom de fichier)

### ## p_test.c - Fonctions d'Affichage

### ### print_redir_type

```c
static *void* print_redir_type(t_redir_type type)

{

if (type == REDIR_INPUT)

printf("<");

else if (type == REDIR_OUTPUT)

printf(">");

else if (type == REDIR_APPEND_OUT)

printf(">>");

else if (type == REDIR_HEREDOC_OUT)

printf("<<");

}
```

#### **Analyse**:

- Fonction utilitaire pour l'affichage des types de redirection
- Convertit le type interne en symbole shell correspondant
- Utilisée uniquement par les fonctions de débogage

### ### print_redirects

```c
static *void* print_redirects(t_redirect *redirect)

{

while (redirect)

{

printf(" ");

print_redir_type(redirect->type);

printf(" %s", redirect->file_or_delimiter);

redirect = redirect->next;

}

}
```

**#### Analyse**:

- Affiche une liste chaînée de redirections
- Format: `<espace><symbole><espace><fichier/délimiteur>`
- Parcourt récursivement toutes les redirections de la liste chaînée

### ###  print_simple_cmd

```c
static *void* print_simple_cmd(t_simple_cmd *cmd)

{

*int* i;

if (!cmd)

return;

*// Afficher les arguments*

for (i = 0; i < cmd->arg_count; i++)

{

printf("%s", cmd->args[i]);

if (i < cmd->arg_count - 1)

printf(" ");

}

*// Afficher les redirections*

if (cmd->redirects)

print_redirects(cmd->redirects);

}
```

**#### Analyse**:

- Affiche une commande simple avec:
    1. Tous ses arguments séparés par des espaces
    2. Toutes ses redirections
- Gère le cas où la commande est NULL
- Format de sortie propre et lisible

### ### print_command

*```c
void* print_command(t_command *cmd)

{

*int* i;

if (!cmd)

{

printf("Command is NULL\n");

return;

}

printf("Command with %d parts:\n", cmd->cmd_count);

for (i = 0; i < cmd->cmd_count; i++)

{

printf("  %d: ", i + 1);

print_simple_cmd(cmd->commands[i]);

if (i < cmd->cmd_count - 1)

printf(" | ");

printf("\n");

}

}
```

**#### Analyse**:

- Fonction principale d'affichage qui montre la structure complète d'une commande
- Formate la sortie sous forme d'un pipeline numéroté
- Utilise `print_simple_cmd` pour afficher chaque commande individuelle
- Affiche des pipes entre les commandes pour représenter le pipeline

### ## u_parse.c - Fonctions de Libération Mémoire

### ### free_redirects

```c
static *void* free_redirects(t_redirect *redirect)

{

t_redirect *next;

while (redirect)

{

next = redirect->next;

*// Ne pas libérer file_or_delimiter car il pointe vers*

*// la valeur d'un token qui sera libéré ailleurs*

free(redirect);

redirect = next;

}

}
```

**#### Analyse**:

- Libère une liste chaînée de redirections
- Conserve le pointeur vers le prochain élément avant de libérer l'élément courant
- Ne libère pas `file_or_delimiter` car il s'agit d'un pointeur vers une chaîne qui appartient à un token

### ### free_simple_cmd

```c
static *void* free_simple_cmd(t_simple_cmd *cmd)

{

if (!cmd)

return;

*// Libérer les arguments*

if (cmd->args)

{

*// Ne pas libérer les strings individuelles car elles*

*// pointent vers les valeurs des tokens*

free(cmd->args);

}

*// Libérer les redirections*

free_redirects(cmd->redirects);

free(cmd);

}
```

**#### Analyse**:

- Libère une commande simple et ses ressources
- Ne libère pas les chaînes individuelles des arguments car elles appartiennent aux tokens
- Appelle `free_redirects` pour libérer les redirections associées
- Gère le cas où cmd est NULL ou cmd->args est NULL

### ### free_command

*```c
void* free_command(t_command *cmd)

{

*int* i;

if (!cmd)

return;

if (cmd->commands)

{

for (i = 0; i < cmd->cmd_count; i++)

free_simple_cmd(cmd->commands[i]);

free(cmd->commands);

}

free(cmd);

}
```

**#### Analyse**:

- Libère une structure de commande complète
- Libère chaque commande simple en appelant `free_simple_cmd`
- Libère le tableau de commandes
- Libère la structure de commande elle-même
- Gère le cas où cmd est NULL ou cmd->commands est NULL

## **## Cas d'Utilisation**

### ### Exemple 1: Commande Simple

echo hello

1. **Tokens**:
    - ```bash
    `WORD("echo")`, `WORD("hello")`, `END_OF_INPUT` 
    ```
2. **Structure résultante**:
    - Une commande avec un tableau args: ["echo", "hello"]

### ### Exemple 2: Pipeline

```ls -la | grep .c | wc -l```

1. **Tokens**:
    - ```bash
    `WORD("ls")`, `WORD("-la")`, `PIPE`, `WORD("grep")`, `WORD(".c")`, `PIPE`, `WORD("wc")`, `WORD("-l")`, `END_OF_INPUT`
    ```
2. **Structure résultante**:
    - Trois commandes:
        - cmd[0]: args = ["ls", "-la"]
        - cmd[1]: args = ["grep", ".c"]
        - cmd[2]: args = ["wc", "-l"]

### ### Exemple 3: Redirections

```cat < input.txt > output.txt```

1. **Tokens**:
    - ```bash
    `WORD("cat")`, `REDIR_IN`, `WORD("input.txt")`, `REDIR_OUT`, `WORD("output.txt")`, `END_OF_INPUT` 
    ```
2. **Structure résultante**:
    - Une commande:
        - args = ["cat"]
        - redirects:
            - {type: REDIR_INPUT, file: "input.txt", next: {...}}
            - {type: REDIR_OUTPUT, file: "output.txt", next: NULL}

## **## Gestion des Erreurs**

Le parser implémente plusieurs mécanismes de gestion d'erreurs:

1. **Vérification des allocations mémoire**:

```
    
    cmd = (t_command *)malloc(sizeof(t_command));
    
    if (!cmd)
    
    return (NULL);
    ```
    
2. **Validation des tokens**:

```
    
    if (!**tokens_ptr || (***tokens_ptr).type != WORD)
    
    return (NULL); *// Erreur: redirection sans fichier/délimiteur
    ```*
    
3. **Libération de mémoire en cas d'erreur**:

```
    
    if (!cmd->commands[i])
    
    {
    
    free_command(cmd);
    
    return (NULL);
    
    }
    ```
    
4. **Gestion du token END_OF_INPUT**:
    
    
    ```
    if (**tokens_ptr && (***tokens_ptr).type == END_OF_INPUT)
    
    (*tokens_ptr)++;
    ```
    

## 

## **## Conclusion**

Le parser de Minishell est un système robuste et modulaire qui transforme efficacement une série de tokens en une structure de commande hiérarchique. Sa conception permet de gérer correctement les commandes simples, les pipelines et différents types de redirections.

Les points forts du parser incluent:

- Structure de données claires et bien définies
- Séparation logique des responsabilités
- Gestion rigoureuse des erreurs et de la mémoire
- Respect strict de la norme 42
- Code lisible et bien documenté
