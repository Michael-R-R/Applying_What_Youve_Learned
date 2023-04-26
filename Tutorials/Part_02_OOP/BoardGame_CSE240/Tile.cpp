#include "Tile.h"
#include "BasePiece.h"

Tile::Tile(const QPoint& p, const QColor& color, QWidget* parent) :
    QWidget(parent),
    vLayout(new QVBoxLayout(this)),
    position(p),
    tileCol(color),
    heldPiece(nullptr)
{
    QString style = QString("background-color: rgb(%1, %2, %3);").arg(QString::number(tileCol.red()),
                                                                      QString::number(tileCol.green()),
                                                                      QString::number(tileCol.blue()));
    setStyleSheet(style);
}

Tile::~Tile()
{

}

void Tile::highlightTile(const int r, const int g, const int b)
{
    QString style = QString("background-color: rgb(%1, %2, %3);"
                            "border: 3px solid rgb(%4, %5, %6);").arg(
                            QString::number(tileCol.red()),
                            QString::number(tileCol.green()),
                            QString::number(tileCol.blue()),
                            QString::number(r),
                            QString::number(g),
                            QString::number(b));

    setStyleSheet(style);
}

void Tile::clearHighlight()
{
    QString style = QString("background-color: rgb(%1, %2, %3);"
                            "border: 0px solid white;").arg(
                            QString::number(tileCol.red()),
                            QString::number(tileCol.green()),
                            QString::number(tileCol.blue()));

    setStyleSheet(style);
}

bool Tile::isEmpty()
{
    return (heldPiece == nullptr);
}

void Tile::clear()
{
    heldPiece = nullptr;
}

const QPoint& Tile::getPosition()
{
    return position;
}

BasePiece* Tile::getPiece() const
{
    return heldPiece;
}

void Tile::setPiece(BasePiece* val)
{
    heldPiece = val;
    vLayout->insertWidget(0, val);
}
