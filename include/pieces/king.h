#pragma once

#include "pieces.h"

class King: public ChessPiece {
    bool hasMoved = false;
public:
    King(Colour colour, Position pos): ChessPiece(colour, pos){}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;

    bool getHasMoved() const;
    void setHasMoved(bool hasMoved);
};