#pragma once

#include "pieces.h"

class Rook: public ChessPiece {
    bool hasMoved = false;
public:
    Rook(Colour colour, Position position): ChessPiece(colour, position) {}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;

    bool getHasMoved() const;
    void setHasMoved(bool hasMoved);
};