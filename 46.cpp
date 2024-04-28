#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void f1()
{
  // Critical section: function f1
  {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Enter username: ";
    std::string username;
    std::cin >> username;
    std::cout << "Username entered: " << username << std::endl;
    ready = true;
  }
  cv.notify_one();
}

void f2()
{
  // Wait until f1 has been executed
  {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []
            { return ready; });
  }

  // Critical section: function f2
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "Enter password: ";
  std::string password;
  std::cin >> password;
  std::cout << "Password entered: " << password << std::endl;
}

int main()
{
  std::thread t1(f1);
  std::thread t2(f2);

  t1.join();
  t2.join();

  return 0;
}
