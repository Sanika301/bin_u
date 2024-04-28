#include <iostream>
#include <semaphore.h>
#include <unistd.h>
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

  // Perform P operation (wait)
  cout << "Waiting for semaphore..." << endl;
  sem_wait(sem);
  cout << "Semaphore acquired. Performing critical section task..." << endl;
  sleep(2); // Simulate critical section task

  // Close semaphore
  sem_close(sem);

  return 0;
}
