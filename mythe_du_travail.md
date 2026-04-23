# Mythes du travail

Objectif d’une équipe de devs:

- Avoir une équipe plus productive que la somme de ses parties
- Soutenir les projets sur le long terme
- Se concentrer sur la livraison plutôt que sur les méthodes de travail

Le mythe: plus de devs, plus de diplômes, plus de ressources = plus de vélocité

La vérité…

## Loi de Brooks

“Ajouter des personnes à un projet logiciel en retard le retarde encore plus” (Fred Brooks dans The Mythical Man-Month, 1975)

À retenir: le nombre de devs n’est pas inversement proportionnel à la vélocité

Causes:

- toutes les tâches ne sont pas divisibles
- overhead de communication
- temps d’onboarding des coéquipiers

Solutions:

- règle des deux pizzas: chaque équipe interne devrait être assez petite pour être nourrie avec deux pizzas
- modèle de l’équipe chirurgicale: un lead dev prend toutes les décisions importantes
- ajouter des gens tôt, pas tard

## Escalade de l’engagement

Schéma de prise de décision dans lequel des individus ou des groupes continuent d’investir dans un plan d’action choisi malgré des preuves croissantes que la décision est mauvaise ou que le projet a peu de chances de réussir.

Causes:

- wishful thinking: croyances basées sur ce qui serait plaisant à imaginer, plutôt que sur des preuves, la rationalité ou la réalité
- biais des coûts irrécupérables (sunk cost fallacy): les gens ont une plus grande tendance à poursuivre un effort une fois qu’un investissement en argent, en effort ou en temps a été fait

Solutions:

- “Si vous vous retrouvez dans un trou, arrêtez de creuser” (Bill Brock, 1983)
- définir un critère d’arrêt avant de commencer
- séparer le constructeur et l’évaluateur
- reformuler “devrait-on continuer X après avoir investi Y ?” en “si on partait de zéro, ferait-on X ?”
- changement de culture (normaliser le fait d’abandonner des features)

## Loi de Hofstadter

“Ça prend toujours plus de temps que prévu, même en tenant compte de la loi de Hofstadter.” (Douglas Hofstadter, 1999)

Les développeurs, et les gens en général, ont des estimations extrêmement imprécises du temps de projet, généralement dans le sens de l’optimisme.

En game dev, on peut parler de “Valve time”, en référence à l’habitude de Valve de livrer en retard.

Causes:

- loi de Vierordt (1868): les intervalles de temps “courts” (ex. 10 secondes) tendent à être surestimés, et les intervalles de temps “longs” tendent à être sous-estimés
- règle du 90/90: “Les premiers 90 pourcents du code représentent les premiers 90 pourcents du temps de développement. Les 10 pourcents restants du code représentent les autres 90 pourcents du temps de développement.” (Tom Cargill, 1985): biais mental de voir les tâches presque-fonctionnelles comme étant presque-livrables
- biais d’optimisme
- biais de présentation de soi

Solutions:

- croire les données plutôt que l’intuition: faire des estimations de temps, les vérifier, et en déduire les dates de livraison avec une approximation
- planning poker (évite l’effet reddit aka biais d’ancrage, utilise la sagesse collective)

## Loi de Parkinson

La durée du travail et le nombre de travailleurs augmentent de façon à remplir toutes les ressources disponibles, indépendamment des besoins (C. Northcote Parkinson, 1955)

Lois liées:

- corollaire de Stock-Sanford: si vous attendez la dernière minute, ça ne prend qu’une minute.
- corollaire d’Asimov: en dix heures par jour, vous avez le temps de prendre deux fois plus de retard qu’en cinq heures par jour.
- bullshit jobs & expansion bureaucratique
- demande induite
- position de Lewis–Mogridge: plus on construit de routes, plus le trafic remplit ces routes (1990)
- paradoxe de Jevons, effet rebond
- effet SnackWell: les personnes au régime mangent plus de snacks allégés jusqu’à atteindre en général leur apport calorique d’avant le régime, via la licence morale

Solutions:

- timeboxing: passer X heures sur Y, puis s’arrêter
- daily standups

## Principe de Peter

“Tout employé tend à s’élever à son niveau d’incompétence” (Laurence J. Peter, 1970)

Causes:

- principe de Dilbert: la promotion des employés incompétents est plutôt fréquente
- l’incompétence est un frein à toute promotion supplémentaire, pas un déclencheur de licenciement, seule la super-incompétence, bien plus rare, l’est
- les compétences ne sont pas toujours transférables (un bon exécutant ne fait pas forcément un bon leader)

## Loi de Conway

“Toute organisation qui conçoit un système produira un design dont la structure est une copie de la structure de communication de l’organisation.”

La structure d’un logiciel reflète la forme de l’équipe, pas le meilleur design possible.

L’Inverse Conway Maneuver est l’application proactive de la loi de Conway. Si on veut que notre architecture logicielle prenne une forme spécifique, on devrait d’abord organiser nos équipes en conséquence.