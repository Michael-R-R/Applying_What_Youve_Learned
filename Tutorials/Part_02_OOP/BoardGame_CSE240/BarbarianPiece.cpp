#include "BarbarianPiece.h"
#include "Board.h"
#include "Tile.h"

BarbarianPiece::BarbarianPiece(int id, int teamId, QWidget* parent) :
    BasePiece(1, id, teamId, 30, 5, parent)
{
    banner->setStyleSheet("QProgressBar::chunk { background: rgb(104, 3, 0); }");
    title->setText("Barbarian");
}

BarbarianPiece::~BarbarianPiece()
{

}

void BarbarianPiece::highlightMoves(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y())); // N
    points.append(QPoint(position.x(), position.y() + 1)); // E
    points.append(QPoint(position.x() + 1, position.y())); // S
    points.append(QPoint(position.x(), position.y() - 1)); // W

    auto tiles = findValidMoveTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(104, 3, 0);
}

void BarbarianPiece::highlightAttacks(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y())); // N
    points.append(QPoint(position.x() - 1, position.y() + 1)); // NE
    points.append(QPoint(position.x(), position.y() + 1)); // E
    points.append(QPoint(position.x() + 1, position.y() + 1)); // SE
    points.append(QPoint(position.x() + 1, position.y())); // S
    points.append(QPoint(position.x() + 1, position.y() - 1)); // SW
    points.append(QPoint(position.x(), position.y() - 1)); // W
    points.append(QPoint(position.x() - 1, position.y() - 1)); // NW

    auto tiles = findValidAttackTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(255, 0, 0);
}
