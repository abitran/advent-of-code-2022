#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BUFFER 256
#define MAX_MONK 20
#define ROUNDS 20

typedef struct monkey{
    int items[256];
    char operation;
    int op_value;
    int divisible;
    int items_inspected;
    int total_items;
    int monkey_true;
    int monkey_false;
}monkey;

void throw_monkey(monkey *, monkey *);

int compare(const void *, const void *);

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    monkey monkies[MAX_MONK];

    char line[BUFFER];
    int num_monkey = 0;

    while (fgets(line, BUFFER, fp)){
        if (line[0] == '\n' ){
            num_monkey++;
        }

        else if (line[2] == 'S'){
            monkies[num_monkey].items_inspected = 0;
            int it_counter = 0;
            char *ptr = line;
            while (*ptr){
                if (isdigit(*ptr) || ((*ptr == ',') && isdigit(*(ptr+1)))){
                    monkies[num_monkey].items[it_counter] = (int)strtol(ptr, &ptr, 10);
                    it_counter++;
                }
                else
                   ptr++;

            monkies[num_monkey].total_items = it_counter;
            }
        }

        else if (line[2] == 'O'){
            monkies[num_monkey].operation = line[23];
            monkies[num_monkey].op_value = atoi(&line[25]);
        }

        else if (line[2] == 'T')
            sscanf(line, "  %*s %*s %*s %d", &(monkies[num_monkey].divisible));
        else if (line[4] == 'I' && line[7] == 't')
            sscanf(line, "    %*s %*s %*s %*s %*s %d", &(monkies[num_monkey].monkey_true));
        else if (line[4] == 'I' && line[7] == 'f')
            sscanf(line, "    %*s %*s %*s %*s %*s %d", &(monkies[num_monkey].monkey_false));

    }

    fclose(fp);


//    for (int i = 0; i < num_monkey+1; i++)
//        printf("Monkey[%d] \n%d\n%c\n%d\n%d\n%d\n%d\n", i, monkies[i].op_value, monkies[i].operation, monkies[i].divisible, monkies[i].monkey_true, \
                monkies[i].monkey_false, monkies[i].total_items);

    int r = ROUNDS;
    while (r--){
        for (int j = 0; j < num_monkey+1; j++){
            while (monkies[j].total_items > 0){

                monkies[j].items_inspected++;

                switch (monkies[j].operation){
                    case '+':
                        if (monkies[j].op_value != 0)
                            monkies[j].items[0] = monkies[j].items[0] + monkies[j].op_value;
                        else
                            monkies[j].items[0] = monkies[j].items[0] + monkies[j].items[0];
                        break;

                    case '*':
                        if (monkies[j].op_value != 0)
                            monkies[j].items[0] = monkies[j].items[0] * monkies[j].op_value;
                        else
                            monkies[j].items[0] = monkies[j].items[0] * monkies[j].items[0];
                        break;
                }

                monkies[j].items[0] = (int)floor((double)monkies[j].items[0] / 3);
                if (monkies[j].items[0] % monkies[j].divisible == 0)
                    throw_monkey(&monkies[j], &monkies[monkies[j].monkey_true]);
                else
                    throw_monkey(&monkies[j], &monkies[monkies[j].monkey_false]);

            }
        }
    }

    for (int i = 0; i < num_monkey+1; i++)
        printf("Monkey[%d]  %d times.\n", i, monkies[i].items_inspected);

    int calc[num_monkey+1];

    for (int i = 0; i < num_monkey+1; i++)
        calc[i] = monkies[i].items_inspected;

    qsort(calc, num_monkey+1, sizeof(int), compare);



    printf("Part 1 : %d\n", calc[0] * calc[1]);

    return 0;
}



void throw_monkey(monkey *from, monkey *to)
{
    if (from->total_items == 0){
        fprintf(stderr, "Queue empty!\n");
        exit(EXIT_FAILURE);
    }

    to->items[to->total_items] = from->items[0];
    to->total_items++;
    for (int i = 0; i < from->total_items - 1; i++)
        from->items[i] = from->items[i+1];

    from->total_items--;

}

int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
