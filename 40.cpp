#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 256
#define KEY 1234

// Define message structure
struct Message
{
  long messageType;
  char messageText[MSG_SIZE];
};

int main()
{
  int msgid;
  Message message;

  // Create message queue
  msgid = msgget(KEY, IPC_CREAT | 0666);
  if (msgid == -1)
  {
    perror("msgget");
    exit(1);
  }

  // Fork a child process for communication
  pid_t pid = fork();

  if (pid == -1)
  {
    perror("fork");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process: receiving messages
    while (1)
    {
      // Receive message
      if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1)
      {
        perror("msgrcv");
        exit(1);
      }
      std::cout << "User 2: " << message.messageText << std::endl;

      // Check if the received message is "exit"
      if (strcmp(message.messageText, "exit") == 0)
      {
        break;
      }
    }
  }
  else
  {
    // Parent process: sending messages
    while (1)
    {
      std::cout << "User 1: ";
      // Prompt for user input
      std::cin.getline(message.messageText, MSG_SIZE);

      // Send message
      message.messageType = 1;
      if (msgsnd(msgid, &message, sizeof(message), 0) == -1)
      {
        perror("msgsnd");
        exit(1);
      }

      // Check if the sent message is "exit"
      if (strcmp(message.messageText, "exit") == 0)
      {
        break;
      }
    }
  }

  // Remove the message queue
  if (msgctl(msgid, IPC_RMID, NULL) == -1)
  {
    perror("msgctl");
    exit(1);
  }

  return 0;
}
