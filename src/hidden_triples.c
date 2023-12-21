#include "hidden_triples.h"
#include <stddef.h>

bool isValid(int n) 
{
    return n == 2 || n == 3;
}

void hidden_triple_unit(Cell **p_cells, int *p_counter) 
{
    int n[10] = {0};
    Cell *coords[10][3];
    for(int i = 1; i <= 9; i++) for(int j = 0; j < 3; j++) coords[i][j] = NULL;

    for(int j1 = 0; j1 < BOARD_SIZE; j1++) 
    {
        if(p_cells[j1]->num_candidates == 1) continue;

        for(int cand = 1; cand <= BOARD_SIZE; cand++) 
        {
            if(is_candidate(p_cells[j1], cand)) 
            {
                if(n[cand] < 3) 
                {
                    coords[cand][n[cand]] = p_cells[j1];
                }
                n[cand]++;
            }
        }
    }

    
}

int hidden_triples(SudokuBoard *p_board)
{
    int counter = 0;

    for(int i = 0; i < BOARD_SIZE; i++) 
    {
        hidden_triple_unit(p_board->p_rows[i], &counter);
        hidden_triple_unit(p_board->p_cols[i], &counter);
        hidden_triple_unit(p_board->p_boxes[i], &counter);
    }

    return counter;
}