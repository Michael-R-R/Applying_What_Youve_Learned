#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QLabel>
#include <QPoint>
#include <QVector>
#include <QSet>

class Board;
class Tile;

class BasePiece : public QWidget
{
    Q_OBJECT

protected:
    QVBoxLayout* vLayout;
    QProgressBar* banner;
    QLabel* title;

    int type;
    int id;
    int teamId;

    int health;
    int damage;

    QPoint position;
    QSet<Tile*> tempValidMoves;
    QSet<Tile*> tempValidAttacks;

public:
    BasePiece(const int type_, const int id_, const int teamId_,
              const int health_, const int damage_, QWidget* parent = nullptr);
    ~BasePiece();

    bool operator==(const BasePiece& other) const { return (this->id == other.id); }
    bool operator!=(const BasePiece& other) const { return (this->id != other.id); }

    virtual void highlightMoves(Board& board) = 0;
    virtual void highlightAttacks(Board& board) = 0;

    virtual bool doMove(const int row, const int col, Board& board);
    virtual bool doAttack(const int row, const int col, Board& board);

    void takeDamage(const int val);

    int getType() const { return type; }
    int getId() const { return id; }
    int getTeamId() const { return teamId; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    const QPoint& getPosition() const { return position; }

    void setPosition(const QPoint& val) { position = val; }

protected:
    bool checkMoveValidity(const QPoint& p, Board& board);
    QSet<Tile*> findValidMoveTiles(const QVector<QPoint>& p, Board& board);

    bool checkAttackValidity(const QPoint& p, Board& board);
    QSet<Tile*> findValidAttackTiles(const QVector<QPoint>& p, Board& board);

signals:
    void dead(const int id);
};

