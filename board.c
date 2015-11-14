#include <stdlib.h>

#include "board.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

void set_value_at(int *board, int row, int column, int value) {
    board[(BOARD_WIDTH * row) + column] = value;
}

int value_at(int *board, int row, int column) {
    return board[(BOARD_WIDTH * row) + column];
}

int check_row(int *board, int r) {
    int row_filled = 1;
    for (int c = 0; c < BOARD_WIDTH; c++) {
        if (value_at(board, r, c) == 0) {
            row_filled = 0;
        }
    }
    return row_filled;
}

void shift_rows_down(int *board, int r) {
    if (r > 0 && r < BOARD_HEIGHT - 1) { 
        // For each column,
        for (int c = 0; c < BOARD_WIDTH; c++) {
            int prev = 0;

            // Go down each row,
            for (int ri = 0; ri <= r; ri++) {
                // Get the value of the current row
                int next = value_at(board, ri, c);

                // And replace it with the one from above
                set_value_at(board, ri, prev);
                prev = next;
            }
        }
    }
}

void clear_full_rows(int *board) {
    // Start from the top and clear full rows by shifting the previous
    // rows down

}
