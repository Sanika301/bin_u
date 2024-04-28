// Write a program using PIPE, to Send file from parent to child over a pipe.
// (unnamed pipe )
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    // Open the file to be sent
    FILE *file = fopen("hello.txt", "r");
    if (file == nullptr)
    {
      cerr << "Failed to open file" << endl;
      return 1;
    }

    char buffer[1024];
    size_t bytesRead;

    // Read from the file and write into the pipe
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
      if (write(fd[1], buffer, bytesRead) == -1)
      {
        cerr << "Write to pipe failed" << endl;
        return 1;
      }
    }

    // Close the writing end of the pipe in the parent process
    close(fd[1]);

    // Wait for the child process to finish
    wait(NULL);
  }
  else
  {               // Child process
    close(fd[1]); // Close the writing end of the pipe in the child process

    // Open a new file to write the received data
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == nullptr)
    {
      cerr << "Failed to create output file" << endl;
      return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    // Read from the pipe and write into the output file
    while ((bytesRead = read(fd[0], buffer, sizeof(buffer))) > 0)
    {
      if (fwrite(buffer, 1, bytesRead, outputFile) != bytesRead)
      {
        cerr << "Write to file failed" << endl;
        return 1;
      }
    }

    // Close the reading end of the pipe in the child process
    close(fd[0]);

    // Close the output file
    fclose(outputFile);
  }

  return 0;
}
