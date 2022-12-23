#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DIRS 500
#define BUFFER 256


int comp(const void *, const void *);


int recurse(FILE *);

static int depth = 0;
static int dirs[MAX_DIRS] = {0};


int main(int argc, char **argv)
{

    const long total_disk = 70000000;
    const long free_disk = 30000000;
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "Can't read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    long total_part2 = 0;
    int total_size = recurse(fp);

    qsort(dirs, MAX_DIRS, sizeof(int), comp);

    for (int i = 0; i < MAX_DIRS; i++)
        if (dirs[i] + total_disk - total_size >= free_disk){
            total_part2 = dirs[i];
            break;
        }

    fclose(fp);

    printf("%ld\n", total_part2);



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


int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
