/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** FileTextureMat-test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../common/material/fileTextureMat.hpp"
#include "../common/PixelInfo.hpp"
#include "../common/APrimitives.hpp"
#include <memory>

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

void redirect_filetexture_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(FileTextureMatSpecific, basic_constructor, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    cr_assert_eq(material.getMaterialType(), MaterialType::FILE_TEXTURE_MAT);
}

// Test texture mapping for sphere
Test(FileTextureMat, sphere_texture_mapping, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(1.0, 0.0, 0.0);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 0.0, 0.0).normalize();
    pixelInfo._color = Color(255, 255, 255);
    MockPrimitive primitive;
    primitive.setScale(1.0);
    material.applyMaterial(pixelInfo, 1.0, 0.0, primitive);
}

Test(FileTextureMat, plane_texture_mapping, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.0, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(0.0, 1.0, 0.0).normalize();
    pixelInfo._color = Color(255, 255, 255);
    class PlaneTestPrimitive : public MockPrimitive {
    public:
        Type getType() const override {
            return Type::PLANE;
        }
    };
    PlaneTestPrimitive planePrimitive;
    material.applyMaterial(pixelInfo, 10.0, 0.0, planePrimitive);
}

Test(FileTextureMat, cylinder_texture_mapping, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(1.0, 0.5, 0.0);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 0.0, 0.0).normalize();
    pixelInfo._color = Color(255, 255, 255);
    class CylinderTestPrimitive : public MockPrimitive {
    public:
        Type getType() const override {
            return Type::CYLINDER;
        }
    };
    CylinderTestPrimitive cylinderPrimitive;
    material.applyMaterial(pixelInfo, 1.0, 2.0, cylinderPrimitive);
}

Test(FileTextureMat, cone_texture_mapping, .init = redirect_filetexture_stdout) {
    FileTextureMat material;

    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.5, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 1.0, 0.0).normalize();
    pixelInfo._color = Color(255, 255, 255);
    class ConeTestPrimitive : public MockPrimitive {
    public:
        Type getType() const override {
            return Type::CONE;
        }
    };
    ConeTestPrimitive conePrimitive;
    material.applyMaterial(pixelInfo, 1.0, 2.0, conePrimitive);
}

Test(FileTextureMat, different_primitive_types, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.5, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(0.0, 1.0, 0.0);
    pixelInfo._color = Color(255, 255, 255);
    class TorusTestPrimitive : public MockPrimitive {
    public:
        Type getType() const override {
            return Type::TORUS;
        }
    };
    TorusTestPrimitive torusPrimitive;
    material.applyMaterial(pixelInfo, 1.0, 0.5, torusPrimitive);
    class OtherTestPrimitive : public MockPrimitive {
    public:
        Type getType() const override {
            return Type::SPHERE;
        }
    };
    OtherTestPrimitive otherPrimitive;
    material.applyMaterial(pixelInfo, 1.0, 0.5, otherPrimitive);
}

Test(FileTextureMat, direct_material_application, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.2, 0.3, 0.4);
    pixelInfo._normalizedVector = Math::Vector3D(0.0, 1.0, 0.0);
    pixelInfo._color = Color(255, 255, 255);
    MockPrimitive primitive;
    material.applyMaterial(pixelInfo, 1.0, 1.0, primitive);
}

Test(FileTextureMat, null_primitive_handling, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.5, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 0.0, 0.0);
    pixelInfo._color = Color(255, 255, 255);
    MockPrimitive primitive;
    primitive.setPosition(Math::Point3D(0.0, 0.0, 0.0));
    Color result = material.applyMaterial(pixelInfo, 1.0, 1.0, primitive);
    cr_assert_eq(result.getRed(), 255);
    cr_assert_eq(result.getGreen(), 255);
    cr_assert_eq(result.getBlue(), 255);
}


Test(FileTextureMat, paterrialNotNull, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.5, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 0.0, 0.0);
    pixelInfo._color = Color(255, 255, 255);
    // Use a dummy path, the code should not crash even if file does not exist
    material.loadTextureFromFile("tests/ressouces/test_image.png");
    MockPrimitive primitive;
    primitive.setPosition(Math::Point3D(0.0, 0.0, 0.0));
    Color result = material.applyMaterial(pixelInfo, 1.0, 1.0, primitive);
    cr_assert_eq(result.getRed(), 255);
    cr_assert_eq(result.getGreen(), 255);
    cr_assert_eq(result.getBlue(), 255);

    // Use valid shared_ptr for u and v
    auto u = std::make_shared<float>(0.0f);
    auto v = std::make_shared<float>(0.0f);
    material.calculUVCoordinates(primitive, pixelInfo, 1.0, 1.0, u, v);
}

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

Test(FileTextureMat, testUvAllPrimitive, .init = redirect_filetexture_stdout) {
    FileTextureMat material;
    PixelInfo pixelInfo;
    pixelInfo._pos = Math::Vector3D(0.5, 0.5, 0.5);
    pixelInfo._normalizedVector = Math::Vector3D(1.0, 0.0, 0.0);
    pixelInfo._color = Color(255, 255, 255);

    auto u = std::make_shared<float>(0.0f);
    auto v = std::make_shared<float>(0.0f);

    MockConePrimitive conePrimitive;
    material.calculUVCoordinates(conePrimitive, pixelInfo, 1.0, 1.0, u, v);

    MockCylinderPrimitive cylinderPrimitive;
    material.calculUVCoordinates(cylinderPrimitive, pixelInfo, 1.0, 1.0, u, v);

    MockPlanePrimitive planePrimitive;
    material.calculUVCoordinates(planePrimitive, pixelInfo, 1.0, 1.0, u, v);

    MockTorusPrimitive torusPrimitive;
    material.calculUVCoordinates(torusPrimitive, pixelInfo, 1.0, 1.0, u, v);

    MockPrimitive spherePrimitive;
    material.calculUVCoordinates(spherePrimitive, pixelInfo, 1.0, 1.0, u, v);
}
