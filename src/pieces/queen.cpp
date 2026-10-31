#include <iostream>
#include <cmath>
#include "pieces/queen.h"
#include "model/board.h"

char Queen::getPieceSymbol() const {
    return this->pieceColour == Colour::White ? 'Q' : 'q';
}

bool Queen::canMove(const Board &board, const Position &destination) const {
    int nrRowsMoved = abs(destination.row - this->piecePosition.row);
    int nrColumnsMoved = abs(destination.column - this->piecePosition.column);

    bool bishopMove = nrColumnsMoved == nrRowsMoved;
    bool rookMove = (nrRowsMoved == 0 && nrColumnsMoved != 0) ||
            (nrRowsMoved != 0 && nrColumnsMoved == 0);
    bool validDirection = bishopMove || rookMove;

    Move movePiece(this->piecePosition, destination);
    return validDirection &&
        board.isPathClear(movePiece);
}

PieceTypes Queen::getPieceType() const {
    return PieceTypes::Queen;
}