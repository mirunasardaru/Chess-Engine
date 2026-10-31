#pragma once

#include <memory>
#include "pieces/pieces.h"

struct Move {
    Position from;
    Position to;

    Move(Position from, Position to): from(from), to(to){}
    Move() = default;
    bool operator==(const Move &second);
};

struct MoveInfo {
    Move move;
    std::unique_ptr<ChessPiece> capturedPiece;
    ChessPiece* movedPiece;
    Position capturedPosition;
    bool pieceWasMoved = false;
};