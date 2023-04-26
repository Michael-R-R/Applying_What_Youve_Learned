#include "RangerPiece.h"
#include "Board.h"
#include "Tile.h"

RangerPiece::RangerPiece(int id, int teamId, QWidget* parent) :
    BasePiece(2, id, teamId, 15, 3, parent)
{
    banner->setStyleSheet("QProgressBar::chunk { background: rgb(0, 196, 20); }");
    title->setText("Ranger");
}

RangerPiece::~RangerPiece()
{

}

void RangerPiece::highlightMoves(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y())); // N
    points.append(QPoint(position.x(), position.y() + 1)); // E
    points.append(QPoint(position.x() + 1, position.y())); // S
    points.append(QPoint(position.x(), position.y() - 1)); // W

    auto tiles = findValidMoveTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(0, 196, 20);
}

void RangerPiece::highlightAttacks(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y())); // N + 0
    points.append(QPoint(position.x() - 2, position.y())); // N + 1
    points.append(QPoint(position.x() - 3, position.y())); // N + 2
    points.append(QPoint(position.x(), position.y() + 1)); // E + 0
    points.append(QPoint(position.x(), position.y() + 2)); // E + 1
    points.append(QPoint(position.x(), position.y() + 3)); // E + 2
    points.append(QPoint(position.x() + 1, position.y())); // S + 0
    points.append(QPoint(position.x() + 2, position.y())); // S + 1
    points.append(QPoint(position.x() + 3, position.y())); // S + 2
    points.append(QPoint(position.x(), position.y() - 1)); // W + 0
    points.append(QPoint(position.x(), position.y() - 2)); // W + 1
    points.append(QPoint(position.x(), position.y() - 3)); // W + 2

    auto tiles = findValidAttackTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(230, 0, 0);
}
