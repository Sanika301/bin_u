#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <algorithm>

#define SHM_SIZE 1024   // Shared memory size
#define MAX_NUMBERS 100 // Maximum numbers that can be stored in shared memory

void bubbleSort(int arr[], int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // swap arr[j] and arr[j+1]
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main()
{
  int shmid;
  key_t key;
  int *shmarr;
  int numbers[MAX_NUMBERS];
  int num_count;

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
  shmarr = (int *)shmat(shmid, NULL, 0);
  if (shmarr == (int *)-1)
  {
    perror("shmat");
    exit(1);
  }

  // Create first child process (Input)
  pid_t pid1 = fork();

  if (pid1 < 0)
  {
    perror("fork");
    exit(1);
  }
  else if (pid1 == 0)
  { // Child process (Input)
    std::cout << "Enter the count of numbers: ";
    std::cin >> num_count;

    std::cout << "Enter " << num_count << " numbers: ";
    for (int i = 0; i < num_count; i++)
    {
      std::cin >> numbers[i];
    }

    // Write numbers to shared memory
    for (int i = 0; i < num_count; i++)
    {
      shmarr[i] = numbers[i];
    }

    // Mark end of numbers in shared memory
    shmarr[num_count] = 0;

    // Detach the shared memory segment
    shmdt(shmarr);
  }
  else
  {             // Parent process
    wait(NULL); // Wait for first child (Input) to finish

    // Create second child process (Sorting)
    pid_t pid2 = fork();

    if (pid2 < 0)
    {
      perror("fork");
      exit(1);
    }
    else if (pid2 == 0)
    { // Child process (Sorting)
      // Wait for the numbers to be written to shared memory
      sleep(1);

      // Read numbers from shared memory
      num_count = 0;
      while (shmarr[num_count] != 0)
      {
        numbers[num_count] = shmarr[num_count];
        num_count++;
      }

      // Sort the numbers
      bubbleSort(numbers, num_count);

      // Write sorted numbers back to shared memory
      for (int i = 0; i < num_count; i++)
      {
        shmarr[i] = numbers[i];
      }

      // Mark end of sorted numbers in shared memory
      shmarr[num_count] = 0;

      // Detach the shared memory segment
      shmdt(shmarr);
    }
    else
    {             // Parent process
      wait(NULL); // Wait for second child (Sorting) to finish

      // Create third child process (Display)
      pid_t pid3 = fork();

      if (pid3 < 0)
      {
        perror("fork");
        exit(1);
      }
      else if (pid3 == 0)
      { // Child process (Display)
        // Wait for the sorted numbers to be written to shared memory
        sleep(2);

        // Read and display numbers from shared memory
        std::cout << "Sorted numbers: ";
        for (int i = 0; shmarr[i] != 0; i++)
        {
          std::cout << shmarr[i] << " ";
        }
        std::cout << std::endl;

        // Detach the shared memory segment
        shmdt(shmarr);
      }
      else
      {             // Parent process
        wait(NULL); // Wait for third child (Display) to finish

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
          perror("shmctl");
          exit(1);
        }
      }
    }
  }

  return 0;
}
