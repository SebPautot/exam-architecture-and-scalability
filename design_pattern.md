# Design Patterns & Principes

Comment atteindre concrètement un codebase lisible, maintenable, à faible couplage et haute cohésion ? Grâce aux principes et patterns — des solutions récurrentes à des problèmes récurrents.

## Principes

### YAGNI — “You Aren’t Gonna Need It”

Ne construisez rien tant que vous n’en avez pas réellement besoin. Pas “on en aura peut-être besoin”, pas “on en aura probablement besoin” — *on en a besoin maintenant*.

**Le problème résolu**: l’abstraction prématurée, le gold plating, la généralité spéculative. Les développeurs construisent des systèmes de plugins pour des jeux qui ne shipperont qu’une seule configuration. Ils écrivent des couches de sérialisation qui gèrent des formats que personne n’utilisera jamais.

**Exemple**: vous écrivez un spawner d’ennemis. Vous *pourriez* le faire supporter des tables de probabilités pondérées, des courbes selon l’heure de la journée, et des overrides par biome. Mais le doc de design dit “spawn 3 gobelins.” Codez pour 3 gobelins. Quand le design change, *là* on généralise.

**Le piège**: YAGNI ne veut pas dire “écrivez du mauvais code.” Ça veut dire ne résolvez pas des problèmes que vous n’avez pas ENCORE. Le code pour 3 gobelins devrait quand même être clean — juste pas abstrait.

### KISS — “Keep It Simple, Stupid”

La solution la plus simple qui fonctionne est généralement la meilleure. La complexité est un coût, pas une feature.

**Le problème résolu**: l’over-engineering. Une hiérarchie de classes de 200 lignes pour représenter quelque chose qu’un dictionnaire pourrait gérer. Une architecture event-driven, message-passing, pub-sub pour un jeu où 3 scripts ont besoin de se parler.

**Test**: est-ce qu’un nouveau membre de l’équipe peut comprendre ce code en moins de 5 minutes ? Si non, est-ce que la complexité est *justifiée* par un vrai besoin, ou est-ce juste du code clever ?

### DRY — “Don’t Repeat Yourself”

Chaque morceau de connaissance devrait avoir une représentation unique et non ambiguë dans le système.

**Le problème résolu**: du code copié-collé où un fix de bug à un endroit ne se propage pas aux 5 autres copies. Une formule de dégâts qui existe dans le système de combat, le tooltip de l’UI, et l’évaluation de l’IA — toutes légèrement différentes.

**La nuance**: DRY concerne la *duplication de connaissance*, pas la *duplication de code*. Deux fonctions qui se ressemblent mais représentent des concepts différents (calcul des dégâts du joueur vs. calcul des dégâts environnementaux) peuvent *correctement* rester séparées, même si la formule est la même aujourd’hui. Elles changent pour des raisons différentes.

**Le danger du DRY sur-appliqué**: forcer deux choses sans rapport dans une abstraction partagée juste parce qu’elles se ressemblent en ce moment. Quand elles divergent plus tard, le code partagé devient un enchevêtrement de conditionnels. On appelle parfois ça la **“mauvaise abstraction”** — c’est pire que la duplication.

### Separation of Concerns

Chaque module, classe ou fonction devrait être responsable d’**un seul aspect** du comportement du programme.

**Le problème résolu**: le God Object. Un `GameManager` qui gère le spawning, le scoring, l’UI, l’audio, la sauvegarde et le réseau. Une classe `Player` qui contient le mouvement, l’input, la santé, l’inventaire, l’animation et l’audio en 3 000 lignes.

**Comment repérer une violation**: une classe où des changements sans rapport entrent constamment en collision. Si fixer la lecture audio nécessite d’éditer le même fichier que fixer le stacking de l’inventaire — ces préoccupations ne sont pas séparées.

**Le danger de la sur-application**: quand il n’y a pas de vrai problème de god class et que la modularisation est faite pour le principe. Une god class peut être un moyen facile de prototyper rapidement quelque chose avant de refactorer plus tard.

### Single Responsibility Principle (SRP)

Une classe devrait avoir **une seule raison de changer**.

**Le problème résolu**: une classe `Player` qui change quand les bindings d’input changent, quand la formule de santé change, quand les sets d’animation changent, et quand le format de sauvegarde change. Quatre raisons sans rapport d’éditer le même fichier — quatre fois plus de surface de merge conflict.

**Version game dev**: `PlayerMovement`, `PlayerHealth`, `PlayerInventory` comme composants séparés. Chacun change pour sa propre raison. Chacun peut être testé, itéré, et assigné à différents développeurs indépendamment.

### Principe de Moindre Surprise

Le code devrait se comporter comme son nom et sa signature le suggèrent. Pas d’effets de bord cachés.

**Le problème résolu**: une fonction appelée `GetScore()` qui reset aussi le multiplicateur de combo. Une méthode appelée `Initialize()` qui détruit et recrée silencieusement l’objet. Du code qui ment sur ce qu’il fait.

