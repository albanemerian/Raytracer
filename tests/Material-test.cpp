/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** Material-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <memory>
#include "../common/material/AMaterial.hpp"
#include "../common/material/flatColorMat.hpp"
#include "../common/material/transparencyMat.hpp"
#include "../common/material/chessboardMat.hpp"
#include "../common/material/fileTextureMat.hpp"
#include "../common/material/perlingNoiseMat.hpp"
#include "../common/PixelInfo.hpp"
#include "../common/Color.hpp"
#include "../common/Vector3D.hpp"
#include "../common/APrimitives.hpp"

class MockPrimitive : public APrimitives {
public:
    MockPrimitive() : APrimitives() {}

    PixelInfo distanceInfo(const Math::Ray &ray) override {
        (void)ray;
        return PixelInfo();
    }

    std::optional<double> distance(const Math::Ray &ray) const override {
        (void)ray;
        return std::nullopt;
    }

    std::optional<Math::Point3D> getIntersection(const Math::Ray &ray) const override {
        (void)ray;
        return std::nullopt;
    }

    std::optional<Math::Vector3D> getNormal(const Math::Point3D &point) const override {
        (void)point;
        return std::nullopt;
    }

    Type getType() const override {
        return Type::SPHERE;
    }
};

class MockCylinderPrimitive : public MockPrimitive {
public:
    Type getType() const override {
        return Type::CYLINDER;
    }
};

class MockPlanePrimitive : public MockPrimitive {
public:
    Type getType() const override {
        return Type::PLANE;
    }
};

class MockConePrimitive : public MockPrimitive {
public:
    Type getType() const override {
        return Type::CONE;
    }
};

class MockTorusPrimitive : public MockPrimitive {
public:
    Type getType() const override {
        return Type::TORUS;
    }
};

Test(FlatColorMat, constructor) {
    FlatColorMat material;

    cr_assert_eq(material.getMaterialType(), MaterialType::FLAT_COLOR, "Material type should be FLAT_COLOR");
    cr_assert_float_eq(material.getTransparency(), 0.0f, 0.001f, "Default transparency should be 0.0f");
}

Test(FlatColorMat, apply_material) {
    FlatColorMat material;
    MockPrimitive primitive;


    Color color(255, 0, 0);
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0, 0, 0);
    PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));


    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);


    cr_assert_eq(result.getRed(), 255, "Red component should be 255");
    cr_assert_eq(result.getGreen(), 0, "Green component should be 0");
    cr_assert_eq(result.getBlue(), 0, "Blue component should be 0");
}



Test(FlatColorMat, apply_material_with_various_colors) {
    FlatColorMat material;
    MockPrimitive primitive;
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0, 0, 0);


    std::vector<Color> testColors = {
        Color(255, 0, 0),
        Color(0, 255, 0),
        Color(0, 0, 255),
        Color(255, 255, 0),
        Color(255, 0, 255),
        Color(0, 255, 255),
        Color(128, 128, 128)
    };

    for (const auto& color : testColors) {
        PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));
        Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);

        cr_assert_eq(result.getRed(), color.getRed(), "Red component should match");
        cr_assert_eq(result.getGreen(), color.getGreen(), "Green component should match");
        cr_assert_eq(result.getBlue(), color.getBlue(), "Blue component should match");
    }
}

Test(FlatColorMat, combine_with_lighting) {
    FlatColorMat material;
    MockPrimitive primitive;


    material.setAmbient(Math::Vector3D(0.1f, 0.1f, 0.1f));
    material.setDiffuse(Math::Vector3D(0.5f, 0.5f, 0.5f));
    material.setSpecular(Math::Vector3D(0.8f, 0.8f, 0.8f));
    material.setShininess(32.0f);


    Color baseColor(100, 150, 200);
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0, 0, 0);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));


    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);



    cr_assert_eq(result.getRed(), baseColor.getRed());
    cr_assert_eq(result.getGreen(), baseColor.getGreen());
    cr_assert_eq(result.getBlue(), baseColor.getBlue());


    cr_assert_float_eq(material.getAmbient().getX(), 0.1f, 0.001f);
    cr_assert_float_eq(material.getDiffuse().getX(), 0.5f, 0.001f);
    cr_assert_float_eq(material.getSpecular().getX(), 0.8f, 0.001f);
    cr_assert_float_eq(material.getShininess(), 32.0f, 0.001f);
}

