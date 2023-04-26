#include "BasePiece.h"
#include "Board.h"
#include "Tile.h"

BasePiece::BasePiece(const int type_, const int id_, const int teamId_,
                     const int health_, const int damage_, QWidget* parent) :
    QWidget(parent),
    vLayout(new QVBoxLayout(this)),
    banner(new QProgressBar(this)),
    title(new QLabel(this)),
    type(type_),
    id(id_),
    teamId(teamId_),
    health(health_),
    damage(damage_),
    position(),
    tempValidMoves(), tempValidAttacks()
{
    banner->setTextVisible(false);
    banner->setMaximum(health);
    banner->setValue(health);

    vLayout->addWidget(banner);
    vLayout->addWidget(title);
}

BasePiece::~BasePiece()
{

}

bool BasePiece::doMove(const int row, const int col, Board& board)
{
    Tile* oldTile = static_cast<Tile*>(board.cellWidget(position.x(), position.y()));
    Tile* newTile = static_cast<Tile*>(board.cellWidget(row, col));

    if(!tempValidMoves.contains(newTile))
        return false;

    oldTile->clear();

    position = QPoint(row, col);
    newTile->setPiece(this);

    return true;
}

bool BasePiece::doAttack(const int row, const int col, Board& board)
{
    Tile* tileToAttack = static_cast<Tile*>(board.cellWidget(row, col));
    if(!tempValidAttacks.contains(tileToAttack))
        return false;

    if(tileToAttack->isEmpty())
        return true;

    BasePiece* pieceToAttack = tileToAttack->getPiece();
    pieceToAttack->takeDamage(damage);

    return true;
}

void BasePiece::takeDamage(const int val)
{
    health -= val;
    banner->setValue(health);
    if(health < 0)
        emit dead(id);
}

bool BasePiece::checkMoveValidity(const QPoint& p, Board& board)
{
    if(!board.boundsCheck(p.x(), p.y()))
        return false;

    Tile* tile = static_cast<Tile*>(board.cellWidget(p.x(), p.y()));
    if(!tile->isEmpty())
        return false;

    return true;
}

QSet<Tile*> BasePiece::findValidMoveTiles(const QVector<QPoint>& p, Board& board)
{
    tempValidMoves.clear();

    for(auto& i : p)
    {
        if(checkMoveValidity(i, board))
            tempValidMoves.insert(static_cast<Tile*>(board.cellWidget(i.x(), i.y())));
    }

    return tempValidMoves;
}

bool BasePiece::checkAttackValidity(const QPoint& p, Board& board)
{
    if(!board.boundsCheck(p.x(), p.y()))
        return false;

    Tile* tile = static_cast<Tile*>(board.cellWidget(p.x(), p.y()));
    if(tile->isEmpty())
        return true;

    BasePiece* piece = tile->getPiece();
    if(this->teamId == piece->getTeamId())
        return false;

    return true;
}

QSet<Tile*> BasePiece::findValidAttackTiles(const QVector<QPoint>& p, Board& board)
{
    tempValidAttacks.clear();

    for(auto& i : p)
    {
        if(checkAttackValidity(i, board))
            tempValidAttacks.insert(static_cast<Tile*>(board.cellWidget(i.x(), i.y())));
    }

    return tempValidAttacks;
}

