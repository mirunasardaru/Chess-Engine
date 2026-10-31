#include <iostream>
#include <cmath>
#include "pieces/pawn.h"
#include "pieces/pieces.h"
#include "model/board.h"

using namespace std;

char Pawn::getPieceSymbol() const{
    return this->pieceColour == Colour::White ? 'P' : 'p';
}

bool Pawn::canMove(const Board &board, const Position &destination) const {
    int nrRowsMoved = destination.row - this->piecePosition.row;
    int nrColumnsMoved = destination.column - this->piecePosition.column;

    int direction = (this->pieceColour == Colour::White) ? -1 : 1;

    //move with one step
    if (direction == nrRowsMoved &&
        nrColumnsMoved == 0 &&
        board.isEmpty(destination)) {
        return true;
    }

    //move with 2 tseps
    bool startPosition =
        (pieceColour == Colour::White && piecePosition.row == 6) ||
        (pieceColour == Colour::Black && piecePosition.row == 1);
    if (startPosition &&
        nrRowsMoved == 2 * direction &&
        nrColumnsMoved == 0) {

        Position middleStep(piecePosition.row + direction, piecePosition.column);
        if (board.isEmpty(middleStep) &&
            board.isEmpty(destination)) {
            return true;
        }
    }

    //move with capture
    if (abs(nrColumnsMoved) == 1 &&
        direction == nrRowsMoved) {
        ChessPiece *otherPiece = board.getPiece(destination);

        if (otherPiece != nullptr &&
            this->pieceColour != otherPiece->getPieceColour()) {
            return true;
        }
    }

    //move en passant


    //pawn promotion


    return false;
}

PieceTypes Pawn::getPieceType() const {
    return PieceTypes::Pawn;
}