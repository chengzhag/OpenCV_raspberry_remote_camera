#include <ctime>
#include <iostream>
#include <raspicam_cv.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "time.h"

#include "SocketMatTransmissionClient.h"  

using namespace cv;
using namespace std;
 
int main(int argc, char **argv)
{
	raspicam::RaspiCam_Cv cam;
	Mat image;
	cam.set(CV_CAP_PROP_FORMAT, CV_8UC3);
//	cam.set(CV_CAP_PROP_FRAME_WIDTH, cam.get(CV_CAP_PROP_FRAME_WIDTH) * 0.5);
//	cam.set(CV_CAP_PROP_FRAME_HEIGHT, cam.get(CV_CAP_PROP_FRAME_HEIGHT) * 0.5);
	cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	if (!cam.open())
		return 1;
	
	cout << "socket connecting..." << endl;
	SocketMatTransmissionClient socketMat;  
	if (socketMat.socketConnect("192.168.2.100", 6666) < 0)  
	{  
		cout << "socket connecting error!" << endl;
		return 0;  
	}  
	cout << "socket connecting success!" << endl;
    
//	const char szSourceWindow[] = "Camera";
//	namedWindow(szSourceWindow, WINDOW_AUTOSIZE);
	double startT, endT; 
	for (;;)
	{
		startT = clock();
		cam.grab();
		cam.retrieve(image);
		
		if (image.empty())  
			return 0;  
		
		socketMat.transmit(image);
		
		endT = clock();
		cout << (endT - startT) / CLOCKS_PER_SEC << endl;
	}
	socketMat.socketDisconnect();  
	cam.release();
}




