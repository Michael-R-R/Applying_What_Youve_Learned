#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QPoint>
#include <QColor>

class BasePiece;

class Tile : public QWidget
{
    QVBoxLayout* vLayout;
    QPoint position;
    QColor tileCol;

    // DOES NOT OWN
    BasePiece* heldPiece;

public:
    Tile(const QPoint& p, const QColor& color, QWidget* parent = nullptr);
    ~Tile();

    bool operator==(const Tile& other) { return (this->position == other.position); }
    bool operator!=(const Tile& other) { return (this->position != other.position); }

    void highlightTile(const int r, const int g, const int b);
    void clearHighlight();
    bool isEmpty();
    void clear();

    const QPoint& getPosition();
    BasePiece* getPiece() const;

    void setPiece(BasePiece* val);
};

