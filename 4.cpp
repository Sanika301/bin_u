#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t child_pid;

  // Create a child process using vfork
  child_pid = vfork();

  if (child_pid == -1)
  {
    // vfork failed
    std::cerr << "Failed to vfork a child process." << std::endl;
    return 1;
  }

  if (child_pid == 0)
  {
    // Child process
    // Execute the application (in this case, open the default text editor)
    execl("/usr/bin/gedit", "gedit", nullptr);

    // If execl fails, print an error message
    std::cerr << "Failed to execute the application." << std::endl;
    _exit(1);
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
