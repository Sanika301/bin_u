#include <iostream>
#include <omp.h>

int main()
{
  int total_threads = 0;
#pragma omp parallel
  {
#pragma omp master
    {
      total_threads = omp_get_num_threads();
      std::cout << "Total number of threads: " << total_threads << std::endl;
    }

    int thread_num = omp_get_thread_num();
    std::cout << "Thread " << thread_num << " reporting." << std::endl;
  }

  return 0;
}
