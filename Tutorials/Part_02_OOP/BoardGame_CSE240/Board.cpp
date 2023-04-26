#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "BasePiece.h"
#include <QHeaderView>

Board::Board(const int rows, const int cols, QWidget* parent) :
    QTableWidget(rows, cols, parent)
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setSelectionMode(QAbstractItemView::NoSelection);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();

    connect(this, &Board::cellClicked, this, &Board::emitTileClicked);
}

Board::~Board()
{

}

void Board::initialize(Player& p1, Player& p2)
{
    // Init board with tiles
    for(int row = 0; row < rowCount(); row++)
    {
        for(int col = 0; col < columnCount(); col++)
        {
            Tile* tile = nullptr;

            if(((row + col) % 2) == 0)
                tile = new Tile(QPoint(row, col), QColor(255, 255, 255), this);
            else
                tile = new Tile(QPoint(row, col), QColor(120, 120, 120), this);

            this->setCellWidget(row, col, tile);
        }
    }

    // Set Player1 pieces
    int count = 0;
    const auto& p1Pieces = p1.getPieces();
    for(int row = 0; row < 2; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            BasePiece* piece = p1Pieces[count++];
            piece->setPosition(QPoint(row, col));

            auto* tile = static_cast<Tile*>(cellWidget(row, col));
            tile->setPiece(piece);
        }
    }

    // Set Player2 pieces
    count = 0;
    const auto& p2Pieces = p2.getPieces();
    for(int row = 7; row > 5; row--)
    {
        for(int col = 0; col < 8; col++)
        {
            BasePiece* piece = p2Pieces[count++];
            piece->setPosition(QPoint(row, col));

            auto* tile = static_cast<Tile*>(cellWidget(row, col));
            tile->setPiece(piece);
        }
    }
}

void Board::clearHighlights()
{
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            Tile* tile = static_cast<Tile*>(cellWidget(row, col));
            tile->clearHighlight();
        }
    }
}

bool Board::boundsCheck(const int row, const int col)
{
    return ((row > -1 && row < rowCount()) &&
            (col > -1 && col < columnCount()));
}

void Board::clearTile(const QPoint& p)
{
    Tile* tile = static_cast<Tile*>(cellWidget(p.x(), p.y()));
    tile->clear();
}

void Board::emitTileClicked(int row, int col)
{
    emit tileClicked(*this, *static_cast<Tile*>(cellWidget(row, col)));
}

