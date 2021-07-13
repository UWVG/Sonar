#include <string>
#include <stdio.h>
#include "ros.h"
#include <std_msgs/UInt8MultiArray.h>
#include <windows.h>

using std::string;
std_msgs::UInt8MultiArray send_str;
ros::NodeHandle nh;
ros::Publisher  pub("/sonar_message_receiver", &send_str);

extern "C" {
#include "sonar_message.h"
}

void stringCallBack(const std_msgs::UInt8MultiArray& msg)
{
	msgCallBack((uint8_t *)msg.data,msg.data_length);
}

void sonar_write(uint8_t* data, int len)
{
	send_str.data = (uint8_t *)data;
	send_str.data_length = len;
	pub.publish(&send_str);
}
int main(int argc, char* argv[])
{
	int a = 0;
	nh.getHardware()->configure((char*)"192.168.1.33", 11411);
	nh.initNode();
	printf("init\n");
	ros::Subscriber<std_msgs::UInt8MultiArray> sub("/sonar_message_sender", stringCallBack);
	nh.advertise(pub);
	nh.subscribe(sub);
	while (1)
	{
		loop();
		nh.spinOnce();
		Sleep(100);
	}
	return 0;
}


