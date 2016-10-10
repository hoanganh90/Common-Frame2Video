#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    string filepath = "/home/anh/Desktop/LogAug/Aug25/5/SaveFrame/";
    string imagePath = filepath + "ImgROI%04d.jpg";
	VideoCapture cap(imagePath);
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR: Cannot open the video file" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	int fourcc = CV_FOURCC('P', 'I', 'M', '1');
	VideoWriter vout;
	cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
        string videoPath = filepath + "MyVideo.avi"; 
	VideoWriter oVideoWriter(videoPath, CV_FOURCC('P', 'I', 'M', '1'), 20,
			frameSize, true); //initialize the VideoWriter object


	if (!oVideoWriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video oVideoWriter" << endl;
		return -1;
	}
	/*if (!vout.isOpened()) {
	 cout << "ERROR: failed to write the video vout" << endl;
	 return -1;
	 }*/
	for (;;) {

		Mat frame;

		/*bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "ERROR: Cannot read a frame from video file" << endl;
			break;
		}*/
		cap >> frame;
		if (frame.empty()) {
			cout << "End of sequence" << endl;
			//system("exec rm -r /home/pi/NetBeansProjects/Bebop_Full_0821/SaveFrame/*");
			break;
		}
		oVideoWriter.write(frame); //writer the frame into the file

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}
