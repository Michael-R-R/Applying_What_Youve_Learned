#include "RoguePiece.h"
#include "Board.h"
#include "Tile.h"

RoguePiece::RoguePiece(int id, int teamId, QWidget* parent) :
    BasePiece(3, id, teamId, 12, 10, parent)
{
    banner->setStyleSheet("QProgressBar::chunk { background: rgb(25, 66, 255); }");
    title->setText("Rogue");
}

RoguePiece::~RoguePiece()
{

}

void RoguePiece::highlightMoves(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y() + 1)); // NE + 0
    points.append(QPoint(position.x() - 2, position.y() + 2)); // NE + 1
    points.append(QPoint(position.x() + 1, position.y() + 1)); // SE + 0
    points.append(QPoint(position.x() + 2, position.y() + 2)); // SE + 1
    points.append(QPoint(position.x() + 1, position.y() - 1)); // SW + 0
    points.append(QPoint(position.x() + 2, position.y() - 2)); // SW + 1
    points.append(QPoint(position.x() - 1, position.y() - 1)); // NW + 0
    points.append(QPoint(position.x() - 2, position.y() - 2)); // NW + 1

    auto tiles = findValidMoveTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(25, 66, 255);
}

void RoguePiece::highlightAttacks(Board& board)
{
    QVector<QPoint> points;
    points.append(QPoint(position.x() - 1, position.y())); // N
    points.append(QPoint(position.x(), position.y() + 1)); // E
    points.append(QPoint(position.x() + 1, position.y())); // S
    points.append(QPoint(position.x(), position.y() - 1)); // W

    auto tiles = findValidAttackTiles(points, board);
    for(auto* i : qAsConst(tiles))
        i->highlightTile(230, 0, 0);
}
