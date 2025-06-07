#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


int socket_fd = -1;
char temp_filename[] = "/tmp/mytempfileXXXXXX";
int temp_fd = -1;


void cleanup_and_exit(int exit_code)
{
  if (socket_fd != -1)
  {
    close(socket_fd);
  }
  if (temp_fd != -1)
  {
    close(temp_fd);
    unlink(temp_filename);
  }

  fflush(stdout);
  fflush(stderr);
  exit(exit_code);
}

void signal_handler(int sig)
{
  const char *msg = "Signal received, cleaning up...\n";
  write(STDERR_FILENO, msg, strlen(msg));

  if (socket_fd != -1) close(socket_fd);
  if (temp_fd != -1)
  {
    close(temp_fd);
    unlink(temp_filename);
  }

  _exit(128 + sig);
}


int main()
{
  struct sigaction sa;
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);

  temp_fd = mkstemp(temp_filename);
  if (temp_fd == -1)
  {
    perror("mkstemp failed");
    return 1;
  }

  socket_fd = open("/dev/null", O_WRONLY);
  if (socket_fd == -1)
  {
    perror("open socket failed");
    cleanup_and_exit(1);
  }

  printf("Program running. Press Ctrl+C to interrupt.\n");

  for (int i = 0; i < 10; i++)
  {
    printf("Working... %d\n", i);
    sleep(1);
  }

  cleanup_and_exit(0);
}