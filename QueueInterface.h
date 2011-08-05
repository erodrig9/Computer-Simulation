#include <strings.h>
//#include <math.h>
#include <stdio.h>

#ifndef Queue_Has_Been_Defined
   typedef struct QueueNodeTag {
     double Item;
     struct QueueNodeTag *Link;
   } QueueNode;

   typedef struct { // a queue is empty if  
     QueueNode *Front; // its Front == NULL 
     QueueNode *Rear;
   } Queue;
#define Queue_Has_Been_Defined
#endif

// defined operations 
extern void InitializeQueue(Queue *Q);
// Initialize the queue Q to be the empty queue 
  
extern int QueueEmpty(Queue *Q);
// Returns TRUE == 1 if and only if the queue Q is empty 

extern int QueueFull(Queue *Q);
// Returns TRUE == 1 if and only if the queue Q is full 

extern void Insert(double R, Queue *Q);
// If Q is not full, insert a new item R onto the rear of Q 
   
extern void Remove(Queue *Q, double *F);
// If Q is non-empty, remove the frontmost item of Q and put it in F 

extern double Sum(Queue *Q);
// Add all nodes in the queue Q 
