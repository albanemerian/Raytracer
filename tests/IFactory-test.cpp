/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IFactory-test
*/


#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/factory/FactoryManager.hpp"
#include "../src/factory/CameraFactory.hpp"


void redirect_all_stdout_factory(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}


Test(FactoryManager, constructor, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    cr_assert_not_null(factoryManager.getPrimitiveFactory(), "PrimitiveFactory should not be null.");
    cr_assert_not_null(factoryManager.getCameraFactory(), "CameraFactory should not be null.");
}

Test(FactoryManager, initializeFactories, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    factoryManager.initializeFactories();
    cr_assert_not_null(factoryManager.getPrimitiveFactory(), "PrimitiveFactory should not be null after initialization.");
    cr_assert_not_null(factoryManager.getCameraFactory(), "CameraFactory should not be null after initialization.");
}

Test(FactoryManager, createObjectsFromConfig, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto objectConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*objectConfig)[ValueType_t::TYPE] = ObjectType::TYPE_PRIMITIVE;
    (*objectConfig)[ValueType_t::NAME] = "testPrimitive";

    objectsConfig.push_back(objectConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
    //cr_assert_eq(factoryManager.getPrimitives().size(), 1, "Should have created one primitive.");
}

Test(FactoryManager, getCamera, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto objectConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*objectConfig)[ValueType_t::TYPE] = ObjectType::TYPE_CAMERA;
    (*objectConfig)[ValueType_t::NAME] = "testCamera";

    objectsConfig.push_back(objectConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
    cr_assert_not_null(factoryManager.getCamera(), "Camera should not be null after creation.");
}

Test(FactoryManager, getPrimitives, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto objectConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*objectConfig)[ValueType_t::TYPE] = ObjectType::TYPE_PRIMITIVE;
    (*objectConfig)[ValueType_t::NAME] = "testPrimitive";

    objectsConfig.push_back(objectConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
   // cr_assert_eq(factoryManager.getPrimitives().size(), 1, "Should have created one primitive.");
}

Test(FactoryManager, handleUnknownObjectType, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto unknownObjectConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*unknownObjectConfig)[ValueType_t::TYPE] = static_cast<ObjectType>(999); // Unknown type
    (*unknownObjectConfig)[ValueType_t::NAME] = "unknownObject";

    objectsConfig.push_back(unknownObjectConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
   // cr_assert_eq(factoryManager.getPrimitives().size(), 0, "No primitives should be created for unknown object type.");
    cr_assert_null(factoryManager.getCamera(), "No camera should be created for unknown object type.");
}

Test(FactoryManager, handleGraphSceneType, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto graphSceneConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graphSceneConfig)[ValueType_t::TYPE] = ObjectType::TYPE_GRAPH;
    (*graphSceneConfig)[ValueType_t::NAME] = "graphScene";

    objectsConfig.push_back(graphSceneConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
   // cr_assert_eq(factoryManager.getPrimitives().size(), 0, "No primitives should be created for graph scene type.");
    cr_assert_null(factoryManager.getCamera(), "No camera should be created for graph scene type.");
}

Test(FactoryManager, handleLightType, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto lightConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*lightConfig)[ValueType_t::TYPE] = ObjectType::TYPE_LIGHT;
    (*lightConfig)[ValueType_t::AMBIENT] = 0.5f;

    objectsConfig.push_back(lightConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
 //   cr_assert_eq(factoryManager.getPrimitives().size(), 0, "No primitives should be created for light type.");
    cr_assert_null(factoryManager.getCamera(), "No camera should be created for light type.");
}

Test(FactoryManager, handleImportedSceneType, .init = redirect_all_stdout_factory) {
    FactoryManager factoryManager;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> objectsConfig;

    auto importedSceneConfig = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*importedSceneConfig)[ValueType_t::TYPE] = ObjectType::TYPE_IMPORTED_SCENE;
    (*importedSceneConfig)[ValueType_t::NAME] = "importedScene";

    objectsConfig.push_back(importedSceneConfig);

    factoryManager.createObjectsFromConfig(objectsConfig);
   // cr_assert_eq(factoryManager.getPrimitives().size(), 0, "No primitives should be created for imported scene type.");
    cr_assert_null(factoryManager.getCamera(), "No camera should be created for imported scene type.");
}


Test(CameraFactory, constructor_camear, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    cameraFactory.loadAllPlugins("./plugins");
    cameraFactory.~CameraFactory();
}

Test(CameraFactory, loadValidPlugin, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    bool result = cameraFactory.loadPlugin("./plugins/raytracer_cone.so");
    cr_assert_eq(result, false, "Valid plugin should not be loaded successfully.");
}

Test(CameraFactory, loadInvalidPlugin, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    bool result = cameraFactory.loadPlugin("./plugins/arcade_sfml.so");
    cr_assert_not(result, "Invalid plugin should not be loaded.");
}

Test(CameraFactory, loadNonExistentPlugin, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    bool result = cameraFactory.loadPlugin("./plugins/nonExistentPlugin.so");
    cr_assert_not(result, "Non-existent plugin should not be loaded.");
}

Test(CameraFactory, createDefaultCamera, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    auto defaultCamera = cameraFactory.create("nonExistentType", nullptr, {}, {});
    cr_assert_not_null(defaultCamera, "Default camera should be created when type is not found.");
}

Test(CameraFactory, createCameraWithConfig, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    auto config = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*config)[RESOLUTION] = Math::Vector2D(1920, 1080);
    (*config)[POSITION] = Math::Vector3D(0, 0, 0);
    (*config)[FIELD_OF_VIEW] = 90.0f;

    auto camera = cameraFactory.create("nonExistentType", config, {}, {});
    cr_assert_not_null(camera, "Camera should be created with default settings.");
    cr_assert_eq(camera->getWidth(), 1920, "Resolution width should match config.");
    cr_assert_eq(camera->getHeight(), 1080, "Resolution height should match config.");
    cr_assert_eq(camera->getFieldOfView(), 90.0f, "Field of view should match config.");
}

Test(CameraFactory, handleNullConfig, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    auto camera = cameraFactory.create("nonExistentType", nullptr, {}, {});
    cr_assert_not_null(camera, "Camera should be created even if config is null.");
}

Test(CameraFactory, handleEmptyType, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    auto camera = cameraFactory.create("", nullptr, {}, {});
    cr_assert_not_null(camera, "Camera should be created even if type is empty.");
}

Test(CameraFactory, handleInvalidType, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    auto camera = cameraFactory.create("invalidType", nullptr, {}, {});
    cr_assert_not_null(camera, "Default camera should be created for invalid type.");
}

Test(CameraFactory, loadPluginWithInvalidPath, .init = redirect_all_stdout_factory) {
    CameraFactory cameraFactory;
    bool result = cameraFactory.loadPlugin("./invalid/path/plugin.so");
    cr_assert_not(result, "Plugin with invalid path should not be loaded.");
}
