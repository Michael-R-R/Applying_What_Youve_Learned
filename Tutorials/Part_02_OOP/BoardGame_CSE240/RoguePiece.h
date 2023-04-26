#pragma once

#include "BasePiece.h"

class RoguePiece : public BasePiece
{

public:
    RoguePiece(int id, int teamId, QWidget* parent = nullptr);
    ~RoguePiece();

    void highlightMoves(Board& board) override;
    void highlightAttacks(Board& board) override;
};

