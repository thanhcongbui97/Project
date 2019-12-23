#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace std;
using namespace cv;
 
void display(VideoCapture cap, Mat img, Mat imgGray){
 
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  //VideoCapture cap("a.mp4"); 
    
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
  }
     
    //Mat frame, imgGray;
  while(1){
 
    // Capture frame-by-frame
    cap >> img;
  //cap.read(frame);
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    // If the frame is empty, break immediately
    if (img.empty())
      break;
 
    // Display the resulting frame
    imshow( "Frame", imgGray );
 
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
