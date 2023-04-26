#pragma once

#include <QTableWidget>

class Player;
class Tile;

class Board : public QTableWidget
{
    Q_OBJECT

public:
    Board(const int rows, const int cols, QWidget* parent = nullptr);
    ~Board();

    void initialize(Player& p1, Player& p2);
    void clearHighlights();
    bool boundsCheck(const int row, const int col);

public slots:
    void clearTile(const QPoint& p);

private slots:
    void emitTileClicked(int row, int col);

signals:
    void tileClicked(Board& board, Tile& tile);
};

