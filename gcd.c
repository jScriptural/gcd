#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//MACROS
#define USE_RECURSION 0


//Function prototypes
int get_cmdline_args(int argc,char **argv,long *n1,long *n2);
long gcd(long num1, long num2);


int main(int argc, char *argv[])
{
  long orig_num1, orig_num2;
  long arg1, arg2, res;

  //incorrect usage
  if(argc != 3)
  {
    errno = argc < 3?EINVAL:E2BIG;
    perror("gcd");
    exit(2);
  }

  if(get_cmdline_args(argc,argv,&orig_num1,&orig_num2) == -1)
  {
    perror("gcd");
    exit(EXIT_FAILURE);
  }

  //ensure all are positive since
  //the signs do not affect gcd.
  arg1 = orig_num1 < 0?orig_num1*-1:orig_num1;
  arg2 = orig_num2 < 0?orig_num2*-1:orig_num2;

  res = gcd(arg1,arg2);
  printf("gcd(%ld,%ld): %ld\n",orig_num1,orig_num2,res);

  exit(EXIT_SUCCESS);
}


long gcd(long num1, long num2)
{
  long smaller;
  long larger;

  larger = ((num1+num2) - (smaller = (num1 < num2)? num1 : num2));

  if(smaller == 0)
    return larger;

  if((larger % smaller) == 0)
    return smaller;

#if USE_RECURSION
  long rem = larger % smaller;
  gcd(smaller,rem);
#else
  while(larger % smaller != 0)
  {
    long rem = larger % smaller;
    larger = smaller;
    smaller = rem;
  }

  return smaller;
#endif
}

int get_cmdline_args(int argc,char **argv,long *num1, long *num2)
{
  char *endptr;
  long arg[2];
  errno = 0;

  for(int i=0; i < 2; ++i)
  {
    arg[i] = strtol(argv[i+1], &endptr, 10);
    if(errno != 0)
      return -1;

    if(arg[i] == 0 && strcmp(argv[i+1],endptr) == 0)
    {
      errno = EINVAL;
      return -1;
    }
  }

  *num1 = arg[0];
  *num2 = arg[1];

  return 0;
}
