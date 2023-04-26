#pragma once

#include "BasePiece.h"

class RangerPiece : public BasePiece
{

public:
    RangerPiece(int id, int teamId, QWidget* parent = nullptr);
    ~RangerPiece();

    void highlightMoves(Board& board) override;
    void highlightAttacks(Board& board) override;
};

