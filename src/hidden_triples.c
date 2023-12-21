#include "hidden_triples.h"
#include <stdio.h>

bool isValid(int n) 
{
    return n == 2 || n == 3;
}

void Exist(Cell **list_cell, int *counter, Cell *cell)
{
    if(cell == NULL) return;
    for(int i = 0; i < *counter; i++)
    {
        if(list_cell[i] == cell)
        {
            return;
        }
    }
    list_cell[(*counter)++] = cell;
}

bool check(Cell **list_cell, int candidate)
{
    return  is_candidate(list_cell[0], candidate) 
            && is_candidate(list_cell[1], candidate) 
            && is_candidate(list_cell[2], candidate);
}

bool check1(Cell *cell, int cand1, int cand2, int cand3)
{
    return  is_candidate(cell, cand1) 
            + is_candidate(cell, cand2)
            + is_candidate(cell, cand3) >= 2;
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

    for(int cand1 = 1; cand1 < BOARD_SIZE; cand1++) 
    {
        if(isValid(n[cand1]) == false) continue;

        for(int cand2 = cand1 + 1; cand2 < BOARD_SIZE; cand2++)
        {
            if(isValid(n[cand2]) == false) continue;

            for(int cand3 = cand2 + 1; cand3 <= BOARD_SIZE; cand3++)
            {
                if(isValid(n[cand3]) == false) continue;

                Cell *list_cell[9];
 
                int counter = 0;

                for(int kCell = 0; kCell < 3; kCell++)
                {
                    Exist(list_cell, &counter, coords[cand1][kCell]);
                    Exist(list_cell, &counter, coords[cand2][kCell]);
                    Exist(list_cell, &counter, coords[cand3][kCell]);
                }

                if(counter != 3) continue;

                if((check(list_cell, cand1) || check(list_cell, cand2) || check(list_cell, cand3))
                    && check1(list_cell[0], cand1, cand2, cand3)
                    && check1(list_cell[1], cand1, cand2, cand3)
                    && check1(list_cell[2], cand1, cand2, cand3))
                {
                    bool result = false;
                    for(int kCell = 0; kCell < 3; kCell++)
                    {
                        Cell *cell = list_cell[kCell];

                        if(cell->num_candidates <= 3) continue;
                        result = true;
                        for(int rm_cand = 1; rm_cand <= BOARD_SIZE; rm_cand++)
                        {
                            if(rm_cand != cand1 && rm_cand != cand2 && rm_cand != cand3 && is_candidate(cell, rm_cand))
                            {
                                unset_candidate(cell, rm_cand);
                            }
                        }
                    }

                    // printf("cand: %d %d %d %s\n", cand1, cand2, cand3, result ? "YES" : "NO");
                    // if(result)
                    // {
                    //     printf("Cell: {%d, %d}, {%d, %d}, {%d, %d}\n", 
                    //                 list_cell[0]->row_index, list_cell[0]->col_index,
                    //                 list_cell[1]->row_index, list_cell[1]->col_index,
                    //                 list_cell[2]->row_index, list_cell[2]->col_index);
                    // }

                    if(result) (*p_counter)++;
                }

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