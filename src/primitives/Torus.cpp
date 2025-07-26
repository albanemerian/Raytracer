/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Torus
*/

#include <map>
#include <memory>
#include <iostream>
#include <algorithm>
#include <string>
#include <optional>
#include <vector>
#include <cmath>
#include <tuple>
#include "Torus.hpp"
#include "../../common/Ray.hpp"

Torus::Torus() :
    APrimitives(), _majorRadius(0), _minorRadius(0), _distance(0) {
}

Torus::~Torus() {
}

Torus::Torus(std::shared_ptr<std::map<ValueType_t, ValueType>> map,
               const std::vector<std::shared_ptr<std::map<ValueType_t,
               ValueType>>> &graphSceneList)
    : APrimitives(map, graphSceneList) {

    if (map->find(ValueType_t::COLOR) != map->end()) {
        auto colorVector = std::get<Math::Vector3D>(
            map->find(ValueType_t::COLOR)->second);
        _color = Color();
        _color = Math::Vector3D(colorVector.getX(),
            colorVector.getY(),
            colorVector.getZ());
    } else {
        _color = Math::Vector3D(0, 0, 0);
    }

    auto it = map->find(ValueType_t::MAJOR_RADIUS);
    if (it != map->end()) {
        _majorRadius = std::get<float>(it->second);
    } else {
        _majorRadius = 1.0f;
    }

    it = map->find(ValueType_t::MINOR_RADIUS);
    if (it != map->end()) {
        _minorRadius = std::get<float>(it->second);
    } else {
        _minorRadius = 0.5f;
    }

    _majorRadius *= scale;
    _minorRadius *= scale;
    _distance = 0;
}

void Torus::setMajorRadius(float radius) {
    _majorRadius = radius;
}

void Torus::setMinorRadius(float radius) {
    _minorRadius = radius;
}

float Torus::getMajorRadius() const {
    return _majorRadius;
}

float Torus::getMinorRadius() const {
    return _minorRadius;
}

Type Torus::getType() const {
    return Type::TORUS;
}

std::tuple<double, double, double, double, double>
    Torus::computeQuarticCoefficients(const Math::Vector3D &localOrigin,
    const Math::Vector3D &localDir) const {
    double R = static_cast<double>(_majorRadius);
    double r = static_cast<double>(_minorRadius);
    double Rsq = R * R;
    double rsq = r * r;

    double ox = localOrigin.getX();
    double oy = localOrigin.getY();
    double oz = localOrigin.getZ();
    double dx = localDir.getX();
    double dy = localDir.getY();
    double dz = localDir.getZ();

    double dDotD = (dx * dx) + (dy * dy) + (dz * dz);
    double oDotD = (ox * dx) + (oy * dy) + (oz * dz);
    double oDotO = (ox * ox) + (oy * oy) + (oz * oz);

    double d_xz_sq = (dx * dx) + (dz * dz);
    double o_xz_sq = (ox * ox) + (oz * oz);
    double o_d_xz = (ox * dx) + (oz * dz);

    double k = oDotO + Rsq - rsq;
    double fourRsq = 4.0 * Rsq;

    double a = dDotD * dDotD;
    double b = 4.0 * dDotD * oDotD;
    double c = 2.0 * dDotD * k + 4.0 * oDotD * oDotD - fourRsq * d_xz_sq;
    double d_coef = 4.0 * oDotD * k - 2.0 * fourRsq * o_d_xz;
    double e = k*k - fourRsq * o_xz_sq;

    return {a, b, c, d_coef, e};
}

double Torus::evaluateQuartic(double t, double a, double b,
    double c, double d_coef, double e) const {
    double t2 = t * t;
    double t3 = t2 * t;
    double t4 = t3 * t;
    return a*t4 + b*t3 + c*t2 + d_coef*t + e;
}

std::vector<double> Torus::findRootCandidates(double a, double b, double c,
    double d_coef, double e) const {
    const double tMin = 0.001;
    const double tMax = 100.0;
    std::vector<double> candidateTs;

    const int numSamples = 100;
    const double step = (tMax - tMin) / numSamples;
    double prevValue = 0.0;
    bool prevValueComputed = false;

    for (int i = 0; i <= numSamples; i++) {
        double t = tMin + i * step;
        double value = evaluateQuartic(t, a, b, c, d_coef, e);

        if (prevValueComputed && ((prevValue < 0 && value > 0) ||
            (prevValue > 0 && value < 0))) {
            double ta = t - step;
            double tb = t;
            const int maxBisectionSteps = 10;
            for (int bisectionStep = 0; bisectionStep < maxBisectionSteps;
                bisectionStep++) {
                double tm = (ta + tb) / 2.0;
                double valueM = evaluateQuartic(tm, a, b, c, d_coef, e);

                if ((valueM < 0 && value > 0) || (valueM > 0 && value < 0)) {
                    ta = tm;
                } else {
                    tb = tm;
                }
            }

            double candidate = (ta + tb) / 2.0;
            if (candidate > tMin) {
                candidateTs.push_back(candidate);
            }
        }
        prevValue = value;
        prevValueComputed = true;
    }

    std::sort(candidateTs.begin(), candidateTs.end());
    return candidateTs;
}

