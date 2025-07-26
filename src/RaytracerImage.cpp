/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** RaytracerImage
*/

#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>
#include <random>

#include "Raytracer.hpp"
#include "../common/Random.hpp"
#include "../common/Vector3D.hpp"
#include "../common/Exception/SceneException.hpp"
#include "mediator/RayMediator.hpp"

void Raytracer::applyLights(std::shared_ptr<PixelInfo> pixelInfo,
    const Math::Ray &ray) const {
    auto lights = this->_scene.getLights();
    if (!lights)
        return;
    lights->traverseGraph(lights, [&](const std::shared_ptr<ILight> &light) {
        if (light)
            light->addLight(pixelInfo, ray);
    });
}

void traverseGraph(const std::shared_ptr<GraphsNodePrimitive>& node,
    const std::function<void(const std::shared_ptr<IPrimitives>&)>& func) {
    if (!node) return;
    if (node->_primitives) {
        func(node->_primitives);
    }
    for (const auto& child : node->_children) {
        traverseGraph(child, func);
    }
}

void Raytracer::setScene() {
    this->_scene = Scene();
    this->_scene.setCamera(this->_factoryManager.getCamera());

    std::vector<std::shared_ptr<IPrimitives>> prims;
    auto root = this->_factoryManager.getPrimitives();
    if (root) {
        traverseGraph(root, [&](const std::shared_ptr<IPrimitives>& prim) {
            prims.push_back(prim);
        });
    }
    this->_scene.setPrimitives(prims);
    this->_scene.setLights(this->_factoryManager.getLights());
}

std::optional<PixelInfo> Raytracer::getClosestPrimitiveHit(const Math::Ray
    &ray) const {
    auto root = _scene.getPrimitives();
    if (!root)
        return std::nullopt;

    std::optional<PixelInfo> closestHit = std::nullopt;
    double closestDistance = std::numeric_limits<double>::max();

    traverseGraph(root, [&](const std::shared_ptr<IPrimitives>& primitive) {
        PixelInfo info = primitive->distanceInfo(ray);
        if (info._isHit && info._distance < closestDistance &&
            info._distance > 0) {
            closestDistance = info._distance;
            closestHit = info;
        }
    });

    return closestHit;
}

Color Raytracer::traceRaySingleSample(double u, double v, uint32_t &state) {
    Math::Ray ray = this->_scene.getCamera()->ray(u, v);
    float ambientLight = this->_factoryManager.getAmbientLight();

    Color incomingLight;
    Color rayColor(255, 255, 255, 255);
    for (int i = 0; i < 3; ++i) {
        std::optional<PixelInfo> hit = getClosestPrimitiveHit(ray);
        if (hit) {
            auto pixelInfoPtr = std::make_shared<PixelInfo>(hit.value());
            applyLights(pixelInfoPtr, ray);
            hit = *pixelInfoPtr;
            ray.setOrigin(hit->_pos);
            ray.setDirection(hit->_normalizedVector.RandomInHemisphere(state));
            incomingLight += hit->_light_color * hit->_light_intensity *
                rayColor;
            incomingLight += hit->_color * ambientLight * rayColor;
            rayColor *= hit->_color;
        } else {
            break;
        }
    }
    return incomingLight;
}

Color Raytracer::computePixelWithAntiAliasing(int x, int y, uint32_t &state) {
    int antiAliasing = _scene.cameraAntiAliasing();
    Math::Vector3D totalIncomingLight;
    int samples = antiAliasing * antiAliasing;
    for (int p = 0; p < antiAliasing; p++) {
        for (int q = 0; q < antiAliasing; q++) {
            double offsetX = (p + Math::Random::pcg(state)) / antiAliasing;
            double offsetY = (q + Math::Random::pcg(state)) / antiAliasing;
            double u = (static_cast<double>(x) + offsetX) / _width;
            double v = (static_cast<double>(y) + offsetY) / _height;
            totalIncomingLight += traceRaySingleSample(u, v, state);
        }
    }
    return totalIncomingLight / static_cast<float>(samples);
}

void Raytracer::initializeScene() {
    setScene();
    if (this->_scene.getCamera() == nullptr) {
        throw SceneException("No camera found in the scene");
    }
    auto primRoot = this->_scene.getPrimitives();

    if (!primRoot || primRoot->_children.empty()) {
        throw SceneException("No primitives found in the scene");
    }
    _width = this->_scene.camereaWidth();
    _height = this->_scene.camereaHeight();
    if (isDebug() == true) {
        std::cout << "Width: " << _width << " Height: " << _height << std::endl;
    }

    this->image = std::make_shared<Image>(_width, _height, 255);
    if (isDebug() == true) {
        std::cout << "Image created" << std::endl;
    }

    if (this->graphicMode == true && this->_display != nullptr) {
        this->_display->setWindow(_width, _height);
    }
}

void Raytracer::renderConsoleMode(const Color& backgroundColor) {
    int width = this->_scene.camereaWidth();
    int height = this->_scene.camereaHeight();
    (void)backgroundColor;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Math::Vector3D totalIncomingLight;
            uint32_t state = static_cast<uint32_t>(x * _width + y);
            totalIncomingLight += computePixelWithAntiAliasing(x, y, state);
            this->image->setPixel(x, y, totalIncomingLight);
        }
    }
}

void Raytracer::finalizeRendering() {
    if (isDebug() == true) {
        std::cout << "Image processing completed" << std::endl;
    }
    this->image->writeToFilePPM(this->_outputfile);
}

void Raytracer::averageImages(const std::vector<std::shared_ptr<Image>>
    &images) {
    int width = this->_scene.camereaWidth();
    int height = this->_scene.camereaHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;

            for (const auto& img : images) {
                Color pixel = img->getPixel(x, y);
                totalRed += pixel.getRed();
                totalGreen += pixel.getGreen();
                totalBlue += pixel.getBlue();
            }

            int numImages = images.size();
            Color averagedColor(
                totalRed / numImages,
                totalGreen / numImages,
                totalBlue / numImages);
            this->image->setPixel(x, y, averagedColor);
        }
    }
}

void Raytracer::StartImage() {
    initializeScene();

    Color backgroundColor(255, 255, 255);
    int width = this->_scene.camereaWidth();
    int height = this->_scene.camereaHeight();
    int totalPixels = width * height;
    std::shared_ptr<int> pixelCount = std::make_shared<int>(0);

    if (this->graphicMode) {
        startPreveiwMode(width, height, pixelCount, totalPixels);
    }

    std::vector<std::shared_ptr<Image>> renderedImages;
    RayMediator mediator;
    for (int i = 0; i < this->numRenders; ++i) {
        mediator.addTask([&, i]() {
            this->image = std::make_shared<Image>(width, height, 255);
            pixelCount = std::make_shared<int>(0);
            renderConsoleMode(backgroundColor);
            renderedImages.push_back(this->image);
        });
    }

    mediator.executeTasks();
    mediator.waitForCompletion();

    this->image = std::make_shared<Image>(width, height, 255);
    averageImages(renderedImages);

    finalizeRendering();
    loopThruType();
}
