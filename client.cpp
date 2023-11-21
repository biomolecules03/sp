#include<bits/stdc++.h>
#include<sys/socket.h>
#include <arpa/inet.h>

int main()
{
 int b,sockfd,sin_size,con,n,len;
 char operation;
 double op1,op2,result;
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
 printf("socket created sucessfully\n");  
  struct sockaddr_in servaddr;
 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.46");
 servaddr.sin_port=8080;
 sin_size = sizeof(struct sockaddr_in);
 if((con=connect(sockfd,(struct sockaddr *) &servaddr, sin_size))==0); //initiate a connection on a socket
  printf("connect sucessful\n");
  char input[5000];
  read(sockfd,&input,sizeof(input));
  printf("%s",input);
  scanf("%c",&operation);
  printf("Enter operands:\n");
 scanf("%lf %lf", &op1, &op2);
 write(sockfd,&operation,1);
 write(sockfd,&op1,sizeof(op1));
 write(sockfd,&op2,sizeof(op2));
 read(sockfd,&result,sizeof(result));
 printf("Operation result from server=%lf\n",result);
 close(sockfd);
}
