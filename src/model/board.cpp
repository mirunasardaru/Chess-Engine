#include <iostream>
#include "model/board.h"
#include "pieces/piecesFactory.h"
#include "pieces/king.h"
#include "pieces/rook.h"

using namespace std;

Board::Board() {
    this->initializeBoard();
}
void Board::initializeBoard() {
    //placing the black pieces
    placePiece(PieceFactory::createPieces(PieceTypes::Rook, Colour::Black, {0,0}), {0,0});
    placePiece(PieceFactory::createPieces(PieceTypes::Knight, Colour::Black, {0, 1}),{0,1});
    placePiece(PieceFactory::createPieces(PieceTypes::Bishop, Colour::Black, {0,2}), {0,2});
    placePiece(PieceFactory::createPieces(PieceTypes::Queen, Colour::Black, {0,3}),{0,3});
    placePiece(PieceFactory::createPieces(PieceTypes::King, Colour::Black, {0,4}),{0,4});
    placePiece(PieceFactory::createPieces(PieceTypes::Bishop, Colour::Black, {0,5}),{0,5});
    placePiece(PieceFactory::createPieces(PieceTypes::Knight, Colour::Black, {0,6}),{0,6});
    placePiece(PieceFactory::createPieces(PieceTypes::Rook, Colour::Black, {0,7}),{0,7});

    //placing the black pawns
    for (int i = 0; i < 8; i++) {
        placePiece(PieceFactory::createPieces(PieceTypes::Pawn, Colour::Black, {1,i}), {1,i});
    }


    //placing the white pieces
    placePiece(PieceFactory::createPieces(PieceTypes::Rook, Colour::White, {7,0}), {7,0});
    placePiece(PieceFactory::createPieces(PieceTypes::Knight, Colour::White, {7, 1}),{7,1});
    placePiece(PieceFactory::createPieces(PieceTypes::Bishop, Colour::White, {7,2}), {7,2});
    placePiece(PieceFactory::createPieces(PieceTypes::Queen, Colour::White, {7,3}),{7,3});
    placePiece(PieceFactory::createPieces(PieceTypes::King, Colour::White, {7,4}),{7,4});
    placePiece(PieceFactory::createPieces(PieceTypes::Bishop, Colour::White, {7,5}),{7,5});
    placePiece(PieceFactory::createPieces(PieceTypes::Knight, Colour::White, {7,6}),{7,6});
    placePiece(PieceFactory::createPieces(PieceTypes::Rook, Colour::White, {7,7}),{7,7});

    //placing the white pawns
    for (int i = 0; i < 8; i++) {
        placePiece(PieceFactory::createPieces(PieceTypes::Pawn, Colour::White, {6,i}), {6,i});
    }
}

std::unique_ptr<ChessPiece> Board::removePiece(Position pos) {
    if (!inBounds(pos)) {
        return nullptr;
    }
    return move(board[pos.row][pos.column]);
}

MoveInfo Board::movePiece(Position from, Position to) {
    if (!inBounds(from) || !inBounds(to)) {
        throw std::out_of_range("Invalid board position.");
    }

    if (board[from.row][from.column] == nullptr) {
        throw std::runtime_error("No piece to move.");
    }

    MoveInfo info;

    info.move = Move(from, to);
    info.capturedPiece = move(board[to.row][to.column]);
    info.capturedPosition = to;

    board[to.row][to.column] = move(board[from.row][from.column]);
    info.movedPiece = board[to.row][to.column].get();
    board[to.row][to.column]->setPiecePosition(to);

    if (info.movedPiece->getPieceType() == PieceTypes::King) {
        King* king = dynamic_cast<King*>(info.movedPiece);
        info.pieceWasMoved = king->getHasMoved();
        king->setHasMoved(true);
    }

    if (info.movedPiece->getPieceType() == PieceTypes::Rook) {
        Rook* rook = dynamic_cast<Rook*>(info.movedPiece);
        info.pieceWasMoved = rook->getHasMoved();
        rook->setHasMoved(true);
    }

    return info;
}

void Board::undoMove(MoveInfo& info){
    Position from = info.move.from;
    Position to = info.move.to;

    board[from.row][from.column] = move(board[to.row][to.column]);
    board[from.row][from.column]->setPiecePosition(from);

    if (info.capturedPiece != nullptr) {
        board[info.capturedPosition.row][info.capturedPosition.column] = move(info.capturedPiece);
    }

    if (board[from.row][from.column]->getPieceType() == PieceTypes::King) {
        King* king = dynamic_cast<King*>(
            board[from.row][from.column].get()
        );

        king->setHasMoved(info.pieceWasMoved);
    }
    else if (board[from.row][from.column]->getPieceType() == PieceTypes::Rook) {
        Rook* rook = dynamic_cast<Rook*>(
            board[from.row][from.column].get()
        );

        rook->setHasMoved(info.pieceWasMoved);
    }
}

void Board::placePiece(std::unique_ptr<ChessPiece> piece, Position pos) {
    if (!inBounds(pos)) {
        return;
    }
    board[pos.row][pos.column] = move(piece);
}

void Board::printBoard() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == nullptr) {
                cout<<". ";
            }
            else {
                cout<<board[i][j]->getPieceSymbol()<<" ";
            }
        }
        cout<<endl;
    }
}

ChessPiece* Board::getPiece(Position pos) const {
    if (!inBounds(pos)) {
        return nullptr;
    }
    return board[pos.row][pos.column].get();
}

bool Board::isEmpty(Position pos) const {
    if (!inBounds(pos)) {
        return false;
    }
    return board[pos.row][pos.column] == nullptr;
}

bool Board::inBounds(Position pos){
    return pos.row >= 0 &&
        pos.row <= 7 &&
            pos.column >= 0 &&
                pos.column <=7;
}

bool Board::isPathClear(const Move &move) const {
    if (move.from == move.to) {
        return false;
    }

    int stepRow = 0;
    int stepColumn = 0;

    if (move.from.row < move.to.row) {
        stepRow = 1;
    }
    else if (move.from.row > move.to.row) {
        stepRow = -1;
    }

    if (move.from.column < move.to.column) {
        stepColumn = 1;
    }
    else if (move.from.column > move.to.column) {
        stepColumn = -1;
    }

    Position currentPos = move.from;
    currentPos.row += stepRow;
    currentPos.column += stepColumn;

    while (!(currentPos == move.to)) {
        if (!isEmpty(currentPos)) {
            return false;
        }

        currentPos.row += stepRow;
        currentPos.column += stepColumn;
    }

    return true;
}

void Board::promotePawn(Position pos, PromotionPieces promotionType) {
    ChessPiece* piece = getPiece(pos);

    if (piece == nullptr) {
        return;
    }

    if (piece->getPieceType() != PieceTypes::Pawn) {
        return;
    }

    Colour pieceColour = piece->getPieceColour();

    if (pieceColour == Colour::White &&
        pos.row != 0) {
        return;
    }
    if (pieceColour == Colour::Black &&
        pos.row != 7) {
        return;
    }

    PieceTypes newPieceType;

    switch (promotionType) {
        case PromotionPieces::Queen:
            newPieceType = PieceTypes::Queen;
        break;
        case PromotionPieces::Rook:
            newPieceType = PieceTypes::Rook;
        break;
        case PromotionPieces::Knight:
            newPieceType = PieceTypes::Knight;
        break;
        case PromotionPieces::Bishop:
            newPieceType = PieceTypes::Bishop;
        break;
    }

    placePiece(PieceFactory::createPieces(newPieceType, pieceColour, pos), pos);
}