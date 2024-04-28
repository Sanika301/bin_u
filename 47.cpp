#include <iostream>
#include <vector>
#include <omp.h>

bool isPrime(int n)
{
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (int i = 5; i * i <= n; i += 6)
  {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

std::vector<int> findPrimes(int start, int end)
{
  std::vector<int> primes;
#pragma omp parallel for
  for (int i = start; i <= end; ++i)
  {
    if (isPrime(i))
    {
#pragma omp critical
      primes.push_back(i);
    }
  }
  return primes;
}

int main()
{
  int start = 2, end = 100;
  std::vector<int> primes = findPrimes(start, end);
  std::cout << "Prime numbers between " << start << " and " << end << " are:" << std::endl;
  for (int prime : primes)
  {
    std::cout << prime << " ";
  }
  std::cout << std::endl;
  return 0;
}
