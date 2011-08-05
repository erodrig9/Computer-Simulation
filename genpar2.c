//==================================================== file = genpar2.c =====
//=  Program to generate bounded Pareto interarrival times                  =
//=    - pdf is f(x) = ((a*k^a) / (1 - (k/p)^a))*x^(-a-1)                   =
//=    - k is lower bound and p is upper bound                              =
//===========================================================================
//=  Notes: 1) Writes to a user specified output file                       =
//=             * File format is <interarrival time delta>                  =
//=         2) Generates samples for user specified time period             =
//=         3) See M. Crovella and M. Harchol-Balter, and C. Murta, "Task   =
//=            Assignment in a Distributed System: Improving Performance    =
//=            by Unbalancing Load," BUCS-TR-1997-018, October 1997.        =
//=-------------------------------------------------------------------------=
//= Example user input:                                                     =
//=                                                                         =
//=   ---------------------------------------- genpar2.c -----              =
//=   -  Program to generate bounded Pareto random variables -              =
//=   -  with lower bound value of k and upper bound of p    -              =
//=   --------------------------------------------------------              =
//=   Enter output file name =========================> output.dat          =
//=   Random number seed (greater than zero) =========> 1                   =
//=   Pareto alpha value =============================> 1.5                 =
//=   Pareto k value =================================> 1.0                 =
//=   Pareto p value =================================> 100.0               =
//=   Number of values to generate ===================> 5                   =
//=   --------------------------------------------------------              =
//=   -  Generating samples to file                                         =
//=   -    * alpha = 1.500000                                               =
//=   -    * k     = 1.000000                                               =
//=   -    * p     = 100.000000                                             =
//=   --------------------------------------------------------              =
//=   --------------------------------------------------------              =
//=   -  Done!                                                              =
//=   --------------------------------------------------------              =
//=-------------------------------------------------------------------------=
//= Example output file ("output.dat" for above):                           =
//=                                                                         =
//=   1.000005                                                              =
//=   1.098472                                                              =
//=   2.552966                                                              =
//=   1.504652                                                              =
//=   1.659515                                                              =
//=-------------------------------------------------------------------------=
//=  Build: bcc32 genpar2.c                                                 =
//=-------------------------------------------------------------------------=
//=  Execute: genpar2                                                       =
//=-------------------------------------------------------------------------=
//=  Author: Kenneth J. Christensen                                         =
//=          University of South Florida                                    =
//=          WWW: http://www.csee.usf.edu/~christen                         =
//=          Email: christen@csee.usf.edu                                   =
//=-------------------------------------------------------------------------=
//=  History: KJC (01/06/99) - Genesis (from genpar1.c)                     =
//=           KJC (05/20/03) - Added Jain's RNG for finer granularity       =
//=           KJC (05/13/09) - Minor clean-up                               =
//=           KJC (05/16/09) - Cleaner inversion expression in bpareto()    =
//=           KJC (06/22/09) - Corrected expression in bpareto()            =
//===========================================================================
//----- Include files -------------------------------------------------------
#include <stdio.h>            // Needed for printf()
#include <stdlib.h>           // Needed for exit() and ato*()
#include <math.h>             // Needed for log() and pow()

//----- Function prototypes -------------------------------------------------
double bpareto(double a, double k, double p); // Returns a bounded Pareto rv
double rand_val(int seed);                    // Jain's RNG

//===== Main program ========================================================
void main(void)
{
  char   in_string[256];      // Input string
  FILE   *fp;                 // File pointer to output file
  double a;                   // Pareto alpha value
  double k;                   // Pareto k value
  double p;                   // Pareto p value
  double pareto_rv;           // Pareto random variable
  int    num_values;          // Number of values
  int    i;                   // Loop counter

  //Output banner
  printf("---------------------------------------- genpar2.c ----- \n");
  printf("-  Program to generate bounded Pareto random variables - \n");
  printf("-  with lower bound value of k and upper bound of p    - \n");
  printf("-------------------------------------------------------- \n");

  // Prompt for output filename and then create/open the file
  printf("Enter output file name =========================> ");
  scanf("%s", in_string);
  fp = fopen(in_string, "w");
  if (fp == NULL)
  {
    printf("ERROR in creating output file (%s) \n", in_string);
    exit(1);
  }

  // Prompt for random number seed and then use it
  printf("Random number seed (greater than zero) =========> ");
  scanf("%s", in_string);
  rand_val((int) atoi(in_string));

  // Prompt for Pareto alpha value
  printf("Pareto alpha value =============================> ");
  scanf("%s", in_string);
  a = atof(in_string);

  // Prompt for Pareto k value
  printf("Pareto k value =================================> ");
  scanf("%s", in_string);
  k = atof(in_string);

  // Prompt for Pareto k value
  printf("Pareto p value =================================> ");
  scanf("%s", in_string);
  p = atof(in_string);

  // Prompt for number of values to generate
  printf("Number of values to generate ===================> ");
  scanf("%s", in_string);
  num_values = atoi(in_string);

  //Output message and generate samples
  printf("-------------------------------------------------------- \n");
  printf("-  Generating samples to file                    \n");
  printf("-    * alpha = %f                                \n", a);
  printf("-    * k     = %f                                \n", k);
  printf("-    * p     = %f                                \n", p);
  printf("-------------------------------------------------------- \n");
  for (i=0; i<num_values; i++)
  {
    pareto_rv = bpareto(a, k, p);
    fprintf(fp, "%f \n", pareto_rv);
  }

  //Output message and close the outout file
  printf("-------------------------------------------------------- \n");
  printf("-  Done! \n");
  printf("-------------------------------------------------------- \n");
  fclose(fp);
}

//===========================================================================
//=  Function to generate bounded Pareto distributed RVs using              =
//=    - Input:  a, k, and p                                                =
//=    - Output: Returns with bounded Pareto RV                             =
//===========================================================================
double bpareto(double a, double k, double p)
{
  double z;     // Uniform random number from 0 to 1
  double rv;    // RV to be returned

  // Pull a uniform RV (0 < z < 1)
  do
  {
    z = rand_val(0);
  }
  while ((z == 0) || (z == 1));
  printf("z: %f", z);
  // Generate the bounded Pareto rv using the inversion method
  rv = pow((pow(k, a) / (z*pow((k/p), a) - z + 1)), (1.0/a));

  return(rv);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
double rand_val(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}
