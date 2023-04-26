#include "Player.h"
#include "BasePiece.h"
#include "RangerPiece.h"
#include "BarbarianPiece.h"
#include "RoguePiece.h"

Player::Player(const int id, const QColor& col, QObject* parent) :
    QObject(parent),
    playerId(id),
    playerCol(col),
    pieces()
{
    setup();
}

Player::~Player()
{
    for(int i = 0; i < pieces.size(); i++)
        delete pieces[i];
}

void Player::setup()
{
    int id = 0;

    for(int i = 0; i < 8; i++)
    {
        auto* piece = new RangerPiece(++id, playerId);
        piece->setStyleSheet(QString("border: 2px solid rgb(%1, %2, %3);").arg(QString::number(playerCol.red()),
                                                                               QString::number(playerCol.green()),
                                                                               QString::number(playerCol.blue())));
        connect(piece, &RangerPiece::dead, this, &Player::removePiece);
        pieces.append(piece);
    }

    for(int i = 0; i < 4; i++)
    {
        auto* piece = new BarbarianPiece(++id, playerId);
        piece->setStyleSheet(QString("border: 2px solid rgb(%1, %2, %3);").arg(QString::number(playerCol.red()),
                                                                               QString::number(playerCol.green()),
                                                                               QString::number(playerCol.blue())));
        connect(piece, &BarbarianPiece::dead, this, &Player::removePiece);
        pieces.append(piece);
    }

    for(int i = 0; i < 4; i++)
    {
        auto* piece = new RoguePiece(++id, playerId);
        piece->setStyleSheet(QString("border: 2px solid rgb(%1, %2, %3);").arg(QString::number(playerCol.red()),
                                                                               QString::number(playerCol.green()),
                                                                               QString::number(playerCol.blue())));
        connect(piece, &RoguePiece::dead, this, &Player::removePiece);
        pieces.append(piece);
    }
}

void Player::removePiece(const int id)
{
    for(int i = 0; i < pieces.size(); i++)
    {
        if(pieces[i]->getId() == id)
        {
            auto* temp = pieces[i];
            emit pieceRemoved(temp->getPosition());
            pieces.removeAt(i);
            delete temp;
            break;
        }
    }

    if(pieces.size() == 0)
        emit emptied();
}

