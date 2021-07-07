// model.h
// marc, marc@gruita.ro

#pragma once
#include <QAbstractTableModel>
#include <QColor>
#include <QPalette>
#include "../../entities/player.h"
#include "../../controller/board.h"

class Model: public QAbstractTableModel {
    Q_OBJECT

private:
    Player* player;
    Board* board;

public:
    explicit Model(QWidget* parent = nullptr, Board* board = nullptr, Player* player = nullptr): board(board), player(player) {

    }

    int rowCount(const QModelIndex& parent) const override { return board->getSize(); }

    int columnCount(const QModelIndex& parent) const override { return board->getSize(); }

    void updateData() {
        emit layoutAboutToBeChanged();
        emit beginResetModel();
        //beginInsertRows(QModelIndex(), 0, service->size() - 1);
        qDebug() << "hitting";
        //endInsertRows();
        emit endResetModel();
        emit layoutChanged();
    }

    QVariant data(const QModelIndex &index, int role) const override {
        auto hits = board->getHits();
        auto marks = board->getMarks();
        auto mines = board->getMines();
        if (role == Qt::BackgroundRole) {
            for (auto hit: hits) {
                if (hit == Coords{.x = index.row(), .y = index.column()}) {
                    return QVariant(QColor(0, 0, 255, 100));
                }
            }
            for (auto mark: marks) {
                if (mark == Coords{.x = index.row(), .y = index.column()}) {
                    return QVariant(QColor(255, 0, 0, 100));
                }
            }
            return QVariant(QColor(0, 255, 0, 100));
        } else if (role == Qt::DisplayRole) {
            for (auto hit: hits) {
                if (hit == Coords{.x = index.row(), .y = index.column()}) {
                    int number = 0;
                    for (auto mine: mines) {
                        if (hit.adjacent(mine)) number++;
                    }

                    return QString(std::to_string(number).c_str());
                }
            }
            for (auto mark: marks) {
                if (mark == Coords{.x = index.row(), .y = index.column()}) {
                    return QString("*");
                }
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role == Qt::DisplayRole)
            return QString(std::to_string(section + 1).c_str());
        return QVariant();
    }
};
