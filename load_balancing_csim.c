//======================================== file = load_balancing_csim.c =======
//=  A CSIM simulation of a 5 queue load balancer                             =
//=============================================================================
//=  Notes:                                                                   =
//=   1) offered_load is a command line input, mu is sent in sim(),           =
//=      lambda is calculated                                                 =
//=   2) Delay is a command line input if DELAY_ON is defined                 =
//=---------------------------------------------------------------------------=
//= Example execution:                                                        =
//=                                                                           =
//=  *** BEGIN SIMULATION ***                                                 =
//=  =============================================================            =
//=  = Lambda               =  4.500 cust/sec                                 =
//=  = Mu (for each server) =  1.000 cust/sec                                 =
//=  =============================================================            =
//=  = Total CPU time     = 18.100 sec                                        =
//=  = Total sim time     = 2000000.000 sec                                   =
//=  = Total completions  = 8998190 cust                                      =
//=  =------------------------------------------------------------            =
//=  = >>> Simulation results                                    -            =
//=  =------------------------------------------------------------            =
//=  = Utilization 1        = 89.976 %                                        =
//=  = Mean num in system 1 =  2.511 cust                                     =
//=  = Mean response time 1 =  2.791 sec                                      =
//=  = Mean service time 1  =  1.000 sec                                      =
//=  = Mean throughput 1    =  0.900 cust/sec                                 =
//=  =------------------------------------------------------------            =
//=  = Utilization 2        = 90.027 %                                        =
//=  = Mean num in system 2 =  2.513 cust                                     =
//=  = Mean response time 2 =  2.793 sec                                      =
//=  = Mean service time 2  =  1.001 sec                                      =
//=  = Mean throughput 2    =  0.900 cust/sec                                 =
//=  =------------------------------------------------------------            =
//=  = Utilization 3        = 90.018 %                                        =
//=  = Mean num in system 3 =  2.511 cust                                     =
//=  = Mean response time 3 =  2.791 sec                                      =
//=  = Mean service time 3  =  1.001 sec                                      =
//=  = Mean throughput 3    =  0.900 cust/sec                                 =
//=  =------------------------------------------------------------            =
//=  = Utilization 4        = 90.024 %                                        =
//=  = Mean num in system 4 =  2.512 cust                                     =
//=  = Mean response time 4 =  2.794 sec                                      =
//=  = Mean service time 4  =  1.001 sec                                      =
//=  = Mean throughput 4    =  0.899 cust/sec                                 =
//=  =------------------------------------------------------------            =
//=  = Utilization 5        = 90.000 %                                        =
//=  = Mean num in system 5 =  2.511 cust                                     =
//=  = Mean response time 5 =  2.788 sec                                      =
//=  = Mean service time 5  =  0.999 sec                                      =
//=  = Mean throughput 5    =  0.901 cust/sec                                 =
//=  =------------------------------------------------------------            =
//=  & Table mean for response time =  2.791 sec                              =
//=  =============================================================            =
//=                                                                           =
//=  TABLE 1:  Response time table                                            =
//=                                                                           =
//=   minimum         0.000000          mean                    2.791199      =
//=   maximum        37.700703          variance                6.594464      =
//=   range          37.700703          standard deviation      2.567969      =
//=   observations     8998185          coefficient of var      0.920024      =
//=                                                                           =
//=   results of run length control using confidence intervals                =
//=                                                                           =
//=   cpu time limit     120.0          accuracy requested      0.010000      =
//=   cpu time used       18.1          accuracy achieved       0.005430      =
//=                                                                           =
//=   > the requested accuracy has been achieved                              =
//=                                                                           =
//=   95.0% confidence interval: 2.791198 +/- 0.015074 = [2.776125, 2.806272] =
//=                                                                           =
//=  *** END SIMULATION ***                                                   =
//=---------------------------------------------------------------------------=
//=  Build: standard CSIM build                                               =
//=---------------------------------------------------------------------------=
//=  Execute: project_1                                                       =
//=---------------------------------------------------------------------------=
//=  Authors: Emmanuel Rodriguez                                              =
//=           University of South Florida                                     =
//=           Email: erodrig9@mail.usf.edu                                    =
//=                                                                           =
//=           Jared Jones                                                     =
//=           University of South Florida                                     =
//=           Email: jvjones@mail.usf.edu                                     =
//=                                                                           =
//=           Ken Christensen (2mm1_csim.c)                                  =
//=           University of South Florida                                     =
//=           WWW: http://www.csee.usf.edu/~christen                          =
//=           Email: christen@csee.usf.edu                                    =
//=---------------------------------------------------------------------------=
//=  History: KJC (06/09/09) - Genesis (2mm1_csim.c)                          =
//=      project_1.c:                                                         =
//=           ER & JJ (06/28/09) - Implemented 5 x mm1                        =
//=           ER & JJ (07/01/09) - Implemented RR and rand policies           =
//=           ER & JJ (07/05/09) - Implemented shortest queue policy          =
//=           ER & JJ (07/07/09) - Implemented bounded pareto service time    =
//=           ER & JJ (07/19/09) - Implemented CI and run-length control      =
//=============================================================================

