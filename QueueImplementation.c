#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "QueueInterface.h"

void InitializeQueue(Queue *Q)
{
    Q->Front = (QueueNode*)malloc(sizeof(QueueNode));
    Q->Rear = (QueueNode*)malloc(sizeof(QueueNode));

    Q->Front = NULL;
    Q->Rear = NULL;
}

int QueueEmpty(Queue *Q)
{
    if (Q->Front == NULL)
    {
        return 1;
    }
    else 
        return 0;
}

int QueueFull(Queue *Q)
{
    return 0;
}

void Insert (double R, Queue *Q)
{
    QueueNode *Temp;
    Temp = (QueueNode *) malloc(sizeof(QueueNode));
    
    if(Temp == NULL)
    {
        fprintf(stderr, "system storage is exhausted");
    }
    else
    {
        // Store Item type in node
        Temp->Item = R;
        // Set node link to null
        Temp->Link = NULL;
        
        // If Queue is empty
        if(Q->Rear == NULL)
        {
            // Set links
            Q->Front = Temp;
            Q->Rear = Temp;
        }
        else 
        {
            // Set links
            Q->Rear->Link = Temp;
            Q->Rear = Temp;
        }
    }
}

void Remove(Queue *Q, double *F)
{
    QueueNode *Temp;
    
    // If queue is empty
    if (Q->Front == NULL)
    {
        fprintf(stderr, "attempt to remove item from empty Queue");
    }
    else 
    {
        // Store itemtype in F
        *F = Q->Front->Item;
        Temp = Q->Front;
        // remove link to node
        Q->Front = Temp->Link;
        free(Temp);
        
        // If queue is empty
        if (Q->Front == NULL)
            Q->Rear = NULL;
    }
}

double Sum(Queue *Q)
{
  double sum = 0;

  if(Q->Front == NULL)
    return 0.0;
  else
  {
    QueueNode *Temp;
    Temp = Q->Front;

    while(Temp != NULL)
    {
      sum = sum + Temp->Item;
      Temp = Temp->Link;
    }
  }

  return sum;
}


