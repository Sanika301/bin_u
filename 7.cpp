#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t child_pid;

  // Create a child process
  child_pid = fork();

  if (child_pid == -1)
  {
    // Fork failed
    std::cerr << "Failed to fork a child process." << std::endl;
    return 1;
  }

  if (child_pid == 0)
  {
    // Child process
    std::cout << "Child process: PID = " << getpid() << std::endl;
    std::cout << "Child process: Parent PID = " << getppid() << std::endl;

    // Simulate some work in the child process
    std::cout << "Child process: Simulating work..." << std::endl;
    sleep(3);

    // Exit the child process with exit status 42
    std::cout << "Child process: Exiting with status 42." << std::endl;
    exit(42);
  }
  else
  {
    // Parent process
    std::cout << "Parent process: PID = " << getpid() << std::endl;
    std::cout << "Parent process: Child PID = " << child_pid << std::endl;

    // Wait for the child process to finish and retrieve its exit status
    int status;
    pid_t terminated_pid = wait(&status);

    if (terminated_pid == -1)
    {
      std::cerr << "Error waiting for child process." << std::endl;
      return 1;
    }

    if (WIFEXITED(status))
    {
      // Child process exited normally
      std::cout << "Parent process: Child process with PID " << terminated_pid
                << " exited with status: " << WEXITSTATUS(status) << std::endl;
    }
    else if (WIFSIGNALED(status))
    {
      // Child process terminated by a signal
      std::cout << "Parent process: Child process with PID " << terminated_pid
                << " terminated by signal: " << WTERMSIG(status) << std::endl;
    }

    std::cout << "Parent process: Done." << std::endl;
  }

  return 0;
}
