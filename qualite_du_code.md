# Qualité du code

Avant de plonger dans le **comment** écrire du bon code, définissons ce qu’on entend par bon code. Ces qualités se renforcent parfois mutuellement (lisibilité + cohésion = maintenabilité), mais s’opposent parfois (un faible couplage peut nuire à la lisibilité). Dans tous les cas un bon codebase est…

## Lisible

Le code est lu **bien plus souvent** qu’il n’est écrit. Un codebase souhaitable peut être compris par quelqu’un qui ne l’a pas écrit, sans avoir besoin de l’auteur dans la pièce. L’intention de chaque morceau de code est apparente — on ne devrait pas avoir à reverse-engineer *ce que* ça fait avant de pouvoir penser à *le modifier*.

Concept lié: la discoverabilité. Un nouveau membre de l’équipe peut **trouver les choses**. Si on doit changer la façon dont les ennemis spawnent, on peut localiser le code pertinent sans grep-er des magic strings ou demander à un collègue. La structure du projet, le nommage et l’organisation nous guident au bon endroit.

Concept lié: la prédictibilité — soyez ennuyeux ! Le code fait **ce qu’il a l’air de faire**. Pas d’effets de bord cachés — appeler `GetHealth()` ne modifie pas secrètement l’état. Pas d’action à distance — changer une valeur dans le fichier A ne casse pas silencieusement un comportement dans le fichier Z. Le principe de moindre surprise: chaque fonction, classe et système se comporte comme son nom et sa signature le suggèrent.

Aussi: la consistance (pas seulement dans les conventions d’écriture). Le codebase suit des **conventions uniformes**. Les problèmes similaires sont résolus de façon similaire. Si les events utilisent des callbacks dans un système, ils n’utilisent pas du polling dans un autre sans raison. Un développeur qui a vu une partie du codebase peut faire des suppositions correctes sur le reste.

## Maintenable

Le codebase peut être **modifié dans le temps** sans effort disproportionné. Fixer un bug n’en introduit pas deux autres. Ajouter une feature ne nécessite pas de réécrire un système. Le coût du changement reste à peu près constant à mesure que le projet grandit, au lieu d’accélérer exponentiellement.

## Montre un Faible Couplage

Les systèmes **dépendent les uns des autres le moins possible**. Le système audio n’a pas besoin de connaître l’inventaire. L’UI ne va pas fouiller dans le moteur physique. Quand on modifie un module, le rayon d’impact est contenu — on ne déclenche pas une cascade de changements dans des fichiers sans rapport.

Effet secondaire: la testabilité ! On peut **vérifier qu’un morceau de code fonctionne** en isolation. Les systèmes peuvent être exercés indépendamment du reste du jeu. Si tester quelque chose nécessite de démarrer tout le moteur, charger un niveau et marcher manuellement avec un personnage jusqu’à un trigger — c’est un signe que le code est trop enchevêtré.

## Modulaire

Le codebase est composé de **pièces discrètes et remplaçables**. On peut changer l’algorithme de pathfinding sans réécrire l’IA. On peut changer le format de sérialisation sans toucher au gameplay. Les frontières entre modules sont explicites — pas juste “conceptuelles” mais appliquées par des interfaces ou des APIs claires.

Corollaire: définir les frontières en fonction de la cohésion: les choses qui vont ensemble **vivent ensemble**. Toute la logique d’un comportement est au même endroit, pas dispersée dans 12 fichiers. Une classe ou un module a un objectif unique et clair. On n’a pas besoin d’ouvrir 6 fichiers pour comprendre une feature. Ça veut aussi dire que les dossiers sont groupés par features, pas par types d’assets !

## Scalable

Le codebase gère **la croissance du contenu et du nombre de features** avec grâce. Ajouter le 50ème type d’ennemi ne devrait pas être plus dur qu’ajouter le 5ème. Ajouter une nouvelle arme ne devrait pas nécessiter de modifier chaque arme existante. L’architecture s’adapte à *plus de la même chose* sans changements structurels. Ça devrait devenir plus facile d’ajouter des features au fur et à mesure, pas l’inverse.

## Debuggable

Quand quelque chose plante, on peut **trouver pourquoi**. L’état est observable. Les erreurs sont remontées, pas avalées. Le chemin du symptôme à la cause est court. On n’a pas besoin d’attacher un debugger et de stepper à travers 40 call frames pour comprendre un crash — les logs, la structure et le nommage nous aident à circonscrire le problème.

## Supprimable

Le code peut être **supprimé en toute sécurité**. Les systèmes morts peuvent être coupés sans crainte de dépendances invisibles. Les features peuvent être désactivées ou extraites proprement. C’est l’inverse souvent oublié de l’extensibilité — un bon codebase est facile à réduire, pas seulement facile à agrandir.