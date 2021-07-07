// board.h
// marc, marc@gruita.ro
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../entities/player.h"
#include "../utils/observer.h"

struct Coords {
    int x, y;

    bool operator==(const Coords& other) {
        return other.x == this->x && other.y == this->y;
    }

    static Coords fromString(std::string str) {
        return Coords { .x = str[0] - 49, .y = str[1] - 49 };
    }

    bool adjacent(Coords other) {
        int _ = abs(this->x - other.x) + abs(this->y - other.y);
        return _ == 1 || _ == 2;
    }
};

class Board: public Observable {
private:
    int size;
    int minesCount;
    std::vector<Coords> mines;
    std::vector<Coords> hits;
    std::vector<Coords> markedMines;

    std::vector<Player> players;

    int indexTurn;

    int dead = 0;
    int markedMinesCount = 0;

public:
    explicit Board(std::string filename);

    void read(std::string filename);

    std::vector<Player> getPlayers() { return players; }
    int getSize() { return size; }

    auto getHits() { return hits; }
    auto getMarks() { return markedMines; }
    auto getMines() { return mines; }

    void reveal(std::string cell);
    void mark(std::string cell);
    int turn() {
        return indexTurn % players.size();
    }

    int getId(std::string name) {
        int i = 0;
        for (auto player: players) {
            if (player.getName() == name) return i;
            i++;
        }
        return i;
    }

    void killCurrent();
    void next() {
        if (dead == players.size() || markedMinesCount == mines.size()) throw std::runtime_error("done");
        indexTurn++;
        while (players[indexTurn].getStatus()) indexTurn++;
    }
};