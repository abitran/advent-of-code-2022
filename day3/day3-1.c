#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    char buffer[100];
    int tablelow[26] = {0};
    int tableup[26] = {0};
    int sum = 0;
    for (int i = 1; i <= 26; i++)
        tablelow[i-1] = i;
    for (int i = 27; i <= 52; i++)
        tableup[i-27] = i;

    for (int i = 0; i < 26; i++)
        printf("%d ", tablelow[i]);

    while (fgets(buffer, sizeof(buffer), fp)){
        int len = strlen(buffer);
        int flag = 0;
        for (int i = 0; i < len/2; i++){
            for (int j = len/2; j < len; j++)
                if (buffer[i] == buffer[j]){
                    printf("%c\n", buffer[i]);
                    if (islower(buffer[i]))
                            sum += tablelow[buffer[i]-'a'];
                    else
                        sum += tableup[buffer[i]-'A'];

                    flag = 1;

                    break;
                }
            if (flag)
                break;
        }
    }

    fclose(fp);

    printf("%d\n", sum);


    return 0;

}
