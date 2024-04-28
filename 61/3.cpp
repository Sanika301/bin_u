#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

int main()
{
  // Open semaphore
  sem_t *sem = sem_open("/my_semaphore", O_RDWR);

  if (sem == SEM_FAILED)
  {
    cerr << "Failed to open semaphore" << endl;
    return 1;
  }

  // Perform V operation (signal)
  cout << "Releasing semaphore..." << endl;
  sem_post(sem);

  // Close semaphore
  sem_close(sem);

  return 0;
}
