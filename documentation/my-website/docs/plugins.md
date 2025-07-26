# Plugins

Le système de plugins du raytracer permet de charger dynamiquement et de gérer des modules externes (primitives, lumières, modes graphiques, etc.) à l'exécution. Cela repose sur la bibliothèque `DLLoader` et des points d'entrée spécifiques exposés par chaque plugin.

## Bibliothèque DLLoader

La classe `DLLoader` gère le chargement dynamique des bibliothèques partagées (`.so`) et l'accès à leurs symboles via `dlopen`, `dlsym` et `dlclose`.

### Principaux composants

- **`ILoader` Interface**  
  Définit le contrat pour tout loader dynamique :
  - `Open(const char *path, int flag)` : Ouvre une bibliothèque partagée.
  - `Symbol(const char *symbolName)` : Récupère un symbole (fonction ou variable).
  - `Close()` : Ferme la bibliothèque.
  - `Error()` : Retourne la dernière erreur rencontrée.
  - `getHandler() const` : Retourne le handler de la bibliothèque.
  - **Détail sur la classe** : [Doc.pdf page 37](../../Doc.pdf#page=39)

- **`DLLoader` Class**  
  Implémente `ILoader` avec une interface template pour la récupération typée des symboles.
  - `Open` : Charge la bibliothèque.
  - `Symbol` : Récupère un symbole et le caste.
  - `Close` : Décharge la bibliothèque.
  - `Error` : Récupère le dernier message d'erreur.

### Exemple de workflow

1. `DLLoader` charge dynamiquement une bibliothèque (ex: `raytracer_sphere.so`).
2. `Open` charge la bibliothèque et stocke le handler.
3. `Symbol` récupère les fonctions d'entrée du plugin.
4. `Close` décharge la bibliothèque.

## Points d'entrée des plugins

Chaque plugin expose des points d'entrée en `extern "C"` pour garantir la compatibilité C (pas de name mangling) et permettre la récupération facile des symboles.

### Plugins de primitives

Les primitives (sphère, plan, cône, cylindre, torus, etc.) sont des plugins dynamiques. Chaque plugin doit exposer les fonctions suivantes :

```cpp
extern "C" {
    std::shared_ptr<IPrimitives> createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        const std::vector<std::shared_ptr<ILight>>& lights
    );
    ObjectType getType();
    std::string getName();
}
```

- **createPrimitive** : Crée une instance de la primitive avec la configuration et les dépendances nécessaires.
- **getType** : Retourne le type d'objet (doit être `TYPE_PRIMITIVE`).
- **getName** : Retourne le nom utilisé dans la configuration.

### Plugins de lumières

Les lumières (directionnelles, phong, etc.) sont aussi des plugins dynamiques. Chaque plugin doit exposer :

```cpp
extern "C" {
    std::shared_ptr<ILight> createLight(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map
    );
    ObjectType getType();
    std::string getName();
}
```

- **createLight** : Crée une instance de la lumière à partir de la configuration.
- **getType** : Retourne le type d'objet (doit être `TYPE_LIGHT`).
- **getName** : Retourne le nom utilisé dans la configuration.

### Plugins de modes graphiques (ex: SFML)

Les modes graphiques (comme SFML) sont aussi des plugins dynamiques. Exemple :

```cpp
extern "C" {
    std::shared_ptr<GraphicMode> createInstance();
}
```

- **createInstance** : Crée une instance du mode graphique.

## Exemple de structure de plugin

Exemple pour une primitive :

```cpp
#include "Sphere.hpp"

extern "C" {
    std::shared_ptr<IPrimitives> createPrimitive(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        const std::vector<std::shared_ptr<ILight>>& lights
    ) {
        return std::make_shared<Sphere>(map, graphSceneList);
    }

    ObjectType getType() { return ObjectType::TYPE_PRIMITIVE; }
    std::string getName() { return "sphere"; }
}
```

Exemple pour une lumière :

```cpp
#include "PhongLight.hpp"

extern "C" {
    std::shared_ptr<ILight> createLight(
        std::shared_ptr<std::map<ValueType_t, ValueType>> map
    ) {
        return std::make_shared<PhongLight>(map);
    }

    ObjectType getType() { return ObjectType::TYPE_LIGHT; }
    std::string getName() { return "phong"; }
}
```

Exemple pour SFML :

```cpp
#include "GraphicMode.hpp"

extern "C" {
    std::shared_ptr<GraphicMode> createInstance() {
        return std::make_shared<GraphicMode>();
    }
}
```

## Résumé

- **Primitives, lumières et modes graphiques** sont tous des plugins dynamiques, chacun avec ses points d'entrée spécifiques.
- Le système permet d'ajouter de nouveaux types d'objets sans recompiler le raytracer.
- Les factories du raytracer chargent dynamiquement ces plugins et utilisent leurs points d'entrée pour instancier les objets nécessaires à la scène.
