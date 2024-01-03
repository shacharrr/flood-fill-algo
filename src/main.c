#include <stdlib.h>
#include "board.h"

#define WIDTH   50
#define HEIGHT  50

#define CHECK_ARRAY_N 2
const int CHECK_ARRAY[] = {1, -1};

struct terminal_board b;

void flood_fill(int x, int y) {
    set_point(&b, x, y, FILLED);
    for(int i = 0; i < CHECK_ARRAY_N; i++) {
        if(!get_point(&b, x, y + CHECK_ARRAY[i])) {
            flood_fill(x, y + CHECK_ARRAY[i]);
        }
        if(!get_point(&b, x + CHECK_ARRAY[i], y)) {
            flood_fill(x + CHECK_ARRAY[i], y);
        }
    }
}

int main(int argc, char** argv) {
    b.w = WIDTH;
    b.h = HEIGHT;
    b.board = (int*)calloc(WIDTH*HEIGHT, sizeof(int));

    // BUILD A TRINAGLE
    for(int i = 10; i < 30; i++) {
        set_point(&b, i, i, FILLED);
        set_point(&b, i, 30, FILLED);
        set_point(&b, 10, i, FILLED);
    }

    flood_fill(15, 20);
    
    display_board(b);

    free(b.board);

    return 0;
}
