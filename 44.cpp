#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024 // Shared memory size

int main()
{
  key_t key;
  int shmid;
  char *shmaddr;

  // Get a key for the shared memory
  key = ftok(".", 's');
  if (key == -1)
  {
    perror("ftok");
    exit(1);
  }

  // Create first child process (Create memory)
  pid_t pid1 = fork();

  if (pid1 < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid1 == 0)
  { // Child process (Create memory)
    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
      perror("shmget");
      exit(1);
    }

    std::cout << "Shared memory created" << std::endl;
  }
  else
  {             // Parent process
    wait(NULL); // Wait for first child (Create memory) to finish

    // Create second child process (Delete memory)
    pid_t pid2 = fork();

    if (pid2 < 0)
    {
      perror("fork");
      exit(1);
    }
    else if (pid2 == 0)
    { // Child process (Delete memory)
      // Get the existing shared memory segment
      shmid = shmget(key, SHM_SIZE, 0);
      if (shmid == -1)
      {
        perror("shmget");
        exit(1);
      }

      // Remove the shared memory segment
      if (shmctl(shmid, IPC_RMID, NULL) == -1)
      {
        perror("shmctl");
        exit(1);
      }

      std::cout << "Shared memory deleted" << std::endl;
    }
    else
    {             // Parent process
      wait(NULL); // Wait for second child (Delete memory) to finish

      // Create third child process (Attach/Detach memory)
      pid_t pid3 = fork();

      if (pid3 < 0)
      {
        perror("fork");
        exit(1);
      }
      else if (pid3 == 0)
      { // Child process (Attach/Detach memory)
        // Create a shared memory segment
        shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
        if (shmid == -1)
        {
          perror("shmget");
          exit(1);
        }

        // Attach the shared memory segment
        shmaddr = (char *)shmat(shmid, NULL, 0);
        if (shmaddr == (char *)-1)
        {
          perror("shmat");
          exit(1);
        }

        std::cout << "Shared memory attached" << std::endl;

        // Detach the shared memory segment
        if (shmdt(shmaddr) == -1)
        {
          perror("shmdt");
          exit(1);
        }

        std::cout << "Shared memory detached" << std::endl;
      }
      else
      {             // Parent process
        wait(NULL); // Wait for third child (Attach/Detach memory) to finish
      }
    }
  }

  return 0;
}