//----- Includes --------------------------------------------------------------
#include <stdio.h>      // Needed for printf()
#include <stdlib.h>     // Needed for atof()
#include <assert.h>     // Needed for assert()
#include <math.h>       // Needed for log() and pow()
#include "csim.h"       // Needed for CSIM19 stuff

//----- Defines ---------------------------------------------------------------
#define SIM_TIME 2.0e6  // Total simulation time in seconds
#define EXP             // Define service time distribution (EXP, DETER, BPAR)
#define RR            // Define load balancing policy (SHORT, RR, RAND, SERV)
#define DELAY_OFF       // Define delay on or off (DELAY_ON, DELAY_OFF)

//----- Globals ---------------------------------------------------------------
FACILITY Server1;       // Declaration of CSIM Server facility #1
FACILITY Server2;       // Declaration of CSIM Server facility #2
FACILITY Server3;       // Declaration of CSIM Server facility #3
FACILITY Server4;       // Declaration of CSIM Server facility #4
FACILITY Server5;       // Declaration of CSIM Server facility #5
TABLE    Util1;         // Declaration of CSIM Server table #1
TABLE    Util2;         // Declaration of CSIM Server table #2
TABLE    Util3;         // Declaration of CSIM Server table #3
TABLE    Util4;         // Declaration of CSIM Server table #4
TABLE    Util5;         // Declaration of CSIM Server table #5
TABLE    Resp_table;    // Declaration of CSIM Table
int      Queue_len[5];  // Number of customers in system
double   Delay;         // Queue state informaion delay
int      Select_q;      // Queue Chosen

//----- Prototypes ------------------------------------------------------------
void generate(double lambda, double mu);                  // Customer generator
void queue1(double service_time, double time_org);        // Single server queue #1
void queue2(double service_time, double time_org);        // Single server queue #2
void queue3(double service_time, double time_org);        // Single server queue #3
void queue4(double service_time, double time_org);        // Single server queue #4
void queue5(double service_time, double time_org);        // Single server queue #5
void load_balancer(double org_time, double service_time); // Load Balancer
void update_state();                                      // Update system information
double bounded_pareto();                                  // Generate bounded pareto rv

