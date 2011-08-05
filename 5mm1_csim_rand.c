//=============================================== file = 5mm1_csim_rand.c =====
//=  A CSIM simulation of a 2 M/M/1 queueing systems with random split        =
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
  double   rv;                   // Random variable

  create("generate");

  // Loop forever to create customers
  while(1)
  {
    // Pull an interarrival time and hold for it
    interarrival_time = exponential(1.0 / lambda);
    hold(interarrival_time);

    // Pull a service time
    //service_time = exponential(1.0 / mu);
    service_time = mu;

    // Generate uniform random variable
    rv = uniform(0.0,1.0);

    // Send the customer to a randomly selected queue
    if (rv < (double)1/(double)5)
      queue1(service_time, clock);
    else if (rv < (double)2/(double)5)
      queue2(service_time, clock);
    else if (rv < (double)3/(double)5)
      queue3(service_time, clock);
    else if (rv < (double)4/(double)5)
      queue4(service_time, clock);
    else
      queue5(service_time, clock);
  }
}

//=============================================================================
//==  Function for single server queue #1                                    ==
//=============================================================================
void queue1(double service_time, double time_org)
{
  create("queue1");

  // Reserve, hold, and release server
  reserve(Server1);
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
  create("queue2");

  // Reserve, hold, and release server
  reserve(Server2);
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
  create("queue3");

  // Reserve, hold, and release server
  reserve(Server3);
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
  create("queue4");

  // Reserve, hold, and release server
  reserve(Server4);
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
  create("queue5");

  // Reserve, hold, and release server
  reserve(Server5);
  hold(service_time);
  release(Server5);

  // Record the response time
  record((clock - time_org), Resp_table);
}
