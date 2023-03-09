Finis ça 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int is_valid(int **board, int row, int col, int val) {
    int i = 0;
    while (i < 9) {
        if (board[row][i] == val) {
            return 0;
        }
        i++;
    }

    i = 0;
    while (i < 9) {
        if (board[i][col] == val) {
            return 0;
        }
        i++;
    }

    int region_row = row - (row % 3);
    int region_col = col - (col % 3);
    int j = region_row;
    while (j < region_row + 3) {
        int k = region_col;
        while (k < region_col + 3) {
            if (board[j][k] == val) {
                return 0;
            }
            k++;
        }
        j++;
    }
    return 1;
}


int solve_sudoku(int **board, int row, int col) {

    if (row == 8 && col == 9) {
        return 1;
    }


    if (col == 9) {
        row++;
        col = 0;
    }


    if (board[row][col] != 0) {
        return solve_sudoku(board, row, col + 1);
    }

    int val = 1;
    while (val <= 9) {

        if (is_valid(board, row, col, val)) {
            board[row][col] = val;
            if (solve_sudoku(board, row, col + 1)) {
                return 1;
            }
        }


        board[row][col] = 0;
        val++;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char buf[90];
    int i = 0;
    int **board;

    int fd = open(argv[1], O_RDONLY);
    int size = read(fd, buf, 90);
    buf[size] = '\0';

    printf("%s\n", buf);

    board = (int **)malloc(9 * sizeof(int *));
    for (i = 0; i < 9; i++) {
        board[i] = (int *)malloc(9 * sizeof(int));
}
int row = 0;
int col = 0;
for (i = 0; i < size; i++) {
    char c = buf[i];
    if (c == '.') {
        board[row][col] = 0;
        col++;
    } else if (c >= '1' && c <= '9') {
        board[row][col] = c - '0';
        col++;
    }
    if (col == 9) {
        row++;
        col = 0;
    }
}


solve_sudoku(board, 0, 0);


printf("\nGrille résolue :\n");
for (i = 0; i < 9; i++) {
    int j;
    for (j = 0; j < 9; j++) {
        printf("%d ", board[i][j]);
    }
    printf("\n");
}


for (i = 0; i < 9; i++) {
    free(board[i]);
}
free(board);

return 0;
}