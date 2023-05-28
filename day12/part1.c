#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER 256

typedef struct points{
    int x;
    int y;
}points;

typedef struct bfs{
    points p;
    int distance;
}bfs;

typedef struct queue{
    int front;
    int rear;
    int size;
    int capacity;
    bfs *data;
}queue;


bool qfull(queue *q);

bool qempty(queue *q);

int steps(char **, int, int);

void free_mem(char **, int);

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    char line[BUFFER];
    char ** grid;

    fgets(line, BUFFER, fp);
    int col = strlen(line);
    int row = 0;
    grid = malloc(sizeof(char *) * (row + 1));

    grid[row] = malloc(sizeof(char) * col);

    for (int i = 0; i < col; i++)
        grid[row][i] = line[i];


    while (fgets(line, BUFFER, fp)){
        row++;
        char **temp;
        temp = realloc(grid, sizeof(char *) * (row + 1));
        grid = temp;

        grid[row] = malloc(sizeof(char) * col);

        for (int i = 0; i < col; i++){
            grid[row][i] = line[i];
        }
    }

    for (int i = 0; i < row+1; i++)
        for (int j = 0; j < col; j++)
            printf("%c", grid[i][j]);

    fclose(fp);

    steps(grid, row, col);

    free_mem(grid, row);

    return 0;

}


int steps(char **g, int r, int c)
{
    points start;
    points end;

    int diffx[] = {0, 0, 1, -1};
    int diffy[] = {-1, 1, 0, 0};


    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (g[i][j] == 'S'){
                start.x = i;
                start.y = j;
                g[start.x][start.y] = 'a';
            }
            if (g[i][j] == 'E'){
                end.x = i;
                end.y = j;
                g[end.x][end.y] = 'z';
            }
        }
    }

    printf("Start: %d,%d - End: %d, %d", start.x, start.y, end.x, end.y);


    return 0;
}

void free_mem(char **g, int r)
{
    for (int i = 0; i < r + 1; i++){
        char *temp = g[i];
        free(temp);
    }

    free(g);
    g = NULL;
}

bool qfull(queue *q)
{
    return (q->size == q->capacity);
}

bool qempty(queue *q)
{

    return (q->size == 0);
}
