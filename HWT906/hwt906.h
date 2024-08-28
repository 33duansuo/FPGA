#ifndef HWT906_HWT906_H_
#define HWT906_HWT906_H_


#include <stdint.h>



/*
��ַ       ����          ����                 ���ʼ���
0x00       SAVE         ���浱ǰ����          ֻд
0x01       CALSW        У׼                  ֻд
0x02       RSW          �ش���������          ��д
0x03       RATE         �ش���������          ��д
0x04       BAUD         ���ڲ�����            ��д
0x05       AXOFFSET     X ����ٶ���ƫ        ��д
0x06       AYOFFSET     Y ����ٶ���ƫ        ��д
0x07       AZOFFSET     Z ����ٶ���ƫ        ��д
0x08       GXOFFSET     X ����ٶ���ƫ        ��д
0x09       GYOFFSET     Y ����ٶ���ƫ        ��д
0x0a       GZOFFSET     Z ����ٶ���ƫ        ��д
0x0b       HXOFFSET     X ��ų���ƫ          ��д
0x0c       HYOFFSET     Y ��ų���ƫ          ��д
0x0d       HZOFFSET     Z ��ų���ƫ          ��д
0x1a       IICADDR      IIC ��ַ/MODBUS ��ַ  ��д
0x30       YYMM         �ꡢ��                ��д
0x31       DDHH         �ա�ʱ                ��д
0x32       MMSS         �֡���                ��д
0x33       MS           ����                  ��д
0x34       AX           X ����ٶ�            ֻ��
0x35       AY           Y ����ٶ�            ֻ��
0x36       AZ           Z ����ٶ�            ֻ��
0x37       GX           X ����ٶ�            ֻ��
0x38       GY           Y ����ٶ�            ֻ��
0x39       GZ           Z ����ٶ�            ֻ��
0x3a       HX           X ��ų�              ֻ��
0x3b       HY           Y ��ų�              ֻ��
0x3c       HZ           Z ��ų�              ֻ��
0x3d       Roll         X ��Ƕ�              ֻ��
0x3e       Pitch        Y ��Ƕ�              ֻ��
0x3f       Yaw          Z ��Ƕ�              ֻ��
*/
void HWT906_SPI_Transmit_Receive(uint8_t* tx,uint8_t* rx);
void HWT906_SPIReadBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]);
void HWT906_SPIWriteBytes(unsigned short usAddr,unsigned char ucLength,unsigned char ucData[]);
void ShortToChar(short sData,unsigned char cData[]);
short CharToShort(unsigned char cData[]);
void WriteCS(uint8_t State);
void HWT_Read_A(float data[]);//��������ٶ�
void HWT_Read_G(float data[]);//��������ٶ�
void HWT_Read_H(float data[]);//������ų�
void HWT_Read_RPY(float data[]);//������Ƕ�




#endif /* HWT906_HWT906_H_ */
