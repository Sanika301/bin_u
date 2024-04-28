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
  key_t key = ftok(".", 'A'); // Generate the same key for the message queue

  // Get the message queue ID
  int msqid = msgget(key, 0666);
  if (msqid == -1)
  {
    perror("msgget");
    exit(1);
  }

  // Receive message
  struct message msg_recv;
  if (msgrcv(msqid, &msg_recv, sizeof(msg_recv.mtext), 1, 0) == -1)
  {
    perror("msgrcv");
    exit(1);
  }
  printf("Process 2: Received message - %s\n", msg_recv.mtext);

  // Reply
  struct message msg_reply;
  msg_reply.mtype = 2; // Message type
  strcpy(msg_reply.mtext, "Loud and Clear");
  if (msgsnd(msqid, &msg_reply, sizeof(msg_reply.mtext), 0) == -1)
  {
    perror("msgsnd");
    exit(1);
  }
  printf("Process 2: Replied - %s\n", msg_reply.mtext);

  return 0;
}
