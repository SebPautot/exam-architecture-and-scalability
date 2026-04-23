# Tests

# Cours sur les tests

Les tests, ce n’est pas juste “vérifier si le code marche”. C’est un outil de design, une boucle de feedback, et un système de gestion du risque. Une bonne suite de tests aide à changer le code plus vite avec moins de peur.

## Types de tests

Il n’existe pas de type de test “meilleur” en absolu. Chaque type répond à une question différente avec un coût différent.

Trade-off typique :

- Les tests de plus bas niveau sont rapides et précis, mais ne capturent pas les problèmes d’intégration full-system.
- Les tests de plus haut niveau sont réalistes et utiles, mais plus lents, plus flaky, et plus coûteux à maintenir.

Pensez en couches, pas en absolus.

### Tests unitaires

Objectif :

- Valider une unité de comportement en isolation.
- Échouer pour une seule raison.
- S’exécuter très vite (millisecondes).

Ce pour quoi ils sont excellents :

- Logique pure.
- Edge cases.
- Éviter la régression sur les bug fixes.

Exemple :

```cpp
// Unit test target: deterministic, pure-ish logic
int CalculateDamage(int baseDamage, int armor) {
    if (baseDamage < 0) return 0;
    if (armor < 0) armor = 0;
    return std::max(0, baseDamage - armor);
}

// Unit tests
TEST(DamageTests, ArmorReducesDamage) {
    ASSERT_EQ(CalculateDamage(50, 10), 40);
}

TEST(DamageTests, NegativeDamageClampedToZero) {
    ASSERT_EQ(CalculateDamage(-5, 10), 0);
}
```

Smell à éviter :

- Si un test “unitaire” démarre des bases de données, charge des maps complètes, ou attend des timers, ce n’est probablement plus un test unitaire.

### Tests d’intégration

Objectif :

- Vérifier que deux modules ou plus fonctionnent correctement ensemble.
- Capturer les mismatchs de contrat aux frontières.

Ce pour quoi ils sont excellents :

- Repository + base de données.
- Service + cache.
- Système de sauvegarde/chargement + format de sérialisation.

Exemple :

```cpp
// Integration test: SaveService + JSON serializer + filesystem
TEST(SaveSystemIntegration, SaveThenLoadRestoresState) {
    PlayerState before;
    before.Level = 7;
    before.Coins = 420;

    SaveService saveService("./tmp_test_save.json");
    ASSERT_TRUE(saveService.Save(before));

    auto after = saveService.Load();
    ASSERT_TRUE(after.has_value());
    ASSERT_EQ(after->Level, 7);
    ASSERT_EQ(after->Coins, 420);
}
```

Smell à éviter :

- Over-mocker les tests d’intégration. Si tout est mocké, vous n’intégrez rien.

### Smoke tests

Objectif :

- Répondre rapidement : “Est-ce que ce build est visiblement cassé ?”

Exemple de checklist smoke :

- Le jeu boot sur le menu principal.
- Une map charge.
- Une partie démarre.
- Un cycle sauvegarde/chargement réussit.

Lancez-les sur chaque build. C’est votre première gate.

### Tests de régression

Objectif :

- Verrouiller un bug passé pour qu’il ne revienne jamais.

Workflow :

1. Reproduire le bug avec un test qui échoue.
2. Corriger le bug.
3. Garder le test pour toujours.

Exemple :

- “L’inventaire duplique un item quand on le drop pendant un lag spike” devient un scénario de test permanent.

### Tests de performance

Objectif :

- Valider les budgets de timing, mémoire, et throughput.

Exemples game dev :

- Budget de frame time sous stress de combat.
- Temps de chargement sur scène lourde en assets.
- Stabilité du tick serveur avec 64 bots.

Ce ne sont pas juste des sessions de profiling. Ils doivent avoir des seuils pass/fail.

### Tests end-to-end

Objectif :

- Valider des parcours joueurs critiques de l’entrée au résultat.
- Prouver que tout le produit fonctionne ensemble dans des conditions réalistes.

Exemple de scénario E2E :

1. Lancer le jeu.
2. Se connecter.
3. Faire le matchmaking.
4. Finir la partie.
5. Donner les récompenses.
6. Persister le profil.
7. Relancer et vérifier que les récompenses sont toujours présentes.

Les tests E2E ont une grande valeur et un grand coût. Gardez-les focalisés sur les flux business critiques.

## Automation Test Framework

Unreal fournit plusieurs styles de tests dans l’écosystème Automation. Utilisez-les comme des couches, pas comme un outil unique.

### Catégories principales de tests dans Unreal

Tests unitaires / automation bas niveau :

- Implémentés en C++ avec des macros comme `IMPLEMENT_SIMPLE_AUTOMATION_TEST`.
- Idéaux pour la logique déterministe et le code moteur/jeu isolé.

Tests style spec :

- Syntaxe type BDD (`Describe`, `It`) avec le style Automation Spec.
- Utile pour la lisibilité et le regroupement de comportements.

Tests fonctionnels :

- Vérifications de comportement in-world, souvent basées sur des maps.
- Bien adaptés aux interactions d’acteurs, au flow gameplay, et à la validation de contenu.

Tests E2E / flows packagés :

- Souvent orchestrés avec Gauntlet et l’outillage de pipeline de build.
- Idéaux pour les chemins critiques de type launch/login/session/exit.

### Exemple minimal de test automation C++ Unreal

```cpp
#include"Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FDamageCalculationTest,
    "Project.Unit.Combat.DamageCalculation",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FDamageCalculationTest::RunTest(const FString& Parameters)
{
    auto CalculateDamage = [](int32 Base, int32 Armor)
    {
        return FMath::Max(0, Base - FMath::Max(0, Armor));
    };

    TestEqual(TEXT("Armor reduces damage"), CalculateDamage(50, 10), 40);
    TestEqual(TEXT("Negative base damage clamps to zero"), CalculateDamage(-3, 10), 0);
    return true;
}
```

Bonnes pratiques :

- Utiliser des entrées stables et déterministes.
- Garder un focus comportemental par test.
- Ranger les tests sous une convention de nommage claire (par exemple : `Project.Unit.*`, `Project.Integration.*`).

### Tests fonctionnels dans Unreal

Utilisez le plugin Functional Testing / les functional test actors quand vous validez du gameplay dans un monde en cours d’exécution.

Bonnes cibles pour les tests fonctionnels :

- Règles de spawn.
- Trigger volumes.
- Comportement des cooldowns d’abilities.
- Conditions de réussite/échec des objectifs.

Conseils :

- Garder les test maps minimales.
- Éviter de dépendre du timing cinématique, sauf si c’est précisément ce qui est testé.
- Préférer des attentes explicites sur des conditions plutôt que des délais arbitraires.

### Exécuter l’automation Unreal en CI

Pattern typique d’exécution headless :

```powershell
UnrealEditor-Cmd.exe MyProject.uproject `
  -ExecCmds="Automation RunTests Project.Unit" `
  -TestExit="Automation Test Queue Empty" `
  -unattended -nop4 -nullrhi -log
```

Notes :

- `nullrhi` est utile pour les runs de test sans rendu en CI.
- Séparez les suites par catégorie (unit/integration/functional) pour faciliter le triage des échecs.
- Publiez les rapports de test comme artifacts CI.