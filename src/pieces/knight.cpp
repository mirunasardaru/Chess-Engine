#include <iostream>
#include <cmath>
#include "pieces/knight.h"
#include "model/board.h"

char Knight::getPieceSymbol() const {
    return this->pieceColour == Colour::White ? 'N' : 'n';
}

bool Knight::canMove(const Board &board, const Position &destination) const {
    int nrColumnsMoved = abs(destination.column - this->piecePosition.column);
    int nrRowsMoved = abs(destination.row - this->piecePosition.row);

    return (nrColumnsMoved == 1 && nrRowsMoved == 2) || (nrColumnsMoved == 2 && nrRowsMoved == 1);
}

PieceTypes Knight::getPieceType() const {
    return PieceTypes::Knight;
}