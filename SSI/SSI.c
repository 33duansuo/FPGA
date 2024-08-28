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
#include "SSI/ssi.h"


#define     NUM_SSI_DATA     1//�������ݷ��ͺͽ������ݵĸ�������λ�ֽڣ�


//@brief    SSIO��ʼ��
//@param    void
//@return   void
void SSI0_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);//SSI0ʱ��ʹ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//GPIOAʱ��ʹ��
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);//PA2�������ó�ʱ����
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);//PA3�������ó�Ƭѡ��
    GPIOPinConfigure(GPIO_PA4_SSI0RX);//PA4�������ó�RX
    GPIOPinConfigure(GPIO_PA5_SSI0TX);//PA5�������ó�TX
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                   GPIO_PIN_2);//�˿ڸ���ӳ��

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,
                       SSI_MODE_MASTER, 1000000, 8);//����SSI0��������������ʾʹ��SSIģʽ��TM4��SSI��������SSI����SPIģʽ��
    //���ĸ�������ʾTM4���ó�����ģʽ�������������ʾʱ������Ҳ�������ɲ�����Ҳ�������ݷ����ٶȣ����һ��������ʾ���ݷ���λ��
    SSIEnable(SSI0_BASE);//ʹ��SSI
}


//@brief    SSI���Ƭѡ���ų�ʼ��PF2
//@param    void
//@return   void
void gpio_ss_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
}


//@brief    SSI���Ƭѡ��������
//@param    void
//@return   void
void gpio_ss_high(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
}


//@brief    SSI���Ƭѡ��������
//@param    void
//@return   void
void gpio_ss_low(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
}


//@brief    SSI��������
//@param    uint32_t data
//@return   void
void SSI0_send(uint32_t data){
    uint32_t pui32DataTx[NUM_SSI_DATA];//���͵�����
    uint32_t ui32Index;//����
    pui32DataTx[0] = data;

    for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++){//ѭ������
        SSIDataPut(SSI0_BASE, pui32DataTx[ui32Index]);
    }
    while(SSIBusy(SSI0_BASE)){//�ȴ��������
    }
}


//@brief    SSI��������
//@param    void
//@return   uint8_t
uint8_t SSI0_receive(void){
    uint32_t pui32DataRx[NUM_SSI_DATA];//���յ�����
    uint32_t ui32Index;//����
    for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++){//ѭ������
        SSIDataGet(SSI0_BASE, &pui32DataRx[ui32Index]);//��������
        pui32DataRx[ui32Index] &= 0x00FF;//pui32DataRx��uint32_t���ͣ���˰�λ��ȡ�Ͱ�λ
    }
    return pui32DataRx[0];
}


