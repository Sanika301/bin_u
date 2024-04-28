#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024 // Shared memory size

int main()
{
  int shmid;
  key_t key;
  char *shmaddr;
  char input[100];

  // Get a key for the shared memory
  key = ftok(".", 's');
  if (key == -1)
  {
    perror("ftok");
    exit(1);
  }

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

  // Create child process
  pid_t pid = fork();

  if (pid < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0)
  { // Child process (Sender)
    std::cout << "Enter input (A to Z or 1 to 100): ";
    std::cin.getline(input, sizeof(input));

    // Write input to shared memory
    sprintf(shmaddr, "%s", input);

    // Detach the shared memory segment
    shmdt(shmaddr);
  }
  else
  {             // Parent process (Receiver)
    wait(NULL); // Wait for child to finish writing to shared memory

    // Open file for writing
    std::ofstream file("output.txt");
    if (!file.is_open())
    {
      perror("ofstream");
      exit(1);
    }

    // Read from shared memory and write to file
    file << shmaddr;

    // Close file
    file.close();

    // Detach the shared memory segment
    shmdt(shmaddr);

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
      perror("shmctl");
      exit(1);
    }

    std::cout << "Data received and written to file 'output.txt'" << std::endl;
  }

  return 0;
}
