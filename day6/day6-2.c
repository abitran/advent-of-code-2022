#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int marker(char *);

int main(int argc, char **argv)
{
    char linebuffer[5000];
    int count = 0;

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(linebuffer, sizeof(linebuffer), fp))
        count += marker(linebuffer);

    fclose(fp);

    printf("%d\n", count);

    return 0;
}


int marker(char *stream)
{
    int len = strlen(stream);
    int i,j;

    int alphas[26] = {0};
    int sum = 0;

    for (i = 0; i < len; i++){
        for (j = i; j < 14 + i; j++)
            alphas[stream[j]-'a']++;

        for (int k = 0; k < 26; k++){
            if (alphas[k] == 1){
                printf("%d ", alphas[k]);
                sum += alphas[k];
            }
        }
        printf("\n");

        if (sum == 14){
            printf("Entramos al break\n");
            break;
        }
        else{
            for (int k = 0; k < 26; k++){
                alphas[k] = 0;
                sum = 0;
            }
        }

    }

    return j;
}
