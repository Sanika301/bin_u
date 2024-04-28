#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
  int sockfd, newsockfd, n;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr, cliaddr;
  socklen_t clilen;

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

  // Accept connections and echo messages
  while (1)
  {
    if ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)) == -1)
    {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    // Read message from client
    n = read(newsockfd, buffer, MAXLINE);
    if (n < 0)
    {
      perror("read");
      exit(EXIT_FAILURE);
    }

    // Echo message back to client
    if (write(newsockfd, buffer, n) < 0)
    {
      perror("write");
      exit(EXIT_FAILURE);
    }

    close(newsockfd);
  }

  close(sockfd);
  return 0;
}
