#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAXLINE 1024

// Function to handle client connections
void *handle_client(void *arg)
{
  int sockfd = *((int *)arg);
  char buffer[MAXLINE];
  int n;

  // Read message from client
  n = read(sockfd, buffer, MAXLINE);
  if (n < 0)
  {
    perror("read");
    close(sockfd);
    pthread_exit(NULL);
  }

  // Echo message back to client
  if (write(sockfd, buffer, n) < 0)
  {
    perror("write");
    close(sockfd);
    pthread_exit(NULL);
  }

  close(sockfd);
  pthread_exit(NULL);
}

int main()
{
  int sockfd, newsockfd, *new_sock;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t clilen;
  pthread_t thread_id;

  // Create a TCP socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // Initialize server address structure
  bzero((char *)&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(PORT);

  // Bind the socket to the server address
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  // Listen for connections on the socket
  if (listen(sockfd, 5) == -1)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  clilen = sizeof(cliaddr);

  // Accept connections and create a new thread to handle each client
  while (1)
  {
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)) == -1)
    {
      perror("accept");
      continue;
    }

    // Create a new thread to handle client
    new_sock = (int *)malloc(1);
    *new_sock = newsockfd;
    if (pthread_create(&thread_id, NULL, handle_client, (void *)new_sock) < 0)
    {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }

    // Detach the thread
    pthread_detach(thread_id);
  }

  close(sockfd);
  return 0;
}
