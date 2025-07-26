# Building

## Factory Pattern dans le Raytracer

Le Raytracer utilise le design pattern Factory pour créer des objets de manière flexible et extensible. Ce pattern permet de déléguer la création d'objets à des classes spécifiques tout en maintenant une interface commune.

### Architecture des Factories

Le système de factories est organisé de manière hiérarchique:

#### 1. Interface IFactory (Interface)  [Go to Page 49](../../Doc.pdf#page=51)
`IFactory` est l'interface générique qui définit le comportement commun pour toutes les factories. Elle permet la création d'objets à partir d'une configuration, l'enregistrement de créateurs, et le chargement dynamique de plugins. Elle gère aussi la propagation des lumières et des graphes de scène pour les objets qui en ont besoin.

```cpp
template <typename T>
class IFactory {
public:
    virtual ~IFactory() = default;
    virtual std::shared_ptr<T> create(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList) = 0;

    virtual std::shared_ptr<T> createSimple(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphSceneList,
        std::vector<std::shared_ptr<IPrimitives>>) = 0;

    virtual void registerCreator(
        const std::string& type,
        std::function<std::shared_ptr<T>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList)> creator) = 0;

    virtual void registerCreatorLight(
        const std::string& type,
        std::function<std::shared_ptr<T>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
            const std::vector<std::shared_ptr<ILight>>&)> creator) = 0;

    virtual bool loadPlugin(const std::string& path) = 0;
};
```

Cette interface permet :
- **create** : Crée un objet d'un type spécifié à partir d'une configuration, d'une liste de graphes et de lumières.
- **createSimple** : Crée un objet sans gestion des lumières.
- **registerCreator / registerCreatorLight** : Enregistre des fonctions de création pour chaque type d'objet, avec ou sans gestion des lumières.
- **loadPlugin** : Charge dynamiquement un plugin contenant des créateurs d'objets.

#### 2. Factories Spécifiques

Le système comprend trois factories spécialisées :

##### PrimitiveFactory [Go to Page 71](../../Doc.pdf#page=73)

Responsable de la création des primitives géométriques (sphères, plans, cônes, cylindres, etc.), elle gère aussi la création et l'association des matériaux, le chargement dynamique de plugins de primitives, et la gestion des textures.

```cpp
class PrimitiveFactory : public IFactory<IPrimitives> {
    // Implémentation spécifique pour créer des primitives
    // Gère la création de primitives, l'association des matériaux,
    // le chargement de plugins et la gestion des textures.
};
```

##### LightFactory [Go to Page 54](../../Doc.pdf#page=56)

Gère la création des différents types de lumières (ponctuelles, directionnelles, etc.), le chargement dynamique de plugins de lumières, et l'enregistrement de créateurs de lumières personnalisées.

```cpp
class LightFactory : public IFactory<ILight> {
    // Implémentation spécifique pour créer des lumières
    // Gère la création de lumières et le chargement de plugins de lumières.
};
```

##### CameraFactory [Go to Page 23](../../Doc.pdf#page=25)

S'occupe de la création des caméras pour la scène, à partir de la configuration fournie.

```cpp
class CameraFactory : public IFactory<Camera> {
    // Implémentation spécifique pour créer des caméras
    // Gère la création de caméras.
};
```

#### 3. FactoryManager [Go to Page 40](../../Doc.pdf#page=42)

Le `FactoryManager` orchestre l'ensemble des factories et fournit un point d'accès unifié. Il gère l'initialisation des factories, la création des objets à partir de la configuration, et stocke les objets créés (primitives, lumières, caméra, lumière ambiante).

```cpp
class FactoryManager {
public:
    FactoryManager();
    ~FactoryManager() = default;

    std::shared_ptr<PrimitiveFactory> getPrimitiveFactory();
    std::shared_ptr<CameraFactory> getCameraFactory();

    void initializeFactories();

    void createObjectsFromConfig(const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& objectsConfig);

    std::shared_ptr<GraphsNodePrimitive> getPrimitives() const;
    std::vector<std::shared_ptr<ILight>> getLights() const;
    std::shared_ptr<Camera> getCamera() const;
    float getAmbientLight() const;

private:
    std::shared_ptr<PrimitiveFactory> _primitiveFactory;
    std::shared_ptr<CameraFactory> _cameraFactory;
    std::shared_ptr<LightFactory> _lightsFactory;
    std::shared_ptr<GraphsNodePrimitive> _primitives;
    std::vector<std::shared_ptr<ILight>> _lights;
    std::shared_ptr<Camera> _camera;
    float _ambientLight;
};
```

### Processus de fabrication des objets

1. **Initialisation** :  
   Le `FactoryManager` initialise les différentes factories et charge les plugins nécessaires.

2. **Parsing de la configuration** :  
   Le parseur analyse le fichier de configuration et crée une structure de maps typées.

3. **Construction d'objets** :  
   Pour chaque objet défini dans la configuration, `FactoryManager` détermine le type d'objet et délègue la création à la factory appropriée (PrimitiveFactory, LightFactory ou CameraFactory). Les objets sont créés avec la gestion des graphes et des lumières si nécessaire.

4. **Extensibilité par plugins** :  
   Les factories peuvent charger dynamiquement des plugins pour étendre leurs capacités. Chaque plugin doit exposer des fonctions spécifiques :
   - `createPrimitive` ou `createLight` : Pour créer une instance d'objet
   - `getType` : Pour identifier le type d'objet
   - `getName` : Pour obtenir le nom utilisé dans la configuration

### Avantages du système de Factory

- **Modularité** : Chaque type d'objet est créé par sa propre factory spécialisée.
- **Extensibilité** : De nouveaux types d'objets peuvent être ajoutés sans modifier le code existant.
- **Chargement dynamique** : Les plugins permettent d'ajouter de nouveaux objets sans recompiler l'application.
- **Séparation des responsabilités** : La création d'objets est séparée de leur utilisation.
- **Uniformité** : Tous les objets sont créés selon un processus standardisé.

### Workflow d'utilisation

1. Le parseur extrait les données de configuration du fichier.
2. `FactoryManager.createObjectsFromConfig()` est appelé avec ces maps.
3. Chaque factory crée les objets correspondants à partir de ces données.
4. Les objets créés sont stockés dans le `FactoryManager` et prêts à être utilisés.

Ce système permet une grande flexibilité dans la définition de scènes 3D et facilite l'extension du raytracer avec de nouvelles primitives, lumières ou types de caméras.
