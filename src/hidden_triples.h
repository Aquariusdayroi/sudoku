#pragma once

#include "sudoku.h"

bool isValid(int n);

void hidden_triple_unit(Cell **p_cells, int *p_counter);

int hidden_triples(SudokuBoard *p_board);