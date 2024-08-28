#ifndef SSI_SSI_H_
#define SSI_SSI_H_




void SSI0_Init(void);
void gpio_ss_init(void);
void gpio_ss_high(void);
void gpio_ss_low(void);
void SSI0_send(uint32_t data);
uint8_t SSI0_receive(void);



#endif