**Règle empirique**: si quelqu’un lit la signature de la fonction sans lire le body, il devrait avoir des attentes correctes sur ce qu’elle fait et ne fait pas.

### Open/Closed Principle

Les systèmes devraient être **ouverts à l’extension, fermés à la modification**. On devrait pouvoir ajouter un nouveau comportement sans éditer le code existant.

**Le problème résolu**: ajouter un nouveau type d’ennemi nécessite d’éditer un `switch` dans 14 fichiers. Ajouter une nouvelle arme implique de modifier le `CombatManager`. Chaque extension est une modification — et chaque modification risque de casser ce qui fonctionne déjà.

**Exemple game dev**: un système de dégâts qui traite tout ce qui implémente une interface `IDamageable`. Ajouter un nouvel objet destructible (tonneau, PNJ, mur destructible) est une pure addition — on implémente l’interface, et le système existant le gère sans changement.

### Dependency Inversion Principle

Les modules de haut niveau ne devraient pas dépendre des modules de bas niveau. Les deux devraient dépendre d’**abstractions**.

**Le problème résolu**: votre système de quêtes appelle directement votre classe `MySQLDatabase`. Maintenant vous ne pouvez pas tester les quêtes sans base de données. Vous ne pouvez pas changer de backend de stockage. La logique de haut niveau (progression des quêtes) est enchaînée à un détail de bas niveau (technologie de base de données).

**Version game dev**: le système de quêtes dépend d’une interface `ISaveStorage`. L’implémentation concrète (fichier, base de données, cloud) est injectée. Pendant les tests, on injecte un mock. Pendant le développement, on injecte un fichier local rapide. En production, on injecte le vrai backend.

Encore une fois, ne sur-appliquez pas: si vous êtes sûr à 99% que votre système va utiliser du SQL, foncez, ajouter une couche de dependency inversion contredit YAGNI et la lisibilité, qui sont sans doute plus importants

## Patterns

### Composition Over Inheritance

**Préférez** construire des objets en combinant des composants petits et focalisés plutôt qu’en étendant des hiérarchies de classes profondes.

**Pourquoi l’héritage échoue à l’échelle**:

```
Entity
├── Character
│   ├── Player
│   │   ├── LocalPlayer
│   │   └── RemotePlayer
│   └── NPC
│       ├── FriendlyNPC
│       └── EnemyNPC
│           ├── MeleeEnemy
│           └── RangedEnemy
│               └── FlyingRangedEnemy
```

Maintenant vous avez besoin d’un `FlyingMeleeEnemy`. Où est-ce qu’il va ? Un `FriendlyNPCThatCanBecomeHostile` ? La hiérarchie ne supporte pas les combinaisons. On finit avec de l’héritage multiple, des problèmes de diamant, ou du copier-coller de code entre les branches.

**Approche par composition**:

```
Entity + MovementComponent (walk, fly, swim)
       + CombatComponent (melee, ranged, none)
       + AIComponent (hostile, friendly, neutral)
       + HealthComponent
```

`FlyingMeleeEnemy` = Entity + FlyMovement + MeleeCombat + HostileAI + Health. Pas de nouvelle classe nécessaire. Pas de hiérarchie à restructurer. Les composants se mixent et se matchent librement.

**Règle empirique**: utilisez l’héritage pour les relations “est-un” qui ne changeront *jamais*. Utilisez la composition pour les relations “a-un”: tout ce qui doit être combiné, reconfiguré ou évoluer dans le temps. En game dev, c’est quasiment tout.

### Code as Documentation

Le code lui-même devrait communiquer l’intention. Les commentaires expliquent le *pourquoi*, pas le *quoi*.

**Mauvais**:

```cpp
// Increment i by 1
i++;

// Check if the player is dead
if (hp <= 0) { ... }
```

Ces commentaires disent ce que le code dit déjà. C’est du bruit.

**Bon**:

```cpp
// Off-by-one: the server counts from 1, not 0
i++;

// <= 0 instead of == 0 because damage can overshoot in a single frame
if (hp <= 0) { ... }
```

Ceux-ci expliquent *pourquoi* le code est tel qu’il est — du contexte que le code ne peut pas exprimer seul.

**Comment y parvenir**:

- Des noms significatifs: `playerSpeed` pas `ps`. `isEligibleForRevive()` pas `check()`.
- Des petites fonctions avec des noms descriptifs: le nom de la fonction *est* le commentaire.
- Éviter les magic numbers: `MAX_INVENTORY_SLOTS` pas `36`.
- Si vous avez besoin d’un commentaire d’un paragraphe pour expliquer une fonction, la fonction est probablement trop complexe.

### Fail Fast

Quand quelque chose ne va pas, **détectez-le immédiatement** et signalez-le clairement. Ne continuez pas silencieusement avec un état corrompu.

**Le problème résolu**: une référence null qui ne crash pas, mais produit silencieusement un mauvais comportement pendant 20 minutes jusqu’à ce que quelque chose *d’autre* crash loin de l’erreur originale. Un fichier de sauvegarde qui charge avec des données manquantes, et le jeu tourne avec des valeurs par défaut jusqu’à ce qu’un joueur remarque que son inventaire a disparu.

