#pragma once

#include <memory>
#include "pieces.h"

class PieceFactory {
public:
    static std::unique_ptr<ChessPiece> createPieces(PieceTypes pieceType, Colour colour, Position pos);
};