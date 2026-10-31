#pragma once

enum Colour{
    White,
    Black
};

struct Position {
    int row;
    int column;

    Position() = default;

    Position(int r, int c): row(r), column(c){}

    bool operator==(const Position &second) const;
};

enum class PieceTypes {
    Pawn,
    Knight,
    Bishop,
    Rook,
    King,
    Queen
};

class Board;

//virtual class ChessPiece, using Factory design pattern
class ChessPiece {
protected:
    Colour pieceColour;
    Position piecePosition;

public:
    ChessPiece(Colour colour, Position position): pieceColour(colour), piecePosition(position){}

    virtual ~ChessPiece()=default;

    Colour getPieceColour() const;
    Position getPiecePosition() const;

    void setPiecePosition(const Position &pos);

    virtual char getPieceSymbol() const = 0;
    virtual PieceTypes getPieceType() const = 0;

    virtual bool canMove(const Board &board, const Position &destination) const = 0;
};


//