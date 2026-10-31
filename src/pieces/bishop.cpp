#include <iostream>
#include <cmath>
#include "pieces/bishop.h"
#include "model/board.h"

char Bishop::getPieceSymbol() const {
    return this->pieceColour == Colour::White ? 'B': 'b';
}

bool Bishop::canMove(const Board &board, const Position &destination) const {
    int nrRowsMoved = abs(destination.row - this->piecePosition.row);
    int nrColumnsMoved = abs(destination.column - this->piecePosition.column);

    bool validDirection = (nrRowsMoved == nrColumnsMoved);

    Move movePiece(this->piecePosition, destination);
    return validDirection &&
        board.isPathClear(movePiece);
}

PieceTypes Bishop::getPieceType() const {
    return PieceTypes::Bishop;
}