#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

#define M_ADDR "226.1.1.1"
#define PORT 2612


struct in_addr localInterface;

struct sockaddr_in groupSock;

int sd;


int main(int argc, char *argv[])
{
    /* Create a datagram socket on which to send. */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)
    {
        perror("Opening datagram socket error");
        exit(1);
    }
    else
        printf("Opening the datagram socket...OK.\n");
    /* Initialize the group sockaddr structure with a */

    /* group address of 226.1.1.1 and port 2612. */

    memset((char *)&groupSock, 0, sizeof(groupSock));

    groupSock.sin_family = AF_INET;

    groupSock.sin_addr.s_addr = inet_addr(M_ADDR);

    groupSock.sin_port = htons(PORT);

    /* Disable loopback so you do not receive your own datagrams. */

    {

        char loopch = 0;

        if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)

        {

            perror("Setting IP_MULTICAST_LOOP error");

            close(sd);

            exit(1);
        }

        else

            printf("Disabling the loopback...OK.\n");
    }

    /* Set local interface for outbound multicast datagrams. */

    /* The IP address specified must be associated with a local, */

    /* multicast capable interface. */

    localInterface.s_addr = inet_addr("127.0.0.1");

    if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)

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
	while(i)
	{
		sprintf(c,"%d",i);
		if (sendto(sd,c, 4, 0, (struct sockaddr *)&groupSock, sizeof(groupSock)) < 0)
		{
			perror("Sending packet error");
		}
		cout<<"Sent"<<c<<endl;
		i++;
		sleep(1);
	}

// Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  //VideoCapture cap("a.mp4"); 

  // Check if camera opened successfully
/*  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
  }
	int imgSize = img.total() * img.elemSize();
	
    //Mat frame, imgGray;
  while(1){

    // Capture frame-by-frame
    cap >> img;
	cout <<" imgSize = "<< imgSize<<endl;
  //cap.read(frame);
        cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    // If the frame is empty, break immediately
    if (img.empty())
      break;

    // Display the resulting frame
   // imshow( "Frame", imgGray );
if (sendto(sd, imgGray.data, 307200, 0, (struct sockaddr *)&groupSock, sizeof(groupSock)) < 0)
		{
			cout<<"Sent failed"<<endl;
		}
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
  */ return 0;
}
/*void display()
{
	VideoCapture cap("a.mp4");
	Mat img, imgGray;
	img = Mat::zeros(480, 640, CV_8UC1);
	int imgSize = img.total() * img.elemSize();
	int bytes = 0;
	int key;
	//make img continuos
	if (!img.isContinuous())
	{
	    img = img.clone();
	    imgGray = img.clone();
	}
	while (1)
	{
	    cap >> img;
	    //do video processing here
	    cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	    //send processed image
//	cout << "data = "<<imgGray.data<<endl<<"size = " <<imgSize<< endl;
	if(img.empty())
		break;	
	imshow("SR",imgGray);
	    if (sendto(sd, imgGray.data, imgSize, 0, (struct sockaddr *)&groupSock, sizeof(groupSock)) < 0)
	    {
		cerr << "bytes = " << bytes << endl;
		//break;
	    }*/
/*	}	
}
*/
