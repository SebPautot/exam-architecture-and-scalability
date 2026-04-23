# Exam

## Anti-patterns

Le burn-out des équipes mentionné dans l'article qui a engendré un taux de turnover élevé. Cela peut engendrer :
- Silos de connaissance : Il ne reste qu'une personne capable d'utiliser ce système, voir il n'y a plus personne et il faut retrouver la personne avec les infos. Perte de savoir-faire constant.
- Dilution de responsabilité : Les problèmes ne sont pas ceux des gens qui viennent d'arriver, et les personnes qui ont engendrés ces problèmes sont déjà partis depuis longtemps.
- Loi de Brooks : L'on-boarding constant a couté beaucoup de temps à la production.

Le grand volume de mécaniques et systèmes semble avoir engendré l'apparition de ces anit-patterns :
- Feature factory : Le grand nombre de feature et le fait de repousser constamment la date de livraison ont probablement joué sur le sentiment de constamment produire comme si c'était le jour où il faut livrer. Grande vélocité apparente, pas de refacto des systèmes et dette technique qui croit librement.
- Loi de Brooks : La taille de l'équipe croissante pour match le nombre de tâches/mécaniques à designer et des edge-cases à prednre en compte a fait ralentir la communication.

Le fait que le projet ne se soit pas fait kill plus tôt semble s'apparenter à :
- L'escalade de l'engagement : L'entreprise ayant déjà investit beaucoup d'argent dans le projet, effectué beaucoup d'embauche qu'ils ne peuvent pas forcément replacer ailleurs en cas d'annulation (severance packages, etc.) ils n'ont pas souhaité annuler le projet plus tôt. De plus le fait d'être allé jusqu'à signer un contrat avec le gouvernement de Singapour afin de continuer d'injecter du financement dans le projet les a forcé à aller jusqu'au bout du développement sous peine de pénalités contractuelles élevées.

## Solutions potentielles

Des solutions potentielles auraient été :
- La réduction de la taille de chaque équipe afin d'opérer une flotille et non un paquebot. Cela aurait permis :
  - D'augmenter la manoeuvrabilité des équipes.
  - De faciliter la communication entre les différentes parties.
  - D'engager des responsabilités à plus petite échelle, on se sent plus concerné quand on connait la personne qui devra résoudre nos problèmes si on ne les règle pas nous-même.
  - Faciliter la communication avec la hierarchie : Les supérieurs n'ont pas une équipe de 50, 100, 200 personnes face à eux mais 5 leads, ce qui permet de s'accorder sur une seule vision et d'éviter des réunions Teams avec plusieurs centaines de personnes.
- Fail-fast : Annuler ou sortir le produit sans attendre aurait permis aux équipes de monter en compétence et d'éviter un crash de la production au ralentis.
- Réduction des attentes : Les attentes étant extrêmement élevées, le budget a été structuré en conséquence. Réduire la taille du jeu et des features, réduire les promesses aux joueurs. Cala aurait permis également de relacher la pression de performance attendue par les joueurs et la hierarchie envers la production et le jeu.
