// board.cpp
// marc, marc@gruita.ro


#include "board.h"

Board::Board(std::string filename) {
    read(filename);
    int _ = minesCount;
    while (_ != 0) {
        if (_ < size)
            mines.push_back(Coords{ .x = _, .y = _ } );
        _--;
    }

    indexTurn = 0;
}

bool Board::reveal(std::string text) {
    Coords cell = Coords::fromString(text);

    if (find(hits.begin(), hits.end(), cell) != hits.end()) {
        throw std::runtime_error("already hit");
    }

    if (find(mines.begin(), mines.end(), cell) != mines.end()) {
        hits.push_back(cell);
        players[turn()].kill();
        std::cout<<"killed "<<players[turn()].getName()<<'\n';
        next();
        notify();
        return true;
    }

    hits.push_back(cell);
    next();
    notify();
    return false;
}

void Board::mark(std::string text) {
    Coords cell = Coords::fromString(text);

    if (find(hits.begin(), hits.end(), cell) != hits.end()) {
        throw std::runtime_error("already hit");
    }

    markedMines.push_back(cell);
    next();
    notify();
}

void Board::read(std::string filename) {
    std::ifstream in(filename);
    std::string _;
    in >> size;
    in >> minesCount;

    std::string name;
    while (in >> name) {
        players.push_back(Player(name));
    }
}

void Board::killCurrent() {
    players[turn()].kill();
    std::cout<<"killed "<<players[turn()].getName()<<'\n';
}



