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


#define     NUM_SSI_DATA     1//定义数据发送和接收数据的个数（单位字节）


//@brief    SSIO初始化
//@param    void
//@return   void
void SSI0_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);//SSI0时钟使能
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);//GPIOA时钟使能
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);//PA2引脚配置成时钟线
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);//PA3引脚配置成片选线
    GPIOPinConfigure(GPIO_PA4_SSI0RX);//PA4引脚配置成RX
    GPIOPinConfigure(GPIO_PA5_SSI0TX);//PA5引脚配置成TX
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                   GPIO_PIN_2);//端口复用映射

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3,
                       SSI_MODE_MASTER, 1000000, 8);//配置SSI0，第三个参数表示使用SSI模式（TM4的SSI可以用作SSI或者SPI模式）
    //第四个参数表示TM4配置成主机模式，第五个参数表示时钟速率也可以理解成波特率也就是数据发送速度，最后一个参数表示数据发送位数
    SSIEnable(SSI0_BASE);//使能SSI
}


//@brief    SSI软件片选引脚初始化PF2
//@param    void
//@return   void
void gpio_ss_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
}


//@brief    SSI软件片选引脚拉高
//@param    void
//@return   void
void gpio_ss_high(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
}


//@brief    SSI软件片选引脚拉低
//@param    void
//@return   void
void gpio_ss_low(void){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
}


//@brief    SSI发送数据
//@param    uint32_t data
//@return   void
void SSI0_send(uint32_t data){
    uint32_t pui32DataTx[NUM_SSI_DATA];//发送的数据
    uint32_t ui32Index;//索引
    pui32DataTx[0] = data;

    for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++){//循环发送
        SSIDataPut(SSI0_BASE, pui32DataTx[ui32Index]);
    }
    while(SSIBusy(SSI0_BASE)){//等待发送完成
    }
}


//@brief    SSI接收数据
//@param    void
//@return   uint8_t
uint8_t SSI0_receive(void){
    uint32_t pui32DataRx[NUM_SSI_DATA];//接收的数据
    uint32_t ui32Index;//索引
    for(ui32Index = 0; ui32Index < NUM_SSI_DATA; ui32Index++){//循环接收
        SSIDataGet(SSI0_BASE, &pui32DataRx[ui32Index]);//接收数据
        pui32DataRx[ui32Index] &= 0x00FF;//pui32DataRx是uint32_t类型，因此按位与取低八位
    }
    return pui32DataRx[0];
}


