#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  const char *filename = argv[1];
  struct stat file_stat;

  // Call stat to retrieve file statistics
  if (stat(filename, &file_stat) == -1)
  {
    cerr << "Error: " << strerror(errno) << endl;
    return 1;
  }

  // Display file statistics
  cout << "File: " << filename << endl;
  cout << "File type: ";
  switch (file_stat.st_mode & S_IFMT)
  {
  case S_IFREG:
    cout << "Regular file";
    break;
  case S_IFDIR:
    cout << "Directory";
    break;
  case S_IFIFO:
    cout << "FIFO/pipe";
    break;
  case S_IFLNK:
    cout << "Symbolic link";
    break;
  case S_IFSOCK:
    cout << "Socket";
    break;
  case S_IFBLK:
    cout << "Block device";
    break;
  case S_IFCHR:
    cout << "Character device";
    break;
  default:
    cout << "Unknown";
  }
  cout << endl;

  // File access permissions
  cout << "File access permissions (FAP): " << ((file_stat.st_mode & 0777) == 0777 ? "rwxrwxrwx" : "N/A") << endl;

  // Other file statistics
  cout << "File size: " << file_stat.st_size << " bytes" << endl;
  cout << "Number of hard links: " << file_stat.st_nlink << endl;
  cout << "User ID of owner: " << file_stat.st_uid << endl;
  cout << "Group ID of owner: " << file_stat.st_gid << endl;
  cout << "Last access time: " << ctime(&file_stat.st_atime);
  cout << "Last modification time: " << ctime(&file_stat.st_mtime);
  cout << "Last status change time: " << ctime(&file_stat.st_ctime);

  return 0;
}
