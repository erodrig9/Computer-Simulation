//============================================== file = 5mm1_csim_short.c =====
//=  A CSIM simulation of a 2 M/M/1 queueing systems with short split         =
//=============================================================================
//=  Notes:                                                                   =
//=   1) Lambda is an command line input, mu is sent in main()                =
//=---------------------------------------------------------------------------=
//= Example execution:                                                        =
//=                                                                           =
//=   *** BEGIN SIMULATION ***                                                =
//=   =============================================================           =
//=   ==   *** CSIM 2 x M/M/1 queueing system simulation ***     ==           =
//=   =============================================================           =
//=   = Lambda               =  1.800 cust/sec                                =
//=   = Mu (for each server) =  1.000 cust/sec                                =
//=   =============================================================           =
//=   = Total CPU time     = 48.032 sec                                       =
//=   = Total sim time     = 10000000.000 sec                                 =
//=   = Total completions  = 17997450 cust                                    =
//=   =------------------------------------------------------------           =
//=   = >>> Simulation results                                    -           =
//=   =------------------------------------------------------------           =
//=   = Utilization 1        = 90.004 %                                       =
//=   = Mean num in system 1 =  9.031 cust                                    =
//=   = Mean response time 1 = 10.035 sec                                     =
//=   = Mean service time 1  =  1.000 sec                                     =
//=   = Mean throughput 1    =  0.900 cust/sec                                =
//=   =------------------------------------------------------------           =
//=   = Utilization 2        = 90.017 %                                       =
//=   = Mean num in system 2 =  9.044 cust                                    =
//=   = Mean response time 2 = 10.051 sec                                     =
//=   = Mean service time 2  =  1.000 sec                                     =
//=   = Mean throughput 2    =  0.900 cust/sec                                =
//=   =------------------------------------------------------------           =
//=   & Table mean for response time = 10.043 sec                             =
//=   =============================================================           =
//=   *** END SIMULATION ***                                                  =
//=---------------------------------------------------------------------------=
//=  Build: standard CSIM build                                               =
//=---------------------------------------------------------------------------=
//=  Execute: 2mm1_csim                                                       =
//=---------------------------------------------------------------------------=
//=  Author: Ken Christensen                                                  =
//=          University of South Florida                                      =
//=          WWW: http://www.csee.usf.edu/~christen                           =
//=          Email: christen@csee.usf.edu                                     =
//=---------------------------------------------------------------------------=
//=  History: KJC (06/09/09) - Genesis (from mm1_csim.c)                      =
//=============================================================================
//----- Includes --------------------------------------------------------------
#include <stdio.h>      // Needed for printf()
#include <stdlib.h>     // Needed for atof()
#include <assert.h>
#include "QueueInterface.h"
#include "csim.h"       // Needed for CSIM19 stuff

//----- Defines ---------------------------------------------------------------
#define SIM_TIME 2.0e6  // Total simulation time in seconds

//----- Globals ---------------------------------------------------------------
FACILITY Server1;       // Declaration of CSIM Server facility #1
FACILITY Server2;       // Declaration of CSIM Server facility #2
FACILITY Server3;       // Declaration of CSIM Server facility #3
FACILITY Server4;       // Declaration of CSIM Server facility #4
FACILITY Server5;       // Declaration of CSIM Server facility #5
TABLE    Resp_table;    // Declaration of CSIM Table
Queue    Q1;
Queue    Q2;
Queue    Q3;
Queue    Q4;
Queue    Q5;

//----- Prototypes ------------------------------------------------------------
void generate(double lambda, double mu);            // Customer generator
void queue1(double service_time, double time_org);  // Single server queue #1
void queue2(double service_time, double time_org);  // Single server queue #2
void queue3(double service_time, double time_org);  // Single server queue #3
void queue4(double service_time, double time_org);  // Single server queue #4
void queue5(double service_time, double time_org);  // Single server queue #5

