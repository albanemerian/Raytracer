/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectFactory
*/

#ifndef OBJECTFACTORY_HPP_
#define OBJECTFACTORY_HPP_

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "ConfigNode.hpp"
#include "PropertyTypes.hpp"
#include "ObjectErrorHandling.hpp"

class ObjectConstructor {
 public:
    ObjectConstructor();
    ~ObjectConstructor();

        void createObject(const ConfigNode& node);
        void createObjects(const ConfigNode& node);
        bool verifyObjectValidity(const ConfigNode& node, const std::string& objectName);
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&
            getObjects() const;

        void printObjectMap() const;
        bool createMaterials(const ConfigNode &node);

    private:
        void fillObject(const ConfigNode& node,
            std::shared_ptr<std::map<ValueType_t, ValueType>> object);
        void handleSimpleValue(std::shared_ptr<std::map<ValueType_t,
                ValueType>> object,
                const ValueType_t& key,
                const ValueType& value,
                ValueDataType dataType);
        void handleVector2DValue(std::shared_ptr<std::map<ValueType_t,
                ValueType>> object, const ValueType_t& key,
                const ConfigNode& node,
                const std::vector<std::string>& components,
                ValueDataType dataType);
        void handleVector3DValue(std::shared_ptr<std::map<ValueType_t, ValueType>> object,
                const ValueType_t& key,
                const ConfigNode& node,
                const std::vector<std::string>& components,
                ValueDataType dataType);
        ValueType convertValue(const ValueType& value, ValueDataType dataType);

        void initShapeDefinitions();

        ObjectErrorHandling _errorHandler;
        std::map<std::string, PropertyConfig> _propertyTypeMap;
        std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> _objects;
        std::vector<ShapeDefinition> _shapeDefinitions;

};

#endif /* !OBJECTFACTORY_HPP_ */
