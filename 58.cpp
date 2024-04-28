#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
  const char *fifoName = "/tmp/myfifo";
  const char *inputFileName = "hello.txt";
  const char *outputFileName = "output.txt";

  // Create the FIFO (named pipe)
  mkfifo(fifoName, 0666);

  pid_t pid = fork(); // Fork a child process

  if (pid == -1)
  {
    cerr << "Fork failed" << endl;
    return 1;
  }
  else if (pid > 0)
  {                                    // Parent process
    int fd = open(fifoName, O_WRONLY); // Open the FIFO for writing

    // Open the input file
    int inputFile = open(inputFileName, O_RDONLY);
    if (inputFile == -1)
    {
      cerr << "Failed to open input file" << endl;
      return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    // Read from the input file and write into the FIFO
    while ((bytesRead = read(inputFile, buffer, sizeof(buffer))) > 0)
    {
      if (write(fd, buffer, bytesRead) == -1)
      {
        cerr << "Write to FIFO failed" << endl;
        return 1;
      }
    }

    // Close the input file and FIFO
    close(inputFile);
    close(fd);
  }
  else
  {                                    // Child process
    int fd = open(fifoName, O_RDONLY); // Open the FIFO for reading

    // Create or truncate the output file
    int outputFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outputFile == -1)
    {
      cerr << "Failed to create output file" << endl;
      return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    // Read from the FIFO and write into the output file
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
    {
      if (write(outputFile, buffer, bytesRead) != bytesRead)
      {
        cerr << "Write to output file failed" << endl;
        return 1;
      }
    }

    // Close the output file and FIFO
    close(outputFile);
    close(fd);
  }

  // Remove the FIFO
  unlink(fifoName);

  return 0;
}
