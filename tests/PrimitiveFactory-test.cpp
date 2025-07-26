/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** PrimitiveFactory-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../src/factory/PrimitiveFactory.hpp"
#include "../common/material/fileTextureMat.hpp"
#include "../common/material/flatColorMat.hpp"
#include "../common/material/chessboardMat.hpp"
#include "../common/material/transparencyMat.hpp"
#include "../common/material/perlingNoiseMat.hpp"
#include <memory>

// Mock concrete implementation of APrimitives for testing
class MockPrimitive : public APrimitives {
public:
    MockPrimitive() : APrimitives() {}
    
    PixelInfo distanceInfo(const Math::Ray &ray) override {
        (void)ray;
        return PixelInfo();
    }
    
    std::optional<double> distance(const Math::Ray &ray) const override {
        (void)ray;
        return std::make_optional(1.0);
    }
    
    std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override {
        (void)ray;
        return std::make_optional(Math::Point3D(0, 0, 0));
    }
    
    std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override {
        (void)point;
        return std::make_optional(Math::Vector3D(0, 1, 0));
    }
    
    Type getType() const override {
        return Type::SPHERE;
    }
};

void redirect_primitivefactory_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

// Test PrimitiveFactory constructor
Test(PrimitiveFactory, constructor, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    cr_assert(true, "PrimitiveFactory constructor should not crash");
}

// Test setTexturePathIfNeeded method
Test(PrimitiveFactory, set_texture_path_if_needed, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Create a primitive with a file texture material
    auto primitive = std::make_shared<MockPrimitive>();
    auto material = std::make_shared<FileTextureMat>();
    primitive->setMaterial(material);
    
    // Create config with path
    auto config = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*config)[ValueType_t::PATH] = std::string("test_texture.png");
    
    // Test setting texture path
    factory.setTexturePathIfNeeded(primitive, config);
    
    // Can't easily verify the result, but the method should not crash
    cr_assert(true, "setTexturePathIfNeeded should not crash");
}

// Test create method
Test(PrimitiveFactory, create_method, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Create a config for a primitive
    auto config = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*config)[ValueType_t::POSITION] = Math::Vector3D(0.0, 0.0, 0.0);
    (*config)[ValueType_t::RADIUS] = 1.0f;
    
    // Test creating with a type that doesn't exist - should return nullptr
    auto primitive = factory.create("nonexistent_type", config, {}, {});
    cr_assert_null(primitive, "Create with nonexistent type should return nullptr");
}

// Test createSimple method
Test(PrimitiveFactory, create_simple_method, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Create a config for a primitive
    auto config = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*config)[ValueType_t::POSITION] = Math::Vector3D(0.0, 0.0, 0.0);
    (*config)[ValueType_t::RADIUS] = 1.0f;
    
    // Test createSimple with a type that doesn't exist - should return nullptr
    auto primitive = factory.createSimple("nonexistent_type", config, {});
    cr_assert_null(primitive, "CreateSimple with nonexistent type should return nullptr");
}

// Test registerCreator and registerCreatorLight methods
Test(PrimitiveFactory, register_creators, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Register a simple creator
    factory.registerCreator("test_primitive", [](
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphList) {
            (void)config;
            (void)graphList;
            return std::make_shared<MockPrimitive>();
    });
    
    // Register a creator with light support
    factory.registerCreatorLight("test_primitive_light", [](
        std::shared_ptr<std::map<ValueType_t, ValueType>> config,
        const std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>>& graphList,
            std::vector<std::shared_ptr<IPrimitives>> primitivesList) {
            (void)config;
            (void)graphList;
            (void)primitivesList;
            return std::make_shared<MockPrimitive>();
    });
    
    // Create a simple config
    auto config = std::make_shared<std::map<ValueType_t, ValueType>>();
    
    // Test using the registered creators
    auto primitive1 = factory.createSimple("test_primitive", config, {});
    cr_assert_not_null(primitive1, "Should create primitive using registered creator");
    
    auto primitive2 = factory.create("test_primitive_light", config, {}, {});
    cr_assert_not_null(primitive2, "Should create primitive using registered light creator");
    
    // Test material handling in registerCreatorLight
    // Create a config with material
    auto configWithMaterial = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*configWithMaterial)[ValueType_t::MATERIAL] = std::string("flatColorMat");
    
    auto primitive3 = factory.create("test_primitive_light", configWithMaterial, {}, {});
    cr_assert_not_null(primitive3, "Should create primitive with material");
}

// Test loadPlugin and plugin-related methods
Test(PrimitiveFactory, load_plugin, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Test loading a non-existent plugin - should not crash
    bool result = factory.loadPlugin("nonexistent_plugin.so");
    cr_assert_eq(result, false, "Loading nonexistent plugin should return false");
}

// Test createMaterialByType method
Test(PrimitiveFactory, create_material_by_type, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Test creating materials of different types
    auto flatColor = factory.createMaterialByType(MaterialType::FLAT_COLOR);
    cr_assert_not_null(flatColor, "Should create FlatColorMat");
    cr_assert_eq(flatColor->getMaterialType(), MaterialType::FLAT_COLOR);
    
    auto transparency = factory.createMaterialByType(MaterialType::TRANSPARENCY_MAT);
    cr_assert_not_null(transparency, "Should create TransparencyMat");
    cr_assert_eq(transparency->getMaterialType(), MaterialType::TRANSPARENCY_MAT);
    
    auto chessboard = factory.createMaterialByType(MaterialType::CHESSBOARD);
    cr_assert_not_null(chessboard, "Should create ChessboardMat");
    cr_assert_eq(chessboard->getMaterialType(), MaterialType::CHESSBOARD);
    
    auto fileTexture = factory.createMaterialByType(MaterialType::FILE_TEXTURE_MAT);
    cr_assert_not_null(fileTexture, "Should create FileTextureMat");
    cr_assert_eq(fileTexture->getMaterialType(), MaterialType::FILE_TEXTURE_MAT);
    
    auto perlingNoise = factory.createMaterialByType(MaterialType::PERLING_NOISE_MAT);
    cr_assert_not_null(perlingNoise, "Should create PerlingNoiseMat");
    cr_assert_eq(perlingNoise->getMaterialType(), MaterialType::PERLING_NOISE_MAT);
    
    // Test default case with unknown material type
    auto unknown = factory.createMaterialByType(static_cast<MaterialType>(999));
    cr_assert_not_null(unknown, "Should create default material for unknown type");
    cr_assert_eq(unknown->getMaterialType(), MaterialType::FLAT_COLOR);
}

// Test createMaterial method
Test(PrimitiveFactory, create_material, .init = redirect_primitivefactory_stdout) {
    PrimitiveFactory factory;
    
    // Test creating materials by name
    auto flatColor = factory.createMaterial("flatColorMat");
    cr_assert_not_null(flatColor, "Should create material by name flatColorMat");
    cr_assert_eq(flatColor->getMaterialType(), MaterialType::FLAT_COLOR);
    
    // Test with unknown material name
    auto unknown = factory.createMaterial("nonexistent_material");
    cr_assert_null(unknown, "Should return nullptr for nonexistent material name");
}
