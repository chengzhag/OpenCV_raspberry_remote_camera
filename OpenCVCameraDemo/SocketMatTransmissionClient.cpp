/*M/////////////////////////////////////////////////////////////////////////////////////// 
// 
//  基于OpenCV和Socket的图像传输（发送） 
//   
//  By 彭曾 , at CUST, 2016.08.07  
// 
//  website: www.pengz0807.com  email: pengz0807@163.com  
//   
//M*/  
  
  
#include "SocketMatTransmissionClient.h"  
#include <iostream>

using namespace std;
using namespace cv;  

SocketMatTransmissionClient::SocketMatTransmissionClient(void)  
{  
}  
  
  
SocketMatTransmissionClient::~SocketMatTransmissionClient(void)  
{  
}  
  
  
int SocketMatTransmissionClient::socketConnect(const char* IP, int PORT)  
{  
	struct sockaddr_in    servaddr;  
  
	if ((sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0)   
	{  
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);  
		return -1;  
	}  
  
	memset(&servaddr, 0, sizeof(servaddr));  
	servaddr.sin_family = AF_INET;  
	servaddr.sin_port = htons(PORT);  
	if (inet_pton(AF_INET, IP, &servaddr.sin_addr) <= 0)   
	{  
		printf("inet_pton error for %s\n", IP);  
		return -1;  
	}  
  
	if (connect(sockClient, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)   
	{  
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);  
		return -1;  
	}  
	else   
	{  
		printf("connect successful!\n");  
	}  
}  
  
  
void SocketMatTransmissionClient::socketDisconnect(void)  
{  
	close(sockClient);  
}  
  
int SocketMatTransmissionClient::transmit(cv::Mat image)  
{  
	vector<int> compressionParams; 
	compressionParams.push_back(IMWRITE_JPEG_QUALITY);
	compressionParams.push_back(50);
//	compressionParams.push_back(IMWRITE_JPEG_OPTIMIZE);
//	compressionParams.push_back(1);
	imencode(".jpg",
		image,
		buf,
		compressionParams);
	uint64_t bufSize = buf.size();
	cout << buf.size() << endl;
	if (buf.data() == NULL)
	{
		printf("empty image\n\n");  
		return -1;  
	}
	if (send(sockClient, &bufSize, sizeof(bufSize), 0) < 0)
	{
		printf("send head error: %s(errno: %d)\n", strerror(errno), errno);  
		return -1;  
	}
	if (send(sockClient, buf.data(), bufSize, 0) < 0)  
	{  
		printf("send image error: %s(errno: %d)\n", strerror(errno), errno);  
		return -1;  
	}  
	return 1;
	
}  