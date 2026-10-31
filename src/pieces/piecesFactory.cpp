#include <iostream>
#include "pieces/piecesFactory.h"
#include "pieces/pawn.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/rook.h"
#include "pieces/king.h"
#include "pieces/queen.h"

using namespace std;

unique_ptr<ChessPiece> PieceFactory::createPieces(PieceTypes pieceType, Colour colour, Position pos) {
    switch (pieceType) {
        case PieceTypes::Pawn:
            return make_unique<Pawn>(colour, pos);
        case PieceTypes::Knight:
            return make_unique<Knight>(colour, pos);
        case PieceTypes::Bishop:
            return make_unique<Bishop>(colour, pos);
        case PieceTypes::Rook:
            return make_unique<Rook>(colour, pos);
        case PieceTypes::King:
            return make_unique<King>(colour,pos);
        case PieceTypes::Queen:
            return make_unique<Queen>(colour, pos);
    }
}