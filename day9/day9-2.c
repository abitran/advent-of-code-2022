#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 1000
#define COLS 1000
#define BUFFER 10


typedef struct rope{
    int posx[BUFFER];
    int posy[BUFFER];
}rope;

void update(char, rope *, char [][COLS]);

int main(int argc, char **argv)
{
    char line[BUFFER];
    rope r;

    for (int i = 0; i < BUFFER; i++){
         r.posx[i] = 500;
         r.posy[i] = 500;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Unable to open file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    char grid[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = '.';

    grid[r.posx[BUFFER-1]][r.posy[BUFFER-1]] = '#';

    while (fgets(line, BUFFER, fp)){
        char dir;
        int steps;
        if (sscanf(line, "%c %d", &dir, &steps) == 2){
            while (steps-- > 0)
                update(dir, &r, grid);
        }
    }

    int part2 = 0;

    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            printf("%c", grid[i][j]);
            if (grid[i][j] == '#')
                    part2++;
        }

        printf("\n");
    }

    printf("\n[Part 2] %d", part2);

    fclose(fp);

    return 0;

}

void update(char dir, rope *r, char g[][COLS])
{
    switch (dir){
        case 'R':
            r->posy[0]++;
            break;

        case 'L':
            r->posy[0]--;
            break;

        case 'D':
            r->posx[0]++;
            break;

        case 'U':
            r->posx[0]--;
            break;
    }

    for (int i = 1; i < BUFFER; i++){

        //printf("[X]: %d, [Y]: %d\n", r->posx[i], r->posy[i]);

        int deltax = abs(r->posx[i-1] - r->posx[i]);
        int deltay = abs(r->posy[i-1] - r->posy[i]);
        int mdist = deltax > deltay ? deltax : deltay;

        if (mdist > 1){
            int dirx = r->posx[i-1] - r->posx[i];
            int diry = r->posy[i-1] - r->posy[i];
            r->posx[i] += abs(dirx) == 2 ? dirx / 2 : dirx;
            r->posy[i] += abs(diry) == 2 ? diry / 2 : diry;
        }

        g[r->posx[9]][r->posy[9]] = '#';
    }

}
