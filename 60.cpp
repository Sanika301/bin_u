#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
  sem_t semaphore;
  sem_init(&semaphore, 1, 1); // Initialize semaphore with value 1

  pid_t pid = fork();

  if (pid == -1)
  {
    cerr << "Fork failed" << endl;
    return 1;
  }
  else if (pid > 0)
  {                       // Parent process
    sem_wait(&semaphore); // Wait for semaphore

    cout << "Parent process: Inside critical section" << endl;
    sleep(2); // Simulate some work

    sem_post(&semaphore); // Release semaphore
  }
  else
  {                       // Child process
    sem_wait(&semaphore); // Wait for semaphore

    cout << "Child process: Inside critical section" << endl;
    sleep(2); // Simulate some work

    sem_post(&semaphore); // Release semaphore
  }

  // Wait for child process to finish
  if (pid > 0)
  {
    wait(NULL);
  }

  sem_destroy(&semaphore); // Destroy semaphore

  return 0;
}
