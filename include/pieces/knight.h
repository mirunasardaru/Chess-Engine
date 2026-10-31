#pragma once
#include "pieces.h"

class Knight: public ChessPiece {
public:
    Knight(Colour colour, Position pos): ChessPiece(colour, pos){}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;
};