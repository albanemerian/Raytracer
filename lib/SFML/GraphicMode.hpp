/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Graphic Mode
*/

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../../common/IGraphicMode.hpp"

#ifndef GRAPHICMODE_HPP_
    #define GRAPHICMODE_HPP_

class GraphicMode : public IGraphicMode {
    public:
        GraphicMode();
        ~GraphicMode();

        void createText(const std::string &text, int size, int x, int y) override;
        void createRectangle(const std::string &id, int x, int y, int width, int height) override;

        bool getRenderingComplete() const override;
        void setWindow(int width, int height) override;
        void setRenderingComplete(bool renderingComplete) override;

        void setPreveiwImage(const sf::Image &image) override;
        std::shared_ptr<sf::Image> getPreviewImage() const override;

        std::string getButtonPressed() override;
        void updateTexture() override;
        void drawPixelColor(int x, int y, uint8_t r, uint8_t g, uint8_t b) override;
        void drawImage() override;
        void drawButtons() override;
        void display() override;
        bool isOpen() override;
        void closeWindow() override;

    private:
        sf::Event _event;
        std::shared_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Image> _image;
        std::shared_ptr<sf::Image> _previewImage;
        std::map<std::string, sf::RectangleShape> _buttons;
        std::shared_ptr<sf::Font> _font;
        std::vector<sf::Text> _texts;
        sf::Texture _texture;
        sf::Texture _previewTexture;
        std::string _title;
        int _width;
        int _height;
        bool _renderingComplete;
};

extern "C" {
    std::shared_ptr<GraphicMode> createInstance();
}

#endif /* !GRAPHICMODE_HPP_ */