Test(TransparencyMat, constructor) {
    TransparencyMat material;

    cr_assert_eq(material.getMaterialType(), MaterialType::TRANSPARENCY_MAT, "Material type should be TRANSPARENCY_MAT");
    cr_assert_float_eq(material.getTransparency(), 0.6f, 0.001f, "Default transparency should be 0.6f");
    cr_assert_float_eq(material.getRefractiveIndex(), 1.5f, 0.001f, "Default refractive index should be 1.5f");
}


Test(TransparencyMat, different_refractive_indices) {
    MockPrimitive primitive;

    Color color(100, 150, 200);
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0, 0, 0);
    PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));


    TransparencyMat airMaterial;
    airMaterial.setRefractiveIndex(1.0f);

    TransparencyMat waterMaterial;
    waterMaterial.setRefractiveIndex(1.33f);

    TransparencyMat glassMaterial;
    glassMaterial.setRefractiveIndex(1.5f);

    TransparencyMat diamondMaterial;
    diamondMaterial.setRefractiveIndex(2.42f);


    cr_assert_float_eq(airMaterial.getRefractiveIndex(), 1.0f, 0.001f,
                      "Air refractive index should be 1.0");
    cr_assert_float_eq(waterMaterial.getRefractiveIndex(), 1.33f, 0.001f,
                      "Water refractive index should be 1.33");
    cr_assert_float_eq(glassMaterial.getRefractiveIndex(), 1.5f, 0.001f,
                      "Glass refractive index should be 1.5");
    cr_assert_float_eq(diamondMaterial.getRefractiveIndex(), 2.42f, 0.001f,
                      "Diamond refractive index should be 2.42");


    Color airResult = airMaterial.applyMaterial(pixel, 1.0f, 1.0f, primitive);
    Color waterResult = waterMaterial.applyMaterial(pixel, 1.0f, 1.0f, primitive);
    Color glassResult = glassMaterial.applyMaterial(pixel, 1.0f, 1.0f, primitive);
    Color diamondResult = diamondMaterial.applyMaterial(pixel, 1.0f, 1.0f, primitive);


    cr_assert_eq(airResult.getRed(), color.getRed());
    cr_assert_eq(waterResult.getGreen(), color.getGreen());
    cr_assert_eq(glassResult.getBlue(), color.getBlue());
    cr_assert_eq(diamondResult.getRed(), color.getRed());
}

Test(ChessboardMat, constructor) {
    ChessboardMat material;

    cr_assert_eq(material.getMaterialType(), MaterialType::CHESSBOARD, "Material type should be CHESSBOARD");


    Color color1 = material.getOptionalColor1();
    Color color2 = material.getOptionalColor2();

    cr_assert_eq(color1.getRed(), 255, "Default color1 R should be 255");
    cr_assert_eq(color1.getGreen(), 255, "Default color1 G should be 255");
    cr_assert_eq(color1.getBlue(), 255, "Default color1 B should be 255");

    cr_assert_eq(color2.getRed(), 0, "Default color2 R should be 0");
    cr_assert_eq(color2.getGreen(), 0, "Default color2 G should be 0");
    cr_assert_eq(color2.getBlue(), 0, "Default color2 B should be 0");

    cr_assert_float_eq(material.getScale(), 2.0f, 0.001f, "Default scale should be 2.0f");
}

