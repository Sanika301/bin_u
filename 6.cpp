// #include <unistd.h>

// int main()
// {
//   // Execute ls -l using execl
//   execl("/bin/ls", "ls", "-l", nullptr);
//   return 0;
// }

#include <unistd.h>

int main()
{
  // Execute ls -l using execv
  char *args[] = {(char *)"/bin/ls", (char *)"-l", nullptr};
  execv("/bin/ls", args);
  return 0;
}

// #include <unistd.h>

// int main()
// {
//   // Execute ls -l using execle with custom environment variable
//   char *env[] = {(char *)"PATH=/bin", nullptr};
//   execle("/bin/ls", "ls", "-l", nullptr, env);
//   return 0;
// }

// #include <unistd.h>

// int main()
// {
//   // Execute ls -l using execve with custom environment variable
//   char *args[] = {(char *)"/bin/ls", (char *)"-l", nullptr};
//   char *env[] = {(char *)"PATH=/bin", nullptr};
//   execve("/bin/ls", args, env);
//   return 0;
// }

// #include <unistd.h>

// int main()
// {
//   // Execute ls -l using execlp
//   execlp("ls", "ls", "-l", nullptr);
//   return 0;
// }

// #include <unistd.h>

// int main() {
//     // Execute ls -l using execvp
//     char *args[] = { (char*)"ls", (char*)"-l", nullptr };
//     execvp("ls", args);
//     return 0;
// }
