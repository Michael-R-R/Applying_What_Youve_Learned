#pragma once

#include <QSet>

#include "BasePiece.h"

class BarbarianPiece : public BasePiece
{

public:
    BarbarianPiece(int id, int teamId, QWidget* parent = nullptr);
    ~BarbarianPiece();

    void highlightMoves(Board& board) override;
    void highlightAttacks(Board& board) override;
};

