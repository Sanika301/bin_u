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
    // Execute gedit
    execl("/usr/bin/gedit", "gedit", nullptr);

    // If execl fails, print an error message
    std::cerr << "Failed to execute gedit." << std::endl;
    return 1;
  }
  else
  {
    // Parent process
    // Wait for the child process to finish
    wait(NULL);
    std::cout << "Child process completed." << std::endl;
  }

  return 0;
}
