# 📝 Documentation – Pipes dans Minishell

## 📌 Introduction

Les pipes (`|`) sont un élément fondamental des shells Unix, permettant de connecter la sortie standard d'une commande à l'entrée standard d'une autre. Cette documentation explique comment les pipes sont implémentés dans Minishell.

---

## 🔄 Principe de fonctionnement

Un pipe crée un canal de communication unidirectionnel entre deux processus :
- Le processus A écrit dans l'extrémité d'écriture du pipe
- Le processus B lit depuis l'extrémité de lecture du pipe

```
Commande1 | Commande2 | Commande3
```

Dans cet exemple :
- La sortie de `Commande1` est connectée à l'entrée de `Commande2`
- La sortie de `Commande2` est connectée à l'entrée de `Commande3`

---

## 🧠 Architecture du code

L'implémentation des pipes dans Minishell est divisée en plusieurs fichiers :

- **e_pipe.c** : Fonctions principales pour créer et gérer les pipes
- **e_pipe2.c** : Fonctions pour attendre les processus enfants et restaurer les descripteurs
- **e_pipe3.c** : Fonction pour exécuter les commandes du pipeline

Cette séparation respecte la norme 42 (maximum 25 lignes par fonction et maximum 4 arguments par fonction) et permet une meilleure organisation du code.

Pour respecter la limite de 4 arguments par fonction, nous utilisons une structure `t_pipeline_data` qui regroupe les données liées au pipeline :

```c
typedef struct s_pipeline_data
{
    int     **pipes;
    pid_t   *pids;
    int     pipe_count;
}   t_pipeline_data;
```

---

## 🔧 Fonctions principales

### 1. `execute_pipeline` (e_pipe.c)

Fonction principale qui orchestre l'exécution d'un pipeline de commandes.

```c
void execute_pipeline(t_command *cmd, t_env **env, t_status *status)
{
    t_pipeline_data data;
    
    // 1. Calculer le nombre de pipes nécessaires (nombre de commandes - 1)
    data.pipe_count = cmd->cmd_count - 1;
    
    // 2. Créer les pipes
    data.pipes = create_pipes(data.pipe_count);
    if (!data.pipes)
    {
        status->exit_code = 1;
        return;
    }
    
    // 3. Allouer un tableau pour stocker les PIDs des processus enfants
    data.pids = malloc(sizeof(pid_t) * cmd->cmd_count);
    if (!data.pids)
    {
        free_pipes(data.pipes, data.pipe_count);
        status->exit_code = 1;
        return;
    }
    
    // 4. Exécuter les commandes du pipeline
    execute_pipeline_commands(cmd, env, status, &data);
}
```

### 2. `create_pipes` (e_pipe.c)

Crée un tableau de pipes pour connecter les commandes.

```c
static int **create_pipes(int count)
{
    int **pipes;
    int i;
    
    // Allouer un tableau de pointeurs vers des paires de descripteurs
    pipes = malloc(sizeof(int *) * count);
    if (!pipes)
        return (NULL);
    
    // Pour chaque connexion entre commandes, créer un pipe
    i = 0;
    while (i < count)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (!pipes[i])
        {
            // Libérer la mémoire déjà allouée en cas d'erreur
            while (--i >= 0)
                free(pipes[i]);
            free(pipes);
            return (NULL);
        }
        
        // Créer le pipe
        if (pipe(pipes[i]) == -1)
        {
            perror("minishell: pipe");
            while (i >= 0)
                free(pipes[i--]);
            free(pipes);
            return (NULL);
        }
        i++;
    }
    return (pipes);
}
```

### 3. `setup_pipes` (e_pipe.c)

Configure les redirections pour un processus dans un pipeline.

```c
void setup_pipes(int cmd_index, int pipe_count, int **pipes)
{
    // Premier processus : rediriger uniquement la sortie
    if (cmd_index == 0)
        dup2(pipes[0][1], STDOUT_FILENO);
    
    // Dernier processus : rediriger uniquement l'entrée
    else if (cmd_index == pipe_count)
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
    
    // Processus intermédiaires : rediriger entrée et sortie
    else
    {
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
        dup2(pipes[cmd_index][1], STDOUT_FILENO);
    }
    
    // Fermer tous les descripteurs de fichiers inutilisés
    close_all_pipes(pipes, pipe_count);
}
```

### 4. `close_all_pipes` (e_pipe.c)

Ferme tous les descripteurs de fichiers des pipes.

```c
void close_all_pipes(int **pipes, int count)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}
```

### 5. `wait_for_children` (e_pipe2.c)

Attend la fin de tous les processus enfants et récupère le code de sortie.

```c
void wait_for_children(pid_t *pids, int count, t_status *status)
{
    int i;
    int cmd_status;
    
    i = 0;
    while (i < count)
    {
        waitpid(pids[i], &cmd_status, 0);
        
        // Le statut du dernier processus devient le statut de sortie
        if (i == count - 1)
        {
            if (WIFEXITED(cmd_status))
                status->exit_code = WEXITSTATUS(cmd_status);
            else if (WIFSIGNALED(cmd_status))
                status->exit_code = 128 + WTERMSIG(cmd_status);
        }
        i++;
    }
}
```

