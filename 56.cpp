// Write a program using FIFO, to Send data from parent to child over a pipe. (named
// pipe)
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main()
{
  const char *fifoName = "/tmp/myfifo";

  // Create the FIFO (named pipe)
  mkfifo(fifoName, 0666);

  pid_t pid = fork(); // Create a child process

  if (pid == -1)
  {
    cerr << "Fork failed" << endl;
    return 1;
  }
  else if (pid > 0)
  {                                    // Parent process
    int fd = open(fifoName, O_WRONLY); // Open the FIFO for writing

    // Data to be sent from parent to child
    string data = "Hello from parent!";

    // Write data to the FIFO
    write(fd, data.c_str(), data.size());

    cout << "Parent sent: " << data << endl;

    // Close the FIFO
    close(fd);
  }
  else
  {                                    // Child process
    int fd = open(fifoName, O_RDONLY); // Open the FIFO for reading

    char buffer[100]; // Buffer to store received data

    // Read data from the FIFO
    int bytes_read = read(fd, buffer, sizeof(buffer));

    // Null-terminate the received data
    buffer[bytes_read] = '\0';

    cout << "Child received: " << buffer << endl;

    // Close the FIFO
    close(fd);
  }

  return 0;
}
