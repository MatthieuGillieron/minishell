# 📝 Documentation – `builtin_exit` (Minishell)

## 📌 Objectif de la commande

La commande **`exit`** dans un shell permet de **quitter le shell en cours d'exécution**, en renvoyant un **code de sortie** au processus parent.

Dans le cadre de Minishell, le comportement doit **imiter Bash en mode sous-shell** (et non le shell principal du terminal).

✅ Cela signifie que **Minishell doit afficher `exit` avant de quitter**, et gérer les mêmes cas d'erreur que Bash lorsqu'il est exécuté en sous-shell.

---

## 🎯 Comportements attendus

| Entrée       | Affichage attendu                                               | Code de sortie |
|--------------|----------------------------------------------------------------|----------------|
| `exit`        | `exit`                                                         | `0`            |
| `exit 42`     | `exit`                                                         | `42`           |
| `exit abc`    | `exit` + `minishell: exit: abc: numeric argument required`     | `2`            |
| `exit 1 2`    | `exit` + `minishell: exit: too many arguments`                 | ne quitte pas  |

✅ **Le message `exit` doit TOUJOURS être affiché**, même si une erreur suit.

---

## 🧠 Points clés implémentation

- Si **aucun argument** → quitter avec code `0`
- Si **un argument numérique valide** → quitter avec ce code
- Si **argument non numérique** → afficher erreur et quitter avec code `2`
- Si **plus d'un argument** → afficher erreur `"too many arguments"` mais **NE PAS quitter**
- Afficher `"exit"` sur la **sortie standard** AVANT de quitter (ou afficher erreur)

---

## 🚩 Restrictions du sujet

✅ Pas d'utilisation de `fprintf` ou `dprintf`  
✅ Affichage sur **stderr** doit être fait via `ft_putstr_fd` / `ft_putendl_fd` ou équivalent  
✅ Pas de gestion d'options (pas `exit --help`, etc.)  
✅ Conforme au comportement de Bash en sous-shell

---

## 📚 Différence avec Bash principal

⚠️ **En Bash principal (terminal direct)** → `exit` ferme simplement le terminal sans afficher de message.

Mais dans Minishell, on doit **suivre le comportement d'un sous-shell** :

```bash
bash
bash$ exit abc
exit
bash: exit: abc: numeric argument required
