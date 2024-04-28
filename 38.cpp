#include <iostream>
#include <thread>
#include <semaphore.h>
#include <queue>

using namespace std;

const int MAX_BUFFER_SIZE = 5;

queue<int> buffer;
sem_t empty_sem, full, mutex;

void producer()
{
  for (int i = 0; i < 10; ++i)
  {
    sem_wait(&empty_sem);
    sem_wait(&mutex);

    buffer.push(i);
    cout << "Produced: " << i << endl;

    sem_post(&mutex);
    sem_post(&full);

    // Simulate some delay
    this_thread::sleep_for(chrono::milliseconds(500));
  }
}

void consumer()
{
  for (int i = 0; i < 10; ++i)
  {
    sem_wait(&full);
    sem_wait(&mutex);

    int val = buffer.front();
    buffer.pop();
    cout << "Consumed: " << val << endl;

    sem_post(&mutex);
    sem_post(&empty_sem);

    // Simulate some delay
    this_thread::sleep_for(chrono::milliseconds(1000));
  }
}

int main()
{
  // Initialize semaphores
  sem_init(&empty_sem, 0, MAX_BUFFER_SIZE);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);

  // Create producer and consumer threads
  thread prod(producer);
  thread cons(consumer);

  // Join threads
  prod.join();
  cons.join();

  // Destroy semaphores
  sem_destroy(&empty_sem);
  sem_destroy(&full);
  sem_destroy(&mutex);

  return 0;
}
