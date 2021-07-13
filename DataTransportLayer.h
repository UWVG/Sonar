/**********************************************************************
**File name:DataTransportLayer.h
**Author:hexiao<hexiao.hrbeu.edu.cn>    Version:1.0    Date:2020.12.24
**Description:Base class for data transport classes.
**GPL-3.0 License Usage
**********************************************************************/
#ifndef DATA_TRANSPORT_LAYER_H_
#define DATA_TRANSPORT_LAYER_H_

extern "C"{
    #include <stdint.h>
}

class DataTransportLayer
{
public:       
        DataTransportLayer(){};
        ~DataTransportLayer(){};
        /**
         * @brief init
         * @return 0 on success,other on fail
         */
        virtual int init() = 0;
        /**
         * @brief obtaining data by specific method
         * @return a string pointer
         */
        virtual int read() = 0;
        /**
         * @brief writing data by specific method
         * @param data refer to the data that is in need of transporting
         * @param length refer to the size of data by bytes
         */
        virtual void write(const unsigned char *,int) = 0;
};

#endif
