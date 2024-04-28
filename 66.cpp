#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

const char *inputFifo = "/tmp/input_fifo";
const char *outputFifo = "/tmp/output_fifo";

int main()
{
  // Create the input FIFO (named pipe) if it doesn't exist
  if (mkfifo(inputFifo, 0666) == -1)
  {
    cerr << "Error creating input FIFO" << endl;
    exit(EXIT_FAILURE);
  }

  // Create the output FIFO (named pipe) if it doesn't exist
  if (mkfifo(outputFifo, 0666) == -1)
  {
    cerr << "Error creating output FIFO" << endl;
    exit(EXIT_FAILURE);
  }

  // Open the input FIFO for reading
  int inputFd = open(inputFifo, O_RDONLY);
  if (inputFd == -1)
  {
    cerr << "Error opening input FIFO for reading" << endl;
    exit(EXIT_FAILURE);
  }

  // Open the output FIFO for writing
  int outputFd = open(outputFifo, O_WRONLY);
  if (outputFd == -1)
  {
    cerr << "Error opening output FIFO for writing" << endl;
    exit(EXIT_FAILURE);
  }

  char buffer[256];
  ssize_t bytesRead;

  // Read from the input FIFO and convert to lowercase
  while ((bytesRead = read(inputFd, buffer, sizeof(buffer))) > 0)
  {
    for (ssize_t i = 0; i < bytesRead; ++i)
    {
      buffer[i] = tolower(buffer[i]);
    }

    // Write the converted text to the output FIFO
    if (write(outputFd, buffer, bytesRead) == -1)
    {
      cerr << "Error writing to output FIFO" << endl;
      exit(EXIT_FAILURE);
    }
  }

  // Close the FIFOs
  close(inputFd);
  close(outputFd);

  // Remove the FIFOs
  unlink(inputFifo);
  unlink(outputFifo);

  cout << "Conversion complete." << endl;

  return 0;
}

// rm /tmp/input_fifo /tmp/output_fifo
// g++ 66.cpp -o uppercase_to_lowercase
// ./uppercase_to_lowercase
// On New Terminal
// echo "HELLO" >/tmp/input_fifo
// cat /tmp/output_fifo
// rm /tmp/input_fifo /tmp/output_fifo
