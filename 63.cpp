#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <sys/file.h> // Include the correct header for flock()

using namespace std;

int main()
{
  const char *filename = "testfile.txt";
  int fd;

  // Open or create the file
  fd = open(filename, O_RDWR | O_CREAT, 0666);
  if (fd == -1)
  {
    cerr << "Error opening file" << endl;
    exit(EXIT_FAILURE);
  }

  // Lock the file
  if (flock(fd, LOCK_EX) == -1)
  {
    cerr << "Error locking file" << endl;
    exit(EXIT_FAILURE);
  }

  // Write to the locked region of the file
  if (write(fd, "Locked region\n", strlen("Locked region\n")) == -1)
  {
    cerr << "Error writing to file" << endl;
    exit(EXIT_FAILURE);
  }

  // Unlock the file
  if (flock(fd, LOCK_UN) == -1)
  {
    cerr << "Error unlocking file" << endl;
    exit(EXIT_FAILURE);
  }

  // Close the file
  close(fd);

  cout << "File locked and unlocked successfully." << endl;

  return 0;
}
