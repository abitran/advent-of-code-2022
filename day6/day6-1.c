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
    int j;
    int flag = 0;
    int count = 0;

    for (int i = 0; i < len; i++){
        if (count == 3)
            break;
        for (j = i+1; j <= 3 + i; j ++){
            if ((stream[i] == stream[j]) || (stream[j] == stream[j+1]) || (stream[j] == stream[j+2])){
                count = 0;
                flag = 0;
                break;
            }
            else{
                flag = 1;
                count++;
                continue;
            }
        }
    }

    return (flag == 1? j:0);
}
