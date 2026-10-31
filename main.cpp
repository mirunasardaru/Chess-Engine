
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <limits.h>

#include "game/game.h"
#include "model/board.h"

using namespace std;


Position parsePosition(const string& text) {
    if (text.size() != 2) {
        return Position(-1, -1);
    }

    char column = tolower(text[0]);
    char row = text[1];

    if (column < 'a' || column > 'h') {
        return Position(-1, -1);
    }

    if (row < '1' || row > '8') {
        return Position(-1, -1);
    }

    int col = column - 'a';
    int boardRow = 8 - (row - '0');

    return Position(boardRow, col);
}


PromotionPieces parsePromotion(char c) {
    c = tolower(c);

    switch (c) {
        case 'q':
            return PromotionPieces::Queen;

        case 'r':
            return PromotionPieces::Rook;

        case 'b':
            return PromotionPieces::Bishop;

        case 'n':
            return PromotionPieces::Knight;

        default:
            return PromotionPieces::Queen;
    }
}


void printBoardWithCoordinates(const Board& board) {

    cout << "\n";
    cout << "    a b c d e f g h\n";
    cout << "  +-----------------+\n";

    for (int row = 0; row < 8; row++) {

        cout << 8 - row << " | ";

        for (int col = 0; col < 8; col++) {

            Position pos(row, col);
            ChessPiece* piece = board.getPiece(pos);

            if (piece == nullptr) {
                cout << ". ";
            }
            else {
                cout << piece->getPieceSymbol() << " ";
            }
        }

        cout << "| " << 8 - row << "\n";
    }

    cout << "  +-----------------+\n";
    cout << "    a b c d e f g h\n\n";
}


int main() {

    Game game;

    cout << "========================================\n";
    cout << "             CHESS ENGINE\n";
    cout << "========================================\n";
    cout << "\n";
    cout << "Mutari: e2 e4\n";
    cout << "Pentru iesire: quit\n";
    cout << "\n";

    while (true) {

        printBoardWithCoordinates(game.getBoard());

        Colour currentPlayer = game.getCurrentPlayer();

        if (currentPlayer == Colour::White) {
            cout << "Alb";
        }
        else {
            cout << "Negru";
        }

        cout << " muta.\n";
        cout << "> ";

        string input;
        getline(cin, input);

        if (input == "quit" || input == "exit") {
            cout << "Joc terminat.\n";
            break;
        }

        string fromText;
        string toText;

        stringstream ss(input);

        ss >> fromText >> toText;

        if (fromText.empty() || toText.empty()) {
            cout << "Format invalid. Foloseste: e2 e4\n";
            continue;
        }

        Position from = parsePosition(fromText);
        Position to = parsePosition(toText);

        if (!Board::inBounds(from) || !Board::inBounds(to)) {
            cout << "Pozitie invalida.\n";
            continue;
        }

        ChessPiece* piece = game.getBoard().getPiece(from);

        if (piece == nullptr) {
            cout << "Nu exista nicio piesa pe "
                 << fromText << ".\n";
            continue;
        }

        PromotionPieces promotionType = PromotionPieces::Queen;

        /*
         * Daca mutarea este a unui pion care ajunge
         * pe ultima linie, cerem piesa de promovare.
         */
        if (piece->getPieceType() == PieceTypes::Pawn) {

            if ((piece->getPieceColour() == Colour::White &&
                 to.row == 0) ||
                (piece->getPieceColour() == Colour::Black &&
                 to.row == 7)) {

                cout << "Promovare [q/r/b/n]: ";

                char promotion;
                cin >> promotion;

                cin.ignore(
                1000, '\n'
                );

                promotionType = parsePromotion(promotion);
            }
        }

        Move move(from, to);

        bool success = game.makeMove(move, promotionType);

        if (!success) {
            cout << "Mutare invalida!\n";
            continue;
        }

        cout << "Mutare efectuata: "
             << fromText << " -> "
             << toText << "\n";

        /*
         * Dupa mutare verificam daca adversarul
         * este in sah / mat / pat.
         */
        Colour opponent =
            game.getCurrentPlayer();

        if (game.isCheckmate(opponent)) {

            printBoardWithCoordinates(game.getBoard());

            if (opponent == Colour::White) {
                cout << "SAH-MAT! Negrul castiga!\n";
            }
            else {
                cout << "SAH-MAT! Albul castiga!\n";
            }

            break;
        }

        if (game.isStalemate(opponent)) {

            printBoardWithCoordinates(game.getBoard());

            cout << "PAT! Remiza.\n";

            break;
        }

        if (game.isCheck(opponent)) {
            cout << "SAH!\n";
        }
    }

    return 0;
}