#include<bits/stdc++.h>
#include<sys/socket.h>
#include <arpa/inet.h>

int main()
{
 int b,sockfd,connfd,l,n,len;
 socklen_t sin_size;
 char operation;
 double op1,op2,result;
 double r,t,x;
 if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
  printf("socket created sucessfully\n");  //socket creation
 struct sockaddr_in servaddr;            
 struct sockaddr_in clientaddr;

 servaddr.sin_family=AF_INET;
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.46");
 servaddr.sin_port=8080;

 if((bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)))==0)
 printf("bind sucessful\n");   
 
 if((listen(sockfd,5))==0) //listen for connections on a socket
  printf("listen sucessful\n");
 
 sin_size = sizeof(struct sockaddr_in);
 if((connfd=accept(sockfd,(struct sockaddr *)&clientaddr,&sin_size))>0);
 printf("accept sucessful\n");
 char menu[] = ("Enter operation:\n +:Addition \n -: Subtraction \n /: Division \n*:Multiplication \n ");
 write(connfd, &menu,sizeof(menu));
 read(connfd, &operation,1);
 read(connfd,&op1,sizeof(op1));
 read(connfd,&op2,sizeof(op2));
 
 switch(operation)
 {
  case '+':
   result=op1 + op2;
    printf("Result is: %lf + %lf = %lf\n",op1, op2, result);
    break;
  case '-':
   result=op1 - op2;
          printf("Result is: %lf - %lf = %lf\n",op1, op2, result);
          break;
  case '*':
   result=op1 * op2;
          printf("Result is: %lf * %lf = %lf\n",op1, op2, result);
          break;
  case '/':
   result=op1 / op2;
          printf("Result is: %lf / %lf = %lf\n",op1, op2, result);
          break;
          
  default:
          printf("ERROR: Unsupported Operation");
     }
 write(connfd,&result,sizeof(result));  
 close(sockfd);

}
