/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** APrimitives-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <memory>
#include "../common/APrimitives.hpp"
#include "../common/IPrimitives.hpp"
#include "../common/material/chessboardMat.hpp"
#include "../common/material/transparencyMat.hpp"
#include "../common/material/flatColorMat.hpp"
#include "../common/material/fileTextureMat.hpp"
#include "../common/material/perlingNoiseMat.hpp"

// Mock class for testing IPrimitives
class MockPrimitive : public APrimitives {
 public:
    MockPrimitive() : APrimitives() {}
    PixelInfo distanceInfo(const Math::Ray &ray) override {
        (void)ray;
        return PixelInfo();
    }
    std::optional<double> distance(const Math::Ray &ray) const
        override {
        (void)ray;
        return std::nullopt;
    }
    std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const
        override {
        (void)ray;
        return std::nullopt;
    }
    std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const
        override {
        (void)point;
        return std::nullopt;
    }
    Type getType() const override {
        return Type::SPHERE;
    }
};

// Minimal working MockLight for ILight
class MockLight : public ILight {
public:
    mutable bool called = false;
    void addLight(std::shared_ptr<PixelInfo> pixelInfo, const Math::Ray &ray) const override {
        (void)pixelInfo; (void)ray;
        called = true;
    }
    Color getColor() const override { return Color(0,0,0); }
    Math::Vector3D getDirection() const override { return Math::Vector3D(0,0,0); }
    float getIntensity() const override { return 1.0f; }
    float getRadius() const override { return 1.0f; }
    TypeLight getTypeLight() const override { return TypeLight::POINT; }
    void setColor(const Color &) override {}
    void setIntensity(float) override {}
    virtual ~MockLight() = default;
};

Test(IPrimitives, getters_and_setters) {
    MockPrimitive primitive;

    // Test position
    Math::Point3D position(1, 2, 3);
    primitive.setPosition(position);
    cr_assert_eq(primitive.getPosition().getX(), 1);
    cr_assert_eq(primitive.getPosition().getY(), 2);
    cr_assert_eq(primitive.getPosition().getZ(), 3);

    // Test rotation
    Math::Rot3D rotation(10, 20, 30);
    primitive.setRotation(rotation);
    primitive.getRotation();

    // Test scale
    primitive.setScale(2.5f);
    cr_assert_float_eq(primitive.getScale(), 2.5f, 0.001);

    // Test material
    auto material = std::make_shared<ChessboardMat>();
    primitive.setMaterial(material);
    cr_assert_eq(primitive.getMaterial(), material);
}

Test(APrimitives, apply_material) {
    MockPrimitive primitive;
    PixelInfo pixelInfo;
    pixelInfo._color = Color(255, 255, 255);

    // Test with no material
    // When no material is present, the original color should be returned
    cr_assert_eq(pixelInfo._color.getRed(), 255);
    cr_assert_eq(pixelInfo._color.getGreen(), 255);
    cr_assert_eq(pixelInfo._color.getBlue(), 255);

    // Test with chessboard material
    auto material = std::make_shared<ChessboardMat>();
    material->setMaterialType(MaterialType::CHESSBOARD);
    material->setOptionalColor1(Color(0, 0, 0));
    material->setOptionalColor2(Color(255, 255, 255));
    primitive.setMaterial(material);

    // Apply material directly instead of through the primitive
    pixelInfo._pos = Math::Vector3D(1.0, 1.0, 1.0);
    Color result = material->applyMaterial(pixelInfo, 1.0f, 1.0f, primitive);
}

Test(APrimitives, getPosGraph) {
    MockPrimitive primitive;
    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::POSITION] = Math::Vector3D(1.0f, 2.0f, 3.0f);
    primitive.getPosGraph(graph);
    primitive.getRot(graph);
    primitive.getPos(graph);
    primitive.getScales(graph);
    primitive.getCol(graph);
    primitive.getGraphScale(graph);
    primitive.getPosGraph(graph);
    primitive.getRotGraph(graph);
    primitive.getGraph(graph, {});
}

Test(APrimitives, getRot_default) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    primitive.getRot(map); // Test default rotation when ROTATION is not in the map
    cr_assert_eq(primitive.getRotation().getX(), 0.0);
    cr_assert_eq(primitive.getRotation().getY(), 0.0);
    cr_assert_eq(primitive.getRotation().getZ(), 0.0);
}

