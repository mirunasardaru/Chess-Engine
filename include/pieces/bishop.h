#pragma once

#include "pieces.h"

class Bishop: public ChessPiece {
public:
    Bishop(Colour colour, Position pos): ChessPiece(colour, pos){}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;
};