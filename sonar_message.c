#include "sonar_message.h"

struct infom_sonar {
	uint8_t a;
	uint32_t len_hex;
	uint16_t len_bin;
	uint8_t b[3];
	uint8_t type;
};

unsigned char buf[1024];
char a[3] = { 1,2,3 };
int idx=0;
int zt = 0;
uint16_t len_b_s;

unsigned char* dhead(unsigned char a) {
	if (zt == 0) {
		if (a == 0X40) {
			buf[idx] = a;
			idx++;
			zt++;
		}	
	}
	else if (zt == 1) {
		buf[idx] = a;
		idx++;
		if (idx == 7) {
			len_b_s = *((uint16_t*)(buf + 5));
			if (len_b_s > 1024) {
				idx = 0;
				zt = 0;
				
			}
			else {
				//printf("_______%d\n", len_b_s);
				zt++;
			}
		}
	}
	else {
		//if (a == 0X40) {/*
		//	idx = 0;
		//	buf[idx] = a;
		//	idx = 1;
		//	zt = 1;
		//}
		//else {*/
			buf[idx] = a;
			idx++;
			if (idx == len_b_s + 6) {
				/*if (a == 0X0A) {*/
					idx = 0;
					zt = 0;
					printf("----------------------bao-SUCCESS!\n");
					return buf;
				//}
			}
		//}
	}
}

void loop()
{
	sonar_write(a, 3);
}



void msgCallBack(uint8_t* data, int len)
{
	
	for (int i = 0; i < len; i++)
	{
		printf("%.2x\40", data[i]);
		dhead(data[i]);
		
	}
		

		//printf("%.2x ", dhead(data[i]));
	//printf("---Len:%d\n", len);
}