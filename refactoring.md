# Refactoring

Le refactoring est un processus discipliné d’amélioration de la structure interne du code sans changer son comportement externe. Le but n’est pas d’avoir un code plus joli pour lui-même ; le but est de rendre les changements plus sûrs, de réduire le taux de défauts, et d’accélérer la livraison dans le temps.

# Anti-patterns

La plupart des refactors ratés ne viennent pas d’un manque de talent. Ils échouent parce que le risque n’est pas contrôlé. Ces anti-patterns sont fréquents dans les vraies équipes, surtout sous pression de deadline.

## Big bang rewrite

Un big bang rewrite promet un redémarrage propre : on met en pause les features, on reconstruit tout, puis on switch en one shot. Ça échoue généralement parce que l’équipe perd le feedback trop longtemps, les surprises d’intégration s’accumulent, et l’ancien système continue d’évoluer pendant que le nouveau est encore incomplet. Au moment où la réécriture est “prête”, les hypothèses sont obsolètes et la confiance est basse. Préférez un remplacement incrémental : livrer de petites tranches, garder le feedback de production vivant, et retirer progressivement l’ancien code.

## Refactoring sans tests

Changer la structure sans filet de sécurité comportemental, c’est de la chirurgie à l’aveugle. Même des développeurs expérimentés introduisent des régressions en déplaçant de la logique, en splitant des classes, ou en changeant des call graphs. Sans tests, les défauts apparaissent tard et loin du changement qui les a causés, ce qui rend le debug coûteux et fait s’effondrer la confiance dans le refactoring. Commencez par ajouter des characterization tests autour des comportements critiques, puis refactorez sous ce filet de sécurité.

## Mélanger changements de comportement et changements structurels

Quand une pull request combine “cleanup”, bug fixes, et nouvelles features, les reviewers ne peuvent plus distinguer ce qui est censé rester équivalent de ce qui change intentionnellement. Ça détruit la qualité de review et la sécurité de rollback. Gardez les commits de refactoring sans changement de comportement et séparés des commits de feature. La question en code review devrait être simple : “Est-ce que la structure s’est améliorée alors que le comportement est resté le même ?”

## Mauvaise abstraction

Ça arrive quand des équipes forcent plusieurs concepts derrière une seule abstraction juste parce qu’ils se ressemblent aujourd’hui. Avec le temps, des besoins divergents sont patchés avec des flags, des conditionnels, et des cas spéciaux jusqu’à ce que l’abstraction devienne plus difficile à gérer que la duplication. Un peu de duplication peut être sain quand les responsabilités évoluent encore. N’abstraire que lorsque les patterns de changement prouvent que les concepts bougent réellement ensemble.

## Code temporaire permanent

Les adapters, compatibility shims, migration flags, et bridge layers sont souvent nécessaires pendant des refactors. L’anti-pattern, c’est de les laisser pour toujours. Chaque couche temporaire qui survit ajoute de l’overhead mental et de la surface de panne. Si vous ajoutez du code temporaire, définissez immédiatement les conditions de suppression : quel milestone le retire, qui possède la suppression, et qu’est-ce qui prouve qu’on peut le supprimer en sécurité.

## Branche de refactor qui vit trop longtemps

Les branches de refactor long-lived dérivent de la réalité de la branche principale. Les merge conflicts grossissent, les hypothèses divergent, et l’intégration finale devient tellement douloureuse que les équipes soit fusionnent de manière dangereuse dans l’urgence, soit abandonnent le travail. Utilisez des increments trunk-based dès que possible : fusionner de petites étapes en continu derrière des flags, et garder chaque étape releasable.

## Refactorer tout, partout, en même temps

Les campagnes de cleanup global semblent productives mais diluent généralement le focus et augmentent le risque sans valeur immédiate. Refactorez là où la pression de changement est la plus forte : hotspots avec bugs fréquents, fort churn, merge conflicts, ou douleur de perf. Les refactors locaux et ciblés liés à de vrais problèmes de livraison donnent de bien meilleurs résultats que les cleanups esthétiques larges.

## Pas de plan de décommissionnement

