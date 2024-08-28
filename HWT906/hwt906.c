#include <stdint.h>
#include <stdbool.h>
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"
#include "HWT906/hwt906.h"
#include "SSI/ssi.h"


#define   CS_Pin_Port     GPIO_PORTF_BASE   //定义片选端口号
#define   CS_Pin          GPIO_PIN_2        //定义片选引脚号



//@brief    单片机和HWT通信
//@param    uint8_t* tx,uint8_t* rx
//@return   void
void HWT906_SPI_Transmit_Receive(uint8_t* tx,uint8_t* rx){
    SSI0_send(*tx);
    *rx = SSI0_receive();

//    SSIDataPut(SSI0_BASE, *tx); //通过外设ssi0发送一个数据
//    while (SSIBusy(SSI0_BASE));
//    SSIDataGet(SSI0_BASE, rx);
//    while (SSIBusy(SSI0_BASE));
}


//@brief    单片机读HWT
//@param    uint8_t* tx,uint8_t* rx
//@return   void
void HWT906_SPIReadBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]){
    unsigned short usTemp;
    uint16_t i;
    gpio_ss_low();//拉低片选
    usTemp = usAddr|0x8000;
    i = 20;//CS 等待至少2us
    while(i--);
    uint8_t data= usTemp>>8;
    uint8_t rx;
    HWT906_SPI_Transmit_Receive(&data,&rx);
    data= usTemp&0xff;
    HWT906_SPI_Transmit_Receive(&data,&rx);
    uint8_t none = 0;
    for (i=0;i<ucLength;i++) {
        HWT906_SPI_Transmit_Receive(&none,ucData+i);
    }
    gpio_ss_high();//拉高片选
}


//@brief    short类型转char类型
//@param    short sData,unsigned char cData[]
//@return   void
void ShortToChar(short sData,unsigned char cData[]){
    cData[0]=sData&0xff;
    cData[1]=sData>>8;
}


//@brief    char类型转short类型
//@param    unsigned char cData[]
//@return   short
short CharToShort(unsigned char cData[]){
    return ((short)cData[1]<<8)|cData[0];
}


//@brief    写片选引脚高低电平
//@param    uint8_t State
//@return   void
//注：该函数不适用于TM4，因为TM4的拉高不是GPIOPinWrite(CS_Pin_Port, CS_Pin, 1);，该函数只用于STM32。在SSI中有两个函数代替这个函数的功能
void WriteCS(uint8_t State){
    GPIOPinWrite(CS_Pin_Port, CS_Pin, State);
}


//@brief    读加速度
//@param    float data[]
//@return   void
//从不同寄存器开始读罢了,要一下全读完的话就从0x34开始读,读24个,就全读完了,spi嘛 懂的都懂.全读就是太费时间了,5Mb/s下,完成一次全部读取需要210us,但不可能四种数据都要呀,所以分开来的话数据够用且省时间,只要60us
void HWT_Read_A(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x34,6,rx);
    data[0]= (float)CharToShort(&rx[0])/2048;
    data[1] = (float)CharToShort(&rx[2])/2048;
    data[2] = (float)CharToShort(&rx[4])/2048;
}


//@brief    读角速度
//@param    float data[]
//@return   void
void HWT_Read_G(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x37,6,rx);
    data[0]= (float)CharToShort(&rx[0])/32768*2000;
    data[1] = (float)CharToShort(&rx[2])/32768*2000;
    data[2] = (float)CharToShort(&rx[4])/32768*2000 ;
}


//@brief    读磁场
//@param    float data[]
//@return   void
void HWT_Read_H(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x3a,6,rx);
    data[0]= (float)CharToShort(&rx[0]);
    data[1] = (float)CharToShort(&rx[2]);
    data[2] = (float)CharToShort(&rx[4]);
}


//@brief    读Roll,Pitch,Yaw
//@param    float data[]
//@return   void
void HWT_Read_RPY(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x3d,6,rx);
    data[0]= (float)CharToShort(&rx[0])/32768*180;
    data[1] = (float)CharToShort(&rx[2])/32768*180;
    data[2] = (float)CharToShort(&rx[4])/32768*180;//结果存储在data数组中
}