Test(ChessboardMat, custom_colors_and_scale) {
    ChessboardMat material;
    MockPrimitive primitive;


    Color red(255, 0, 0);
    Color blue(0, 0, 255);
    material.setOptionalColor1(red);
    material.setOptionalColor2(blue);


    material.setScale(0.5f);


    Color color1 = material.getOptionalColor1();
    Color color2 = material.getOptionalColor2();

    cr_assert_eq(color1.getRed(), 255);
    cr_assert_eq(color1.getGreen(), 0);
    cr_assert_eq(color1.getBlue(), 0);

    cr_assert_eq(color2.getRed(), 0);
    cr_assert_eq(color2.getGreen(), 0);
    cr_assert_eq(color2.getBlue(), 255);

    cr_assert_float_eq(material.getScale(), 0.5f, 0.001f);


    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0.25, 0.25, 0.25);
    Color baseColor(100, 100, 100);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));

    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);


    bool isRedOrBlue = (
        (result.getRed() == 255 && result.getGreen() == 0 && result.getBlue() == 0) ||
        (result.getRed() == 0 && result.getGreen() == 0 && result.getBlue() == 255)
    );

    cr_assert(isRedOrBlue, "Color should match one of the chessboard colors");
}

Test(ChessboardMat, scale_effect_on_pattern) {


    ChessboardMat smallScale;
    smallScale.setScale(0.5f);

    ChessboardMat largeScale;
    largeScale.setScale(5.0f);


    MockPrimitive primitive;


    Math::Vector3D normal(0, 1, 0);
    std::vector<Math::Vector3D> positions = {
        Math::Vector3D(0.2, 0, 0),
        Math::Vector3D(0.4, 0, 0),
        Math::Vector3D(0.6, 0, 0),
        Math::Vector3D(0.8, 0, 0)
    };


    int smallScaleChanges = 0;
    Color prevColor;

    for (size_t i = 0; i < positions.size(); i++) {
        PixelInfo pixel(Color(0, 0, 0), normal, 1.0, true, positions[i], 1.0f, Color(255, 255, 255));
        Color result = smallScale.applyMaterial(pixel, 1.0f, 1.0f, primitive);

        if (i > 0) {
            if (result.getRed() != prevColor.getRed() ||
                result.getGreen() != prevColor.getGreen() ||
                result.getBlue() != prevColor.getBlue()) {
                smallScaleChanges++;
            }
        }
        prevColor = result;
    }


    int largeScaleChanges = 0;

    for (size_t i = 0; i < positions.size(); i++) {
        PixelInfo pixel(Color(0, 0, 0), normal, 1.0, true, positions[i], 1.0f, Color(255, 255, 255));
        Color result = largeScale.applyMaterial(pixel, 1.0f, 1.0f, primitive);

        if (i > 0) {
            if (result.getRed() != prevColor.getRed() ||
                result.getGreen() != prevColor.getGreen() ||
                result.getBlue() != prevColor.getBlue()) {
                largeScaleChanges++;
            }
        }
        prevColor = result;
    }




    cr_assert(smallScaleChanges >= largeScaleChanges,
              "Smaller scale should generally produce more pattern alternations");
}

Test(PerlingNoiseMat, constructor) {
    PerlingNoiseMat material;

    cr_assert_eq(material.getMaterialType(), MaterialType::PERLING_NOISE_MAT,
                 "Material type should be PERLING_NOISE_MAT");
}

Test(PerlingNoiseMat, apply_material) {
    PerlingNoiseMat material;
    MockPrimitive primitive;
    Color color(100, 150, 200);
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(1.5, 2.5, 3.5);
    PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));
    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);


    cr_assert(result.getRed() >= 0 && result.getRed() <= 255,
              "Red component should be in valid range");
    cr_assert(result.getGreen() >= 0 && result.getGreen() <= 255,
              "Green component should be in valid range");
    cr_assert(result.getBlue() >= 0 && result.getBlue() <= 255,
              "Blue component should be in valid range");
}

