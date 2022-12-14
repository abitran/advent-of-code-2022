#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /*
     * A = rocks, B = paper, C = scissors
     * X = rocks, Y = paper, Z = scissors
     * shape points = 1, 2, 3
     * winpoints = 0, 3, 6
     * */

    FILE *fp = fopen(argv[1], "r");
    char buffer[100];
    char p1, p2;
    int total_points = 0;
    int table[3] = {3, 2, 1};

    while(fgets(buffer, sizeof(buffer), fp)){
        sscanf(buffer, "%c %c", &p1, &p2);
        int points = 0;
        points += table['Z'- p2];
        if ((p2 == 'X') && (p1 == 'A'))
            points += 3;
        if ((p2 == 'X') && (p1 == 'C'))
            points += 6;
        if ((p2 == 'Y') && (p1 == 'B'))
            points += 3;
        if ((p2 == 'Y') && (p1 == 'A'))
            points += 6;
        if ((p2 == 'Z') && (p1 == 'C'))
            points += 3;
        if ((p2 == 'Z') && (p1 == 'B'))
            points += 6;

        total_points += points;

    }

    fclose(fp);

    printf("%d\n", total_points);

    return 0;

}
