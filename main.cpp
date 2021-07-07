// main.cpp.c
// marc, marc@gruita.ro

#include "controller/board.h"
#include "ui/window.h"
#include <string>
#include <QApplication>

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    std::string filename = "../input.txt";

    Board board{ filename };

    std::vector<Window*> windows;
    for (auto player: board.getPlayers()) {
        windows.push_back(new Window{nullptr, &board, player});
    }

    for (auto w: windows) w->show();

    return QApplication::exec();
}