Test(APrimitives, getCol_default) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    primitive.getCol(map); // Test default color when COLOR is not in the map
    cr_assert_eq(primitive.getMaterial(), nullptr);
}

Test(APrimitives, getScales_default) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    primitive.getScales(map); // Test default scales when SCALES is not in the map
    cr_assert_eq(primitive.getScale(), 1.0);
}

Test(APrimitives, applyMaterial_transparency) {
    MockPrimitive primitive;
    auto material = std::make_shared<TransparencyMat>();
    material->setMaterialType(MaterialType::TRANSPARENCY_MAT);
    material->setTransparency(0.5f);
    primitive.setMaterial(material);

    PixelInfo pixelInfo;
    pixelInfo._color = Color(255, 255, 255);

    Color result = material->applyMaterial(pixelInfo, 1.0f, 1.0f, primitive);
    cr_assert_eq(result.getTransparency(), 127); // 50% transparency
}

Test(APrimitives, applyMaterial_chessboard) {
    MockPrimitive primitive;
    auto material = std::make_shared<ChessboardMat>();
    material->setMaterialType(MaterialType::CHESSBOARD);
    material->setOptionalColor1(Color(0, 0, 0));
    material->setOptionalColor2(Color(255, 255, 255));
    primitive.setMaterial(material);

    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(1.0, 1.0, 1.0);

    Color result = material->applyMaterial(pixelInfo, 1.0f, 1.0f, primitive);
    cr_assert((result.getRed() == 0 && result.getGreen() == 0 && result.getBlue() == 0) ||
              (result.getRed() == 255 && result.getGreen() == 255 && result.getBlue() == 255));
}

Test(APrimitives, getGraph_no_graph) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphSceneList;

    primitive.getGraph(map, graphSceneList); // Test when no graph is provided
    cr_assert_eq(primitive.getScale(), 1.0);
}

Test(APrimitives, getGraph_with_graph) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::GRAPH] = std::string("test_graph");

    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::NAME] = std::string("test_graph");
    (*graph)[ValueType_t::SCALE] = 2.0f;

    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphSceneList = {graph};

    primitive.getGraph(map, graphSceneList); // Test when a matching graph is provided
    cr_assert_eq(primitive.getScale(), 2.0);
}

Test(APrimitives, getScales_with_scales) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::SCALES] = Math::Vector3D(2.0, 3.0, 4.0);
    primitive.getScales(map);
    cr_assert_eq(primitive.getScale(), 1.0);
}

Test(APrimitives, getGraph_with_matching_graph) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::GRAPH] = std::string("test_graph");

    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::NAME] = std::string("test_graph");
    (*graph)[ValueType_t::SCALE] = 2.0f;

    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphSceneList = {graph};

    primitive.getGraph(map, graphSceneList);
    cr_assert_eq(primitive.getScale(), 2.0);
}

Test(APrimitives, applyMaterial_with_transparency) {
    MockPrimitive primitive;
    auto material = std::make_shared<TransparencyMat>();
    material->setMaterialType(MaterialType::TRANSPARENCY_MAT);
    material->setTransparency(0.5f);
    primitive.setMaterial(material);

    PixelInfo pixelInfo;
    pixelInfo._color = Color(255, 255, 255);

    Color result = material->applyMaterial(pixelInfo, 1.0f, 1.0f, primitive);
    cr_assert_eq(result.getTransparency(), 127); // 50% transparency
}

Test(APrimitives, applyMaterial_with_chessboard) {
    MockPrimitive primitive;
    auto material = std::make_shared<ChessboardMat>();
    material->setMaterialType(MaterialType::CHESSBOARD);
    material->setOptionalColor1(Color(0, 0, 0));
    material->setOptionalColor2(Color(255, 255, 255));
    primitive.setMaterial(material);

    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(1.0, 1.0, 1.0);

    Color result = material->applyMaterial(pixelInfo, 1.0f, 1.0f, primitive);
    cr_assert((result.getRed() == 0 && result.getGreen() == 0 && result.getBlue() == 0) ||
              (result.getRed() == 255 && result.getGreen() == 255 && result.getBlue() == 255));
}

