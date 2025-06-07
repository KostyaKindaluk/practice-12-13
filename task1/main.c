#include <signal.h>
#include <stdio.h>


int counter = 10;

void handle_sigint(int sig)
{
  printf("Caught signal %d\n ", sig);
  
  counter--;
  if (counter > 0)
  {
    printf("%d left :)\n", counter);
  }
  else
  {
    printf("Congratulations, you got out!\n");
  }
}

int main()
{
  signal(SIGINT, handle_sigint);
  while (counter > 0) {}
}