#pragma once

#include "sudoku.h"

void hidden_pair_unit(Cell **p_cells, int *p_counter);

int hidden_pairs(SudokuBoard *p_board);