**Exemples**:

- Assert les préconditions à l’entrée de la fonction: si l’argument est invalide, crashez maintenant avec un message clair, pas plus tard avec un message mystérieux.
- Validez les données au chargement, pas à l’utilisation.
- Ne retournez pas `null` en espérant que l’appelant vérifie — utilisez des types ou des exceptions qui rendent l’échec impossible à ignorer.

### Encapsulation / Information Hiding

Exposez l’**interface minimale nécessaire**. Gardez les détails internes privés.

**Le problème résolu**: la loi de Hyrum — si c’est public, quelqu’un va en dépendre. Une liste interne qui devait être un détail d’implémentation est accédée directement par 15 autres systèmes. Maintenant vous ne pouvez plus changer la structure de données sans tout casser.

**Exemple game dev**: un système de pathfinding expose `FindPath(from, to) → Path`. La représentation interne (navmesh, grille, waypoints) est cachée. Si vous passez de A* à du pathfinding hiérarchique, aucun code appelant ne change.

**Règle**: rendez tout privé par défaut. N’exposez les choses que quand il y a un consommateur concret qui a besoin d’un accès. Si vous rendez quelque chose public “au cas où” — c’est du YAGNI.

### Favorisez les Fonctions Pures

Quand c’est possible, écrivez des fonctions qui prennent un input, retournent un output, et **ne touchent à rien d’autre**. Pas de state global, pas d’effets de bord.

**Pourquoi c’est important**:

- Les fonctions pures sont trivialement testables — passez un input, vérifiez l’output. Pas de setup, pas de mocks.
- Elles sont parallélisables — pas de state mutable partagé.
- Elles sont prédictibles — le même input donne toujours le même output.

**Réalité du game dev**: on ne peut pas tout rendre pur (les jeux sont stateful par nature), mais on peut isoler la logique de l’état. Un calcul de dégâts peut être pur: `CalculateDamage(baseDamage, armor, resistances) → int`. La fonction qui *applique* les dégâts mute l’état, mais le *calcul* n’en a pas besoin.

### Programmation Défensive vs. Design by Contract

Deux philosophies opposées:

**Programmation défensive**: ne faites confiance à rien. Validez tous les inputs, gérez tous les edge cases, ajoutez des null checks partout. Sûr, mais produit du code volumineux plein de guards qui pourraient ne jamais se déclencher.

**Design by contract**: définissez explicitement les préconditions et postconditions. Si l’appelant viole le contrat, le comportement est *son* problème. Plus léger, mais requiert de la discipline et une documentation claire.

**Juste milieu pragmatique en game dev**:

- **Défensif aux frontières du système** (input réseau, chargement de fichiers, input utilisateur, APIs de plugins) — tout ce qui est externe peut être du garbage.
- **Basé sur le contrat en interne** — si votre propre code passe un null à une fonction qui attend un objet valide, c’est un bug dans l’appelant, pas un null check manquant dans l’appelé. Utilisez des asserts pour catcher les violations de contrat dans les builds de debug.

## Anti-Patterns à Surveiller

### Optimisation Prématurée

“On devrait utiliser un object pool ici pour la perf.” Est-ce que c’est vraiment lent ? Avez-vous profilé ? L’optimisation avant la mesure ajoute de la complexité pour des problèmes imaginaires. Faites que ça marche, faites que ça soit bien, *puis* faites que ça soit rapide — dans cet ordre.

### Code Stringly Typed

Utiliser des strings là où un enum, un type ou une constante devrait être utilisé. `SendMessage("PlayerDied")` — une typo devient un échec silencieux. `FindObjectByTag("Ennemy")` — bonne chance pour debugger ça en plein crunch à 2h du mat’.

### Primitive Obsession

Tout représenter avec des types basiques. La santé est un `int`, l’argent est un `int`, l’ID du joueur est un `int` — et inévitablement on passe l’ID du joueur à une fonction qui attend la santé. Un type `Health`, un type `Money` et un type `PlayerId` permettent au compilateur de catcher les erreurs pour vous.

```cpp
// do
struct Money {
  int value;
};
void compute(Money money);

// don't
void compute(int money);
```

### Boolean Blindness

`Spawn(true, false, true)` — qu’est-ce que ces booléens veulent dire ? Utilisez des enums ou des paramètres nommés: `Spawn(team: Team.Red, isBot: false, spawnImmediately: true)`.

## La Méta-Règle

Chaque principe ici est un **compromis**, pas un commandement. YAGNI dit ne construisez pas ce dont vous n’avez pas besoin — mais parfois on *a* besoin de prévoir le réseau ou les systèmes de sauvegarde. DRY dit ne vous répétez pas — mais parfois la duplication est plus simple qu’une mauvaise abstraction. Composition over inheritance est presque toujours juste — mais une hiérarchie simple à deux niveaux convient quand elle colle.

Le talent n’est pas de connaître les principes. C’est de savoir **quand les appliquer et quand les relâcher** — et ça vient avec l’expérience de construire des choses et de faire des erreurs.