double Torus::refineRoot(double t, double a, double b, double c,
    double d_coef, double e) const {
    const double tMin = 0.001;
    const double tMax = 100.0;
    const int maxIterations = 20;
    const double epsilon = 1e-6;

    for (int i = 0; i < maxIterations; ++i) {
        double t2 = t * t;
        double t3 = t2 * t;
        double t4 = t3 * t;

        double f = a*t4 + b*t3 + c*t2 + d_coef*t + e;
        double df = 4*a*t3 + 3*b*t2 + 2*c*t + d_coef;

        if (std::abs(df) < 1e-10) {
            break;
        }

        double nextT = t - f / df;
        if (std::abs(nextT - t) < epsilon) {
            t = nextT;
            break;
        }

        if (nextT >= tMin && nextT <= tMax) {
            t = nextT;
        } else {
            break;
        }
    }
    return t;
}

std::optional<double> Torus::distance(const Math::Ray &ray) const {
    Math::Vector3D localOrigin = _rotation.inverseRotate(
        ray.getOrigin() - _position);
    Math::Vector3D localDir = _rotation.inverseRotate(
        ray.getDirection().normalize());
    auto [a, b, c, d_coef, e] = computeQuarticCoefficients(
        localOrigin, localDir);
    std::vector<double> candidateTs = findRootCandidates(a, b, c, d_coef, e);
    const double tMin = 0.001;
    for (double t : candidateTs) {
        if (t < tMin) {
            continue;
        }

        t = refineRoot(t, a, b, c, d_coef, e);
        double finalValue = evaluateQuartic(t, a, b, c, d_coef, e);

        if (std::abs(finalValue) < 0.1) {
            return t;
        }
    }
    return std::nullopt;
}

PixelInfo Torus::distanceInfo(const Math::Ray &ray) {
    PixelInfo pixelInfo;
    Math::Ray scaledRay = computeScaledRay(ray);

    auto t = distance(scaledRay);
    if (!t.has_value()) {
        pixelInfo._isHit = false;
        return pixelInfo;
    }

    Math::Point3D intersection = scaledRay.getOrigin() +
        scaledRay.getDirection().normalize() * t.value();

    Math::Point3D worldIntersection = Math::Point3D(intersection * _scales);

    Math::Vector3D normal = getNormal(
        worldIntersection).value_or(Math::Vector3D(0, 0, 0));

    pixelInfo._isHit = true;
    pixelInfo._distance = t.value();
    pixelInfo._pos = worldIntersection + _position;
    pixelInfo._normalizedVector = normal.normalize();
    pixelInfo._color = _color;

    if (material != nullptr) {
        pixelInfo._color = material->applyMaterial
            (pixelInfo, 0.0f, 0.0f, *this);
    }

    return pixelInfo;
}

std::optional<Math::Point3D> Torus::getIntersection(const Math::Ray &ray)
    const {
    auto t = distance(ray);

    if (t.has_value()) {
        Math::Point3D intersection = ray.getOrigin() +
            ray.getDirection().normalize() * t.value();
        return intersection;
    }
    return std::nullopt;
}

std::optional<Math::Vector3D> Torus::getNormal(const Math::Point3D &point)
    const {
    Math::Vector3D localPoint = _rotation.inverseRotate(point - _position);
    Math::Vector3D projectedPoint(localPoint.getX(), 0, localPoint.getZ());
    float projectedLength = projectedPoint.length();

    if (projectedLength < 1e-6) {
        return Math::Vector3D(0, localPoint.getY() > 0 ? 1 : -1, 0);
    }

    Math::Vector3D toProjectedCenter = projectedPoint.normalize();
    Math::Vector3D circleCenterOnMajorCircle =
        toProjectedCenter * _majorRadius;
    Math::Vector3D normal = localPoint - circleCenterOnMajorCircle;

    return _rotation.rotate(normal.normalize());
}

extern "C" {
    std::shared_ptr<IPrimitives>createPrimitive(std::shared_ptr<std::map
        <ValueType_t, ValueType>> map,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>> &graphSceneList) {
        return std::make_shared<Torus>(map, graphSceneList);
    }

    ObjectType getType() {
        return ObjectType::TYPE_PRIMITIVE;
    }

    std::string getName() {
        return "torus";
    }
}
