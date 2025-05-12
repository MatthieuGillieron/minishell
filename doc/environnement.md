# 🌍 Minishell – Gestion de l'environnement

## 📝 Pourquoi une copie de l'environnement ?

Dans le projet Minishell, **on n'a droit qu'à une seule variable globale**.

On ne peut pas directement utiliser la variable `environ` ou `envp` partout, ni les modifier globalement.

✅ **Solution** : créer une **copie indépendante de l'environnement** → `env_copy`

Cela permet :

- De manipuler un tableau dynamique et modifiable
- De respecter la règle d'UNE SEULE variable globale
- De passer explicitement l'environnement à toutes les fonctions
- D'éviter de modifier l'environnement système

---

## 🏗️ Fonction `copy_env`

**But** : Dupliquer le tableau `envp` en un nouveau tableau dynamique.

**Étapes de fonctionnement** :

1. **Compter** le nombre de variables dans `envp`
2. **Allouer** un tableau de pointeurs de taille `count + 1` (pour `NULL`)
3. **Dupliquer chaque string** avec `ft_strdup`
4. Si un `malloc` échoue :
   - Libérer toutes les chaînes déjà allouées
   - Libérer le tableau
   - Retourner `NULL`

```c
char **copy_env(char **envp);

Exemple de contenu copié :
env_copy[0] = "PATH=/usr/bin:/bin"
env_copy[1] = "HOME=/home/user"
env_copy[2] = NULL