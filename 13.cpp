#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  // Specify the path to the file
  const char *filename = "/home/sanika/Sanika/cpp/UOS/7.cpp";

  // Open the file
  int fd = open(filename, O_RDONLY);
  if (fd == -1)
  {
    std::cerr << "Error opening file\n";
    return 1;
  }

  // Declare a struct to hold file statistics
  struct stat fileStat;

  // Call fstat to retrieve file statistics
  if (fstat(fd, &fileStat) == -1)
  {
    std::cerr << "Error getting file statistics\n";
    close(fd);
    return 1;
  }

  // Output important fields
  std::cout << "File Access Permissions (FAP): " << (fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) << std::endl;
  std::cout << "File Type: ";
  if (S_ISREG(fileStat.st_mode))
    std::cout << "Regular file\n";
  else if (S_ISDIR(fileStat.st_mode))
    std::cout << "Directory\n";
  else if (S_ISCHR(fileStat.st_mode))
    std::cout << "Character special file\n";
  else if (S_ISBLK(fileStat.st_mode))
    std::cout << "Block special file\n";
  else if (S_ISFIFO(fileStat.st_mode))
    std::cout << "FIFO (named pipe)\n";
  else if (S_ISLNK(fileStat.st_mode))
    std::cout << "Symbolic link\n";
  else if (S_ISSOCK(fileStat.st_mode))
    std::cout << "Socket\n";
  else
    std::cout << "Unknown\n";

  // Close the file
  close(fd);

  return 0;
}
