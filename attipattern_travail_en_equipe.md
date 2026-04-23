# Antipatterns du travail en équipe

## Communication

### L’Architecte dans sa Tour d’Ivoire

Une personne conçoit tout le système en isolation, puis transmet les specs à l’équipe. Les développeurs deviennent des “pisseurs de code” — ils ne comprennent pas le design ni n’y adhèrent, donc ils l’implémentent mal ou le contournent. L’architecte ne touche pas au codebase, donc ses designs dérivent de la réalité.

### Silos de Connaissance

Une seule personne comprend la couche réseau. Une seule personne peut builder le projet. Une seule personne sait comment fonctionne le système de sauvegarde. Quand elle est malade, en vacances ou démissionne — l’équipe est paralysée. C’est un **bus factor de 1**.

### Le Manager Mouette

Apparaît occasionnellement, fait beaucoup de bruit, chie sur tout, puis s’envole. Aucune implication continue, aucun contexte, juste des critiques en passant qui démoralisent l’équipe.

### Le Stakeholder Absent

Le game designer / directeur créatif n’est jamais disponible pour les questions. Les développeurs devinent ce qui était prévu, construisent la mauvaise chose, puis se font dire de tout refaire. Les boucles de feedback passent d’heures à semaines.

### Des Meetings qui Devraient Être des Emails

Chaque décision nécessite de rassembler 8 personnes dans une salle. Rien n’est écrit. La même discussion a lieu la semaine suivante parce que personne ne se souvient de la conclusion.

## Processus

### Cargo Cult Agile

L’équipe fait des standups, des sprints et des rétros — mais rien ne change vraiment. Les standups sont des rapports de statut au lead. Les rétros ne produisent aucune action. Les sprints ont un scope fixe imposé par le management. C’est du waterfall avec du vocabulaire agile.

### La Culture du Héros

Un développeur reste jusqu’à 3h du matin pour “sauver” le sprint. Il est célébré. Ça incentivise le crunch, décourage le rythme soutenable, et cache des problèmes systémiques (pourquoi le sprint était-il en danger en premier lieu ?). Le héros devient un single point of failure, et les autres arrêtent de prendre leurs responsabilités parce que “il va le fix de toute façon.”

### Le Gold Plating

Les développeurs sur-polissent des systèmes que personne n’a demandés. Le moteur physique gère des edge cases qui n’arriveront jamais en gameplay. Le framework UI supporte des thèmes que le jeu n’utilisera jamais. Du perfectionnisme déguisé en professionnalisme — généralement le signe que les priorités ne sont pas claires ou qu’il n’y a pas de pression externe.

### La Feature Factory

L’équipe devient un tapis roulant de features. Ship une feature → prochaine feature → prochaine feature. Pas de temps pour la dette technique, pas de temps pour le refactoring, pas de rétrospective sur le fait que les features *fonctionnent* ou non. La vélocité a l’air super. Le codebase pourrit. Le jeu n’est pas fun mais a 47 systèmes.

### La Culture du LGTM

Les code reviews sont des tampons en caoutchouc. Chaque PR reçoit un “Looks Good To Me” en 30 secondes. Les reviews existent pour la conformité au processus, pas pour la qualité. Les bugs passent tranquillement, le savoir ne se propage pas, et l’étape de review devient du pur overhead sans aucune valeur.

## Technique

### Le Lava Flow

Du code mort, des expérimentations abandonnées et des systèmes à moitié terminés s’accumulent dans le codebase. Personne ne les supprime parce que “quelqu’un pourrait en avoir besoin” ou “j’ai peur d’y toucher.” Les nouveaux développeurs ne peuvent pas distinguer ce qui est actif de ce qui est fossilisé. Le codebase devient une fouille archéologique.

### Le Copy-Paste Inheritance

Au lieu de concevoir des systèmes partagés, les développeurs copient-collent du code d’autres features et l’adaptent. On se retrouve avec 6 systèmes d’inventaire légèrement différents. Un fix de bug dans l’un ne se propage pas aux autres. Personne ne se souvient lequel est le “vrai”.

### L’Abstraction Prématurée

Un développeur construit un système générique et extensible pour un problème qui a exactement une instance. Trois couches d’interfaces, de factories et de dependency injection — pour une barre de vie. De l’over-engineering qui fait qu’un changement simple nécessite de toucher à 8 fichiers.

### Le God Object

Une classe (souvent appelée `GameManager`) fait tout. Spawning, scoring, UI, audio, sauvegarde, réseau. C’est 5 000 lignes. Chaque feature la touche. Chaque merge crée un conflit. On ne peut pas la tester en isolation. Tout le monde a peur de la refactorer parce qu’elle *est* le jeu.

## Dynamiques Humaines

### La Brigade du Bikeshed

Des débats intenses de 45 minutes sur les conventions de nommage, le formatage du code ou la structure des dossiers — pendant que le pathfinding cassé a droit à un “ouais, on fixera plus tard” de 2 minutes. Les équipes dépensent une énergie proportionnelle à la *facilité* d’avoir une opinion sur un sujet, pas à son *importance*.

### Le Senior Intouchable

Le code d’un développeur expérimenté n’est jamais questionné. Ses PRs ne sont pas reviewées (“il sait ce qu’il fait”). Ses décisions architecturales ne sont pas challengées. Avec le temps, le codebase reflète les préférences et les angles morts d’une seule personne. Les juniors arrêtent de progresser parce qu’ils ne voient jamais d’alternatives.

### La Dilution de Responsabilité

“Quelqu’un devrait fixer la pipeline de build.” Tout le monde est d’accord. Personne ne le fait. La tâche appartient à *l’équipe*, ce qui veut dire qu’elle n’appartient à *personne*. Sans ownership explicite, les problèmes partagés sont des problèmes orphelins.

### Le Resume-Driven Development

Un développeur pousse une techno parce que ça fera bien sur son CV, pas parce que ça résout les problèmes du projet. “Réécrivons l’UI dans un framework ECS custom” — le jeu a 3 menus. Le projet sert la carrière du développeur au lieu de servir le jeu.

### L’Ownership Passif-Agressif

“Très bien, fais comme tu veux.” Le développeur implémente la décision de l’équipe mais sans conviction, en la sabotant subtilement pour prouver que son approche était meilleure. Quand ça échoue, il dit “je vous l’avais dit.” Ça empoisonne la confiance et rend la prise de décision collaborative dangereuse.