//=============================================================================
//==  Main program                                                           ==
//=============================================================================
void sim(int argc, char *argv[])
{
  double   lambda;      // Mean arrival rate (cust/sec)
  double   mu;          // Mean service rate (cust/sec)
  double   offered_load;
  
  // Create the simulation
  create("sim");
  
  // Output usage 
  if (argc != 2) 
  { 
    printf("Usage: 'offered_load' - offered_load between 0 and 1 \n"); 
    return; 
  } 
  offered_load = atof(argv[1]);
  assert((offered_load > 0.0) && (offered_load < 1.0));
  
  // CSIM initializations
  Server1 = facility("Server1");
  Server2 = facility("Server2");
  Server3 = facility("Server3");
  Server4 = facility("Server4");
  Server5 = facility("Server5");
  Resp_table = table("Response time table");

  // Parameter initializations
  mu = 1.0;
  lambda = offered_load * (double)5;
  InitializeQueue(&Q1);
  InitializeQueue(&Q2);
  InitializeQueue(&Q3);
  InitializeQueue(&Q4);
  InitializeQueue(&Q5);
  
  // Output begin-of-simulation banner
  printf("*** BEGIN SIMULATION *** \n");

  // Initiate generate function and hold for SIM_TIME
  generate(lambda, mu);
  hold(SIM_TIME);

  // Output results
  printf("============================================================= \n");
  printf("==   *** CSIM 5 x M/M/1 queueing system simulation ***     == \n");
  printf("============================================================= \n");
  printf("= Lambda               = %6.3f cust/sec   \n", lambda);
  printf("= Mu (for each server) = %6.3f cust/sec   \n", mu);
  printf("============================================================= \n");
  printf("= Total CPU time     = %6.3f sec      \n", cputime());
  printf("= Total sim time     = %6.3f sec      \n", clock);
  printf("= Total completions  = %ld cust       \n",
    (completions(Server1) + completions(Server2) + completions(Server3) + completions(Server4) + completions(Server5)));
  printf("=------------------------------------------------------------ \n");
  printf("= >>> Simulation results                                    - \n");
  printf("=------------------------------------------------------------ \n");
  printf("= Utilization 1        = %6.3f %%       \n", 100.0 * util(Server1));
  printf("= Mean num in system 1 = %6.3f cust     \n", qlen(Server1));
  printf("= Mean response time 1 = %6.3f sec      \n", resp(Server1));
  printf("= Mean service time 1  = %6.3f sec      \n", serv(Server1));
  printf("= Mean throughput 1    = %6.3f cust/sec \n", tput(Server1));
  printf("=------------------------------------------------------------ \n");
  printf("= Utilization 2        = %6.3f %%       \n", 100.0 * util(Server2));
  printf("= Mean num in system 2 = %6.3f cust     \n", qlen(Server2));
  printf("= Mean response time 2 = %6.3f sec      \n", resp(Server2));
  printf("= Mean service time 2  = %6.3f sec      \n", serv(Server2));
  printf("= Mean throughput 2    = %6.3f cust/sec \n", tput(Server2));
  printf("=------------------------------------------------------------ \n");
  printf("= Utilization 3        = %6.3f %%       \n", 100.0 * util(Server3));
  printf("= Mean num in system 3 = %6.3f cust     \n", qlen(Server3));
  printf("= Mean response time 3 = %6.3f sec      \n", resp(Server3));
  printf("= Mean service time 3  = %6.3f sec      \n", serv(Server3));
  printf("= Mean throughput 3    = %6.3f cust/sec \n", tput(Server3));
  printf("=------------------------------------------------------------ \n");
  printf("= Utilization 4        = %6.3f %%       \n", 100.0 * util(Server4));
  printf("= Mean num in system 4 = %6.3f cust     \n", qlen(Server4));
  printf("= Mean response time 4 = %6.3f sec      \n", resp(Server4));
  printf("= Mean service time 4  = %6.3f sec      \n", serv(Server4));
  printf("= Mean throughput 4    = %6.3f cust/sec \n", tput(Server4));
  printf("=------------------------------------------------------------ \n");
  printf("= Utilization 5        = %6.3f %%       \n", 100.0 * util(Server5));
  printf("= Mean num in system 5 = %6.3f cust     \n", qlen(Server5));
  printf("= Mean response time 5 = %6.3f sec      \n", resp(Server5));
  printf("= Mean service time 5  = %6.3f sec      \n", serv(Server5));
  printf("= Mean throughput 5    = %6.3f cust/sec \n", tput(Server5));
  printf("=------------------------------------------------------------ \n");
  printf("& Table mean for response time = %6.3f sec   \n",
    table_mean(Resp_table));
  printf("============================================================= \n");
  
  // Output end-of-simulation banner
  printf("*** END SIMULATION *** \n");
  getchar();
}

