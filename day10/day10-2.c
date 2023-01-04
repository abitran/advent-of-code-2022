#include <stdio.h>
#include <stdlib.h>
#define BUFFER 20


void draw(int, int *);

int main(int argc, char **argv)
{

    char line[BUFFER];

    int regX = 1;
    int cycle = 0;
    int signals = 0;

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, BUFFER, fp)){
        char str[10];
        char ops;
        int val;
        if (sscanf(line, "%s",str)){
            ops = str[0];
        }

       // printf("cycle=%d - regX=%d\n", cycle, regX);

        if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
            signals += cycle * regX;


        switch (ops){
            case 'n':
            cycle++;
            draw(cycle, &regX);

            break;

            case 'a':
            cycle++;

            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
                signals += cycle * regX;

            draw(cycle, &regX);
            cycle++;

            if (cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
                signals += cycle * regX;

            sscanf(line, "%*s %d", &val);
            draw(cycle, &regX);
            regX += val;
            break;

        }

    }


    printf("[Part1] ==> %d\n", signals);

    fclose(fp);

    return 0;
}

void draw(int cycle, int *regX)
{

    int pos = (cycle % 40) + 1;
    if (pos < *regX + 1 || pos > *regX + 3)
        printf(".");

    else
        printf("#");

    if (pos == 1)
        printf("\n");
}
