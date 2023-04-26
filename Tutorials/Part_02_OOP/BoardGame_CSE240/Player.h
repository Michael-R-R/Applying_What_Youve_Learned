#pragma once

#include <QObject>
#include <QColor>
#include <QVector>

class BasePiece;
class Board;
class Tile;

class Player : public QObject
{
    Q_OBJECT

    int playerId;
    QColor playerCol;
    QVector<BasePiece*> pieces;

public:
    Player(const int id, const QColor& col, QObject* parent = nullptr);
    ~Player();

    int getPlayerId() const { return playerId; }
    const QVector<BasePiece*>& getPieces() const { return pieces; }

private:
    void setup();

private slots:
    void removePiece(const int id);

signals:
    void pieceRemoved(const QPoint& p);
    void emptied();
};

