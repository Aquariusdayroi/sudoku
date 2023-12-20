#include "naked_pairs.h"
#include<stdio.h>
#include <stdlib.h>

bool check_value(Cell *a, Cell *b) {
    for(int val = 1; val<=BOARD_SIZE; val++) {
        if(is_candidate(a, val)^is_candidate(b, val)) return false;
    }
    return (a->num_candidates==2 && b->num_candidates == 2);
}

void set_naked_pair(Cell **p_cell, Cell *a, Cell *b) {
    for(int i=0; i<BOARD_SIZE; i++) {
        if(p_cell[i]==a || p_cell[i]==b) continue;
        for(int val = 1; val<=BOARD_SIZE; val++) {
            if(is_candidate(a, val) && is_candidate(p_cell[i], val)) 
                unset_candidate(p_cell[i], val);
        }
    }
}

int find_naked_pairs_rows(Cell **p_cell, int oke[][BOARD_SIZE*BOARD_SIZE], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {
            
            int x = id*BOARD_SIZE+i;
            int y = id*BOARD_SIZE+j;

            if(!oke[x][y] && check_value(p_cell[i], p_cell[j])) {
                //  printf("%d, %d, %d____\n", x, y, id);
                res++;
                oke[x][y] = 1;
                set_naked_pair(p_cell, p_cell[i], p_cell[j]);
            }
        }
    }
    return res;
}

int find_naked_pairs_cols(Cell **p_cell, int oke[][BOARD_SIZE*BOARD_SIZE], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {
            int x = i*BOARD_SIZE+id;
            int y = j*BOARD_SIZE+id;
            if(!oke[x][y] && check_value(p_cell[i], p_cell[j])) {
                res++;
                oke[x][y] = 1;
                set_naked_pair(p_cell, p_cell[i], p_cell[j]);
            }
        }
    }
    return res;
}

int find_naked_pairs_boxes(Cell **p_cell, int oke[][BOARD_SIZE*BOARD_SIZE], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {

            int x = 3*(id/3)*BOARD_SIZE+(i/3)*BOARD_SIZE+(id%3)*3+i%3;
            int y = 3*(id/3)*BOARD_SIZE+(j/3)*BOARD_SIZE+(id%3)*3+j%3;
        
            if(!oke[x][y] && check_value(p_cell[i], p_cell[j])) {
                // printf("%d, %d, %d\n", x, y, id);
                res++;
                oke[x][y] = 1;
                set_naked_pair(p_cell, p_cell[i], p_cell[j]);
            }
        }
    }
    return res;
}


int naked_pairs(SudokuBoard *p_board)
{
    int res = 0;
    int oke[BOARD_SIZE*BOARD_SIZE][BOARD_SIZE*BOARD_SIZE] = {{0}};
    
    for(int i=0; i<BOARD_SIZE; i++) {
        res += find_naked_pairs_rows(p_board->p_rows[i], oke, i);
        res += find_naked_pairs_cols(p_board->p_cols[i], oke, i);
        res += find_naked_pairs_boxes(p_board->p_boxes[i], oke, i);
    }
    
    // free(oke);
    return res;
}