/*
filename server_ipaddr portno

argv[0] fileame
argv[1] server_ipaddr
argv[2] portno
*/

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
void error(const char *msg)
{
      perror(msg);
      exit(1);
}
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
            fprintf(stderr,"Port Number Not Provided , Program terminated\n");
            exit(1);
    }
    int sockfd , newsockfd , portno , n;
    char buffer[255];
    struct sockaddr_in serv_addr , cli_addr;
    socklen_t clilen;
    struct hostent *server;
    portno = atol(argv[2]);
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
          error("Error opening Socket.");
    }
    server = gethostbyname(argv[1]);
    if(server == NULL )
    {
        fprintf(stderr,"Error , no such host");
    }
    bzero((char *) &serv_addr , sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,(char *) &serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);//Transformes host byts into network byts
    if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
      error("Connection failed");
    while(1)
    {
      bzero(buffer , 255);
      fgets(buffer , 255 ,stdin);
      n=write(sockfd,buffer,strlen(buffer));
      if(n<0)
        error("Error in write");
      bzero(buffer , 255);
      n=read(sockfd , buffer , 255);
      if(n<0)
        error("Error on reading");
      printf("Server %s",buffer);
      int i = strncmp("Bye" , buffer , 3);
      if(i == 0)
      break;
    
    }
    close(sockfd);
    return 0;
  }
 
