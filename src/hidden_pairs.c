#include "hidden_pairs.h"

void hidden_pair_unit(Cell **p_cells, int *p_counter) 
{
    int n[10] = {0};
    Cell *coords[10][2];
    
    for(int j1 = 0; j1 < BOARD_SIZE; j1++) 
    {
        if(p_cells[j1]->num_candidates == 1) continue;
        
        for(int cand = 1; cand <= BOARD_SIZE; cand++) 
        {
            if(is_candidate(p_cells[j1], cand)) 
            {
                if(n[cand] < 2) 
                {
                    coords[cand][n[cand]] = p_cells[j1];
                }
                n[cand]++;
            }
        }
    }

    for(int cand1 = 1; cand1 < BOARD_SIZE; cand1++) 
    {
        if(n[cand1] != 2) continue;
        
        for(int cand2 = cand1 + 1; cand2 <= BOARD_SIZE; cand2++) 
        {
            bool result = false;
            if( n[cand2] == 2
                && coords[cand1][0] == coords[cand2][0]
                && coords[cand1][1] == coords[cand2][1] )
            {
                for(int kCell = 0; kCell < 2; kCell++) 
                {
                    Cell *cell = coords[cand1][kCell];

                    if(cell->num_candidates == 2) continue;
                    for(int rm_cand = 1; rm_cand <= BOARD_SIZE; rm_cand++) 
                    {
                        if(rm_cand != cand1 && rm_cand != cand2 && is_candidate(cell, rm_cand)) 
                        {
                            unset_candidate(cell, rm_cand);
                        }
                    }
                    result = true;
                }
                
                if(result) (*p_counter)++;
            }
        }
    }
}

int hidden_pairs(SudokuBoard *p_board)
{
    int counter = 0;

    for(int i = 0; i < BOARD_SIZE; i++) 
    {
        hidden_pair_unit(p_board->p_rows[i], &counter);
        hidden_pair_unit(p_board->p_cols[i], &counter);
        hidden_pair_unit(p_board->p_boxes[i], &counter);
    }

    return counter;
}
