/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  ����OpenCV��Winsock��ͼ���䣨���գ�
//
//  By ���� , at CUST, 2016.08.06
//
//  website: www.pengz0807.com  email: pengz0807@163.com
//
//M*/




#include "WinsockMatTransmissionServer.h"  

int main()
{
	WinsockMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		return 0;
	}

	cv::Mat image;
	while (1)
	{
		if (socketMat.receive(image) > 0)
		{
			cv::imshow("", image);
			cv::waitKey(30);
		}
	}

	socketMat.socketDisconnect();
	return 0;
}