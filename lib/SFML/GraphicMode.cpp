/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Graphic Mode
*/

#include <string>
#include <memory>
#include <iostream>
#include "GraphicMode.hpp"

GraphicMode::GraphicMode() : _title("Raytracer"), _width(1280), _height(720),
    _renderingComplete(false) {
    createRectangle("ppm", 1635, 150, 200, 75);
    createRectangle("png", 1635, 250, 200, 75);
    createRectangle("preview", 1635, 450, 200, 75);

    _font = std::make_shared<sf::Font>();
    if (_font->loadFromFile("assets/font.ttf")) {
        createText("DOWNLOAD", 30, 1675, 100);
        createText(".ppm", 30, 1710, 165);
        createText(".png", 30, 1710, 265);
        createText("PREVIEW", 30, 1685, 400);
        createText(".ppm", 30, 1710, 465);
    } else {
        std::cerr << "Error: Could not load font from assets/font.ttf" <<
        std::endl;
    }
}

GraphicMode::~GraphicMode() {
}

void GraphicMode::createText(const std::string &text, int size, int x, int y) {
    sf::Text newText;

    newText.setFont(*_font);
    newText.setString(text);
    newText.setCharacterSize(size);
    newText.setFillColor(sf::Color(5, 5, 5));
    newText.setPosition(sf::Vector2f(x, y));
    _texts.push_back(newText);
}

void GraphicMode::createRectangle(const std::string &id, int x,
    int y, int width, int height) {
    sf::RectangleShape newRect(sf::Vector2f(width, height));

    newRect.setFillColor(sf::Color(175, 175, 175));
    newRect.setOutlineThickness(3);
    newRect.setOutlineColor(sf::Color(5, 5, 5));
    newRect.setPosition(sf::Vector2f(x, y));
    this->_buttons[id] = newRect;
}

bool GraphicMode::getRenderingComplete() const {
    return this->_renderingComplete;
}

void GraphicMode::setWindow(int width, int height) {
    this->_window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(1920, 1080), this->_title);
    this->_window->setFramerateLimit(60);
    this->_image = std::make_shared<sf::Image>();
    this->_image->create(width, height, sf::Color(230, 230, 230));
    this->_previewImage = std::make_shared<sf::Image>();
    this->_previewImage->create(256, 144, sf::Color(230, 230, 230));
    updateTexture();
}

void GraphicMode::setRenderingComplete(bool renderingComplete) {
    this->_renderingComplete = renderingComplete;
}

std::string GraphicMode::getButtonPressed() {
    for (auto &pair : this->_buttons) {
        sf::Vector2i mouse = sf::Mouse::getPosition(*this->_window);
        sf::FloatRect area = pair.second.getGlobalBounds();

        if (area.contains(static_cast<sf::Vector2f>(mouse))) {
            pair.second.setFillColor(sf::Color(150, 150, 150));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                return pair.first;
            }
        } else {
            pair.second.setFillColor(sf::Color(175, 175, 175));
        }
    }
    return "";
}

void GraphicMode::updateTexture() {
    this->_texture.loadFromImage(*this->_image);
    this->_texture.setSmooth(true);
    if (_previewImage)
        this->_previewTexture.loadFromImage(*this->_previewImage);
    this->_previewTexture.setSmooth(true);
}

void GraphicMode::setPreveiwImage(const sf::Image &image) {
    if (!_previewImage)
        _previewImage = std::make_shared<sf::Image>();
    _previewImage = std::make_shared<sf::Image>(image);
    updateTexture();
}
std::shared_ptr<sf::Image> GraphicMode::getPreviewImage() const {
    return this->_previewImage;
}

void GraphicMode::drawPixelColor(int x, int y, uint8_t r, uint8_t g,
    uint8_t b) {
    this->_image->setPixel(x, y, sf::Color(r, g, b));
}

void GraphicMode::drawImage() {
    sf::Sprite sprite(this->_texture);

    sprite.setScale(sf::Vector2f(0.8, 0.8));
    sprite.setPosition(sf::Vector2f(6, 6));
    this->_window->draw(sprite);
    sf::Sprite previewSprite(this->_previewTexture);
    previewSprite.setScale(sf::Vector2f(0.8, 0.8));
    previewSprite.setPosition(sf::Vector2f(1635, 600));
    this->_window->draw(previewSprite);
}

void GraphicMode::drawButtons() {
    for (auto &pair : _buttons) {
        this->_window->draw(pair.second);
    }

    for (auto &text : _texts) {
        this->_window->draw(text);
    }
}

void GraphicMode::display() {
    this->_window->clear(sf::Color(200, 200, 200));
    this->drawButtons();
    this->drawImage();
    this->_window->display();
}

bool GraphicMode::isOpen() {
    while (this->_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            return false;
        }
    }
    return true;
}

void GraphicMode::closeWindow() {
    this->_window->close();
}

extern "C" {
    std::shared_ptr<GraphicMode> createInstance() {
        return std::make_shared<GraphicMode>();
    }
}
