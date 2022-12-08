#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>


int check_array(int *, int *);

int overlap(int *, int *, int, int, int, int);

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    int lo1, lo2, hi1, hi2;
    int pairs = 0;

    while (fscanf(fp, "%d-%d,%d-%d", &lo1, &hi1, &lo2, &hi2) == 4){

        int elf1[100] = {0};
        int elf2[100] = {0};

        for (int i = lo1; i <= hi1; i++)
            elf1[i] = i;
        for (int i = lo2; i <= hi2; i++)
            elf2[i] = i;

        //if (check_array(elf1, elf2) || check_array(elf2, elf1))
         //   pairs++;

        if (overlap(elf1, elf2, lo1, lo2, hi1, hi2))
            pairs++;

    }

    fclose(fp);

    printf("%d\n", pairs);

    return 0;

}


int overlap(int *a1, int *a2, int lo1, int lo2, int hi1, int hi2)
{
    int i, j;

    for (i = lo1; i <= hi1; i++){
        for (j = lo2; j <= hi2; j++){
            if (a1[i] == a2[j])
                return 1;
        }
    }

    return 0;
}


int check_array(int *a1, int *a2)
{
    int i, j;

    for (i = 0; i < 100; i++){
        for (j = 0; j < 100; j++){
            if (a1[i] == a2[j])
                break;
        }

        if (j == 100)
            return 0;
    }

    return 1;
}
