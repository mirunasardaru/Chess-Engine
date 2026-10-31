#pragma once

#include "pieces.h"

class Pawn: public ChessPiece {
public:
    Pawn(Colour colour, Position pos): ChessPiece(colour, pos){}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;
};