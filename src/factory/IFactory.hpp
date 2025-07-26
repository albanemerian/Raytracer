#ifndef IFACTORY_HPP_
#define IFACTORY_HPP_

#include <memory>
#include <string>
#include <map>
#include "../../common/ValueType.hpp"
#include "../../common/ILight.hpp"

template <typename T>
class IFactory {
public:
    virtual ~IFactory() = default;
    virtual std::shared_ptr<T> create(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>>& graphSceneList,
        std::vector<std::shared_ptr<IPrimitives>> primitivesList) = 0;

    virtual std::shared_ptr<T> createSimple(const std::string& type,
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t,
        ValueType>>>& graphSceneList) = 0;

    virtual void registerCreator(
        const std::string& type,
        std::function<std::shared_ptr<T>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t,
            ValueType>>>&)> creator) = 0;
    virtual void registerCreatorLight(
        const std::string& type,
        std::function<std::shared_ptr<T>(
            std::shared_ptr<std::map<ValueType_t, ValueType>>,
            const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>&,
        std::vector<std::shared_ptr<IPrimitives>>)> creator) = 0;
    virtual bool loadPlugin(const std::string& path) = 0;
};

#endif /* !IFACTORY_HPP_ */

