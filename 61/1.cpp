#include <iostream>
#include <semaphore.h>
#include <fcntl.h>

using namespace std;

int main()
{
  // Initialize semaphore
  sem_t *sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0644, 1);

  if (sem == SEM_FAILED)
  {
    cerr << "Failed to initialize semaphore" << endl;
    return 1;
  }

  // Display semaphore ID
  cout << "Semaphore ID: " << sem << endl;

  // Close semaphore
  sem_close(sem);

  return 0;
}
