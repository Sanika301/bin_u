#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

void signal_handler(int signal)
{
  cout << "Signal " << signal << " received." << endl;
}

int main()
{
  pid_t pid;

  // Fork a child process
  pid = fork();

  if (pid < 0)
  {
    // Fork failed
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    // Child process
    cout << "Child process created with PID: " << getpid() << endl;

    // Install signal handler for SIGUSR1
    signal(SIGUSR1, signal_handler);

    // Wait for signal from parent
    pause();

    cout << "Child process exiting." << endl;
    exit(EXIT_SUCCESS);
  }
  else
  {
    // Parent process
    cout << "Parent process created with PID: " << getpid() << endl;

    // Wait for a moment to ensure child is ready to receive signal
    sleep(1);

    // Send SIGUSR1 signal to child
    cout << "Sending SIGUSR1 signal to child process..." << endl;
    if (kill(pid, SIGUSR1) == -1)
    {
      perror("kill");
      exit(EXIT_FAILURE);
    }

    // Wait for child to exit
    wait(NULL);

    cout << "Parent process exiting." << endl;
    exit(EXIT_SUCCESS);
  }
}
