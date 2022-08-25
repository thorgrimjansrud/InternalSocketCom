#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <errno.h>
#include <sys/un.h>  // sockaddr_in
//#include <netinet/in.h>  // sockaddr_un
#include <time.h>

#define SERV_PATH "a"

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, servlen;
    struct sockaddr_un serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_UNIX, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SERV_PATH);
    printf("\n The size of socket addr. is %lu\n", (unsigned long)sizeof(serv_addr));

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 1); // only 1 client connection

    printf("\n Server started \n");
 
    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);    // Socket in listening mode until accepted / connected (process sleeps)
    ticks = time(NULL);
    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
    write(connfd, sendBuff, strlen(sendBuff)); 
    close(connfd);
    unlink(SERV_PATH);
    printf("\n Server terminated \n\n");
    
}





