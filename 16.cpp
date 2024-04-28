#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

void *print_message(void *ptr)
{
  char *message = (char *)ptr;
  std::cout << message << std::endl;
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];
  char *messages[NUM_THREADS] = {
      "Hello from Thread 1!",
      "Greetings from Thread 2!",
      "Salutations from Thread 3!"};

  int i;
  for (i = 0; i < NUM_THREADS; i++)
  {
    int ret = pthread_create(&threads[i], NULL, print_message, (void *)messages[i]);
    if (ret)
    {
      std::cerr << "Error creating thread " << i << std::endl;
      return 1;
    }
  }

  pthread_exit(NULL);
}
