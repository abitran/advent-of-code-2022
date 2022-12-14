#include <stdio.h>
#include <stdlib.h>

int compare(const void*, const void*);

int main(int argc, char **argv)
{

    int *buffer;
    char line[100];
    FILE *in = fopen(argv[1], "r");

    if (in == NULL){
        fprintf(stdin, "Error opening file!\n");
        exit(1);
    }

    int i = 0;
    int calories = 0;
    buffer = malloc(sizeof(int));
    while (fgets(line, 50, in)){

        if (*line != '\n'){
            calories += atoi(line);
            buffer[i] = calories;
        }
        else{
            calories = 0;
            i++;
            int *temp = realloc(buffer, sizeof(int) * (i+1));
            buffer = temp;
        }

    }

    fclose(in);

    qsort(buffer, i+1, sizeof(int), compare);

    int total_cals = 0;
    for (int j = 0; j < 3; j++)
       total_cals += buffer[i-j];

    printf("%d\n", total_cals);

    free(buffer);

    return 0;

}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);

}