//=============================================================================
//==  Main program                                                           ==
//=============================================================================
void sim(int argc, char *argv[])
{
  double   lambda;       // Mean arrival rate (cust/sec)
  double   mu;           // Mean service rate (cust/sec)
  double   offered_load; // Offered load
  int      i;            // Iteration value

  // Create the simulation
  create("sim");

#ifdef DELAY_ON
  // Output usage
  if (argc != 3)
  {
    printf("Usage: ./a.out OfferedLoad Delay\n");
    return;
  }
  Delay = atof(argv[2]);
#else
  if (argc != 2)
  {
    printf("Usage: ./a.out OfferedLoad\n");
	return;
  }
#endif
  offered_load = atof(argv[1]);
  assert((offered_load > 0.0) && (offered_load < 1.0));

  // CSIM initializations
  Server1 = facility("Server1");
  Server2 = facility("Server2");
  Server3 = facility("Server3");
  Server4 = facility("Server4");
  Server5 = facility("Server5");
  Resp_table = table("Response time table");
  Util1 = table("Server1 Util");
  Util2 = table("Server2 Util");
  Util3 = table("Server3 Util");
  Util4 = table("Server4 Util");
  Util5 = table("Server5 Util");

  // CI run length control
  table_confidence(Resp_table);
  table_run_length(Resp_table, 0.01, 0.95, 120.0);

  // Initializations
  mu = 1.0;
  lambda = offered_load * (double)5;
  Select_q = 1;
  for(i=0; i<5; i++)
    Queue_len[i] = 0;

  // Output begin-of-simulation banner
  printf("*** BEGIN SIMULATION *** \n");

  // Initiate generate function and hold for SIM_TIME
  generate(lambda, mu);
#ifdef DELAY_ON
  update_state();
#endif
  wait(converged);

  // Output results
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

  report_table(Resp_table);

  // Output end-of-simulation banner
  printf("*** END SIMULATION *** \n");
  getchar();
}

//=============================================================================
//==  Function to generate customers                                         ==
//=============================================================================
void generate(double lambda, double mu)
{
  double   interarrival_time;    // Interarrival time to next send
  double   service_time;         // Service time for this customer
//  int      i;                    // Iteration value

  create("generate");

  // Loop forever to create customers
  while(1)
  {
	  // Check for unstable system
	  if (qlength(Server1) > 100 || qlength(Server2) > 100 || qlength(Server3) > 100 || qlength(Server4) > 100 || qlength(Server5) > 100)
    {
      fprintf(stderr, "\nQueue Limit Exceeded!\n");
      getchar();
      exit(1);
    }


    // Pull an interarrival time and hold for it
    interarrival_time = exponential(1.0 / lambda);
    hold(interarrival_time);

    // Pull a service time
#if defined(EXP)
    service_time = exponential(1.0 / mu);
#elif defined(DETER)
    service_time = mu;
#else
    service_time = bounded_pareto();
#endif

    // Load balance jobs among servers
    load_balancer(clock, service_time);
  }
}