Beaucoup de migrations construisent avec succès un nouveau chemin mais n’éteignent jamais complètement l’ancien. Résultat : double maintenance, comportement incohérent, et ownership flou. Un refactor n’est pas terminé quand le nouveau code marche ; il est terminé quand l’ancien code est supprimé, que les routes sont basculées, et que l’ownership opérationnel est simplifié.

# Techniques

## Strangler fig

https://martinfowler.com/bliki/StranglerFigApplication.html

Le pattern Strangler fig est une stratégie de remplacement incrémental pour les systèmes legacy. Au lieu de tout réécrire et de basculer en un moment risqué, on introduit une frontière devant le comportement existant et on migre une tranche verticale à la fois vers le nouveau code. L’ancien système continue de tourner pendant que le nouveau grandit autour de lui, exactement comme un figuier étrangleur qui pousse autour d’un arbre hôte jusqu’à sa disparition.

La clé est de migrer par use case, pas par couche technique. Les équipes échouent souvent quand elles essaient de migrer “tous les controllers”, puis “tous les services”, puis “tous les repositories” sans valeur de bout en bout. Une approche plus sûre : choisir un flow concret, l’implémenter dans le nouveau module, router uniquement ce flow via le nouveau chemin, et laisser tout le reste intact. Les flows en lecture seule sont souvent les meilleurs points de départ car ils portent moins de risque de cohérence des données.

Le contrôle opérationnel est ce qui rend cette technique puissante. Gardez un switch de routage, un feature flag, ou une règle de dispatcher pour pouvoir augmenter progressivement le trafic et rollback vite si le comportement diverge. Pendant la migration, faites tourner les anciens et nouveaux chemins en parallèle quand c’est possible, comparez les outputs, et surveillez latence / taux d’erreur. Ça transforme un changement d’architecture en rollout mesurable au lieu d’un saut de la foi.

Le plus gros piège est d’oublier le décommissionnement. Une migration n’est pas finie quand le nouveau chemin marche pour une requête ; elle est finie quand l’ancien chemin est supprimé, que l’ownership est clair, et que les adapters temporaires sont supprimés. Si les deux systèmes restent vivants indéfiniment, la complexité double et la migration perd l’essentiel de son bénéfice.

## Technique de Mikado

La technique Mikado est une méthode orientée dépendances pour les refactors enchevêtrés. Vous commencez par le changement voulu, vous l’essayez rapidement, et vous observez ce qui casse parce que des prérequis manquent. Au lieu de forcer sur une branche à moitié cassée, vous notez les bloqueurs, vous annulez l’essai, puis vous résolvez les bloqueurs dans le bon ordre, récursivement avec la technique Mikado, jusqu’à ce que le bloqueur du nœud de changement soit assez simple à modifier. Le résultat est un graphe d’étapes prérequises sûres qui ramène à votre objectif initial.

Cette méthode est utile quand des refactors “petits” explosent sans arrêt à cause d’un couplage caché. Par exemple, extraire de la logique d’une grosse classe peut révéler des hypothèses cachées dans la sérialisation, les bindings UI, les hooks de réplication, et les fixtures de test. Mikado aide à éviter les panic rewrites en transformant les surprises en nœuds explicites : chaque bloqueur devient une petite tâche qui peut être terminée indépendamment et validée.

## Expand and contract

Expand and contract (aussi appelé parallel change) est la manière la plus sûre de faire évoluer des contrats partagés comme les APIs, schémas de messages, et modèles de base de données. Dans la phase expand, vous ajoutez de la compatibilité pour accepter à la fois les anciens et nouveaux formats. Dans la phase migration, les consommateurs sont poussés à utiliser les nouveaux formats via la dépréciation des anciennes APIs, tout en gardant le support. Dans la phase contract, les anciens chemins de compatibilité sont supprimés une fois l’adoption terminée.

Good boy: ReactJS, qui fait exactement ça, en facilitant l’adoption des nouvelles versions. Presque tout le monde utilise la dernière version de React (v19) ou une version proche.

https://w3techs.com/technologies/history_details/js-react/all/y

Bad boy: Python 2 a été sorti en 2008 avec une fin de support en 2020 alors qu’il représentait 40% des usages.

https://hugovk.dev/pypi-tools/charts.html