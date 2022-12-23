#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DIRS 500
#define BUFFER 256


int recurse(FILE *);

static int depth = 0;
static int dirs[MAX_DIRS] = {0};


int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "Can't read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    int total_size = recurse(fp);
    int total_part1 = 0;

    fclose(fp);


    for (int i = 0; i < MAX_DIRS; i++)
        if (dirs[i] <= 100000)
            total_part1 += dirs[i];


    printf("%d", total_part1);

    return 0;

}


int recurse(FILE *fp)
{
    char buffer[BUFFER];
    int d= depth++;

    while (fgets(buffer, BUFFER, fp)){
        if (buffer[0] == '$'){
            if (buffer[2] == 'c'){
                if (buffer[5] == '.')
                    break;
                else
                    dirs[d] += recurse(fp);

            }
        }
        else if ((buffer[0] >= '0') && (buffer[0] <= '9')){
            int sizes = 0;
            if (sscanf(buffer, "%d", &sizes) == 1)
                dirs[d] += sizes;
        }

    }

    return dirs[d];
}
