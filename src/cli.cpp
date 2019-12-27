#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include "opencv2/opencv.hpp"
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace cv;

#define M_ADDR "226.1.1.1"
#define SRV_PORT 2612
#define CLI_PORT 1997
void display(VideoCapture cap, Mat img, Mat imgGray, int second);

int str_to_int(char *s);

int main(int argc, char *argv[])

{
	struct sockaddr_in cli_localAddr;
	struct sockaddr_in srv_localAddr;
	struct ip_mreq groupSock;
	int sd, second;
	VideoCapture cap("small.mp4");
	Mat img, imgGray;
	int bytes;
	char databuf[6];

    /* Create a datagram socket on which to receive. */

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sd < 0)

    {

        perror("Opening datagram socket error");

        exit(1);
    }

    else

        printf("Opening datagram socket....OK.\n");

    /* Enable SO_REUSEADDR to allow multiple instances of this  application to receive copies of the multicast datagrams. */

    {

        int reuse = 1;

        if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)

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

    memset((char *)&cli_localAddr, 0, sizeof(cli_localAddr));

    cli_localAddr.sin_family = AF_INET;

    cli_localAddr.sin_port = htons(SRV_PORT);

    cli_localAddr.sin_addr.s_addr = INADDR_ANY;
	
    memset((char *)&srv_localAddr, 0, sizeof(srv_localAddr));
    srv_localAddr.sin_family = AF_INET;

    srv_localAddr.sin_port = htons(SRV_PORT);

    srv_localAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sd, (struct sockaddr *)&cli_localAddr, sizeof(cli_localAddr)))

    {
        perror("Binding datagram socket error");
        close(sd);
        exit(1);
    }
    else
        printf("Binding datagram socket...OK.\n");

    /* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */

    /* interface. Note that this IP_ADD_MEMBERSHIP option must be */

    /* called for each local interface over which the multicast */

    /* datagrams are to be received. */

    groupSock.imr_multiaddr.s_addr = inet_addr(M_ADDR);

    groupSock.imr_interface.s_addr = inet_addr("10.72.63.197");

    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&groupSock, sizeof(groupSock)) < 0){

        perror("Adding multicast group error");

        close(sd);

        exit(1);
    }

    else

        printf("Adding multicast group...OK.\n");

    /* Read from the socket. */

		if((bytes = read(sd, databuf, 6)) < 0)
		{	
		    perror("Reading datagram message error");
			close(sd);
		    exit(1);
		}
		else
		{
			printf("Reading datagram packet...OK.\n");
			databuf[bytes+1] = '\0';
		}
		second = str_to_int(databuf);
		display(cap, img , imgGray, second);
//	}
/*Open CV 
    Mat img;
    img = Mat::zeros(480 , 640, CV_8UC1);
    int imgSize = img.total() * img.elemSize();
    uchar *iptr = img.data;
    int bytes = 0;
    int key;

    //make img continuos
    if ( ! img.isContinuous() ) {
          img = img.clone();
    }

    std::cout << "Image Size:" << imgSize << std::endl;


 	 namedWindow("TV",1);

	len = (socklen_t)sizeof(srv_localAddr);
    while(key != 'q') 
	{

      //  if ((bytes = recvfrom(sd, iptr, imgSize , 0, (struct sockaddr *)&srv_localAddr, &len) < 0)) {
	if((bytes = read(sd, iptr, imgSize)) == -1 )
	{        
    	std::cerr << "recv failed, received bytes = " << bytes << std::endl;
	break;
        }
	cout << "imgSize = " << bytes << endl;
        imshow("TV", img);

        // Press  ESC on keyboard to exit
            char c = (char)waitKey(25);
            if (c == 27)
                break;
        }


        // Closes all the frames
        destroyAllWindows();

    close(sd); */ 
	    
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
