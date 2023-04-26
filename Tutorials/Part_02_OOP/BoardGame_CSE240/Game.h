#pragma once

#include <QObject>

class Board;
class Player;
class Tile;

class Game : public QObject
{
    Q_OBJECT

    enum class TurnPhase
    {
        NoMoveSelected,
        MoveSelected,
        NoAttackSelected
    };

    TurnPhase currPhase;

protected:
    Board& board;

    Player* player1;
    Player* player2;
    unsigned roundCount;

    Player* currPlayer;
    Tile* selectedTile;

public:
    Game(Board& board_, QObject* parent = nullptr);
    ~Game();

    virtual void start();

protected:
    virtual void onTurnEnded(const int prevId);

protected slots:
    virtual void onTileClicked(Board& board, Tile& tile);

private:
    bool doMovePhase(Board& board, Tile& tile);
    bool doAttackPhase(Board& board, Tile& tile);

signals:
    void turnEnded(const int prevId);
};