Test(PerlingNoiseMat, position_based_variations) {
    PerlingNoiseMat material;
    MockPrimitive primitive;


    Color baseColor(100, 150, 200);
    Math::Vector3D normal(0, 1, 0);

    Math::Vector3D position1(0.0, 0.0, 0.0);
    Math::Vector3D position2(0.5, 0.5, 0.5);
    Math::Vector3D position3(1.0, 1.0, 1.0);
    PixelInfo pixel1(baseColor, normal, 1.0, true, position1, 1.0f, Color(255, 255, 255));
    PixelInfo pixel2(baseColor, normal, 1.0, true, position2, 1.0f, Color(255, 255, 255));
    PixelInfo pixel3(baseColor, normal, 1.0, true, position3, 1.0f, Color(255, 255, 255));
    Color result1 = material.applyMaterial(pixel1, 1.0f, 1.0f, primitive);
    Color result2 = material.applyMaterial(pixel2, 1.0f, 1.0f, primitive);
    Color result3 = material.applyMaterial(pixel3, 1.0f, 1.0f, primitive);

    bool allColorsAreSame = (
        result1.getRed() == result2.getRed() &&
        result1.getRed() == result3.getRed() &&
        result1.getGreen() == result2.getGreen() &&
        result1.getGreen() == result3.getGreen() &&
        result1.getBlue() == result2.getBlue() &&
        result1.getBlue() == result3.getBlue()
    );
    cr_assert(!allColorsAreSame, "Perlin noise should produce varied colors at different positions");

    auto isValidColor = [](const Color& c) -> bool {
        return (c.getRed() >= 0 && c.getRed() <= 255 &&
                c.getGreen() >= 0 && c.getGreen() <= 255 &&
                c.getBlue() >= 0 && c.getBlue() <= 255);
    };
    cr_assert(isValidColor(result1), "Result should be a valid color");
    cr_assert(isValidColor(result2), "Result should be a valid color");
    cr_assert(isValidColor(result3), "Result should be a valid color");
}

Test(PerlingNoiseMat, transparency_application) {
    PerlingNoiseMat material;
    material.setTransparency(0.5f);
    MockPrimitive primitive;
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0.5, 0.5, 0.5);
    Color baseColor(100, 150, 200);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));
    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);

    float expectedTransparency = (1.0f - 0.5f) * 255.0f;
}

Test(FileTextureMat, constructor) {
    FileTextureMat material;
    cr_assert_eq(material.getMaterialType(), MaterialType::FILE_TEXTURE_MAT,
                 "Material type should be FILE_TEXTURE_MAT");
    cr_assert_eq(material.getColorTexture(), nullptr,
                 "Default color texture should be nullptr");
}

Test(FileTextureMat, set_texture_path) {
    FileTextureMat material;

    cr_assert_eq(material.getColorTexture(), nullptr,
                 "Default color texture should be nullptr");

    std::shared_ptr<std::string> texturePath = std::make_shared<std::string>("assets/texture/example.png");
    material.setColorTexture(texturePath);

    cr_assert_not_null(material.getColorTexture(), "Color texture should not be nullptr after setting");
    cr_assert_str_eq(material.getColorTexture()->c_str(), "assets/texture/example.png",
                    "Texture path should match the one that was set");
}

Test(FileTextureMat, apply_material_without_texture) {
    FileTextureMat material;
    MockPrimitive primitive;

    Color baseColor(100, 150, 200);
    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0.5, 0.5, 0.5);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));

    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);
    cr_assert_eq(result.getRed(), baseColor.getRed(),
                "Without texture, red component should match base color");
    cr_assert_eq(result.getGreen(), baseColor.getGreen(),
                "Without texture, green component should match base color");
    cr_assert_eq(result.getBlue(), baseColor.getBlue(),
                "Without texture, blue component should match base color");
}

Test(FileTextureMat, uv_coordinate_calculation) {
    FileTextureMat material;

    MockPrimitive spherePrimitive;
    MockCylinderPrimitive cylinderPrimitive;
    MockPlanePrimitive planePrimitive;
    MockConePrimitive conePrimitive;

    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0.5, 0.5, 0.5);
    PixelInfo pixel(Color(100, 100, 100), normal, 1.0, true, position, 1.0f, Color(255, 255, 255));



    Color sphereResult = material.applyMaterial(pixel, 1.0f, 1.0f, spherePrimitive);
    Color cylinderResult = material.applyMaterial(pixel, 1.0f, 1.0f, cylinderPrimitive);
    Color planeResult = material.applyMaterial(pixel, 2.0f, 1.0f, planePrimitive);
    Color coneResult = material.applyMaterial(pixel, 1.0f, 2.0f, conePrimitive);

    cr_assert(sphereResult.getRed() >= 0 && sphereResult.getRed() <= 255 &&
              sphereResult.getGreen() >= 0 && sphereResult.getGreen() <= 255 &&
              sphereResult.getBlue() >= 0 && sphereResult.getBlue() <= 255,
              "Sphere texture application should produce a valid color");
    cr_assert(cylinderResult.getRed() >= 0 && cylinderResult.getRed() <= 255 &&
              cylinderResult.getGreen() >= 0 && cylinderResult.getGreen() <= 255 &&
              cylinderResult.getBlue() >= 0 && cylinderResult.getBlue() <= 255,
              "Cylinder texture application should produce a valid color");
    cr_assert(planeResult.getRed() >= 0 && planeResult.getRed() <= 255 &&
              planeResult.getGreen() >= 0 && planeResult.getGreen() <= 255 &&
              planeResult.getBlue() >= 0 && planeResult.getBlue() <= 255,
              "Plane texture application should produce a valid color");
    cr_assert(coneResult.getRed() >= 0 && coneResult.getRed() <= 255 &&
              coneResult.getGreen() >= 0 && coneResult.getGreen() <= 255 &&
              coneResult.getBlue() >= 0 && coneResult.getBlue() <= 255,
              "Cone texture application should produce a valid color");
}

