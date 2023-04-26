#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include "BasePiece.h"

Game::Game(Board& board_, QObject* parent) :
    QObject(parent),
    currPhase(TurnPhase::NoMoveSelected),
    board(board_),
    player1(new Player(1, QColor(230, 0, 0), this)),
    player2(new Player(2, QColor(0, 0, 230), this)),
    roundCount(0),
    currPlayer(nullptr), selectedTile(nullptr)
{

}

Game::~Game()
{

}

void Game::start()
{
    board.initialize(*player1, *player2);

    currPlayer = player1;

    connect(player1, &Player::pieceRemoved, &board, &Board::clearTile);
    connect(player2, &Player::pieceRemoved, &board, &Board::clearTile);
    connect(&board, &Board::tileClicked, this, &Game::onTileClicked);
}

void Game::onTurnEnded(const int prevId)
{
    currPlayer = (prevId == 1) ? player2 : player1;
    selectedTile = nullptr;
    roundCount++;
}

void Game::onTileClicked(Board& board, Tile& tile)
{
    switch(currPhase)
    {
    case TurnPhase::NoMoveSelected:
    {
        if(tile.isEmpty())
            return;

        BasePiece* piece = tile.getPiece();
        if(currPlayer->getPlayerId() != piece->getTeamId())
            return;

        piece->highlightMoves(board);
        selectedTile = &tile;
        currPhase = TurnPhase::MoveSelected;

        break;
    }
    case TurnPhase::MoveSelected:
    {
        if(*selectedTile == tile)
        {
            board.clearHighlights();
            selectedTile->getPiece()->highlightAttacks(board);
            currPhase = TurnPhase::NoAttackSelected;
        }
        else if(tile.isEmpty())
        {
            if(!doMovePhase(board, tile))
                break;

            board.clearHighlights();
            selectedTile = &tile;
            selectedTile->getPiece()->highlightAttacks(board);
            currPhase = TurnPhase::NoAttackSelected;
        }
        else if(!tile.isEmpty())
        {
            board.clearHighlights();
            selectedTile = nullptr;
            currPhase = TurnPhase::NoMoveSelected;
            onTileClicked(board, tile);
        }

        break;
    }
    case TurnPhase::NoAttackSelected:
    {
        if(*selectedTile == tile)
        {
            board.clearHighlights();
            currPhase = TurnPhase::NoMoveSelected;
            selectedTile = nullptr;
            onTurnEnded(currPlayer->getPlayerId());
            emit turnEnded(currPlayer->getPlayerId());
        }
        else if(doAttackPhase(board, tile))
        {
            board.clearHighlights();
            currPhase = TurnPhase::NoMoveSelected;
            selectedTile = nullptr;
            onTurnEnded(currPlayer->getPlayerId());
            emit turnEnded(currPlayer->getPlayerId());
        }

        break;
    }
    default: { break; }
    }
}

bool Game::doMovePhase(Board& board, Tile& tile)
{
    if(!selectedTile)
        return false;

    BasePiece* piece = selectedTile->getPiece();
    if(!piece)
        return false;

    const QPoint& p = tile.getPosition();
    return piece->doMove(p.x(), p.y(), board);
}

bool Game::doAttackPhase(Board& board, Tile& tile)
{
    if(!selectedTile)
        return false;

    BasePiece* piece = selectedTile->getPiece();
    if(!piece)
        return false;

    const QPoint& p = tile.getPosition();
    return piece->doAttack(p.x(), p.y(), board);
}

