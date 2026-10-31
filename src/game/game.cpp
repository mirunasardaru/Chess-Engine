#include <iostream>
#include "game/game.h"
#include "model/board.h"
#include "pieces/rook.h"
#include "pieces/king.h"

void Game::switchTurn() {
    if (currentPlayer == Colour::White) {
        currentPlayer = Colour::Black;
    }
    else {
        currentPlayer = Colour::White;
    }
}
bool Game::makeMove(const Move& move, PromotionPieces promotionType) {
    if (!Board::inBounds(move.from) || !Board::inBounds(move.to)) {
        return false;
    }

    ChessPiece *piece = board.getPiece(move.from);
    if (piece == nullptr) {
        return false;
    }

    if (piece->getPieceColour() != currentPlayer) {
        return false;
    }

    bool enPassant = false;
    bool castling = false;

    if (!piece->canMove(board, move.to)) {

        if (isEnPassant(move)) {
            enPassant = true;
        }
        else if (isCastling(move)) {
            castling = true;
        }
        else {
            return false;
        }
    }

    ChessPiece* destination = board.getPiece(move.to);
    if (destination != nullptr) {
        if (destination->getPieceColour() == piece->getPieceColour()) {
            return false;
        }
    }

    MoveInfo info = board.movePiece(move.from, move.to);
    if (enPassant) {
        Position posCaptured(move.from.row, move.to.column);

        info.capturedPiece = board.removePiece(posCaptured);
        info.capturedPosition = posCaptured;
    }
    else {
        info.capturedPosition = move.to;
    }

    if (castling) {
        int row = move.from.row;

        if (move.to.column == 6) {
            // King side
            board.movePiece(
                Position(row, 7),
                Position(row, 5)
            );
        }
        else {
            // Queen side
            board.movePiece(
                Position(row, 0),
                Position(row, 3)
            );
        }
    }

    if (isCheck(currentPlayer)){
        board.undoMove(info);
        return false;
    }

    //promote pawn
    ChessPiece* movedPiece = board.getPiece(move.to);
    if (movedPiece != nullptr &&
        movedPiece->getPieceType() == PieceTypes::Pawn) {
        if ((movedPiece->getPieceColour() == Colour::White &&
            movedPiece->getPiecePosition().row == 0) ||
            (movedPiece->getPieceColour() == Colour::Black &&
                movedPiece->getPiecePosition().row == 7)) {

            board.promotePawn(movedPiece->getPiecePosition(), promotionType);
        }
    }

    this->lastMove = move;
    this->hasLastMove = true;

    switchTurn();
    return true;
}
Colour Game::getCurrentPlayer() const {
    return currentPlayer;
}
Board& Game::getBoard(){
    return board;
}

bool Game::isCheck(Colour colour) const {
    Position kingPosition = findKing(colour);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Position currentPos(row, col);
            ChessPiece* piece = board.getPiece(currentPos);

            if (piece == nullptr) {
                continue;
            }

            if (colour == piece->getPieceColour()) {
                continue;
            }

            if (piece->canMove(board, kingPosition)) {
                return true;
            }
        }
    }
    return false;
}

Position Game::findKing(Colour colour) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Position currentPos(row, col);
            ChessPiece* piece = board.getPiece(currentPos);

            if (piece == nullptr) {
                continue;
            }

            if (piece->getPieceColour() == colour &&
                piece->getPieceType() == PieceTypes::King) {
                return currentPos;
            }
        }
    }

    throw std::runtime_error("King not found");
}

bool Game::hasLegalMove(Colour colour) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Position from(row, col);
            ChessPiece* piece = board.getPiece(from);

            if (piece == nullptr) {
                continue;
            }
            if (piece->getPieceColour() != colour) {
                continue;
            }

            for (int destRow = 0; destRow < 8; destRow++) {
                for (int destCol = 0; destCol < 8; destCol++) {
                    Position dest(destRow, destCol);

                    Move testMove(from, dest);
                    if (!piece->canMove(board, dest) &&
                        !isEnPassant(testMove) &&
                        !isCastling(testMove)) {
                        continue;
                    }

                    ChessPiece* movedPiece = board.getPiece(dest);

                    if (movedPiece != nullptr &&
                        movedPiece->getPieceColour() == colour) {
                        continue;
                    }

                    bool enPassant = isEnPassant(testMove);
                    MoveInfo info = board.movePiece(from, dest);

                    if (enPassant) {
                        Position capturedPos(from.row, dest.column);
                        info.capturedPiece = board.removePiece(capturedPos);
                        info.capturedPosition = capturedPos;
                    }

                    if (!isCheck(colour)) {
                        board.undoMove(info);
                        return true;
                    }
                    board.undoMove(info);
                }
            }
        }
    }
    return false;
}

