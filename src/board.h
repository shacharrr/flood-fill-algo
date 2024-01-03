#ifndef BOARD_H
#define BOARD_H

enum point_state {
    NONE = 0,
    FILLED = 1
};

struct terminal_board {
    int w;
    int h;
    int* board;
};

void set_point(struct terminal_board* board, int x, int y, int ps);
int get_point(struct terminal_board* board, int x, int y);

void display_board(struct terminal_board board);

#endif // !BOARD_H
