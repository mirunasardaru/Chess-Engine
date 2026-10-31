#include <iostream>
#include <cmath>
#include "pieces/king.h"

char King::getPieceSymbol() const {
    return this->pieceColour == Colour::White ? 'K':'k';
}

bool King::canMove(const Board &board, const Position &destination) const {
    int nrRowsMoved = abs(destination.row - this->piecePosition.row);
    int nrColumnsMoved = abs(destination.column - this->piecePosition.column);

    return nrRowsMoved <= 1 &&
        nrColumnsMoved <= 1 &&
            !(nrRowsMoved == 0 && nrColumnsMoved == 0);
}

PieceTypes King::getPieceType() const {
    return PieceTypes::King;
}

bool King::getHasMoved() const {
    return this->hasMoved;
}

void King::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}