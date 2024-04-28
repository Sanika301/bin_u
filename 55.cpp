#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
  int fd[2]; // File descriptors for the pipe

  // Create the pipe
  if (pipe(fd) == -1)
  {
    cerr << "Pipe creation failed" << endl;
    return 1;
  }

  pid_t pid = fork(); // Create a child process

  if (pid == -1)
  {
    cerr << "Fork failed" << endl;
    return 1;
  }
  else if (pid > 0)
  {               // Parent process
    close(fd[0]); // Close the reading end of the pipe in the parent process

    // Data to be sent from parent to child
    string data = "Hello from parent!";

    // Write data to the pipe
    if (write(fd[1], data.c_str(), data.size()) == -1)
    {
      cerr << "Write to pipe failed" << endl;
      return 1;
    }

    cout << "Parent sent: " << data << endl;

    // Close the writing end of the pipe in the parent process
    close(fd[1]);
  }
  else
  {               // Child process
    close(fd[1]); // Close the writing end of the pipe in the child process

    char buffer[100]; // Buffer to store received data

    // Read data from the pipe
    int bytes_read = read(fd[0], buffer, sizeof(buffer));

    if (bytes_read == -1)
    {
      cerr << "Read from pipe failed" << endl;
      return 1;
    }

    // Null-terminate the received data
    buffer[bytes_read] = '\0';

    cout << "Child received: " << buffer << endl;

    // Close the reading end of the pipe in the child process
    close(fd[0]);
  }

  return 0;
}
