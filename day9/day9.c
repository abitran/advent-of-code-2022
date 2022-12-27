#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 1000
#define COLS 1000
#define BUFFER 10


typedef struct rope{
    int xhead;
    int yhead;
    int xtail;
    int ytail;
}rope;

void update(char, int, rope *, char [][COLS]);

int main(int argc, char **argv)
{
    char line[BUFFER];
    rope r;
    r.xhead = r.xtail = 500;
    r.yhead = r.ytail = 500;

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Unable to open file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    char grid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = '.';

    grid[r.xtail][r.ytail] = '#';

    while (fgets(line, BUFFER, fp)){
        char dir;
        int steps;
        if (sscanf(line, "%c %d", &dir, &steps) == 2)
            update(dir, steps, &r, grid);
    }

    int part1 = 0;

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            printf("%c", grid[i][j]);
            if (grid[i][j] == '#')
                    part1++;
        }

        printf("\n");
    }

    printf("\n[Part 1] %d", part1);

    fclose(fp);

    return 0;

}

void update(char dir, int steps, rope *r, char g[][COLS])
{

    switch (dir){

        case 'R':
            for (int i = 0; i < steps; i++){
                r->yhead++;

                if (abs(r->yhead - r->ytail) > 1){
                    r->ytail++;

                    if (r->xtail < r->xhead)
                        r->xtail++;

                    else if (r->xtail > r->xhead)
                        r->xtail--;

                    else
                        r->xtail = r->xhead;

                }
                g[r->xtail][r->ytail] = '#';
            }

            break;

        case 'L':
            for (int i = 0; i < steps; i++){
                r->yhead--;

                if(abs(r->ytail - r->yhead) > 1){
                    r->ytail--;

                    if (r->xtail < r->xhead)
                        r->xtail++;

                    else if (r->xtail > r->xhead)
                        r->xtail--;

                    else
                        r->xtail = r->xhead;

                }
                g[r->xtail][r->ytail] = '#';
            }

            break;

        case 'U':
            for (int i = 0; i < steps; i++){
                r->xhead--;

                if (abs(r->xtail - r->xhead) > 1){
                    r->xtail--;

                    if (r->ytail < r->yhead)
                        r->ytail++;

                    else if (r->ytail > r->yhead)
                        r->ytail--;
                    else
                        r->ytail = r->yhead;
                }
                g[r->xtail][r->ytail] = '#';

            }

            break;

        case 'D':
            for (int i = 0; i < steps; i++){
                r->xhead++;

                if (abs(r->xhead - r->xtail) > 1){
                    r->xtail++;

                    if (r->ytail < r->yhead)
                        r->ytail++;

                    else if (r->ytail > r->yhead)
                        r->ytail--;

                    else
                        r->ytail = r->yhead;

                }
                g[r->xtail][r->ytail] = '#';
            }

            break;

    }
}
