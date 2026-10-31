#pragma once

#include "pieces.h"

class Queen: public ChessPiece {
public:
    Queen(Colour colour, Position position): ChessPiece(colour, position) {}

    char getPieceSymbol() const override;
    bool canMove(const Board &board, const Position &destination) const override;
    PieceTypes getPieceType() const override;
};