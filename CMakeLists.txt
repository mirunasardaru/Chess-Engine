cmake_minimum_required(VERSION 3.30)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(ChessEngine main.cpp
        src/pieces/pieces.cpp
        include/pieces/pieces.h
        include/pieces/pawn.h
        include/pieces/knight.h
        include/pieces/bishop.h
        include/pieces/rook.h
        include/pieces/queen.h
        include/pieces/king.h
        src/pieces/pawn.cpp
        src/pieces/bishop.cpp
        src/pieces/knight.cpp
        src/pieces/rook.cpp
        src/pieces/queen.cpp
        src/pieces/king.cpp
        include/pieces/piecesFactory.h
        src/pieces/piecesFactory.cpp
        src/model/board.cpp
        include/model/board.h
        include/model/moves.h
        src/model/moves.cpp
        include/game/game.h
        src/game/game.cpp
        include/model/promotionPieces.h
        src/model/promotionPieces.cpp)

target_include_directories(ChessEngine PRIVATE include)