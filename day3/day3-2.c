#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char **group_rucks(FILE *);

char check_common(char **);

int calc(char );

int main(int argc, char **argv)
{

    char **rucks;
    int sum = 0;
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Couldn't read the file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    rucks = group_rucks(fp);
    while(!feof(fp)){
        char c = check_common(rucks);
        sum += calc(c);
        rucks = group_rucks(fp);
    }

    free(rucks);

    printf("%d\n", sum);

    return 0;

}


char **group_rucks(FILE *fp)
{
    char buffer[100];
    char **rucks = malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++){
        fgets(buffer, sizeof(buffer), fp);
        rucks[i] = malloc(sizeof(char) * strlen(buffer));
        strncpy(rucks[i], buffer, strlen(buffer));
    }

    return rucks;

}

char check_common(char **rucks)
{
    int table0[128] = {0};
    int table1[128] = {0};
    int table2[128] = {0};

    for (int i = 0; i < strlen(rucks[0]); i++)
        if (rucks[0][i] != '\n')
            table0[(int)rucks[0][i]]++;

    for (int i = 0; i < strlen(rucks[1]); i++)
        if (rucks[0][i] != '\n')
            table1[(int)rucks[1][i]]++;

    for (int i = 0; i < strlen(rucks[2]); i++)
        if (rucks[0][i] != '\n')
            table2[(int)rucks[2][i]]++;

    for (int i = 0; i < 128; i++){
        if (table0[i] != 0 && table1[i] != 0 && table2[i] != 0)
            return (char)i;
    }

    return 0;
}


int calc(char c)
{
    if (islower(c))
        return (c-96);

    return (c-38);
}
