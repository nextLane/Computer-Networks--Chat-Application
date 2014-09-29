
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<math.h>
int main(int argc , char *argv[])
{
    int socket_dscp , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
     
    //Create socket
    socket_dscp = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_dscp == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );  
//port must vary from 1024 to 65535
     
    //Bind
    if( bind(socket_dscp,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_dscp , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_dscp, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
     
    //Receive a message from client
     int op1=0, op2=0;
     int cnt=0;    
     int ans= 0;
  char *cmm , *cm;
while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
    {
       cmm=client_message;

  op1=cmm[0]-'0';
  op2=cmm[2]-'0';     
  
  
    ans=op1+op2;
char buf[sizeof(int)*3+2];
snprintf(buf, sizeof buf, "%d", ans);
    
        //Send the message back to client
        write(client_sock , buf , 10);
   break;   
 }
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
   
     
    return 0;
}