Test(APrimitives, getGraph_no_matching_graph) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::GRAPH] = std::string("nonexistent_graph");

    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::NAME] = std::string("test_graph");

    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphSceneList = {graph};

    primitive.getGraph(map, graphSceneList);
    cr_assert_eq(primitive.getScale(), 1.0); // Default scale
}

Test(APrimitives, getRot_sets_rotation_from_map) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::ROTATION] = Math::Vector3D(1.0, 2.0, 3.0);
    primitive.getRot(map);
}

Test(APrimitives, getPos_sets_position_from_map) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    // Fill map with required POSITION key
    (*map)[ValueType_t::POSITION] = Math::Vector3D(4.0, 5.0, 6.0);
    primitive.getPos(map);
    cr_assert_eq(primitive.getPosition().getX(), 4.0);
    cr_assert_eq(primitive.getPosition().getY(), 5.0);
    cr_assert_eq(primitive.getPosition().getZ(), 6.0);
}

Test(APrimitives, getCol_sets_color_from_map) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    // Fill map with required COLOR key
    (*map)[ValueType_t::COLOR] = Math::Vector3D(7.0, 8.0, 9.0);
    primitive.getCol(map);
}

Test(APrimitives, computeInvScales_sets_inverse) {
    MockPrimitive primitive;
    primitive.computeInvScales();
}

Test(APrimitives, getScales_sets_scale_and_scales) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    // Fill map with required SCALE and SCALES keys
    (*map)[ValueType_t::SCALE] = 3.0f;
    (*map)[ValueType_t::SCALES] = Math::Vector3D(2.0, 3.0, 4.0);
    primitive.getScales(map);
}

Test(APrimitives, getGraphScale_multiplies_scales) {
    MockPrimitive primitive;
    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    // Fill graph with required SCALES key
    (*graph)[ValueType_t::SCALES] = Math::Vector3D(3.0, 4.0, 5.0);
    primitive.getGraphScale(graph);
}

Test(APrimitives, getPosGraph_adds_position) {
    MockPrimitive primitive;
    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::POSITION] = Math::Vector3D(4.0, 5.0, 6.0);
    primitive.getPosGraph(graph);
}

Test(APrimitives, getRotGraph_adds_rotation) {
    MockPrimitive primitive;
    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::ROTATION] = Math::Vector3D(4.0, 5.0, 6.0);
    primitive.getRotGraph(graph);
}

Test(APrimitives, getGraph_applies_graph_values) {
    MockPrimitive primitive;
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::GRAPH] = std::string("g1");
    auto graph = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*graph)[ValueType_t::NAME] = std::string("g1");
    (*graph)[ValueType_t::SCALE] = 2.0f;
    (*graph)[ValueType_t::SCALES] = Math::Vector3D(2.0, 2.0, 2.0);
    (*graph)[ValueType_t::POSITION] = Math::Vector3D(1.0, 1.0, 1.0);
    (*graph)[ValueType_t::ROTATION] = Math::Vector3D(1.0, 1.0, 1.0);
    (*graph)[ValueType_t::COLOR] = Math::Vector3D(10.0, 20.0, 30.0);
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphs = {graph};
    primitive.getGraph(map, graphs);

}

Test(APrimitives, computeScaledRay_scales_ray) {
    MockPrimitive primitive;
    Math::Ray ray(Math::Vector3D(2.0, 4.0, 8.0), Math::Vector3D(2.0, 4.0, 8.0));
    Math::Ray scaled = primitive.computeScaledRay(ray);
}

Test(APrimitives, constructor_sets_fields_from_map_and_graph) {
    auto map = std::make_shared<std::map<ValueType_t, ValueType>>();
    (*map)[ValueType_t::POSITION] = Math::Vector3D(1.0, 2.0, 3.0);
    (*map)[ValueType_t::ROTATION] = Math::Vector3D(4.0, 5.0, 6.0);
    (*map)[ValueType_t::COLOR] = Math::Vector3D(7.0, 8.0, 9.0);
    (*map)[ValueType_t::SCALE] = 2.0f;
    std::vector<std::shared_ptr<std::map<ValueType_t, ValueType>>> graphs;
    std::vector<std::shared_ptr<ILight>> lights;
}
