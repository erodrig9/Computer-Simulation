//***************************************************//
// filename: queueTest.c
// Programmer: Karl King
// Description: An application to test the Queue ADT
//**************************************************//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "QueueInterface.h"

int main()
{
	Queue Q;	//A queue variable Q
  Queue D;
	double a;
	double b;
	double c;
	double d;

  a = 4.6;
  b = 5.7;
  c = 5.3;
  d = 8.3;
	
double compare = 7.5895;
double num = 7.5895;

  if(compare == num)
    printf("ahhhhhhhh");

	printf("\n\t\t--- Queue ADT Test ---\n\n");
	
	//Initialize the queue
	InitializeQueue(&Q);
  InitializeQueue(&D);
	
	/*Insert (a,&Q);
	Insert (b,&Q);
  Insert (c,&Q);
  Insert (d,&Q);*/
    
  printf("\nSum Q: %f\n\n", Sum(&Q));
  printf("\nSum D: %f\n\n", Sum(&D));

	/*Remove (&Q,&c);
	Remove (&Q,&d);*/

  Insert (a,&Q);
	Insert (b,&Q);
  Insert (c,&D);
  Insert (d,&D);

  printf("Q: %f, %f\n\n", a, b);
  printf("D: %f, %f\n\n", c, d);

  printf("\nSum Q: %f\n\n", Sum(&Q));
  printf("Sum D: %f", Sum(&D));

	Remove (&Q,&c);
	Remove (&Q,&d);
  Remove (&D,&d);
  Remove (&D,&d);

  printf("\nSum Q: %f\n\n", Sum(&Q));
  printf("\nSum D: %f\n\n", Sum(&D));

	QueueEmpty(&Q);
	return (0);
}
