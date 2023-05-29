#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <zconf.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "../include/protocol.h"
#include <netinet/in.h>
#include <netdb.h> 
#include <semaphore.h>

int resultHistogram[20];
int clientStatus[20];
sem_t sem;



void * checkMessage(void * newsockfd) //method that each thread uses to read requests and send responses
{
  int buffer[22];
  bzero(buffer,22 * sizeof(int));
  int fd = *(int *)newsockfd;
  int n = read(fd, buffer,22 * sizeof(int)); //read request from client
  if(buffer[1] < 0)  //error handling for a client having an invalid ID number
  {
    buffer[1] = 1;   
    n = write(fd,buffer, 22 * sizeof(int)); //send a response to client indicating a failed exectution because the client had an invalid ID number.
    sem_post(&sem);
    return NULL;
  }
  else
  {
    if (n < 0) 
      perror("SERVER: ERROR reading from socket");

  if (buffer[0] == UPDATE_WSTAT)   //check for UPDATE_WSTAT request
  {
    printf("[%d] UPDATE_WSTAT\n", buffer[1]);
    for(int i = 2; i < 22; i++)
    {
      resultHistogram[i-2] = buffer[i] + resultHistogram[i-2];
    }
    clientStatus[buffer[1]-1]++;
    buffer[2] = buffer[1];
    buffer[1] = 1;
    int send[3] = {buffer[0], buffer[1], buffer[2]};
    n = write(fd,send, 3 * sizeof(int));  //send response to UPDATE_STAT request
  }
  else if(buffer[0] == GET_MY_UPDATES) //check for GET_MY_UPDATES request
  {
    printf("[%d] GET_MY_UPDATES\n", buffer[1]);
    buffer[2] = clientStatus[buffer[1]-1];
    buffer[1] = 1;
    int send[3] = {buffer[0], buffer[1], buffer[2]};
    n = write(fd,send, 3 * sizeof(int)); //send response to GET_MY_UPDATES request
  }
  else if(buffer[0] == GET_ALL_UPDATES)  //check for GET_ALL_UPDATES request
  {
    printf("[%d] GET_ALL_UPDATES\n", buffer[1]);
    for(int i = 0; i < 20; i++)
    {
      buffer[2] = buffer[2] + clientStatus[i];
    }
    buffer[1] = 1;
    int send[3] = {buffer[0], buffer[1], buffer[2]};
    n = write(fd,send, 3 * sizeof(int)); //send response to GET_ALL_UPDATES request
  }
  else if(buffer[0] == GET_WSTAT)  //check for GET_WSTAT request
  {
    printf("[%d] GET_WSTAT\n", buffer[1]);
    for(int i = 0; i < 20; i++)
    {
      buffer[i + 2] = resultHistogram[i];
    }
    buffer[1] = 1;
    int send[22] = {buffer[0], buffer[1]};
    for(int i = 0; i < 20; i++)
    {
      send[i+2] = resultHistogram[i];
    }
    n = write(fd,send, 22 * sizeof(int)); //send response to GET_WSTAT request
  }
  else     //error handling for not giving a valid request code
  {
    buffer[1] = 1;   
    n = write(fd,buffer, 22 * sizeof(int)); //send a response to client indicating a failed exectution because a non valid request code was used
  }
  sem_post(&sem);
  return NULL;
  }

}


int main(int argc, char *argv[]) {

     int newsockfd;
     int sockfd, portno;
     socklen_t clilen;
    
     struct sockaddr_in serv_addr, cli_addr;
     
     sem_init(&sem,0,0);

     
     if (argc < 2) {
       fprintf(stderr,"SERVER: Usage: %s portno\n", argv[0]);
       exit(1);
     }

     //Create Socket of type TCP 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        perror("SERVER: ERROR opening socket");

     //Prepare Server address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);  //set port number from input parameter
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     //Bind the socket to server address and port */
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              perror("SERVER: ERROR on binding");

     // Convert socket to listening server socket
     listen(sockfd,5);
     printf("server is listening\n");

    
     pthread_t cTid[20];
     int count = 0;
     while(1)
     {
    
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //accept connection from client
    char *ip = inet_ntoa(cli_addr.sin_addr);
     printf("open connection from %s:%d\n", ip, ntohs(cli_addr.sin_port));
    
    int *fd= malloc(1);
	   *fd = newsockfd;
    int acception = pthread_create(&cTid[count], NULL, checkMessage, (void *) fd); //create new thread and have it call checkMessage to process a client request
    if (acception){
          printf("SERVER: ERROR on accept\n");
       }
    printf("close connection from %s:%d\n", ip, ntohs(cli_addr.sin_port));
    sem_wait(&sem);
    close(newsockfd);
       count ++;
    
    }
     
     // Close listening socket 
     close(sockfd);

    exit(EXIT_SUCCESS);
} 