//=============================================================================
//==  Function to generate Poisson customers                                 ==
//==   - Random split to queue1() and queue2()                               ==
//=============================================================================
void generate(double lambda, double mu)
{
  double   interarrival_time;    // Interarrival time to next send
  double   service_time;         // Service time for this customer
  double   rv;                   // Random Value
  double   queue_len[5];         // Number of customers in system
  double   short_val;            // Shortest Queue value
  int      ties[5];              // Tied queue values
  int      select_q;             // Queue Chosen
  int      num_ties;             // Number of ties 
  int      i;                    // Iteration value
  int test = 1;
  create("generate");

  // Loop forever to create customers
  while(1)
  {
    // Pull an interarrival time and hold for it
    interarrival_time = exponential(1.0 / lambda);
    hold(interarrival_time);

    // Pull a service time
    service_time = exponential(1.0 / mu);

    // Get # customers in each system
    queue_len[0] = Sum(&Q1);
    queue_len[1] = Sum(&Q2);
    queue_len[2] = Sum(&Q3);
    queue_len[3] = Sum(&Q4);
    queue_len[4] = Sum(&Q5);

    if (test == 1000000)
      printf("0:%f  1:%f  2:%f  3:%f 4:%f\n", queue_len[0], queue_len[1], queue_len[2], queue_len[3], queue_len[4]);
    
    // Calculate shortest queue
    short_val = queue_len[0];
    for(i=1; i<5; i++)
    {
      if(queue_len[i] < short_val)
        short_val = queue_len[i];
    }

    // Determine ties
    num_ties = 0;
    for(i=0; i<5; i++)
    {
      if (short_val == queue_len[i])
      {
        select_q = i;
        ties[num_ties] = i;
        num_ties++;
      }
    }

    // Randomly select queue if tie occurs
    if(num_ties > 1)
    {
      rv = uniform(0.0,(double)num_ties);
      
      for(i=1; i<=num_ties; i++)
      {
        if(rv <= i)
        {
          select_q = ties[i-1];
          break;
        }
      }
    }
 
    // Send the customer to shortest queue
    if(select_q == 0)
    {
      Insert (service_time,&Q1);
      queue1(service_time, clock);
    }
    else if(select_q == 1)
    {
      Insert (service_time,&Q2);
      queue2(service_time, clock);
    }    
    else if(select_q == 2)
    {
      Insert (service_time,&Q3);
      queue3(service_time, clock);
    }
    else if(select_q == 3)
    {
      Insert (service_time,&Q4);
      queue4(service_time, clock);
    }
    else
    {
      Insert (service_time,&Q5);
      queue5(service_time, clock);
    }
    test++;
  }
}

//=============================================================================
//==  Function for single server queue #1                                    ==
//=============================================================================
void queue1(double service_time, double time_org)
{
  double temp = 0;

  create("queue1");

  // Reserve, hold, and release server
  reserve(Server1);
  Remove (&Q1,&temp);
  hold(service_time);
  release(Server1);

  // Record the response time
  record((clock - time_org), Resp_table);
}

//=============================================================================
//==  Function for single server queue #2                                    ==
//=============================================================================
void queue2(double service_time, double time_org)
{
  double temp = 0;
  create("queue2");

  Insert (service_time,&Q2);

  // Reserve, hold, and release server
  reserve(Server2);
  Remove (&Q2,&temp);
  hold(service_time);
  release(Server2);

  // Record the response time
  record((clock - time_org), Resp_table);
}

//=============================================================================
//==  Function for single server queue #3                                    ==
//=============================================================================
void queue3(double service_time, double time_org)
{
  double temp = 0;

  create("queue3");

  Insert (service_time,&Q3);

  // Reserve, hold, and release server
  reserve(Server3);
  Remove (&Q3,&temp);
  hold(service_time);
  release(Server3);

  // Record the response time
  record((clock - time_org), Resp_table);
}

//=============================================================================
//==  Function for single server queue #4                                    ==
//=============================================================================
void queue4(double service_time, double time_org)
{
  double temp = 0;

  create("queue4");

  Insert (service_time,&Q4);

  // Reserve, hold, and release server
  reserve(Server4);
  Remove (&Q4,&temp);
  hold(service_time);
  release(Server4);

  // Record the response time
  record((clock - time_org), Resp_table);
}

//=============================================================================
//==  Function for single server queue #5                                    ==
//=============================================================================
void queue5(double service_time, double time_org)
{
  double temp = 0;

  create("queue5");

  Insert (service_time,&Q5);

  // Reserve, hold, and release server
  reserve(Server5);
  Remove (&Q5,&temp);
  hold(service_time);
  release(Server5);

  // Record the response time
  record((clock - time_org), Resp_table);
}
