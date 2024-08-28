#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "HWT906/hwt906.h"
#include "SSI/ssi.h"


float jiaodu[3];//存储Roll、Yaw、Pitch


int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //console初始化
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);


    gpio_ss_init();
    SSI0_Init();


	while(1){
	    HWT_Read_RPY(jiaodu);//读三轴角度

	    UARTprintf("%d,%d,%d\r\n",(int)jiaodu[0],(int)jiaodu[1],(int)jiaodu[2]);
	}
}




