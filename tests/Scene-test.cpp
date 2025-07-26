/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Scene-test
*/

#include <criterion/criterion.h>
#include "../common/Scene.hpp"

Test(Scene, default_constructor) {
    Scene scene;
    cr_assert_eq(scene.getCamera()->getWidth(), 0);
    cr_assert_eq(scene.getCamera()->getHeight(), 0);
}

Test(Scene, parameterized_constructor) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IPrimitives>> primitives;
    Scene scene(camera, primitives);
    cr_assert_eq(scene.getCamera()->getWidth(), 0);
    cr_assert_eq(scene.getCamera()->getHeight(), 0);
    scene.~Scene();
}

Test(Scene, setCamera) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    Scene scene;
    scene.setCamera(camera);
    cr_assert_eq(scene.getCamera()->getWidth(), 0);
    cr_assert_eq(scene.getCamera()->getHeight(), 0);
}

Test(Scene, setPrimitives) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IPrimitives>> primitives;
    Scene scene(camera, primitives);
}

Test(Scene, camereaWidth) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    Scene scene(camera, {});
    cr_assert_eq(scene.camereaWidth(), 0);
}

Test(Scene, camereaHeight) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    Scene scene(camera, {});
    cr_assert_eq(scene.camereaHeight(), 0);
}

Test(Scene, destructor) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IPrimitives>> primitives;
    Scene* scene = new Scene(camera, primitives);
    delete scene;
    cr_assert(true);
}

Test(Scene, empty_primitives) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<IPrimitives>> primitives;
    Scene scene(camera, primitives);
}

Test(Scene, getPrimitvesList) {
    std::vector<std::shared_ptr<IPrimitives>> primitives;
    Scene scene;

    scene.setPrimitives(primitives);
    scene.getPrimitives();
}

Test(Scene, setLights) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    std::vector<std::shared_ptr<ILight>> lights;
    Scene scene(camera, {});
    scene.setLights(lights);
    scene.getLights();
}

Test(Scene, cameraAntiAliasing) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    Scene scene(camera, {});
    scene.setAntiAliasing(4);
    cr_assert_eq(scene.cameraAntiAliasing(), 4);
}

Test(Scene, getAmbientLight) {
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    Scene scene(camera, {});
    scene.getAmbientLight();
}


