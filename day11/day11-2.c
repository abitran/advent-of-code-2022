#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define BUFFER 256
#define MAX_MONK 20
#define ROUNDS 10000


typedef struct monkey{
    long int items[512];
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


void check_items(monkey *);


int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    monkey monkeys[MAX_MONK];

    char line[BUFFER];
    int num_monkey = 0;

    while (fgets(line, BUFFER, fp)){
        if (line[0] == '\n' ){
            num_monkey++;
        }

        else if (line[2] == 'S'){
            monkeys[num_monkey].items_inspected = 0;
            int it_counter = 0;
            char *ptr = line;
            while (*ptr){
                if (isdigit(*ptr) || ((*ptr == ',') && isdigit(*(ptr+1)))){
                    monkeys[num_monkey].items[it_counter] = (long int)strtol(ptr, &ptr, 10);
                    it_counter++;
                }
                else
                   ptr++;

            monkeys[num_monkey].total_items = it_counter;
            }
        }

        else if (line[2] == 'O'){
            monkeys[num_monkey].operation = line[23];
            monkeys[num_monkey].op_value = atoi(&line[25]);
        }

        else if (line[2] == 'T')
            sscanf(line, "  %*s %*s %*s %d", &(monkeys[num_monkey].divisible));
        else if (line[4] == 'I' && line[7] == 't')
            sscanf(line, "    %*s %*s %*s %*s %*s %d", &(monkeys[num_monkey].monkey_true));
        else if (line[4] == 'I' && line[7] == 'f')
            sscanf(line, "    %*s %*s %*s %*s %*s %d", &(monkeys[num_monkey].monkey_false));
    }

    fclose(fp);

    check_items(monkeys);

    int factors = 1;
    for (int i = 0; i < num_monkey+1; i++)
        factors *= monkeys[i].divisible;

    int r = ROUNDS;
    while (r--){
        for (int j = 0; j < num_monkey+1; j++){
            while (monkeys[j].total_items > 0){

                switch (monkeys[j].operation){
                    case '+':
                        if (monkeys[j].op_value != 0)
                            monkeys[j].items[0] = monkeys[j].items[0] + monkeys[j].op_value;
                        else
                            monkeys[j].items[0] = monkeys[j].items[0] + monkeys[j].items[0];
                        break;

                    case '*':
                        if (monkeys[j].op_value != 0)
                            monkeys[j].items[0] = monkeys[j].items[0] * monkeys[j].op_value;
                        else
                            monkeys[j].items[0] = monkeys[j].items[0] * monkeys[j].items[0];
                        break;
                }

                monkeys[j].items[0] %= factors;;

                if (monkeys[j].items[0] % monkeys[j].divisible == 0)
                    throw_monkey(&monkeys[j], &monkeys[monkeys[j].monkey_true]);
                else
                    throw_monkey(&monkeys[j], &monkeys[monkeys[j].monkey_false]);

            }
        }
        check_items(monkeys);
    }

    for (int i = 0; i < num_monkey+1; i++)
        printf("Monkey[%d]  %d times.\n", i, monkeys[i].items_inspected);

    int calc[num_monkey+1];

    for (int i = 0; i < num_monkey+1; i++)
        calc[i] = monkeys[i].items_inspected;

    qsort(calc, num_monkey+1, sizeof(int), compare);

    printf("Part 1 : %ldd\n", (long)calc[0] * (long)calc[1]);

    return 0;
}


void throw_monkey(monkey *from, monkey *to)
{
    if (from->total_items == 0){
        fprintf(stderr, "Queue empty!\n");
        exit(EXIT_FAILURE);
    }

    if (to->total_items > 256){
        fprintf(stderr, "Queue full!\n");
        exit(EXIT_FAILURE);
    }

    to->items[to->total_items] = from->items[0];
    to->total_items++;

    for (int i = 0; i < from->total_items - 1; i++)
        from->items[i] = from->items[i+1];

    from->items_inspected++;
    from->total_items--;

}


int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}


void check_items(monkey *m)
{
    for (int i = 0; i < 4; i++){
        printf("Monkey[%d]: ", i);
        for (int j = 0; j < m[i].total_items; j++)
            printf("%ld ", m[i].items[j]);
        printf("\n");
    }
    printf("\n");
}
