#include <check.h>

#include "board.h"

START_TEST(test_value_at) {
    int board[BOARD_WIDTH * BOARD_HEIGHT];
    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {
            int i = (BOARD_WIDTH * r) + c;
            board[i] = i;
        }
    }

    ck_assert_int_eq(value_at(board, 0, 0), 0);
    ck_assert_int_eq(value_at(board, 0, 1), 1);
    ck_assert_int_eq(value_at(board, 1, 0), BOARD_WIDTH);
    ck_assert_int_eq(value_at(board, BOARD_HEIGHT - 1, BOARD_WIDTH - 1), 
                    (BOARD_WIDTH * BOARD_HEIGHT) - 1);
}
END_TEST

START_TEST(test_check_row) {
    // Don't fill the first row but fill the second
    int board[BOARD_WIDTH * BOARD_HEIGHT];
    board[0] = 1;

    for (int c = 0; c < BOARD_WIDTH; c++) {
        set_value_at(board, 1, c, 42);
    }

    ck_assert_int_eq(check_row(board, 0), 0);
    ck_assert_int_eq(check_row(board, 1), 1);
}
END_TEST

START_TEST(test_clear_full_rows) {
    int board[BOARD_WIDTH * BOARD_HEIGHT];
    board[0] = 1;

    // Fill 2nd and 5th rows
    for (int c = 0; c < BOARD_WIDTH; c++) {
        set_value_at(board, 1, c, 42);
    }

    for (int c = 0; c < BOARD_WIDTH; c++) {
        set_value_at(board, 4, c, 42);
    }

    int *rowsToDelete;
    int numRowsToDelete;
    mark_rows_to_delete(board, &rowsToDelete, &numRowsToDelete);

    ck_assert_int_eq(numRowsToDelete, 2);
    ck_assert_int_eq(rowsToDelete[0], 1);
    ck_assert_int_eq(rowsToDelete[0], 4);
}
END_TEST

Suite *board_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("Board");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_value_at);
    tcase_add_test(tc_core, test_check_row);
    tcase_add_test(tc_core, test_mark_rows_to_delete);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int numberFailed;
    Suite *s;
    SRunner *sr;
    
    s = board_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    numberFailed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (numberFailed == 0) ? 0 : 1;
}
