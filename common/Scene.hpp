/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** IScene
*/

#include <memory>
#include <vector>
#include "Camera.hpp"
#include "APrimitives.hpp"
#include "Graphs.hpp"

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

class Scene {
    public:
        Scene();
        Scene(std::shared_ptr<Camera>, std::vector<std::shared_ptr<IPrimitives>>);
        ~Scene();

        /* Getter */
        std::shared_ptr<Camera> getCamera() const;
        std::shared_ptr<GraphsNodePrimitive> getPrimitives() const;
        std::shared_ptr<GraphsNodeLight> getLights() const;
        int camereaWidth() const;
        int camereaHeight() const;
        int cameraAntiAliasing() const;
        float getAmbientLight() const;

        /* Setter */
        void setCamera(std::shared_ptr<Camera> camera);
        void setPrimitives(const std::vector<std::shared_ptr<IPrimitives>> &primitives);
        void setLights(const std::vector<std::shared_ptr<ILight>> &lights);
        void setAntiAliasing(int antiAliasing);
      //  void setAmbientLight(float ambientLight);

       private:
        std::shared_ptr<Camera> _camera;
        std::vector<std::shared_ptr<IPrimitives>> _primTemp;
       // std::vector<std::shared_ptr<IPrimitives>> _primitives;
        std::shared_ptr<GraphsNodePrimitive> _primitives;
        std::shared_ptr<GraphsNodeLight> _lights;
      //  std::vector<std::shared_ptr<ILight>> _lights;
        float _ambientLight;
};

#endif /* !ISCENE_HPP_ */
