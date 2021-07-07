// player.h
// marc, marc@gruita.ro
#pragma once

#include <string>
#include <iostream>
#include <vector>

class Player {
private:
    //int id;
    std::string name;
    //std::vector<Coords> hits;
    bool dead = false;

public:
    explicit Player(std::string name): name(name) {//, id(id) {
        //this->id = id;
        std::cout<<"created player "<<name<<'\n';
    }
    Player() = default;

    std::string getName() { return name; }

    void kill() { dead = true; }
    bool getStatus() { return dead; }
};
