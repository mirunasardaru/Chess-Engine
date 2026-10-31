#pragma once
#include "model/board.h"
#include "model/moves.h"
#include "model/promotionPieces.h"

class Game {
    Board board;
    Colour currentPlayer;
    Move lastMove;
    bool hasLastMove = false;

public:
    Game(): currentPlayer(Colour::White){}

    void switchTurn();
    bool makeMove(const Move& move, PromotionPieces promotionType = PromotionPieces::Queen);
    Colour getCurrentPlayer() const;
    Board &getBoard();

    bool isCheck(Colour colour) const;
    Position findKing(Colour colour) const;
    bool hasLegalMove(Colour colour);
    bool isCheckmate(Colour colour);
    bool isStalemate(Colour colour);
    bool isEnPassant(const Move& move) const;
    bool isCastling(const Move& move);
};