#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main()
{
  pid_t pid;
  int i;

  // Loop to create 3 child processes
  for (i = 0; i < 5; i++)
  {
    pid = fork(); // Create a new process (fork)

    if (pid == 0)
    {
      // Child process
      cout << "Child " << i + 1 << " PID: " << getpid() << std::endl; // Print child process ID
      sleep(2 * i);                                                   // Simulate some work
      exit(0);                                                        // Terminate child process
    }
    else if (pid < 0)
    {
      // Error handling if fork fails
      perror("fork failed"); // Handle fork failure
      exit(1);
    }
  }

  // Parent process
  for (i = 0; i < 5; i++)
  {
    wait(NULL);
    cout << "Completed Process " << i << endl;
  }

  // Print parent process ID
  cout << "Parent PID: " << getpid() << std::endl; // Print parent process ID

  return 0;
}