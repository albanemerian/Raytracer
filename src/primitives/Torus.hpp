/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Torus
*/

#include "../../common/APrimitives.hpp"
#include "../../common/Ray.hpp"
#include <map>
#include <memory>
#include <optional>
#include <vector>

#ifndef TORUS_HPP_
    #define TORUS_HPP_

class Torus : public APrimitives {
    public:
        Torus();
        Torus(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
          const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> &graphSceneList);
        ~Torus() override;

        /* Setter */
        void setMajorRadius(float radius);
        void setMinorRadius(float radius);

        /* Getter */
        float getMajorRadius() const;
        float getMinorRadius() const;
        Type getType() const override;

        std::optional<double> distance(const Math::Ray &ray) const override;
        PixelInfo distanceInfo(const Math::Ray &ray) override;
        std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override;
        std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override;

    private:
        float _majorRadius;
        float _minorRadius;
        double _distance;

        std::tuple<double, double, double, double, double> computeQuarticCoefficients(const Math::Vector3D &localOrigin, const Math::Vector3D &localDir) const;
        double evaluateQuartic(double t, double a, double b, double c, double d_coef, double e) const;
        std::vector<double> findRootCandidates(double a, double b, double c, double d_coef, double e) const;
        double refineRoot(double t, double a, double b, double c, double d_coef, double e) const;
};

#endif /* !TORUS_HPP_ */
