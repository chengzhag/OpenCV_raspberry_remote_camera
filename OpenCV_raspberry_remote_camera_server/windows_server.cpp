/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  基于OpenCV和Winsock的图像传输（接收）
//
//  By 彭曾 , at CUST, 2016.08.06
//
//  website: www.pengz0807.com  email: pengz0807@163.com
//
//M*/



#include <iostream>
#include "WinsockMatTransmissionServer.h"  

using namespace std;

int main()
{
	cout << "socket connecting..." << endl;
	WinsockMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		cout << "socket connecting error!" << endl;
		return 0;
	}
	cout << "socket connecting success!" << endl;

	cv::Mat image;
	while (1)
	{
		if (socketMat.receive(image) > 0)
		{
			cv::imshow("", image);
			cv::waitKey(1);
		}
	}

	socketMat.socketDisconnect();
	return 0;
}