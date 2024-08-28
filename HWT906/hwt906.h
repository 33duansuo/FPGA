#ifndef HWT906_HWT906_H_
#define HWT906_HWT906_H_


#include <stdint.h>



/*
地址       符号          含义                 访问级别
0x00       SAVE         保存当前配置          只写
0x01       CALSW        校准                  只写
0x02       RSW          回传数据内容          读写
0x03       RATE         回传数据速率          读写
0x04       BAUD         串口波特率            读写
0x05       AXOFFSET     X 轴加速度零偏        读写
0x06       AYOFFSET     Y 轴加速度零偏        读写
0x07       AZOFFSET     Z 轴加速度零偏        读写
0x08       GXOFFSET     X 轴角速度零偏        读写
0x09       GYOFFSET     Y 轴角速度零偏        读写
0x0a       GZOFFSET     Z 轴角速度零偏        读写
0x0b       HXOFFSET     X 轴磁场零偏          读写
0x0c       HYOFFSET     Y 轴磁场零偏          读写
0x0d       HZOFFSET     Z 轴磁场零偏          读写
0x1a       IICADDR      IIC 地址/MODBUS 地址  读写
0x30       YYMM         年、月                读写
0x31       DDHH         日、时                读写
0x32       MMSS         分、秒                读写
0x33       MS           毫秒                  读写
0x34       AX           X 轴加速度            只读
0x35       AY           Y 轴加速度            只读
0x36       AZ           Z 轴加速度            只读
0x37       GX           X 轴角速度            只读
0x38       GY           Y 轴角速度            只读
0x39       GZ           Z 轴角速度            只读
0x3a       HX           X 轴磁场              只读
0x3b       HY           Y 轴磁场              只读
0x3c       HZ           Z 轴磁场              只读
0x3d       Roll         X 轴角度              只读
0x3e       Pitch        Y 轴角度              只读
0x3f       Yaw          Z 轴角度              只读
*/
void HWT906_SPI_Transmit_Receive(uint8_t* tx,uint8_t* rx);
void HWT906_SPIReadBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]);
void HWT906_SPIWriteBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]);
void ShortToChar(short sData,unsigned char cData[]);
short CharToShort(unsigned char cData[]);
void WriteCS(uint8_t State);
void HWT_Read_A(float data[]);//读三轴加速度
void HWT_Read_G(float data[]);//读三轴角速度
void HWT_Read_H(float data[]);//读三轴磁场
void HWT_Read_RPY(float data[]);//读三轴角度




#endif /* HWT906_HWT906_H_ */
