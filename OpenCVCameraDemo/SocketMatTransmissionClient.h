/*M/////////////////////////////////////////////////////////////////////////////////////// 
// 
//  ����OpenCV��Socket��ͼ���䣨���ͣ� 
//   
//  By ���� , at CUST, 2016.08.07 
// 
//  website: www.pengz0807.com  email: pengz0807@163.com  
//   
//M*/  
  
#ifndef __SOCKETMATTRANSMISSIONCLIENT_H__  
#define __SOCKETMATTRANSMISSIONCLIENT_H__  
  
#include "opencv2/opencv.hpp"  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <vector>  
  

class SocketMatTransmissionClient  
{  
	std::vector<uchar> buf;
public:  
	SocketMatTransmissionClient(void);  
	~SocketMatTransmissionClient(void);  
  
private:  
	int sockClient;  
  
public:  
  
    // ��socket����  
    // params : IP      ��������ip��ַ  
    //          PORT    ����˿�  
    // return : -1      ����ʧ��  
    //          1       ���ӳɹ�  
	int socketConnect(const char* IP, int PORT);  
  
  
    // ����ͼ��  
    // params : image ������ͼ��  
    // return : -1      ����ʧ��  
    //          1       ����ɹ�  
	int transmit(cv::Mat image);  
  
  
    // �Ͽ�socket����  
	void socketDisconnect(void);  
};  
  
#endif  