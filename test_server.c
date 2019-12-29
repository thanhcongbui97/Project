#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/addr.h"
#include <pthread.h>
struct in_addr localInterface ;

struct sockaddr_in groupSock, client_addr;

int sd, n;
int len = sizeof(client_addr);
char buffer[6];

int bufflen = sizeof(buffer);

void * receive(void * data)
{
	while(1)
	{
		if((n =recvfrom(sd, (char*)buffer, bufflen, MSG_WAITALL, (struct sockaddr*)&client_addr, (socklen_t*)&len)) > 0)
		{
			printf("Client joined\n");
		}
	}
}
int main (int argc, char *argv[ ])

{

/* Create a datagram socket on which to send. */

	pthread_t idthread;
sd = socket(AF_INET, SOCK_DGRAM, 0);

if(sd < 0)

{

  perror("Opening datagram socket error");

  exit(1);

}

else

  printf("Opening the datagram socket...OK.\n");

 

/* Initialize the group sockaddr structure with a */

/* group address of 225.1.1.1 and port 5555. */

memset((char *) &groupSock, 0, sizeof(groupSock));

groupSock.sin_family = AF_INET;

groupSock.sin_addr.s_addr = inet_addr(M_ADDR);

groupSock.sin_port = htons(PORT);

memset((char *) &client_addr, 0, sizeof(client_addr));
client_addr.sin_family = AF_INET;

client_addr.sin_addr.s_addr = inet_addr(C_ADDR);

client_addr.sin_port = htons(PORT);

/* Disable loopback so you do not receive your own datagrams.

{

char loopch = 0;

if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)

{

perror("Setting IP_MULTICAST_LOOP error");

close(sd);

exit(1);

}

else

printf("Disabling the loopback...OK.\n");

}

*/

 

/* Set local interface for outbound multicast datagrams. */

/* The IP address specified must be associated with a local, */

/* multicast capable interface. */

localInterface.s_addr = inet_addr(S_ADDR);

if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)

{

  perror("Setting local interface error");

  exit(1);

}

else

  printf("Setting the local interface...OK\n");

/* Send a message to the multicast group specified by the*/

/* groupSock sockaddr structure. */

/*int datalen = 1024;*/


    printf("Reading video frame...\n");
    printf("Streaming packet to Multicast Group ID: %s\n...\n",M_ADDR);
    int i = 1;
    char *c = (char*)malloc(sizeof(int));
	
	pthread_create(&idthread,NULL,&receive,NULL);
    while(i)
    {
        sprintf(c,"%d",i);
        if (sendto(sd,c, 4, 0, (struct sockaddr *)&groupSock, sizeof(groupSock)) < 0)
        {
            perror("Sending packet error");
        }
        printf("Sending packet %d\n",i);
        i++;
        sleep(1);
    }

/* Try the re-read from the socket if the loopback is not disable

if(read(sd, databuf, datalen) < 0)

{

perror("Reading datagram message error\n");

close(sd);

exit(1);

}

else

{

printf("Reading datagram message from client...OK\n");

printf("The message is: %s\n", databuf);

}

*/

return 0;

}
