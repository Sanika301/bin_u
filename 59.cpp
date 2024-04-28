#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>

using namespace std;

int main()
{
  int fd[2]; // File descriptors for the pipe
  pid_t pid;

  // Create the pipe
  if (pipe(fd) == -1)
  {
    cerr << "Pipe creation failed" << endl;
    return 1;
  }

  // Fork a child process
  pid = fork();

  if (pid == -1)
  {
    cerr << "Fork failed" << endl;
    return 1;
  }
  else if (pid > 0)
  {               // Parent process
    close(fd[0]); // Close the reading end of the pipe in the parent process

    // Open the file to read input from
    ifstream inputFile("hello.txt");
    if (!inputFile.is_open())
    {
      cerr << "Failed to open input file" << endl;
      return 1;
    }

    char ch;
    while (inputFile.get(ch))
    {
      // Convert uppercase character to lowercase
      if (isupper(ch))
      {
        ch = tolower(ch);
      }
      // Write the character to the pipe
      write(fd[1], &ch, 1);
    }

    // Close the writing end of the pipe in the parent process
    close(fd[1]);

    // Wait for the child process to finish
    wait(NULL);
  }
  else
  {               // Child process
    close(fd[1]); // Close the writing end of the pipe in the child process

    // Read from the pipe and print the converted characters
    char ch;
    while (read(fd[0], &ch, 1) > 0)
    {
      cout << ch;
    }

    // Close the reading end of the pipe in the child process
    close(fd[0]);
  }

  return 0;
}
