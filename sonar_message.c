#include "sonar_message.h"
char a[3] = { 1,2,3 };
void loop()
{
	sonar_write(a, 3);
}

void msgCallBack(uint8_t* data, int len)
{
	
	for (int i = 0; i < len; i++)
		printf("%.2x ", data[i]);
	printf("---Len:%d\n", len);
}