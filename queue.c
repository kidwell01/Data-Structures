#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 5
bool flag = 0;

struct Queue
{
    int data[SIZE];
    int top, bot;
};

int enqueue(struct Queue *queue, int data)
{
    if (queue->top == queue->bot && flag == 1)
        return -1;
    queue->data[queue->top] = data;
    queue->top++;
    queue->top %= SIZE;
    if (queue->top == queue->bot)
        flag = 1;
    return 1;
}

int *dequeue(struct Queue *queue)
{
    if (queue->top == queue->bot && flag == 0)
        return NULL;
    int *tmp = &(queue->data[queue->bot]);
    queue->bot++;
    queue->bot %= SIZE;
    if (queue->top == queue->bot)
        flag = 0;
    return tmp;
}

int main()
{
    int data, *temp;
    char command[50];
    struct Queue queue;
    queue.top = 0;
    queue.bot = 0;
    while (1)
    {
        scanf("%s", command);
        if (strcmp(command, "exit") == 0)
        {
            break;
        }
        else if (strcmp(command, "enqueue") == 0)
        {
            printf("Please input a integer data:");
            scanf("%d", &data);
            if (enqueue(&queue, data) == 1)
            {
                printf("Successfully enqueue data %d into queue.\n", data);
            }
            else
            {
                printf("Failed to enqueue data into queue.\n");
            }
        }
        else if (strcmp(command, "dequeue") == 0)
        {
            temp = dequeue(&queue);
            if (temp == NULL)
            {
                printf("Failed to dequeue a data from queue.\n");
            }
            else
            {
                printf("Dequeue data %d from queue.\n", *temp);
            }
        }
    }
}