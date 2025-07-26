# Parser

Le module parser est responsable du chargement et de l'interprétation des fichiers de configuration qui définissent la scène 3D pour le raytracer. Il transforme les données de configuration en une structure exploitable par les autres composants du raytracer.

## Principaux composants

### 1. **ConfigParser**
- **Rôle** : Gère l'analyse des fichiers de configuration à l'aide de la bibliothèque `libconfig++`.
- **Fonctions clés** :
  - `loadConfig(const std::string &filename, ConfigNode &rootNode)` : Charge un fichier de configuration et construit un arbre (`ConfigNode`) représentant la configuration.
  - `buildConfigTree(const Setting &setting, ConfigNode &node)` : Traite récursivement les paramètres de configuration en une structure arborescente.
  - `handleGroupType`, `handleArrayType`, `handleListType`, `handleValueType` : Fonctions utilitaires pour traiter les différents types de paramètres (groupes, tableaux, listes, valeurs).
- **Détail sur la classe** : Voir [Doc.pdf page 32](../../Doc.pdf#page=34)

### 2. **ObjectConstructor**
- **Rôle** : Crée les objets (formes, lumières, matériaux, etc.) à partir des données de configuration analysées.
- **Fonctions clés** :
  - `initShapeDefinitions()` : Initialise les définitions des formes supportées.
  - `createObject` et `createObjects` : Créent les objets à partir des données de configuration.
  - `_propertyTypeMap` : Associe les noms de propriétés à leurs types et formats attendus.
  - `_shapeDefinitions` : Stocke les définitions des formes supportées.
- **Détail sur la classe** : Voir [Doc.pdf page 60](../../Doc.pdf#page=62)

### 3. **ValueConverter**
- **Rôle** : Convertit les valeurs de configuration en types de données spécifiques.
- **Fonctions clés** :
  - `getFloatFromVariant` : Convertit une valeur de configuration en float.
  - `getVector2DFromComponents` : Convertit des composantes en vecteur 2D.
  - `getVector3DFromComponents` : Convertit des composantes en vecteur 3D.
- **Détail sur la classe** : Voir [Doc.pdf page 86](../../Doc.pdf#page=88)

### 4. **ObjectErrorHandling**
- **Rôle** : Valide les données de configuration et gère les erreurs liées à la création d'objets.
- **Fonctions clés** :
  - `isParameterValid`, `isParameterMandatory`, `isParameterOptional` : Valident les paramètres des objets.
  - `checkSimpleValueValidity`, `checkVector2DValueValidity`, `checkVector3DValueValidity` : Valident les types de valeurs spécifiques.
- **Détail sur la classe** : Voir [Doc.pdf page 61](../../Doc.pdf#page=63)

### 5. **Parser**
- **Rôle** : Orchestration du processus de parsing et accès aux objets analysés.
- **Fonctions clés** :
  - `loadConfig(const std::string &filename)` : Charge le fichier de configuration.
  - `parse()` : Traite les données de configuration et crée les objets (caméra, lumières, primitives, etc.).
  - `getObjects()` : Retourne la liste des objets analysés.
- **Détail sur la classe** : Voir [Doc.pdf page 61](../../Doc.pdf#page=63)

## Workflow

1. **Chargement de la configuration** : `ConfigParser` lit le fichier de configuration et construit une structure arborescente (`ConfigNode`).
2. **Création des objets** : `ObjectConstructor` utilise la configuration analysée pour créer les objets (formes, lumières, matériaux...).
3. **Validation** : `ObjectErrorHandling` s'assure que les données de configuration sont valides.
4. **Conversion** : `ValueConverter` convertit les valeurs de configuration dans les bons types.
5. **Accès aux objets** : `Parser` fournit l'accès aux objets créés pour le raytracer.

Cette architecture modulaire rend le parser extensible et capable de gérer efficacement des configurations complexes.
