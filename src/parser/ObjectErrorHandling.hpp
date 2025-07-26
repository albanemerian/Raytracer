/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** ObjectErrorHandling
*/

#ifndef OBJECTERRORHANDLING_HPP_
#define OBJECTERRORHANDLING_HPP_

#include <iostream>
#include <map>
#include <variant>
#include <memory>
#include "ConfigNode.hpp"
#include "PropertyTypes.hpp"
#include "../../common/ValueType.hpp"

class ObjectErrorHandling {
    public:
        ObjectErrorHandling();
        ~ObjectErrorHandling();

        bool checkArrayValidity(const ConfigNode& node,
            const std::string& objectName);
        bool checkGroupValidity(const ConfigNode& node,
            const std::string& objectName);
        bool checkListValidity(const ConfigNode& node,
            const std::string& objectName);
        bool checkValueValidity(const ConfigNode& node,
            const std::string& objectName);
        bool verifyObjectValidity(const ConfigNode& node,
            const std::string& objectName);

        void setShapeDefinitions
            (std::vector<ShapeDefinition> shapeDefinitions);
        void setPropertyTypeMap(const std::map<std::string,
                                PropertyConfig>& propertyTypeMap);

    protected:
    private:
        std::vector<ShapeDefinition> _shapeDefinitions;
        std::map<std::string, PropertyConfig> _propertyTypeMap;

        std::string getDataTypeName(ValueDataType type) const;
        std::shared_ptr<const ShapeDefinition> getShapeDefinition
            (const std::string& objectName) const;

        bool isParameterValid(const std::string& parameter,
                                const std::string& objectName) const;
        bool isParameterMandatory(const std::string& parameter,
                                const std::string& objectName) const;
        bool isParameterOptional(const std::string& parameter,
                                const std::string& objectName) const;
        bool checkParameterType(const std::string& parameter,
                                const ConfigNode& node) const;

        bool isValueTypeValid(const ValueType& value,
            ValueDataType expectedType) const;
        bool checkSimpleValueValidity(const ConfigNode& node,
            const std::string &parameter, const PropertyConfig& config) const;
        bool checkVector2DValueValidity(const ConfigNode& node,
            const std::string &parameter, const PropertyConfig& config) const;
        bool checkVector3DValueValidity(const ConfigNode& node,
            const std::string &parameter, const PropertyConfig& config) const;

        bool checkMandatoryParameters(const ConfigNode& node,
            const std::string& objectName) const;
        bool checkOptionalParameters(const ConfigNode& node,
            const std::string& objectName) const;
        bool checkUnknownParameters(const ConfigNode& node,
            const std::string& objectName) const;

};

#endif /* !OBJECTERRORHANDLING_HPP_ */
