/*
 * This is the module for the client.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#include "inet_client.h"

int main(argc, argv)
int argc;
char **argv;
{
  char c;
  FILE *fp;
  int i, j, client_sock, len, num_sets;
  struct hostent *hp;
  struct sockaddr_in client_sockaddr;
  struct linger opt;
  int sockarg;
  printf("inside client code\n");//delete

  if (argc < 2)
  {
    printf("Usage: inet_client <server hostname>\n");
    exit(-1);
  }
  printf("correct # of args\n");//delete

  if ((hp = gethostbyname(argv[1])) == NULL)
  {
    fprintf(stderr, "Error: %s unknown host.\n", argv[1]);
    exit(-1);
  }
  printf("Hostname correct\n");// delete

  if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("client: socket");
    exit(-1);
  }
  printf("Socket right\n");// delete

  client_sockaddr.sin_family = AF_INET;
  client_sockaddr.sin_port = htons(LOCAL_PORT);
  bcopy(hp->h_addr, &client_sockaddr.sin_addr, hp->h_length);
  printf("binding done\n"); //delete

  /* discard undelivered data on closed socket */ 
  opt.l_onoff = 1;
  opt.l_linger = 0;

  sockarg = 1;

  setsockopt(client_sock, SOL_SOCKET, SO_LINGER, (char*) &opt, sizeof(opt));

  setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sockarg, sizeof(int));
  printf("socket set\n");// delete

  while (connect(client_sock, (struct sockaddr*)&client_sockaddr,
     sizeof(client_sockaddr)) < 0) 
  {
    printf("Unable to connect to server... retrying in 5 seconds...\n");
    sleep(5);
  }
  printf("able to connect\n");//delete

  signal(SIGPIPE, broken_pipe_handler);
  printf("signal for broken pipe set"); // delete

  fp = fdopen(client_sock, "r");
  printf("open client_sock\n");//delete

  num_sets = 2;

  send(client_sock, (char *)&num_sets, sizeof(int), 0);
  printf("sent something\n");//delete
  
  for (j = 0; j < num_sets; j++)
  {      printf("in for loop to get server string\n");//delete
    
    /* Read the server string and print it out */
    while ((c = fgetc(fp)) != EOF)  //it blows up here!! it is not calling broken pipe handler after server closes
    {       printf("               in while loop to read server string\n");//delete
      if (c != '\n')
      {
        putchar(c);
      }
      
      else
      {
        break;
      }
    }

    /* Send test string and then lat and long to the server */
    for (i = 0; i < 2; i++)
    {
      send(client_sock, strs[i], strlen(strs[i]), 0);
      printf("Sent something else\n");
    }
    
  }

  printf("Done reading the server string");//delete
  /* Listen for drones and alert the server when one is heard 
  while (1) {

  }
  */

  close(client_sock);
  printf("close client socket");//delete

  exit(0);

}


void broken_pipe_handler()
{
  printf("\nbroken pipe signal received\n");
}
