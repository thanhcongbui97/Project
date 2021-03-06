#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/addr.h"


void display( int second);

int str_to_int(char *s);

struct sockaddr_in client_addr, server_addr;
struct ip_mreq group;
int sd;
int bytes;
char databuf[6];

int main(int argc, char *argv[])
{
	/* Create a datagram socket on which to receive. */
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0)
	{

		perror("Opening datagram socket error");

		exit(1);

	}

	else

	printf("Opening datagram socket....OK.\n");

	 

	/* Enable SO_REUSEADDR to allow multiple instances of this */

	/* application to receive copies of the multicast datagrams. */

	{

	int reuse = 1;

	if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)

	{

	perror("Setting SO_REUSEADDR error");

	close(sd);

	exit(1);

	}

	else

	printf("Setting SO_REUSEADDR...OK.\n");

	}

	 

	/* Bind to the proper port number with the IP address */

	/* specified as INADDR_ANY. */

	memset((char *) &client_addr, 0, sizeof(client_addr));
	memset((char *) &server_addr, 0, sizeof(server_addr));

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(PORT);
	client_addr.sin_addr.s_addr = INADDR_ANY;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	

	if(bind(sd, (struct sockaddr*)&client_addr, sizeof(client_addr)))
	{
	perror("Binding datagram socket error");
	close(sd);
	exit(1);
	}
	else

	printf("Binding datagram socket...OK.\n");

	 

	/* Join the multicast group 226.1.1.1 on the local interface. Note that this IP_ADD_MEMBERSHIP option must be called for each local interface over which the multicast datagrams are to be received. */

	group.imr_multiaddr.s_addr = inet_addr(M_ADDR);

	group.imr_interface.s_addr = inet_addr(C_ADDR);

	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)

	{
	perror("Adding multicast group error");

	close(sd);

	exit(1);

	}

	else

	printf("Adding multicast group %s....\n", M_ADDR);
	printf("Waiting for the server...\n");

	/* Read from the socket. */

	if((bytes = read(sd, databuf, 6)) < 0)

	{

	perror("Reading datagram message error");

	close(sd);

	exit(1);

	}

	else

	{

	printf("Receving packet frame...OK.\n");
	databuf[bytes+1] = '\0';

	}

	int second = str_to_int(databuf);
	int len = sizeof(server_addr);
	sendto(sd, (const char*)databuf, strlen(databuf), MSG_CONFIRM, (sockaddr*)&server_addr, len);
	display(second);

	return 0;
}


	int str_to_int(char *s)
	{
		int i=0, ret = 0;
		while(s[i] != '\0')
		{
			ret*=10;
			ret+=(s[i] - '0');
			i++;
		}
		return ret;
	}

