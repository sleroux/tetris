#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

void set_value_at(int *board, int row, int column, int value);

int value_at(int *board, int row, int column);

int check_row(int *board, int r);

void shift_row_down(int *board, int r);

void clear_full_rows(int *board);

#endif /* BOARD_H */

