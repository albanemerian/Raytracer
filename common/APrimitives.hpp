/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** APrimitives
*/

#include <memory>
#include <map>
#include <string>
#include <vector>

#include "IPrimitives.hpp"
#include "ValueType.hpp"
#include "material/IMaterial.hpp"
#include "ILight.hpp"


#ifndef APRIMITIVES_HPP_
#define APRIMITIVES_HPP_

class APrimitives : public IPrimitives {
    public:
        APrimitives() : _position(0, 0, 0), scale(1), material(nullptr),
            _color(-1, -1, -1), _scales(1, 1, 1), _invScales(1, 1, 1), _graph("") {}
        APrimitives(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>
            &graphSceneList);
        virtual ~APrimitives() = default;

        /*Method */
        virtual PixelInfo distanceInfo(const Math::Ray &ray) = 0;
        virtual std::optional<double> distance(const Math::Ray &ray) const = 0;
        virtual Type getType() const override = 0;
        Math::Ray computeScaledRay(const Math::Ray &ray) const override;

        /* Getter */
        Math::Point3D getPosition() const override { return _position; }
        Math::Rot3D getRotation() const override { return _rotation; }
        float getScale() const override { return scale; }
        std::shared_ptr<IMaterial> getMaterial() const override { return material; }
        Math::Vector3D getInvScales() const { return _invScales; }

        /* Setter */
        void setPosition(const Math::Point3D &newPosition) override { _position = newPosition; }
        void setRotation(const Math::Rot3D &newRotation) override { _rotation = newRotation; }
        void setScale(const float newScale) override {
            scale = newScale;
            computeInvScales();
        }
        void setMaterial(std::shared_ptr<IMaterial> newMaterial) override { material = newMaterial; }

        /* Sub Functions */
        void getPos(std::shared_ptr<std::map<ValueType_t,
            ValueType>> map);
        void getRot(std::shared_ptr<std::map<ValueType_t,
                ValueType>> map);
        void getCol(std::shared_ptr<std::map<ValueType_t,
            ValueType>> map);
        void getScales(std::shared_ptr<std::map<ValueType_t,
            ValueType>> map);
        void getGraph(std::shared_ptr<std::map<ValueType_t,
            ValueType>> map, const std::vector<std::shared_ptr<std::map<ValueType_t,
            ValueType>>> &graphSceneList);
        void computeInvScales();

        /* Graph Method */
        void getGraphScale(const std::shared_ptr<std::map<ValueType_t, ValueType>> &graph);
        void getPosGraph(const std::shared_ptr<std::map<ValueType_t,
            ValueType>> &graph);
        void getRotGraph(const std::shared_ptr<std::map<ValueType_t,
            ValueType>> &graph);

    protected:
        Math::Point3D _position;
        Math::Rot3D _rotation;
        float scale;
        std::shared_ptr<IMaterial> material;
        Color _color;
        Math::Vector3D _scales;
        Math::Vector3D _invScales;
        std::string _graph;
};

#endif /* !APRIMITIVES_HPP_ */