### 6. `execute_child_process` (e_pipe2.c)

Exécute une commande dans un processus enfant du pipeline.

```c
void execute_child_process(t_simple_cmd *cmd_data, t_env **env, t_status *status)
{
    // Configurer les signaux pour le processus enfant
    handle_signals_child();
    
    // Appliquer les redirections si présentes
    if (cmd_data->redirects)
    {
        if (apply_redirections(cmd_data->redirects) == -1)
            exit(1);
    }
    
    // Exécuter la commande (builtin ou externe)
    if (check_builtin(cmd_data->args, env, status))
        exit(status->exit_code);
    execute_command(cmd_data->args, env, status);
    exit(status->exit_code);
}
```

### 7. `execute_pipeline_commands` (e_pipe3.c)

Crée les processus enfants et exécute les commandes du pipeline.

```c
void execute_pipeline_commands(t_command *cmd, t_env **env, t_status *status,
                            t_pipeline_data *data)
{
    int i;

    // Configurer les signaux pour le processus parent
    handle_signals_parent();
    
    // Créer un processus pour chaque commande
    i = 0;
    while (i < cmd->cmd_count)
    {
        data->pids[i] = fork();
        if (data->pids[i] == -1)
        {
            perror("minishell: fork");
            status->exit_code = 1;
            break;
        }
        else if (data->pids[i] == 0)
        {
            // Processus enfant
            setup_pipes(i, data->pipe_count, data->pipes);
            execute_child_process(cmd->commands[i], env, status);
        }
        i++;
    }
    
    // Fermer tous les pipes dans le processus parent
    close_all_pipes(data->pipes, data->pipe_count);
    
    // Attendre la fin de tous les processus enfants
    wait_for_children(data->pids, cmd->cmd_count, status);
}
```

---

## 🔍 Flux d'exécution d'un pipeline

Prenons l'exemple de la commande `ls -la | grep .c | wc -l` :

1. Le parser détecte 3 commandes séparées par des pipes et crée une structure `t_command` avec `cmd_count = 3`
2. `execute_pipeline` est appelée avec cette structure
3. 2 pipes sont créés (nombre de commandes - 1)
4. 3 processus enfants sont créés (un pour chaque commande)
5. Pour chaque processus :
   - Le premier (`ls -la`) : sa sortie standard est redirigée vers l'entrée du premier pipe
   - Le deuxième (`grep .c`) : son entrée standard est connectée à la sortie du premier pipe, et sa sortie est connectée à l'entrée du deuxième pipe
   - Le troisième (`wc -l`) : son entrée standard est connectée à la sortie du deuxième pipe
6. Tous les descripteurs de fichiers inutilisés sont fermés
7. Le processus parent attend la fin de tous les processus enfants
8. Le code de sortie du dernier processus devient le code de sortie du pipeline

---

## 🚩 Points importants

1. **Fermeture des descripteurs inutilisés** : Chaque processus doit fermer tous les descripteurs de fichiers qu'il n'utilise pas pour éviter les blocages.

2. **Gestion des redirections** : Si une commande dans le pipeline a des redirections (`>`, `<`, etc.), celles-ci sont appliquées après la configuration des pipes.

3. **Gestion des signaux** : Les signaux sont correctement gérés dans tous les processus du pipeline.

4. **Code de retour** : Le code de retour du pipeline est celui de la dernière commande.

5. **Builtins** : Les commandes internes (builtins) sont exécutées dans le processus enfant lorsqu'elles font partie d'un pipeline.

---

## 📊 Exemple d'utilisation

```bash
# Pipeline simple
ls -la | grep .c | wc -l

# Pipeline avec redirections
cat < input.txt | grep "pattern" > output.txt

# Pipeline avec commandes internes
echo "Hello" | grep "H" | wc -c
```

---

## 🔄 Intégration avec le reste du code

La fonction `execute_pipeline` est appelée par `execute_parsed_command` lorsque `cmd->cmd_count > 1` :

```c
void execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
    if (!cmd || !cmd->commands)
        return;
    
    if (cmd->cmd_count == 1)
    {
        execute_simple_cmd(cmd->commands[0], env, status);
    }
    else
    {
        execute_pipeline(cmd, env, status);
    }
}
```

Cette architecture permet une séparation claire entre l'exécution d'une commande simple et l'exécution d'un pipeline.

---

## 🧩 Schéma de fonctionnement

```
[Commande 1] --> pipe[0] --> [Commande 2] --> pipe[1] --> [Commande 3]
   |                |                |                |
   v                v                v                v
stdout --> pipe[0][1]    pipe[0][0] --> stdin    stdout --> pipe[1][1]    pipe[1][0] --> stdin
```

Ce schéma montre comment les descripteurs de fichiers sont connectés entre les commandes d'un pipeline.