Test(FileTextureMat, uv_coordinate_calculation_with_different_primitives) {
    FileTextureMat material;

    MockPrimitive spherePrimitive;
    MockCylinderPrimitive cylinderPrimitive;
    MockPlanePrimitive planePrimitive;
    MockConePrimitive conePrimitive;

    Math::Vector3D normal(0, 1, 0);
    Math::Vector3D position(0.5, 0.5, 0.5);
    Color baseColor(100, 150, 200);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));


    Color sphereResult = material.applyMaterial(pixel, 1.0f, 1.0f, spherePrimitive);
    Color cylinderResult = material.applyMaterial(pixel, 1.0f, 1.0f, cylinderPrimitive);
    Color planeResult = material.applyMaterial(pixel, 1.0f, 1.0f, planePrimitive);
    Color coneResult = material.applyMaterial(pixel, 1.0f, 1.0f, conePrimitive);

    cr_assert_eq(sphereResult.getRed(), baseColor.getRed());
    cr_assert_eq(cylinderResult.getRed(), baseColor.getRed());
    cr_assert_eq(planeResult.getRed(), baseColor.getRed());
    cr_assert_eq(coneResult.getRed(), baseColor.getRed());
}

Test(AMaterial, setters_and_getters) {

    std::shared_ptr<AMaterial> material = std::make_shared<FlatColorMat>();

    Math::Vector3D ambient(0.1f, 0.2f, 0.3f);
    Math::Vector3D diffuse(0.4f, 0.5f, 0.6f);
    Math::Vector3D specular(0.7f, 0.8f, 0.9f);
    material->setAmbient(ambient);
    material->setDiffuse(diffuse);
    material->setSpecular(specular);
    cr_assert_float_eq(material->getAmbient().getX(), 0.1f, 0.001f);
    cr_assert_float_eq(material->getAmbient().getY(), 0.2f, 0.001f);
    cr_assert_float_eq(material->getAmbient().getZ(), 0.3f, 0.001f);
    cr_assert_float_eq(material->getDiffuse().getX(), 0.4f, 0.001f);
    cr_assert_float_eq(material->getDiffuse().getY(), 0.5f, 0.001f);
    cr_assert_float_eq(material->getDiffuse().getZ(), 0.6f, 0.001f);
    cr_assert_float_eq(material->getSpecular().getX(), 0.7f, 0.001f);
    cr_assert_float_eq(material->getSpecular().getY(), 0.8f, 0.001f);
    cr_assert_float_eq(material->getSpecular().getZ(), 0.9f, 0.001f);

    material->setShininess(50.0f);
    material->setReflectivity(0.3f);
    material->setTransparency(0.4f);
    material->setRefractiveIndex(1.6f);
    material->setOpacity(0.8f);
    material->setScale(3.0f);
    cr_assert_float_eq(material->getShininess(), 50.0f, 0.001f);
    cr_assert_float_eq(material->getReflectivity(), 0.3f, 0.001f);
    cr_assert_float_eq(material->getTransparency(), 0.4f, 0.001f);
    cr_assert_float_eq(material->getRefractiveIndex(), 1.6f, 0.001f);
    cr_assert_float_eq(material->getOpacity(), 0.8f, 0.001f);
    cr_assert_float_eq(material->getScale(), 3.0f, 0.001f);

    Color color1(10, 20, 30);
    Color color2(40, 50, 60);
    material->setOptionalColor1(color1);
    material->setOptionalColor2(color2);
    Color result1 = material->getOptionalColor1();
    Color result2 = material->getOptionalColor2();
    cr_assert_eq(result1.getRed(), 10);
    cr_assert_eq(result1.getGreen(), 20);
    cr_assert_eq(result1.getBlue(), 30);
    cr_assert_eq(result2.getRed(), 40);
    cr_assert_eq(result2.getGreen(), 50);
    cr_assert_eq(result2.getBlue(), 60);

    material->setMaterialType(MaterialType::CHESSBOARD);
    cr_assert_eq(material->getMaterialType(), MaterialType::CHESSBOARD);
}

