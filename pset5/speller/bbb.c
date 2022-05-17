#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *table[3];

    //sposob na alokacje pamieci dla macierzy
    //node (*table)[3] = calloc(3, sizeof(node));


    int count = 0;

    while (count < 10)
    {
        node *n = malloc(sizeof(node));
        n->number = count;
        n->next = NULL;

        n->next = table[0];
        table[0] = n;
        count++;
    }

    //table[1]->number = 3;

    printf("table content[0]: %i\n", table[0]->next->next->next->next->number);

    printf("table content [1]: %i\n and the other number is %i\n", table[0]->number, table[0]->next->number);

    printf("So far, so good\n");


}