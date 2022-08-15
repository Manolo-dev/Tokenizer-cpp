# Tokenizer

Le Tokenizer est un analyseur lexicale, il permet, comme Flex and Yacc par exemple, de tokenizer du code, c'est à dire transformer du code en liste de tokens. En l'occurence, contrairement à Flex and Yacc, la liste de token est hiérarchisée et chaque token est typé.

### Qu'est-ce que c'est quoi dis donc un token ?

Un token, litteralement, c'est un jeton... Bof bof comme définition... Repprenons. Un token c'est une chaîne de caractères qui, ensemble, ont une signification. En bon français, la chaîne de caractères qui forme un jeton est appelée Lexeme.

### Et à quoi ça sert ?

La tokenization, c'est la première étape de la compilation ou de l'interprétation de la plupart des langages informatiques. Prenons Python par exemple, l'ordinateur ne sait absolument pas quoi faire avec le ficher qu'on lui donne, il le découpe donc pour avoir chacun des mots du code et pouvoir comprendre ce qu'on lui demande.

---

## Exemple :

Du code python comme celui ci :

```python
def hello(name) :
    print("Hello", name, "!")
```

sera convertit en YAML (ou n'importe quel autre langage de stockage de données comme JSON par exemple) en :

```yaml
---
- {value: 'def', type: function.declaration}
- {value: 'hello', type: name.funciton.declaration}
- {value: '(', type: punctuation.begin}
- {value: 'name', type: parameter}
- {value: ')', type: punctuation.end}
- {value: ':', type: start.node}
- - {value: 'print', type: function}
  - {value: '(', type: punctuation.begin}
  - {value: '"Hello"', type: string}
  - {value: ',', type: separator}
  - {value: 'name', type: variable}
  - {value: ',', type: separator}
  - {value: '"!"', type: string}
  - {value: ')', type: punctuation.end}
```

Ici les tokens sont hiérarchisés et typés, c'est à dire que pour chaque nœud, une nouvelle liste de tokens est créée et pour chaque token de cette liste, un type lui est appliqué.

Le typage des tokens peut par exemple être utile pour créer un fichier de colorisation syntaxique en assignant une couleur à chaque type.

---

## Spécifications

| technologie                  |        outil |
|:---------------------------- |-------------:|
| Langage                      |          C++ |
| Version du langage           |           20 |
| Environnement                | Windows 7/10 |
| Librairie                    |              |

---

## Installation

---

## To do list

- [ ] Grammaire
- [ ] Classe Token
- [ ] Classe Node
- [ ] Main
- [ ] Gestion des erreurs
- [ ] Detection des noeuds dans le match

# Grammaire

Oui, il faut une grammaire à l'outil de grammaire ! Grammaception !
 c++

## Corps

Le corps se compose d'au moins deux parties, `variables`, qui contient des expressions RegExp, et les modules, dont `main`, seul module obligatoire.

- `variables`

- `main`

- `<modules>`

## Module

`main` est le seul module qui est appelé sans qu'on l'incluse manuellement.

Les `modules` traitent le code et s'occupe de la grosse part du travail, ils peuvent utiliser les variables définies dans le module, dans un module encore ouvert (variables locale) ou dans `variables`.

## Méthodes

- `include`, inclut un `module`.

- `match`, correspond à un `SI <token> correspond <expression> FAIRE`, assigne à l'**objet courant** le token trouvé et exécute le module donné (nommé ou non).

- `save`, assigne un type à l'**objet courant** et enregistre le token dans la liste des tokens.

- `if`, vérifie la condition donnée (liste de trois arguments, le premier est l'opérateur, le second et le troisième sont les valeurs à tester). Exemple: `if: ['==', ;a, ;b]`

- `begin`, crée un nœud et le débute.

- `end`, ferme le nœud. Si 1 est renvoyé, le noeud se ferme sans erreur, sinon, une erreur est renvoyée au noeud parent.

- `ignore`, ne fait pas avancer le curseur dans le texte.

- `var`, modifie les variables de la même manière que le module `variables`, la variable `_` représente le `token` trouvé.

- `error`, génère une erreur (équivalent au raise python)

- `print`, affiche le texte donné dans la console.

## Variables

Il y deux moyens d'utiliser les variables. Dans le cas d'une variable d'exemple appelée `var`, on peut faire :

- `;var`, est remplacé par la variable nommée `var`. À ne pas placer sans ancre, au risque d'une mauvaise interprétation. À placer de préférence entre parenthèses dans une expression plus longue.

- `str:n`, permet de supprimer n caractères à la chaîne str.

## Exemple

```yaml
variables:
  open: '\('
  close: '\)'
main:
  - match: ';open'
    save: 'open'
    begin: # Ceci est un module non nommé
    - match: ';close'
      save: 'close'
      end: 1
    - include: 'main'
  - match: '[^()]+' # pour éviter de prendre des parenthèses involontairement
    save: 'other'
  - match: ';close'
    error: 'il y a une parenthèse de fermeture en trop'
```

Cette grammaire fait de la parenthétisation simple, en simple, elle transforme ce code :

```
1 / (3 * (1 + 2))
```

en :

```yaml
---
- {value: '1 / ', type: 'other'}
- {value: '(', type: 'open'}
- - {value: '3 * ', type: 'other'}
  - {value: '(', type: 'open'}
  - - {value: '1 + 2', type: 'other'}
  - {value: ')', type: 'close'}
- {value: ')', type: 'close'}
```