/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-raytracer-albane.merian
** File description:
** chessboardMat
*/

#ifndef CHESSBOARDMAT_HPP_
#define CHESSBOARDMAT_HPP_
#include "AMaterial.hpp"
#include "../IPrimitives.hpp"
#include "../PixelInfo.hpp"

class ChessboardMat : public AMaterial {
    public:
        ChessboardMat();
        ~ChessboardMat() override = default;
        Color applyMaterial(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const override;

    private:
        Color applySphereChessboard(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const;
        Color applyPlaneChessboard(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const;
        Color applyCylinderChessboard(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const;
        Color applyConeChessboard(const PixelInfo& pixelInfo, float radius, float height, const IPrimitives &primitive) const;
};

#endif /* !CHESSBOARDMAT_HPP_ */