Test(ChessboardMat, apply_material_sphere) {
    ChessboardMat material;
    MockPrimitive primitive;

    Math::Vector3D position(0, 0, 0);
    Color color(100, 100, 100);
    Math::Vector3D normal(0, 1, 0);
    PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));

    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);

    cr_assert(result.getRed() >= 0 && result.getRed() <= 255,
              "Red component should be in valid range");
    cr_assert(result.getGreen() >= 0 && result.getGreen() <= 255,
              "Green component should be in valid range");
    cr_assert(result.getBlue() >= 0 && result.getBlue() <= 255,
              "Blue component should be in valid range");
}



Test(ChessboardMat, apply_material_to_different_primitives) {
    ChessboardMat material;
    MockPrimitive spherePrimitive;
    MockCylinderPrimitive cylinderPrimitive;
    MockPlanePrimitive planePrimitive;
    MockConePrimitive conePrimitive;
    Math::Vector3D position(0.5, 0.5, 0.5);
    Math::Vector3D normal(0, 1, 0);
    Color baseColor(100, 100, 100);
    PixelInfo pixel(baseColor, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));

    Color sphereResult = material.applyMaterial(pixel, 1.0f, 1.0f, spherePrimitive);
    Color cylinderResult = material.applyMaterial(pixel, 1.0f, 1.0f, cylinderPrimitive);
    Color planeResult = material.applyMaterial(pixel, 1.0f, 1.0f, planePrimitive);
    Color coneResult = material.applyMaterial(pixel, 1.0f, 1.0f, conePrimitive);

    auto isValidColor = [](const Color& c) -> bool {
        return (c.getRed() >= 0 && c.getRed() <= 255 &&
                c.getGreen() >= 0 && c.getGreen() <= 255 &&
                c.getBlue() >= 0 && c.getBlue() <= 255);
    };
    cr_assert(isValidColor(sphereResult), "Sphere chessboard should produce valid colors");
    cr_assert(isValidColor(cylinderResult), "Cylinder chessboard should produce valid colors");
    cr_assert(isValidColor(planeResult), "Plane chessboard should produce valid colors");
    cr_assert(isValidColor(coneResult), "Cone chessboard should produce valid colors");
}



Test(AMaterial, testSetMap) {
    std::shared_ptr<AMaterial> material = std::make_shared<FlatColorMat>();
    std::shared_ptr<std::string> map = std::make_shared<std::string>("assets/texture/example.png");

    material->setNormalMap(map);
    material->getNormalMap();
}

Test(ChessboardMat, testTorus) {
    ChessboardMat material;
    MockTorusPrimitive primitive;

    Math::Vector3D position(0, 0, 0);
    Color color(100, 100, 100);
    Math::Vector3D normal(0, 1, 0);
    PixelInfo pixel(color, normal, 1.0, true, position, 1.0f, Color(255, 255, 255));

    Color result = material.applyMaterial(pixel, 1.0f, 1.0f, primitive);

    cr_assert_eq(result.getRed(), 0, "Red component should be 100");
    cr_assert_eq(result.getGreen(), 0, "Green component should be 100");
    cr_assert_eq(result.getBlue(), 0, "Blue component should be 100");
}

