#pragma once

#include <memory>
#include <array>
#include "pieces/pieces.h"
#include "model/moves.h"
#include "model/promotionPieces.h"

class Board {
    std::array<std::array<std::unique_ptr<ChessPiece>,8>,8> board;

public:
    Board();
    void initializeBoard();

    std::unique_ptr<ChessPiece> removePiece(Position pos);
    MoveInfo movePiece(Position from, Position to);
    void placePiece(std::unique_ptr<ChessPiece> piece, Position pos);
    void undoMove(MoveInfo& info);

    ChessPiece* getPiece(Position pos) const;

    bool isEmpty(Position pos) const;
    static bool inBounds(Position pos);
    bool isPathClear(const Move &move) const;
    void promotePawn(Position pos, PromotionPieces promotionType);

    void printBoard() const;

    void clearBoard() {
        for (auto& row : board) {
            for (auto& piece : row) {
                piece.reset();
            }
        }
    }
};
