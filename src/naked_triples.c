#include "naked_triples.h"
#include<stdio.h>
#include <stdlib.h>

#define BOARD_SIZE1D 81

bool check_val_triples(Cell *a, Cell *b, Cell *c) {
    int cnt = 0;
    for(int val = 1; val<=BOARD_SIZE; val++) {
        if(is_candidate(a, val)|is_candidate(b, val) | is_candidate(c, val)) cnt++;
    }
    int size_a = a->num_candidates;
    int size_b = b->num_candidates;
    int size_c = c->num_candidates;
    return (size_a >=2 && size_b >=2 && size_c >=2 &&
            size_a <=3 && size_b <= 3 && size_c <=3 && 
            cnt == 3 );
}

void set_naked_triples(Cell **p_cell, Cell *a, Cell *b, Cell *c) {
    for(int i=0; i<BOARD_SIZE; i++) {
        if(p_cell[i]==a || p_cell[i]==b || p_cell[i] == c) continue;
        for(int val = 1; val<=BOARD_SIZE; val++) {
            if(is_candidate(a, val) && is_candidate(p_cell[i], val)) 
                unset_candidate(p_cell[i], val);
            if(is_candidate(b, val) && is_candidate(p_cell[i], val)) 
                unset_candidate(p_cell[i], val);
            if(is_candidate(c, val) && is_candidate(p_cell[i], val)) 
                unset_candidate(p_cell[i], val);
        }
    }
}

int find_naked_triples_rows(Cell **p_cell, int oke[][BOARD_SIZE1D][BOARD_SIZE1D], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {
            for(int k = j+1; k<BOARD_SIZE; k++) {
                int x = id*BOARD_SIZE + i;
                int y = id*BOARD_SIZE + j;
                int z = id*BOARD_SIZE + k;
                if(!oke[x][y][z] && check_val_triples(p_cell[i], p_cell[j], p_cell[k])) {
                    res++;
                    oke[x][y][z] = 1;
                    set_naked_triples(p_cell, p_cell[i], p_cell[j], p_cell[k]);
                }
            }
        }
    }
    return res;
}

int find_naked_triples_cols(Cell **p_cell, int oke[][BOARD_SIZE1D][BOARD_SIZE*BOARD_SIZE], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {
            for(int k = j+1; k<BOARD_SIZE; k++) {

                int x = i*BOARD_SIZE + id;
                int y = j*BOARD_SIZE + id;
                int z = k*BOARD_SIZE + id;

                if(!oke[x][y][z] && check_val_triples(p_cell[i], p_cell[j], p_cell[k])) {
                    res++;
                    oke[x][y][z] = 1;
                    set_naked_triples(p_cell, p_cell[i], p_cell[j], p_cell[k]);
                }
            }
        }
    }
    return res;
}

int find_naked_triples_boxes(Cell **p_cell, int oke[][BOARD_SIZE1D][BOARD_SIZE1D], int id) {
    int res = 0;
    for(int i=0; i<BOARD_SIZE; i++) {
        for(int j=i+1; j<BOARD_SIZE; j++) {
            for(int k = j+1; k<BOARD_SIZE; k++) {
                
                int x = 3*(id/3)*BOARD_SIZE+(i/3)*BOARD_SIZE+(id%3)*3+i%3;
                int y = 3*(id/3)*BOARD_SIZE+(j/3)*BOARD_SIZE+(id%3)*3+j%3;
                int z = 3*(id/3)*BOARD_SIZE+(k/3)*BOARD_SIZE+(id%3)*3+k%3;
                
                
                if(!oke[x][y][z] && check_val_triples(p_cell[i], p_cell[j], p_cell[k])) {
                    // printf("%d, %d, %d, %d\n", x, y, z, id);
                    res++;
                    oke[x][y][z] = 1;
                    set_naked_triples(p_cell, p_cell[i], p_cell[j], p_cell[k]);
                }
            }
        }
    }
    return res;
}

int naked_triples(SudokuBoard *p_board)
{   
    int res = 0;
    int oke[BOARD_SIZE1D][BOARD_SIZE1D][BOARD_SIZE1D] = {{{0}}};
    
    for(int i =0; i<BOARD_SIZE; i++) {
        res += find_naked_triples_rows(p_board->p_rows[i], oke, i);
        res += find_naked_triples_cols(p_board->p_cols[i], oke, i);
        res += find_naked_triples_boxes(p_board->p_boxes[i], oke, i);
    }
    
    return res;
}