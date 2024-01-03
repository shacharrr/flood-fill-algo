#include <stdio.h>
#include "board.h"

void set_point(struct terminal_board* board, int x, int y, int ps) {
    if(x >= 0 && x < board->w && y >= 0 && y < board->h) {
        board->board[(y * board->w) + x] = ps;
    }
}

int get_point(struct terminal_board* board, int x, int y) {
    if(x >= 0 && x < board->w && y >= 0 && y < board->h) {
        return board->board[(y * board->w) + x]; 
    }
    return FILLED;
}

void display_board(struct terminal_board board) {
    printf("\033c");
    for(int y = 0; y < board.h; y++) {
        for(int x = 0; x < board.w; x++) {
            int point_state = get_point(&board, x, y);
            if(!point_state) {
                printf("   ");
            } else {
                printf(" # ");
            }
        }
        printf("\n");
    }
}

