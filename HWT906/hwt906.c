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


#define   CS_Pin_Port     GPIO_PORTF_BASE   //����Ƭѡ�˿ں�
#define   CS_Pin          GPIO_PIN_2        //����Ƭѡ���ź�



//@brief    ��Ƭ����HWTͨ��
//@param    uint8_t* tx,uint8_t* rx
//@return   void
void HWT906_SPI_Transmit_Receive(uint8_t* tx,uint8_t* rx){
    SSI0_send(*tx);
    *rx = SSI0_receive();

//    SSIDataPut(SSI0_BASE, *tx); //ͨ������ssi0����һ������
//    while (SSIBusy(SSI0_BASE));
//    SSIDataGet(SSI0_BASE, rx);
//    while (SSIBusy(SSI0_BASE));
}


//@brief    ��Ƭ����HWT
//@param    uint8_t* tx,uint8_t* rx
//@return   void
void HWT906_SPIReadBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]){
    unsigned short usTemp;
    uint16_t i;
    gpio_ss_low();//����Ƭѡ
    usTemp = usAddr|0x8000;
    i = 20;//CS �ȴ�����2us
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
    gpio_ss_high();//����Ƭѡ
}


//@brief    short����תchar����
//@param    short sData,unsigned char cData[]
//@return   void
void ShortToChar(short sData,unsigned char cData[]){
    cData[0]=sData&0xff;
    cData[1]=sData>>8;
}


//@brief    char����תshort����
//@param    unsigned char cData[]
//@return   short
short CharToShort(unsigned char cData[]){
    return ((short)cData[1]<<8)|cData[0];
}


//@brief    дƬѡ���Ÿߵ͵�ƽ
//@param    uint8_t State
//@return   void
//ע���ú�����������TM4����ΪTM4�����߲���GPIOPinWrite(CS_Pin_Port, CS_Pin, 1);���ú���ֻ����STM32����SSI������������������������Ĺ���
void WriteCS(uint8_t State){
    GPIOPinWrite(CS_Pin_Port, CS_Pin, State);
}


//@brief    �����ٶ�
//@param    float data[]
//@return   void
//�Ӳ�ͬ�Ĵ�����ʼ������,Ҫһ��ȫ����Ļ��ʹ�0x34��ʼ��,��24��,��ȫ������,spi�� ���Ķ���.ȫ������̫��ʱ����,5Mb/s��,���һ��ȫ����ȡ��Ҫ210us,���������������ݶ�Ҫѽ,���Էֿ����Ļ����ݹ�����ʡʱ��,ֻҪ60us
void HWT_Read_A(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x34,6,rx);
    data[0]= (float)CharToShort(&rx[0])/2048;
    data[1] = (float)CharToShort(&rx[2])/2048;
    data[2] = (float)CharToShort(&rx[4])/2048;
}


//@brief    �����ٶ�
//@param    float data[]
//@return   void
void HWT_Read_G(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x37,6,rx);
    data[0]= (float)CharToShort(&rx[0])/32768*2000;
    data[1] = (float)CharToShort(&rx[2])/32768*2000;
    data[2] = (float)CharToShort(&rx[4])/32768*2000 ;
}


//@brief    ���ų�
//@param    float data[]
//@return   void
void HWT_Read_H(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x3a,6,rx);
    data[0]= (float)CharToShort(&rx[0]);
    data[1] = (float)CharToShort(&rx[2]);
    data[2] = (float)CharToShort(&rx[4]);
}


//@brief    ��Roll,Pitch,Yaw
//@param    float data[]
//@return   void
void HWT_Read_RPY(float data[]){
    uint8_t rx[6];
    HWT906_SPIReadBytes(0x3d,6,rx);
    data[0]= (float)CharToShort(&rx[0])/32768*180;
    data[1] = (float)CharToShort(&rx[2])/32768*180;
    data[2] = (float)CharToShort(&rx[4])/32768*180;//����洢��data������
}













