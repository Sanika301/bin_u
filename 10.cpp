#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>

using namespace std;

// Global flag to indicate whether alarm has occurred
volatile sig_atomic_t alarm_flag = 0;

// Signal handler for SIGALRM
void alarm_handler(int signal)
{
  alarm_flag = 1;
}

int main()
{
  // Install signal handler for SIGALRM
  signal(SIGALRM, alarm_handler);

  int input;

  // Set alarm for 5 seconds
  alarm(5);

  cout << "Enter a number within 5 seconds: ";
  cin >> input;

  // Cancel the alarm
  alarm(0);

  // Check if alarm occurred
  if (alarm_flag)
  {
    cout << "Time's up! You did not enter a number within 5 seconds." << endl;
  }
  else
  {
    cout << "You entered: " << input << endl;
  }

  return 0;
}
