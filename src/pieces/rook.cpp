#include <iostream>
#include <cmath>
#include "pieces/rook.h"
#include "model/board.h"
#include "model/moves.h"

char Rook::getPieceSymbol() const {
    return this->pieceColour == Colour::White ? 'R' : 'r';
}

bool Rook::canMove(const Board &board, const Position &destination) const {
    int nrRowsMoved = abs(destination.row - this->piecePosition.row);
    int nrColumnsMoved = abs(destination.column - this->piecePosition.column);

    bool validDirection = ( nrRowsMoved == 0 && nrColumnsMoved != 0) ||
        (nrRowsMoved != 0 && nrColumnsMoved == 0);

    Move movePiece(this->piecePosition, destination);
    return validDirection &&
        board.isPathClear(movePiece);
}

PieceTypes Rook::getPieceType() const {
    return PieceTypes::Rook;
}

bool Rook::getHasMoved() const {
    return this->hasMoved;
}

void Rook::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}