//=============================================================================
//==  Function for load balancer                                             ==
//=============================================================================
void load_balancer (double org_time, double service_time)
{
  int      ties[5];              // Tied queue values
  int      util_ties[5];         // Tied utilization values
  double   serv_util[5];         // Server Utilizations
  double   rv;                   // Random Value
  double   lowest_util;          // Lowest utilization
  int      num_ties;             // Number of ties
  int      serv_ties;            // Number of utilization ties
  int      short_val;            // Shortest Queue value
  int      i;                    // Iteration value
  
#if ((defined(SHORT) || defined(SERV)) && defined(DELAY_OFF))
  // Determine # customers in each system
  Queue_len[0] = qlength(Server1) + num_busy(Server1);
  Queue_len[1] = qlength(Server2) + num_busy(Server2);
  Queue_len[2] = qlength(Server3) + num_busy(Server3);
  Queue_len[3] = qlength(Server4) + num_busy(Server4);
  Queue_len[4] = qlength(Server5) + num_busy(Server5);
#endif

#if (defined(SHORT) || defined(SERV))
  // Calculate shortest queue
  short_val = Queue_len[0];
  for(i=1; i<5; i++)
  {
    if(Queue_len[i] < short_val)
      short_val = Queue_len[i];
  }

  // Determine ties
  num_ties = 0;
  for(i=0; i<5; i++)
  {
    if (short_val == Queue_len[i])
    {
      Select_q = i;
      ties[num_ties] = i;
      num_ties++;
    }
  }
#endif

#ifdef RAND
  num_ties = 5;
  for(i=0; i<5; i++)
    ties[i] = i;
#endif

#if (defined(RAND) || defined(SHORT))
  // Randomly select queue if tie occurs
  if(num_ties > 1)
  {
    rv = uniform(0.0,(double)num_ties);

    for(i=1; i<=num_ties; i++)
    {
      if(rv <= (double)i)
      {
        Select_q = ties[i-1];
        break;
      }
    }
  }
#endif

#if defined(SERV)
  if(num_ties > 1)
  {
    serv_util[0] = table_sum(Util1);
    serv_util[1] = table_sum(Util2);
    serv_util[2] = table_sum(Util3);
    serv_util[3] = table_sum(Util4);
    serv_util[4] = table_sum(Util5);
    
    lowest_util = serv_util[ties[0]];
    for(i=1; i<num_ties; i++)
    {
      if(serv_util[ties[i]] < lowest_util)
        lowest_util = serv_util[ties[i]];
    }
  
    // Determine ties
    serv_ties = 0;
    for(i=0; i<num_ties; i++)
    {
      if (lowest_util == serv_util[ties[i]])
      {
        util_ties[serv_ties] = ties[i];
        serv_ties++;
      }
    }

    if(serv_ties <= 1)
    {

      if(lowest_util == serv_util[0])
        Select_q = 0;
      else if(lowest_util == serv_util[1])
        Select_q = 1;
      else if(lowest_util == serv_util[2])
        Select_q = 2;
      else if(lowest_util == serv_util[3])
        Select_q = 3;
      else
        Select_q = 4;
    }
    else
    {
      rv = uniform(0.0,(double)serv_ties);

      for(i=1; i<=serv_ties; i++)
      {
        if(rv <= (double)i)
        {
          Select_q = util_ties[i-1];
          break;
        }
      }
    }
  }
#endif

#if (defined(RAND) || defined(SHORT) || defined(SERV))
  // Send the customer to shortest queue
  if(Select_q == 0)
    queue1(service_time, org_time);
  else if(Select_q == 1)
    queue2(service_time, org_time);
  else if(Select_q == 2)
    queue3(service_time, org_time);
  else if(Select_q == 3)
    queue4(service_time, org_time);
  else
    queue5(service_time, org_time);
#else
  if (Select_q == 1)
    {
      queue1(service_time, clock);
      Select_q++;
    }
    else if (Select_q == 2)
    {
      queue2(service_time, clock);
      Select_q++;
    }
    else if (Select_q == 3)
    {
      queue3(service_time, clock);
      Select_q++;
    }
    else if (Select_q == 4)
    {
      queue4(service_time, clock);
      Select_q++;
    }
    else
    {
      queue5(service_time, clock);
      Select_q = 1;
    }
#endif
}

//=============================================================================
//==  Function for state update                                              ==
//=============================================================================
void update_state()
{
  create("state update");

  while(1)
  {
    // Update state informaion
    Queue_len[0] = qlength(Server1) + num_busy(Server1);
    Queue_len[1] = qlength(Server2) + num_busy(Server2);
    Queue_len[2] = qlength(Server3) + num_busy(Server3);
    Queue_len[3] = qlength(Server4) + num_busy(Server4);
    Queue_len[4] = qlength(Server5) + num_busy(Server5);

    // Hold for Delay seconds
    hold(Delay);
  }

}

//=============================================================================
//==  Function for single server queue #1                                    ==
//=============================================================================
void queue1(double service_time, double time_org)
{
  create("queue1");

  record(service_time, Util1);

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

  record(service_time, Util2);

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

  record(service_time, Util3);

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

  record(service_time, Util4);

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

  record(service_time, Util5);

  // Reserve, hold, and release server
  reserve(Server5);
  hold(service_time);
  release(Server5);

  // Record the response time
  record((clock - time_org), Resp_table);
}

//=============================================================================
//==  Function for bounded pareto distribution                               ==
//==    - Inversion expression from genpar2.c                                ==
//=============================================================================
double bounded_pareto()
{
  double a;     // Alpha value
  double min;   // Min value
  double max;   // Max value
  double z;     // Uniform random number from 0 to 1
  double rv;    // RV to be returned


  // Initialize parameters
  a = 1.985;
  min = 0.5;
  max = 100.0;

  // Pull a uniform RV
  do
  {
    z = uniform(0.0,1.0);
  }
  while ((z == 0) || (z == 1));

  // Generate the bounded Pareto rv using the inversion method
  rv = pow((pow(min, a) / (z*pow((min/max), a) - z + 1)), (1.0/a));

  return(rv);
}
