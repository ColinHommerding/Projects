#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include "../include/protocol.h"
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h>

FILE *logfp;

ssize_t getLineFromFile(FILE *fp, char *line, size_t len) {   //getLineFromFile function used to get a line from a file
    memset(line, '\0', len);
    return getline(&line, &len, fp);
}

void parse(char* ln, int buffer[]){
    int size;
    if (ln[strlen(ln)-1]=='\n'){                //removes new line character from the end of non final lines in the file
            ln[strlen(ln)-1]='\0';
        }
        char *wrd = strtok(ln, " ");
        while (wrd !=NULL){                //Loops through each word in the lines and adds 1 to the corresponding count at that word's
            size = strlen(wrd);            //corresponding index in the histogram                                       
            buffer[size + 1]++;
            wrd = strtok(NULL, " ");
        }
}

void createLogFile(void) {   //function that creates the log file
    pid_t p = fork();
    if (p == 0)
        execl("/bin/rm", "rm", "-rf", "log", NULL);
    wait(NULL);
    mkdir("log", ACCESSPERMS);
    logfp = fopen("log/log_client.txt", "w");
}

int main(int argc, char *argv[]) {

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    

    int buffer[22];

    /* Hostname and port no. are passed as arguments */
    if (argc < 3) {
       fprintf(stderr,"CLIENT: usage %s hostname port\n", argv[0]);
       exit(0);
    }
    char folderName[256];
    strcpy(folderName, argv[1]); //set folderName to be equal to the folder containing the input files
    int numClients = atoi(argv[2]);  //set number of clients input parameter
    /* Get server's IP Address */
    server = gethostbyname(argv[3]);    //set the servers's ip address variable from the input
    portno = atoi(argv[4]);            //set he server's port number variable from the input

    createLogFile();    //create the log file


    pid_t pid1;
	for(int i=0; i<numClients; i++){      //Loops for numClients times and creates a new process each time using fork
    
		pid1 = fork();
		if (pid1<0){
		printf("Failure creating child process (error number: %d)\n", errno);      //Checks if fork() worked
		}
        if(pid1 == 0)   //check if the current process is a child process
        {

        bzero(buffer,22 * sizeof(int));

        //Create TCP socket 
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) 
            perror("CLIENT: ERROR opening socket");

         //Create server's address structure
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
        serv_addr.sin_port = htons(portno);

        //Connect to server
        fprintf(logfp, "[%d] open connection\n", i+1);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        {
        perror("CLIENT: ERROR connecting");
        }

        char filePath[256];
        sprintf(filePath, "/%d.txt", i+1); //create input file path
        strcat(folderName, filePath);
        char ln[256];
        FILE * fname = fopen(folderName, "r"); //open an input file

        if(fname == NULL) //check if this processes' input file exists
        {
            close(sockfd);
            fprintf(logfp, "[%d] close connection (successful execution)\n", i+1);
            break;
        }
        else{
        while(getLineFromFile(fname, ln, 256) > 0)   //loops through the lines in the file
            {
                parse(ln, buffer);  //parse each line and count words.
            }

            buffer[0] = 1;
            buffer[1] = 1 + i;
            n = write(sockfd,buffer,22 * sizeof(int)); //send UPDATE_WSTAT request
            fprintf(logfp,"[%d] UPDATE_WSTAT: 1\n", i+1);
            if (n < 0) 
                perror("ERROR writing to socket");

            bzero(buffer,22 * sizeof(int));
            n = read(sockfd,buffer,3 * sizeof(int));  //read the response from server
            if (n < 0) 
                perror("CLIENT: ERROR reading from socket");

            if(buffer[1] == 0)
            {
                fprintf(logfp, "[%d] close connection (failed execution)\n", i+1);
                close(sockfd);
            }
            else
            {
                fprintf(logfp, "[%d] close connection (successful execution)\n", i+1);
                close(sockfd);
                fprintf(logfp, "[%d] open connection\n", i+1);
                sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
            {
                perror("CLIENT: ERROR connecting");
            }
            bzero(buffer,22 * sizeof(int));
            buffer[0] = 2;
            buffer[1] = 1 + i;
            n = write(sockfd,buffer,22 * sizeof(int)); //send GET_MY_UPDATES request

            if (n < 0) 
                perror("ERROR writing to socket");

            bzero(buffer,22 * sizeof(int));
            n = read(sockfd,buffer,3 * sizeof(int)); //read the response from server
            fprintf(logfp,"[%d] GET_MY_UPDATES: %d %d\n", i+1, buffer[1], buffer[2]);

            if (n < 0) 
                perror("CLIENT: ERROR reading from socket");

            if(buffer[1] == 0)
            {
            fprintf(logfp, "[%d] close connection (failed execution)\n", i+1);
            close(sockfd); 
            }
            else 
            {
                fprintf(logfp, "[%d] close connection (successful execution)\n", i+1);
                close(sockfd);
                fprintf(logfp, "[%d] open connection\n", i+1);
                sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
                {
                perror("CLIENT: ERROR connecting");
                }
            bzero(buffer,22 * sizeof(int));
            buffer[0] = 3;
            buffer[1] = 1 + i;
            n = write(sockfd,buffer,22 * sizeof(int)); //send GET_ALL_UPDATES request

            if (n < 0) 
                perror("ERROR writing to socket");

            bzero(buffer,22 * sizeof(int));
            n = read(sockfd,buffer,3 * sizeof(int)); //read the response from server
            fprintf(logfp,"[%d] GET_ALL_UPDATES: %d %d\n", i+1, buffer[1], buffer[2]);

            if (n < 0) 
                perror("CLIENT: ERROR reading from socket");

            if(buffer[1] == 0)
            {
            fprintf(logfp, "[%d] close connection (failed execution)\n", i+1);
            close(sockfd); 
            }
            else
            {
                fprintf(logfp, "[%d] close connection (successful execution)\n", i+1);
                close(sockfd);
                fprintf(logfp, "[%d] open connection\n", i+1);
                sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
                {
                perror("CLIENT: ERROR connecting");
                }
            bzero(buffer,22 * sizeof(int));
            buffer[0] = 4;
            buffer[1] = 1 + i;
            n = write(sockfd,buffer,22 * sizeof(int));  //send GET_WSTAT request

            if (n < 0) {
                perror("ERROR writing to socket");
            }

            bzero(buffer,22 * sizeof(int));
            n = read(sockfd,buffer,22 * sizeof(int)); //read the response from server
            fprintf(logfp,"[%d] GET_WSTAT: %d", i+1, buffer[1]);
            for(int i = 0; i < 20; i++)
                {
                fprintf(logfp," %d", buffer[i+2]);
                }
            fprintf(logfp, "\n");

            if (n < 0) 
                perror("CLIENT: ERROR reading from socket");

            if(buffer[1] == 0)
            {
                fprintf(logfp, "[%d] close connection (failed execution)\n", i+1);
                close(sockfd);
            }
            else
            {
                fprintf(logfp, "[%d] close connection (successful execution)\n", i+1);
                close(sockfd);
                break;
                     }

                 }

                }
    
            }
         } 
    }
    
  }
     
        
   pid_t terminated_pid;  
    while((terminated_pid = wait(NULL)) > 0) {  //wait for child processes to terminate
      }


    fclose(logfp); //close log file

    return EXIT_SUCCESS;

}
