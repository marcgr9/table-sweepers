// Window.cpp.cc
// marc, marc@gruita.ro

#include "window.h"
#include "model/model.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>

Window::Window(QObject *parent, Board *board, Player player): board(board), player(player) {
    setWindowTitle(QString(player.getName().c_str()));
    board->addObserver(this);

    table = new QTableView;
    input = new QLineEdit("");

    model = new Model{nullptr, board, &player};
    table->setModel(model);
    table->horizontalHeader()->setDefaultSectionSize(50);
    table->verticalHeader()->setDefaultSectionSize(50);
    auto layout = new QVBoxLayout();
    layout->addWidget(table);
    layout->addWidget(input);

    revealButton = new QPushButton("Reveal");
    connect(revealButton, &QPushButton::pressed, this, &Window::reveal);

    markButton = new QPushButton("Mark as mine");
    connect(markButton, &QPushButton::pressed, this, &Window::mark);

    layout->addWidget(revealButton);
    layout->addWidget(markButton);
    setLayout(layout);
}

void Window::reveal() {
    auto mb = new QMessageBox(this);
    auto cell = input->text().toStdString();

    if (cell.empty()) {
        mb->setText("Fields can't be empty");
        mb->exec();
        return;
    }

    try {
        board->reveal(cell);
    } catch (...) {
        mb->setText("Error");
        mb->exec();
    }


}

void Window::mark() {
    auto mb = new QMessageBox(this);
    auto cell = input->text().toStdString();

    if (cell.empty()) {
        mb->setText("Fields can't be empty");
        mb->exec();
        return;
    }

    try {
        board->mark(cell);
    } catch (...) {
        mb->setText("Error");
        mb->exec();
    }
}

void Window::update() {
    model->updateData();
    if (board->getPlayers()[board->getId(player.getName())].getStatus()) {
        revealButton->setEnabled(false);
        markButton->setEnabled(false);
        //board->next();
        return;
    }

    if (board->turn() != board->getId(player.getName())) {
        revealButton->setEnabled(false);
        markButton->setEnabled(false);
    } else {
        revealButton->setEnabled(true);
        markButton->setEnabled(true);
    }
}


