#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
  pid_t child_pid;
  char *login_name;

  // Create a child process using vfork
  child_pid = vfork();

  if (child_pid == -1)
  {
    perror("vfork");
    exit(EXIT_FAILURE);
  }

  if (child_pid == 0)
  {
    // Child process
    // Get the login name
    login_name = getlogin();

    if (login_name == NULL)
    {
      perror("getlogin");
      exit(EXIT_FAILURE);
    }

    cout << "Child process: Login name: " << login_name << endl;
    _exit(EXIT_SUCCESS);
  }
  else
  {
    // Parent process
    char password[20];

    // Prompt the user for a password
    cout << "Parent process: Enter password: ";
    cin >> password;

    // Wait for the child process to finish
    wait(NULL);

    cout << "Parent process: Child process completed" << endl;
  }

  return 0;
}
