#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

#define SHM_SIZE 1024
#define KEY 1234

int main()
{
  int shmid;
  char *shared_memory;
  char input[SHM_SIZE];

  // Create shared memory segment
  shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
  if (shmid == -1)
  {
    perror("shmget");
    exit(1);
  }

  // Attach shared memory segment
  shared_memory = (char *)shmat(shmid, NULL, 0);
  if (shared_memory == (char *)-1)
  {
    perror("shmat");
    exit(1);
  }

  // Fork a child process for communication
  pid_t pid = fork();

  if (pid == -1)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process: receiving input
    std::cout << "Child Process: Enter input (A to Z or 1 to 100): ";
    std::cin.getline(input, SHM_SIZE);

    // Copy input to shared memory
    strncpy(shared_memory, input, SHM_SIZE);

    // Detach shared memory segment
    if (shmdt(shared_memory) == -1)
    {
      perror("shmdt");
      exit(1);
    }
  }
  else
  {
    // Parent process: receiving input from child
    wait(NULL); // Wait for child to complete

    // Attach shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1)
    {
      perror("shmat");
      exit(1);
    }

    // Print received input
    std::cout << "Parent Process: Received input: " << shared_memory << std::endl;

    // Detach shared memory segment
    if (shmdt(shared_memory) == -1)
    {
      perror("shmdt");
      exit(1);
    }

    // Remove shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
      perror("shmctl");
      exit(1);
    }
  }

  return 0;
}
