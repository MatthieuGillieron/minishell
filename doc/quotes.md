# 📝 Documentation – Gestion des Guillemets dans Minishell

## 📌 Introduction

La gestion des guillemets est une fonctionnalité essentielle d'un shell Unix. Dans le cadre du projet Minishell, nous devons implémenter deux types de guillemets avec des comportements distincts, conformément aux exigences du sujet 42.

---

## 🔄 Types de guillemets supportés

| Symbole | Nom | Description | Comportement |
|---------|-----|-------------|-------------|
| `'` | Guillemet simple | Empêche l'interprétation de tous les caractères spéciaux | Tout est pris littéralement, y compris `$` |
| `"` | Guillemet double | Empêche l'interprétation des caractères spéciaux sauf `$` | Les variables d'environnement sont expandées |

---

## 🧠 Architecture du code

Notre implémentation est divisée en plusieurs fichiers pour respecter la norme 42 :

- `quotes.c` : Gère la tokenisation des chaînes entre guillemets
- `expand.c` : Gère l'expansion des variables d'environnement
- `expand2.c` : Contient des fonctions auxiliaires pour l'expansion
- `p_expand.c` : Traite les tokens pour l'expansion des variables

### Fonctions principales

1. **`tokenize_squote`** : Tokenise une chaîne entre guillemets simples
   ```c
   t_token *tokenize_squote(t_lexer *lexer);
   ```

2. **`tokenize_dquote`** : Tokenise une chaîne entre guillemets doubles avec gestion des caractères d'échappement
   ```c
   t_token *tokenize_dquote(t_lexer *lexer);
   ```

3. **`expand_variables`** : Expande les variables d'environnement dans une chaîne
   ```c
   char *expand_variables(char *str, t_env *env, t_status *status);
   ```

4. **`process_dollar`** : Traite un caractère $ et expande la variable correspondante
   ```c
   int process_dollar(char *str, int i, char *result, int *j, t_env *env, t_status *status);
   ```

5. **`expand_tokens`** : Traite tous les tokens pour l'expansion
   ```c
   void expand_tokens(t_token **tokens, t_env *env, t_status *status);
   ```

---

## 🔧 Fonctionnement technique

### Tokenisation des guillemets simples

```c
t_token *tokenize_squote(t_lexer *lexer)
{
    size_t start = lexer->position;
    advance_lexer(lexer);  // Avancer après le guillemet ouvrant
    
    while (lexer->current_char && lexer->current_char != '\'')
        advance_lexer(lexer);
    
    if (lexer->current_char != '\'')
        return (NULL);  // Guillemet non fermé
    
    advance_lexer(lexer);  // Avancer après le guillemet fermant
    
    char *value = ft_substr(lexer->input, start + 1, lexer->position - start - 2);
    return create_token(SQUOTE, value, start);
}
```

### Tokenisation des guillemets doubles avec gestion des caractères d'échappement

```c
t_token *tokenize_dquote(t_lexer *lexer)
{
    size_t start = lexer->position;
    advance_lexer(lexer);  // Avancer après le guillemet ouvrant
    
    char *processed = malloc(ft_strlen(lexer->input) + 1);
    if (!processed)
        return (NULL);
    
    int p_index = 0;
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
    
    return create_token(DQUOTE, processed, start);
}
```

### Expansion des variables

```c
char *expand_variables(char *str, t_env *env, t_status *status)
{
    char *result = malloc(ft_strlen(str) * 4 + 1);  // Allocation généreuse
    if (!result)
        return (NULL);
    
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
            i = process_dollar(str, i, result, &j, env, status);
        else
            result[j++] = str[i++];
    }
    
    result[j] = '\0';
    return (result);
}
```

### Traitement des caractères $ et expansion des variables

```c
int process_dollar(char *str, int i, char *result, int *j, t_env *env, t_status *status)
{
    i++;  // Avancer après le $
    
    if (str[i] == '?')  // Cas spécial pour $?
    {
        expand_exit_code(result, j, status);
        return (i + 1);
    }
    
    char *var_name = extract_var_name(&str[i]);
    if (var_name)
    {
        expand_env_var(result, j, var_name, env);
        int name_len = ft_strlen(var_name);
        free(var_name);
        return (i + name_len);
    }
    
    // Si ce n'est pas une variable valide, on garde le $ tel quel
    result[(*j)++] = '$';
    return (i);
}
```

---

## 🚩 Gestion des erreurs

Chaque fonction de tokenisation vérifie :
- Si le guillemet est correctement fermé
- Si l'allocation mémoire a réussi

En cas d'erreur :
- La fonction retourne `NULL`
- La commande n'est pas exécutée

---

## 📊 Exemples d'utilisation

```bash
# Guillemets simples - pas d'expansion
echo 'Hello $USER'
# Affiche: Hello $USER

# Guillemets doubles - avec expansion
echo "Hello $USER"
# Affiche: Hello username

# Guillemets doubles avec caractères d'échappement
echo "Hello \"World\""
# Affiche: Hello "World"

# Expansion de $?
echo "Exit status: $?"
# Affiche: Exit status: 0 (ou autre valeur selon le dernier code de sortie)

# Guillemets mixtes
echo "Path: '$PATH'"
# Affiche: Path: '/usr/local/bin:/usr/bin:/bin'

# Guillemets non fermés
echo "Hello
# Affiche une erreur
```

---

## 🔍 Points techniques importants

1. Les guillemets simples (`'`) empêchent toute interprétation, y compris les variables d'environnement.
2. Les guillemets doubles (`"`) permettent l'expansion des variables d'environnement.
3. Les caractères d'échappement (`\`) sont correctement traités dans les guillemets doubles.
4. La variable spéciale `$?` est expandée avec le code de sortie de la dernière commande.
5. Les guillemets non fermés sont détectés et génèrent une erreur.
6. L'expansion des variables se fait uniquement dans les guillemets doubles et les mots sans guillemets.
7. Les guillemets ne sont pas inclus dans la valeur du token.

---

## 🔄 Intégration avec le reste du code

L'expansion des variables est intégrée dans la boucle principale du shell :

```c
tokens = tokenize_input(line);
if (tokens)
{
    // Traiter les guillemets et expandre les variables
    expand_tokens(tokens, status->env, status);
    
    // Continuer le traitement normal
    cmd = parse_tokens(tokens);
    // ...
}
```

---

## 🧩 Schéma de fonctionnement

```
[Entrée utilisateur] --> [Lexer] --> [Tokens] --> [Expansion] --> [Parser] --> [Exécution]
   "echo $USER"          |           |             |              |            |
                         v           v             v              v            v
                      Détecte     DQUOTE:      Expande        Crée une     Exécute
                    les guillemets  "$USER"    en valeur     commande     la commande
                                               réelle       avec args
```

Ce schéma montre comment les guillemets sont traités à travers le pipeline de traitement du shell.

---

## 📚 Conformité avec le sujet 42

Notre implémentation respecte les exigences du sujet 42 :

✅ Gestion des guillemets simples (`'`) qui empêchent l'interprétation des métacaractères  
✅ Gestion des guillemets doubles (`"`) qui empêchent l'interprétation des métacaractères sauf `$`  
✅ Gestion des caractères d'échappement dans les guillemets doubles  
✅ Expansion des variables d'environnement (`$` suivi d'une séquence de caractères)  
✅ Expansion de la variable spéciale `$?` avec le code de sortie  
✅ Respect de la norme 42 (fonctions ≤ 25 lignes, etc.)