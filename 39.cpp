#include <iostream>
#include <thread>
#include <semaphore.h>
#include <mutex>

using namespace std;

const int NUM_READERS = 3;
const int NUM_WRITERS = 2;

mutex mtx;
sem_t rw_mutex, sem_mutex;
int readers_count = 0;

void reader(int id)
{
  while (true)
  {
    sem_wait(&sem_mutex);
    readers_count++;
    if (readers_count == 1)
    {
      sem_wait(&rw_mutex);
    }
    sem_post(&sem_mutex);

    // Reading section
    cout << "Reader " << id << " is reading" << endl;

    sem_wait(&sem_mutex);
    readers_count--;
    if (readers_count == 0)
    {
      sem_post(&rw_mutex);
    }
    sem_post(&sem_mutex);

    // Simulate some delay
    this_thread::sleep_for(chrono::milliseconds(1000));
  }
}

void writer(int id)
{
  while (true)
  {
    sem_wait(&rw_mutex);

    // Writing section
    cout << "Writer " << id << " is writing" << endl;

    sem_post(&rw_mutex);

    // Simulate some delay
    this_thread::sleep_for(chrono::milliseconds(2000));
  }
}

int main()
{
  // Initialize semaphores
  sem_init(&rw_mutex, 0, 1);
  sem_init(&sem_mutex, 0, 1);

  // Create reader and writer threads
  thread readers[NUM_READERS], writers[NUM_WRITERS];

  for (int i = 0; i < NUM_READERS; ++i)
  {
    readers[i] = thread(reader, i + 1);
  }

  for (int i = 0; i < NUM_WRITERS; ++i)
  {
    writers[i] = thread(writer, i + 1);
  }

  // Join threads
  for (int i = 0; i < NUM_READERS; ++i)
  {
    readers[i].join();
  }

  for (int i = 0; i < NUM_WRITERS; ++i)
  {
    writers[i].join();
  }

  // Destroy semaphores
  sem_destroy(&rw_mutex);
  sem_destroy(&sem_mutex);

  return 0;
}
