/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Header
*/

#include <memory>
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

#ifndef IGRAPHICMODE_HPP_
    #define IGRAPHICMODE_HPP_

class IGraphicMode {
    public:
        virtual ~IGraphicMode() = default;

        /* Method */
        virtual void createText(const std::string &text, int size, int x, int y) = 0;
        virtual void updateTexture() = 0;
        virtual void drawPixelColor(int x, int y, uint8_t r, uint8_t g, uint8_t b) = 0;
        virtual void drawImage() = 0;
        virtual void createRectangle(const std::string &id, int x, int y, int width, int height) = 0;
        virtual void drawButtons() = 0;
        virtual void display() = 0;
        virtual bool isOpen() = 0;
        virtual void closeWindow() = 0;

        /* Getter */
        virtual bool getRenderingComplete() const = 0;
        virtual std::shared_ptr<sf::Image> getPreviewImage() const = 0;
        virtual std::string getButtonPressed() = 0;

        /* Setter */
        virtual void setWindow(int width, int height) = 0;
        virtual void setRenderingComplete(bool renderingComplete) = 0;
        virtual void setPreveiwImage(const sf::Image &image) = 0;
};

#endif /* !IGRAPHICMODE_HPP_ */
