#ifndef *HEADER_H*
#define *HEADER_H*

#include <LPC21xx.h>

/*---------------- TYPE DEFINITIONS ----------------*/
typedef unsigned char u8;
typedef unsigned int  u32;

/*---------------- I2C FUNCTIONS ----------------*/
void i2c_init(void);
void i2c_write(u8 sa, u8 mr, u8 data);
u8   i2c_read(u8 sa, u8 mr);

/*---------------- UART FUNCTIONS ----------------*/
void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
void uart0_tx_string(char *p);
unsigned char uart0_rx(void);

/*---------------- UART INTERRUPT ----------------*/
void config_uart0(void);
void uart0_string(void) __irq;

/*---------------- LCD FUNCTIONS ----------------*/
void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_string(char *str);

/*---------------- DELAY ----------------*/
void delay_ms(unsigned int ms);

/*---------------- GLOBAL VARIABLES ----------------*/
extern char a[30];
extern volatile char flag;

#endif

