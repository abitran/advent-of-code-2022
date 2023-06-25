#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER 256


typedef struct data{
    int x;
    int y;
    int distance;
}data;


typedef struct node{
    data *data;
    struct node *next;
}node;


typedef struct queue{
    node *front;
    node *rear;
    int size;
}queue;

queue *createqueue();

void qenqueue(queue *, data *);

data  *qdequeue(queue *);

bool qempty(queue *);

int qsize(queue *);

data *qpeek(queue *q);

void shortest(char **, int, int);

void steps(char **, int, int);

void free_mem(char **, int);

void qdestroy(queue *);

int startx, starty, endx, endy;


int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL){
        fprintf(stderr, "[!] Unable to read file %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    char line[BUFFER];
    char ** grid;

    fgets(line, BUFFER, fp);
    int col = strlen(line)-1;
    int row = 0;
    grid = malloc(sizeof(char *) * (row+1));

    grid[row] = malloc(sizeof(char) * col);

    for (int i = 0; i < col; i++)
        grid[row][i] = line[i];

    while (fgets(line, BUFFER, fp)){
        row++;
        char **temp;
        temp = realloc(grid, sizeof(char *) * (row+1));
        grid = temp;

        grid[row] = malloc(sizeof(char) * col);

        for (int i = 0; i < col; i++){
            grid[row][i] = line[i];
        }
    }

    fclose(fp);

    steps(grid, row+1, col);

    shortest(grid, row+1, col);

    free_mem(grid, row+1);

    return 0;

}


queue *createqueue()
{
    queue *q = malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}


void qenqueue(queue *q, data *item)
{
    node *newnode;
    newnode = malloc(sizeof(node));
    newnode->data = malloc(sizeof(data));
    memcpy(newnode->data, item, sizeof(data));
    newnode->next = NULL;

    if (qempty(q)){
        q->front = newnode;
        q->rear = newnode;
    }

    else{
        q->rear->next = newnode;
        q->rear = newnode;
    }

    q->size++;
}


data *qdequeue(queue *q)
{
    if (qempty(q))
        return NULL;

    data *item = q->front->data;
    node *temp = q->front;

    if (q->size == 1){
        q->front = NULL;
        q->rear = NULL;
    }
    else
        q->front = q->front->next;

    free(temp);
    q->size--;

    return item;
}


int qsize(queue *q)
{
    return q->size;
}


bool qempty(queue *q)
{
    return (q->size == 0);
}


data *qpeek(queue *q)
{
    if (qempty(q))
        return NULL;

    return q->front->data;

}


void qdestroy(queue *q)
{
    node *current = q->front;;
    while (current != NULL){
        free(current->data);
        current = current->next;
        free(current);
    }

    free(q);
}


void shortest(char **g, int row, int col)
{
    // possible moves in the grid

    const int dx[] = {1, 0, -1, 0};
    const int dy[] = {0, 1, 0, -1};

    data *item = malloc(sizeof(data));

    int visited[BUFFER][BUFFER] = {0};

    item->x = startx;
    item->y = starty;
    item->distance = 0;

    queue *q = createqueue();

    qenqueue(q, item);

    visited[startx][starty] = 1;

    while (!qempty(q)){

        item = qdequeue(q);

        if (item == NULL) {
            break;
        }

        int crow = item->x;
        int ccol = item->y;
        int cdist = item->distance;

        for (int i = 0; i < 4; i++){

            int nrow = crow + dx[i];
            int ncol = ccol + dy[i];

            if ((nrow < 0) || (ncol < 0) || (nrow >= row) || (ncol >= col))
                continue;

            if (visited[nrow][ncol] == 1)
                continue;

            char cpos = g[crow][ccol];
            char npos = g[nrow][ncol];

            if ((int)npos - (int)cpos < -1)
                continue;

            if (nrow == endx && ncol == endy){
                printf("We arrived! %d\n", cdist + 1);
                break;
            }

            visited[nrow][ncol] = 1;

            item->x = nrow;
            item->y = ncol;
            item->distance = cdist + 1;

            qenqueue(q, item);
        }
    }

    qdestroy(q);
}


void steps(char **g, int r, int c)
{
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            if (g[i][j] == 'S'){
                endx = i;
                endy = j;
                g[startx][starty] = 'a';
            }

            if (g[i][j] == 'E'){
                startx = i;
                starty = j;
                g[endx][endy] = 'z';
            }
        }
    }
}

void free_mem(char **g, int r)
{
    for (int i = 0; i < r; i++){
        char *temp = g[i];
        free(temp);
    }

    free(g);
    g = NULL;
}
