/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  基于OpenCV和Winsock的图像传输（发送）
//
//  By 彭曾 , at CUST, 2016.08.06
//
//  website: www.pengz0807.com  email: pengz0807@163.com
//
//M*/


#include "opencv2/opencv.hpp"
#include "WinsockMatTransmissionClient.h"  

using namespace cv;

int main()
{
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("192.168.2.100", 6666) < 0)
	{
		return 0;
	}

	//cv::VideoCapture capture(0);
	cv::Mat image;
	image=imread("lena.png");
	resize(image, image, Size(320, 240));

	while (1)
	{
		//if (!capture.isOpened())
		//	return 0;

		//capture >> image;

		if (image.empty())
			return 0;

		socketMat.transmit(image);
	}

	socketMat.socketDisconnect();
	return 0;
}