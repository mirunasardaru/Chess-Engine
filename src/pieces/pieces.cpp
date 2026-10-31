#include <iostream>
#include "pieces/pieces.h"

using namespace std;

bool Position::operator==(const Position &second) const {
    return (row == second.row) && (column == second.column);
}

Colour ChessPiece::getPieceColour() const {
    return this->pieceColour;
}
Position ChessPiece::getPiecePosition() const {
    return this->piecePosition;
}

void ChessPiece::setPiecePosition(const Position &pos) {
    this->piecePosition = pos;
}