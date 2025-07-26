/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Raytracer
*/

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <optional>

#include "../common/APrimitives.hpp"
#include "../common/ValueType.hpp"

#include "../common/Error.hpp"
#include "../common/Image.hpp"
#include "../common/Camera.hpp"
#include "../common/Scene.hpp"
#include "../lib/DLLoader.hpp"
#include "../lib/ILoader.hpp"
#include "factory/FactoryManager.hpp"
#include "../lib/SFML/GraphicMode.hpp"
#include "../common/Graphs.hpp"

#ifndef RAYTRACER_HPP_
#define RAYTRACER_HPP_

struct InfoPixelDisplay {
      double distance;
      Color color;
      float transparency;
};


class Raytracer {
      public:
         Raytracer();
         ~Raytracer();

         /* Getter */
         std::string getSceneFile() const;
         std::string getOutputFile() const;
         std::string getOutputFormat() const;
         std::shared_ptr<Image> getImage() const;
         bool getGraphicMode() const;
         bool isDebug() const;
         Scene getScene() const;

         /* Setter */
         void setSceneFile(std::string sceneFile);
         void setOutputFile(std::string outputFile);
         void setOutputFormat(std::string outputFormat);
         void setImage(std::shared_ptr<Image> Image);
         void setScene(Scene scene);
         bool setGraphicMode();

         /* Methods */
         void writeToFilePPM(std::string fileName);
         void parseCmd(int ac, char **av);
         void LoadAllformlibs(const std::vector<std::shared_ptr<std::map
               <ValueType_t, ValueType>>>& objectsConfig);
         std::optional<PixelInfo> getClosestPrimitiveHit(const Math::Ray &ray) const;


         /* Image Method */
         void InitParams();
         void setScene();
         void StartImage();
         std::vector<InfoPixelDisplay> calculatePixel(const Math::Ray& ray);
         void averageImages(const std::vector<std::shared_ptr<Image>>& images);
         void loopThruType();

         /* New image processing methods */
         void initializeScene();
         Color computePixelWithAntiAliasing(int x, int y, uint32_t& state);
         Color traceRaySingleSample(double u, double v, uint32_t& state);
         void renderConsoleMode(const Color& backgroundColor);
         void finalizeRendering();
         void debugPrimitiveGraph();
         void applyLights(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const;

         /* Graphic mode method */
         void renderGraphicMode(int width, int height, std::shared_ptr<int> pixelCount);
         void displayGraphicMode(std::shared_ptr<int> pixelCount, int totalPixels);
         void startPreveiwMode(int width, int height,
            std::shared_ptr<int> pixelCount, int totalPixels);
         void renderPreviewImage();
   protected:
   private:
      bool graphicMode;
      bool debugMode;
      std::string _scenefile;
      std::string _outputfile;
      std::string _outputformat;
      int numRenders;
      std::shared_ptr<Image> image;
      Scene _scene;
      FactoryManager _factoryManager;
      std::shared_ptr<GraphicMode> _display;
      int _width;
      int _height;
      bool previewRendered = false;
      sf::Image previewImage;
   public:
};

#endif /* !RAYTRACER_HPP_ */
