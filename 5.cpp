#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t child_pid;

  // Create a child process using fork
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
    sleep(3); // Simulate some work in the child process
    std::cout << "Child process: Done." << std::endl;
    return 0;
  }
  else
  {
    // Parent process
    std::cout << "Parent process: PID = " << getpid() << std::endl;
    std::cout << "Parent process: Child PID = " << child_pid << std::endl;

    // Wait for the child process to finish
    int status;
    pid_t terminated_pid = wait(&status);

    if (terminated_pid == -1)
    {
      std::cerr << "Error waiting for child process." << std::endl;
      return 1;
    }

    if (WIFEXITED(status))
    {
      std::cout << "Parent process: Child process with PID " << terminated_pid << " terminated normally with status: " << WEXITSTATUS(status) << std::endl;
    }
    else if (WIFSIGNALED(status))
    {
      std::cout << "Parent process: Child process with PID " << terminated_pid << " terminated by signal: " << WTERMSIG(status) << std::endl;
    }

    std::cout << "Parent process: Done." << std::endl;
  }

  return 0;
}
