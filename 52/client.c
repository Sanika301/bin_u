#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr;

  // Creating socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  memset(&servaddr, 0, sizeof(servaddr));

  // Filling server information
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int n;
  socklen_t len;

  printf("Enter message: ");
  fgets(buffer, sizeof(buffer), stdin);

  sendto(sockfd, (const char *)buffer, strlen(buffer),
         MSG_CONFIRM, (const struct sockaddr *)&servaddr,
         sizeof(servaddr));
  printf("Message sent.\n");

  n = recvfrom(sockfd, (char *)buffer, MAXLINE,
               MSG_WAITALL, (struct sockaddr *)&servaddr,
               &len);
  buffer[n] = '\0';
  printf("Server : %s\n", buffer);

  close(sockfd);
  return 0;
}
