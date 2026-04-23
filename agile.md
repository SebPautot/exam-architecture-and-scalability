# Agile

## Waterfall (cascade)

![alt text](../en/images/2_agile/image.png)

alt text

L’un des premiers modèles de développement logiciel. Décrit en 1956 mais nommé waterfall en 1976.

1. Analyse des besoins
2. Conception du système
3. Implémentation
4. Tests
5. Déploiement
6. Maintenance

Avantages:

- prévisibilité (apparente) pour les parties prenantes
- légalement requis par certaines industries
- fonctionne bien quand les exigences sont fixées
- pas de scope creep

Tombe en miettes quand:

- les exigences ne sont pas connues
- des edge cases de code et de design apparaissent

En pratique, tombe en miettes quasiment à chaque fois. C’était un standard mais est désormais déprécié. Même le département de la défense américain, qui l’utilisait comme standard officiel en 1985, le déconseille explicitement depuis 1994 en faveur de l’acquisition incrémentale de logiciels développés itérativement.

## Programmation agile

En 2001, 17 développeurs ont publié le *Manifeste pour le Développement Agile de Logiciels* qui énonçait leurs valeurs:

> Les individus et leurs interactions plutôt que les processus et les outilsUn logiciel fonctionnel plutôt qu’une documentation exhaustiveLa collaboration avec le client plutôt que la négociation contractuelleL’adaptation au changement plutôt que le suivi d’un plan
> 

ainsi que 12 principes. Ce qu’il faut retenir, c’est que l’Agile est une *philosophie* plutôt qu’un ensemble de directives. Il existe des implémentations de l’agile comme XP, SAFe, ou Scrum, mais ce sont des *méthodologies*.

En réalité, beaucoup de méthodologies soi-disant agiles sont en fait très éloignées de la philosophie originale

https://www.youtube.com/watch?v=a-BOSpxYJ9M&t=153s

TL;DR

- l’agile est devenu une industrie plutôt qu’une philosophie
- on ne peut pas vendre une philosophie, mais on peut vendre des outils, des rôles et des certifications
- la peur fait vendre
- le cool fait vendre

Martin Fowler, également co-auteur du manifeste, [partage le même point de vue](https://martinfowler.com/agile.html). Même sans participer au complexe industriel agile, les équipes peuvent tomber dans le cargo cult agile.

## Extreme Programming (XP)

![alt text](../en/images/2_agile/image-1.png)

alt text

Favorisé par la bulle dotcom, les ingénieurs logiciels avaient besoin d’une méthodologie supportant un time to market plus rapide.

XP a été conçu pour être réactif aux changements d’exigences client grâce à des cycles de développement itératifs courts.

Antérieur à l’Agile (années 1990 vs 2001) mais est considéré comme une méthodologie agile à cet égard.

Définit un calendrier approximatif pour chaque cycle et préconise un ensemble de pratiques (pair programming, tests unitaires, YAGNI, management horizontal, …).

## Scrum

![alt text](../en/images/2_agile/image-2.png)

alt text

https://scrumguides.org/docs/scrumguide/v2020/2020-Scrum-Guide-US.pdf#zoom=100

En gros un ensemble de pratiques pour rendre l’agile plus digeste pour les managers et les investisseurs en ajoutant ces rôles:

- product owner: décide quoi construire et dans quel ordre (possède le backlog)
- scrum master: pas un manager. Facilite les processus.
- équipe de dev: 3-9 personnes, auto-organisée, cross-fonctionnelle

ainsi que ces cérémonies pour chaque sprint (1-4 semaines):

1. sprint planning
2. daily scrum
3. sprint review
4. sprint retrospective
5. déploiement

le framework définit aussi des artefacts:

1. product goal
2. sprint goal
3. DoD (definition of done)

En théorie, c’est un processus léger, mais les critiques (comme Allen Holub et Martin Fowler) notent qu’en pratique, ça dérive souvent de la philosophie agile originale:

- usage massif de processus et outils prédéterminés plutôt que d’individus (Jira étant le pire offender)
- usage massif de dashboards de monitoring (contre la loi de Goodhart: quand une mesure devient un objectif, elle cesse d’être une bonne mesure, par ex. avec l’inflation des story points pour booster la vélocité)
- industrie complexe de certifications
- burndown chart comme outil de micromanagement
- meeting bloat
- cargo cult de doctrines, comme l’usage du “En tant que [utilisateur], je veux [chose], afin de [raison]”, qui est appliqué de force même quand c’est absurde: “En tant que développeur, je veux que le build ne crash pas, afin de pouvoir déployer”
- les éditeurs d’outils comme Atlassian profitent de la complexité

## NoEstimates

Pratique agile popularisée par Allen Holub qui observe les failles des implémentations agiles typiques et tente d’y remédier:

- les estimations sont toujours fausses, et pourtant on se plie en quatre pour les rendre justes
- le temps passé à estimer est du temps mieux investi à coder
- les story points sont de l’obfuscation de temps
- après plus de 20 stories dans notre backlog, les choses relèvent de la pure fantaisie
- philosophie Toyota: laisser les gens qui font le travail créer les processus
- des *projections* précises sont utiles et devraient être faites, mais pas sur le temps:
    - devrait-on tuer le projet ?
    - devrait-on ajouter plus de personnes ?
    - quelle sera la date de release ? (n’estimez pas, [comptez simplement](https://youtu.be/QVBlnCTu9Ms?si=3lchzNvBB1rUQ_Zu&t=1600))

Bon en théorie, populaire sur internet grâce à sa nature radicale, en pratique rarement utilisé.