#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    int buffer[6];
    char line[100];
    FILE *in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stdin, "Error opening file!\n");
        exit(1);
    }
    int i = 0;
    int calories = 0;
    int maxcalories = 0;

    while (fgets(line, 100, in)){
        calories+= atoi(line);

        if (*line == '\n'){
           buffer[i++] = calories;
           maxcalories = calories > maxcalories? calories:maxcalories;
           calories= 0;
        }

    }

    fclose(in);

    printf("%d\n", maxcalories);

    return 0;

}
