/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** RaytracerGraphic
*/

#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <memory>

#include "Raytracer.hpp"
#include "mediator/RayMediator.hpp"

void Raytracer::startPreveiwMode(int width, int height,
    std::shared_ptr<int> pixelCount, int totalPixels) {

    if (setGraphicMode()) {
        this->_display->setWindow(width, height);
        displayGraphicMode(pixelCount, totalPixels);
        _display->closeWindow();
        return;
    }
}

void Raytracer::renderGraphicMode(int width, int height,
    std::shared_ptr<int> pixelCount) {
    int batchSize = 10;
    int startY = (*pixelCount) / width;
    int endY = std::min(startY + batchSize, height);

    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < width; ++x) {
            Math::Vector3D totalIncomingLight;
            uint32_t state = static_cast<uint32_t>(x * _width + y);
            totalIncomingLight += computePixelWithAntiAliasing(x, y, state);
            this->image->setPixel(x, y, totalIncomingLight);
            this->_display->drawPixelColor(x, y, totalIncomingLight.getX(),
                totalIncomingLight.getY(), totalIncomingLight.getZ());
            (*pixelCount)++;
        }
    }
}

void Raytracer::renderPreviewImage() {
    int previewWidth = 256;
    int previewHeight = 144;
    previewImage.create(previewWidth, previewHeight, sf::Color(230, 230, 230));
    for (int y = 0; y < previewHeight; ++y) {
        for (int x = 0; x < previewWidth; ++x) {
            uint32_t state = static_cast<uint32_t>(x * previewWidth + y);
            Color color = traceRaySingleSample(
                static_cast<double>(x) / previewWidth,
                static_cast<double>(y) / previewHeight,
                state);
            previewImage.setPixel(x, y, sf::Color(color.getRed(),
            color.getGreen(), color.getBlue()));
        }
    }
    if (this->_display)
        this->_display->setPreveiwImage(previewImage);
    previewRendered = true;
}


void Raytracer::displayGraphicMode(std::shared_ptr<int> pixelCount,
    int totalPixels) {
    int width = this->_scene.camereaWidth();
    int height = this->_scene.camereaHeight();

    while (true) {
        if (this->_display->isOpen() == false) {
            this->_display->closeWindow();
            exit(0);
        }
        renderPreviewImage();
        if (this->_display->getRenderingComplete()) {
            if (this->_display->getButtonPressed().compare("preview") == 0) {
                this->image->writeToFilePPM(this->_outputfile);
            }
            this->_display->display();
            continue;
        }

        this->renderGraphicMode(width, height, pixelCount);
        this->_display->updateTexture();
        this->_display->display();

        if ((*pixelCount) >= totalPixels) {
            this->_display->setRenderingComplete(true);
        }
    }
}
