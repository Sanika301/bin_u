#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct message
{
  long mtype;
  char mtext[100];
};

int main()
{
  key_t key = ftok(".", 'A'); // Generate a unique key for the message queue

  // Create a message queue
  int msqid = msgget(key, IPC_CREAT | 0666);
  if (msqid == -1)
  {
    perror("msgget");
    exit(1);
  }

  // Send message
  struct message msg_send;
  msg_send.mtype = 1; // Message type
  strcpy(msg_send.mtext, "Are you hearing me?");
  if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), 0) == -1)
  {
    perror("msgsnd");
    exit(1);
  }
  printf("Process 1: Sent message - %s\n", msg_send.mtext);

  // Receive reply
  struct message msg_recv;
  if (msgrcv(msqid, &msg_recv, sizeof(msg_recv.mtext), 2, 0) == -1)
  {
    perror("msgrcv");
    exit(1);
  }
  printf("Process 1: Received reply - %s\n", msg_recv.mtext);

  // Send acknowledgment
  strcpy(msg_send.mtext, "I can hear you too");
  if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), 0) == -1)
  {
    perror("msgsnd");
    exit(1);
  }
  printf("Process 1: Sent acknowledgment - %s\n", msg_send.mtext);

  // Clean up: Remove message queue
  if (msgctl(msqid, IPC_RMID, NULL) == -1)
  {
    perror("msgctl");
    exit(1);
  }

  return 0;
}
