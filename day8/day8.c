#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define ROWS 200
#define COLS 200
#define BUFFER 256



typedef struct grid{
    int data[ROWS][COLS];
    int rows;
    int cols;
}grid;

int load_grid(FILE *, grid *);

int check_left(int, int, grid);

int check_right(int, int, int, grid);

int check_top(int, int, grid);

int check_bottom(int, int, int, grid);

int view_to_left(int, int, grid);

int view_to_right(int, int, int, grid);

int view_to_top(int, int, grid);

int view_to_bottom(int, int, int, grid);

int main(int argc, char **argv)
{

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Unable to find file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    grid g;
    g.rows = 0;
    g.cols = 0;

    if (load_grid(fp, &g) == -1){
        fprintf(stderr, "error populating grid\n");
        exit(EXIT_FAILURE);
    }

/*

    for (int i = 0; i < g.rows; i++){
        for (int j = 0; j < g.cols; j++)
            printf("%d", g.data[i][j]);
        printf("\n");
    }

    */

    int visible = 0;
    int max_view = 0;

    visible += (2*g.rows) + (2*g.cols) - 4;

    for (int i = 1; i < g.rows - 1; i++)
        for (int j = 1; j < g.cols - 1; j++){
            if (check_left(i, j, g) || check_right(i, j, g.cols, g) || check_top(i, j, g) \
                       || check_bottom(i, j, g.rows, g))
                visible++;

            int view = 0;
            view = view_to_left(i, j, g) * view_to_right(i, j, g.cols, g) * view_to_top(i, j, g) \
                   * view_to_bottom(i, j, g.rows, g);
            if (view > max_view)
                max_view = view;

        }


    printf("[Part 1] %d\n", visible);
    printf("[Part 2] %d\n", max_view);


    return 0;
}

int load_grid(FILE *fp, grid *g)
{

    char buffer[BUFFER] = {0};
    int row = 0;

    while (fgets(buffer, BUFFER, fp)){
        int i = 0;
        int col = 0;

        while (buffer[i] != '\n'){
            g->data[row][col++] = (int)(buffer[i] - '0');

            if (col == COLS)
                break;

            i++;

        }
            if (row == 0)
                g->cols = col;

            row++;

            if (row == ROWS)
                break;
    }
    g->rows = row;

    return 0;
}


int check_left(int r, int c, grid g)
{
    for (int i = 0; i < c; i++)
        if (g.data[r][i] >= g.data[r][c])
            return 0;

    return 1;
}

int check_right(int r, int c, int maxcol, grid g)
{
    for (int i = maxcol; i > c; i--)
        if (g.data[r][i] >= g.data[r][c])
            return 0;

    return 1;
}

int check_top(int r, int c, grid g)
{
    for (int i = 0; i < r; i++)
        if (g.data[i][c] >= g.data[r][c])
            return 0;
    return 1;
}

int check_bottom(int r, int c, int maxrow, grid g)
{
    for (int i = maxrow; i > r; i--)
        if (g.data[i][c] >= g.data[r][c])
            return 0;
    return 1;
}


int view_to_left(int r, int c, grid g)
{
    int view_count = 0;
    for (int i = c-1; i >= 0; i--){
        if (g.data[r][i] < g.data[r][c])
            view_count++;
        else if (g.data[r][i] >= g.data[r][c]){
            view_count++;
            break;
        }
        else
            break;
    }
    return view_count;
}

int view_to_right(int r, int c, int maxcol, grid g)
{
    int view_count = 0;
    for (int i = c+1; i < maxcol; i++ ){
        if (g.data[r][i] < g.data[r][c])
            view_count++;
        else if(g.data[r][i] >= g.data[r][c]){
            view_count++;
            break;
        }
        else
            break;
    }
    return view_count;
}

int view_to_top(int r, int c, grid g)
{
    int view_count = 0;
    for (int i = r-1; i >= 0; i--){
        if (g.data[i][c] < g.data[r][c])
            view_count++;
        else if (g.data[i][c] >= g.data[r][c]){
            view_count++;
            break;
        }
        else
            break;
    }
    return view_count;
}

int view_to_bottom(int r, int c, int maxrow, grid g)
{
    int view_count = 0;
    for (int i = r+1; i < maxrow; i++){
        if (g.data[i][c] < g.data[r][c])
            view_count++;
        else if (g.data[i][c] >= g.data[r][c]){
            view_count++;
            break;
        }
    }

    return view_count;
}
