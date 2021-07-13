/**********************************************************************
**File name:WindowsSocketClient.h
**Author:hexiao<hexiao.hrbeu.edu.cn>    Version:1.0    Date:2020.12.24
**Description:Windows socket class 
**GPL-3.0 License Usage
**********************************************************************/
#ifndef WINDOWS_SOCKET_CLIENT_H_
#define WINDOWS_SOCKET_CLIENT_H_

#include "../DataTransportLayer.h"

class WindowsSocketClient : public DataTransportLayer
{
public:
        WindowsSocketClient();
        ~WindowsSocketClient();

        virtual int init();
        virtual int read();
        virtual void write(const unsigned char *data,int length);
        int configure(char* addr, uint32_t port);
        unsigned long time();

        
private:
        unsigned int    socketClient;
        int             port;
        char            *addr;

};


#endif
