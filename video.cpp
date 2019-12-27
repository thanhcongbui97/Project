#include "opencv2/opencv.hpp"
#include <iostream>
#include <unistd.h> 
using namespace std;
using namespace cv;
 
void display(int second){
	VideoCapture cap("video.mp4");
   	Mat img;
	if(!cap.isOpened()){
		cout << "Error opening video stream or file" << endl;
	}   
	namedWindow("Streamming");
	int fps = cap.get(CAP_PROP_FPS);
	int frame_no = second*fps;
    cout << "Playing video at "<<fps<<" fps"<<" from frames "<<frame_no<<endl;
	while(1)
	{
	cap.set(CAP_PROP_POS_FRAMES, frame_no);
    
	cap >> img;
    // If the frame is empty, break immediately
    if (img.empty())
      break;
 
    // Display the resulting frame
    imshow( "Streamming", img );
	frame_no++;
    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
  
  // When everything done, release the video capture object
  cap.release();
 
  // Closes all the frames
  destroyAllWindows();
}
