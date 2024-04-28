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

  int hours, minutes;
  cout << "Enter the time for the alarm (HH MM): ";
  cin >> hours >> minutes;

  // Validate input
  if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59)
  {
    cerr << "Invalid time entered. Please enter a valid time (HH MM)." << endl;
    return 1;
  }

  // Convert hours and minutes to seconds
  int seconds = hours * 3600 + minutes * 60;

  // Set the alarm
  alarm(seconds);

  cout << "Alarm set for " << hours << ":" << minutes << endl;

  // Wait for the alarm to trigger
  while (!alarm_flag)
    ;

  cout << "Alarm! Time's up!" << endl;

  return 0;
}
