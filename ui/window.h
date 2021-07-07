// Window.h
// marc, marc@gruita.ro

#pragma once

#include <QWidget>
#include <QTableView>
#include "../controller/board.h"
#include "model/model.h"
#include <QPushButton>

class Window: public QWidget, public Observer {
    Q_OBJECT

public:
    explicit Window(QObject* parent = nullptr, Board* board = nullptr, Player player = Player());
    void update() override;
private:
    Board* board;
    Model* model;
    Player player;

    QTableView* table;
    QLineEdit* input;

    QPushButton* revealButton;
    QPushButton* markButton;

    void reveal();
    void mark();
};