bool Game::isCheckmate(Colour colour) {
    return isCheck(colour) &&
        !hasLegalMove(colour);
}

bool Game::isStalemate(Colour colour) {
    return !isCheck(colour) &&
        !hasLegalMove(colour);
}

bool Game::isEnPassant(const Move& move) const {
    if (!hasLastMove) {
        return false;
    }

    ChessPiece* piece = board.getPiece(move.from);

    if (piece == nullptr ||
        piece->getPieceType() != PieceTypes::Pawn) {
        return false;
        }

    int nrRowsMoved = move.to.row - move.from.row;
    int nrColumnsMoved = move.to.column - move.from.column;

    int direction =
        (piece->getPieceColour() == Colour::White) ? -1 : 1;

    if (nrRowsMoved != direction ||
        abs(nrColumnsMoved) != 1) {
        return false;
        }

    if (!board.isEmpty(move.to)) {
        return false;
    }

    Position posAdjacent(move.from.row, move.to.column);
    ChessPiece* adjacentPiece = board.getPiece(posAdjacent);

    if (adjacentPiece == nullptr ||
        adjacentPiece->getPieceType() != PieceTypes::Pawn ||
        adjacentPiece->getPieceColour() == piece->getPieceColour()) {
        return false;
        }

    if (lastMove.to != posAdjacent) {
        return false;
    }

    if (abs(lastMove.to.row - lastMove.from.row) != 2) {
        return false;
    }

    return true;
}

bool Game::isCastling(const Move& move) {
    ChessPiece* piece = board.getPiece(move.from);

    if (piece == nullptr) {
        return false;
    }

    if (piece->getPieceType() != PieceTypes::King) {
        return false;
    }

    King* king = dynamic_cast<King*>(piece);

    if (king == nullptr) {
        return false;
    }

    if (king->getHasMoved()) {
        return false;
    }

    if (move.from.row != move.to.row) {
        return false;
    }

    int columnDifference =
        move.to.column - move.from.column;

    if (abs(columnDifference) != 2) {
        return false;
    }

    if (move.from.column != 4) {
        return false;
    }

    int row = move.from.row;

    if (columnDifference == 2) {

        Position rookPosition(row, 7);

        ChessPiece* pieceRook =
            board.getPiece(rookPosition);

        if (pieceRook == nullptr) {
            return false;
        }

        if (pieceRook->getPieceType() != PieceTypes::Rook) {
            return false;
        }

        if (pieceRook->getPieceColour() !=
            king->getPieceColour()) {
            return false;
        }

        Rook* rook = dynamic_cast<Rook*>(pieceRook);

        if (rook == nullptr || rook->getHasMoved()) {
            return false;
        }

        if (!board.isEmpty(Position(row, 5)) ||
            !board.isEmpty(Position(row, 6))) {
            return false;
        }
    }
    else {

        Position rookPosition(row, 0);

        ChessPiece* pieceRook =
            board.getPiece(rookPosition);

        if (pieceRook == nullptr) {
            return false;
        }

        if (pieceRook->getPieceType() != PieceTypes::Rook) {
            return false;
        }

        if (pieceRook->getPieceColour() !=
            king->getPieceColour()) {
            return false;
        }

        Rook* rook = dynamic_cast<Rook*>(pieceRook);

        if (rook == nullptr || rook->getHasMoved()) {
            return false;
        }

        if (!board.isEmpty(Position(row, 1)) ||
            !board.isEmpty(Position(row, 2)) ||
            !board.isEmpty(Position(row, 3))) {
            return false;
        }
    }
    if (isCheck(king->getPieceColour())) {
        return false;
    }

    Position middlePosition(
    row,
    move.from.column +
        (columnDifference > 0 ? 1 : -1)
);

    MoveInfo middleMove = board.movePiece(move.from, middlePosition);

    bool middleSafe = !isCheck(king->getPieceColour());

    board.undoMove(middleMove);

    if (!middleSafe) {
        return false;
    }

    return true;
}