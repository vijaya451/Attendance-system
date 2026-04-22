#include <LPC21xx.H>
#include "header.h"

void i2c_init(void){
	PINSEL0|=0x50;//P0.2-> SCL, P0.3->SDA
	I2CONSET=(1<<6);//I2EN=1
	I2SCLH=I2SCLL=75;// 100Kbps speed
}

/*byte write frame*/
#define SI ((I2CONSET>>3)&1)
void i2c_write(u8 sa, u8 mr, u8 data){
	/*step1: generate start condi*/
	I2CONSET=(1<<5);//STA=1 (generates start condi)
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);//wait for start condi to get generated
	I2CONCLR=(1<<5);//STA=0*
	
	/*step2: send sa+w & check ack*/
	I2DAT=sa;//send sa+w
	I2CONCLR=(1<<3);//clear SI 
	while(SI==0);
	if(I2STAT==0x20){
	 uart0_tx_string("Err:SA+W\r\n");
	 goto exit;
	}
	
	/*step3: send memory addr & check ack*/
	I2DAT=mr;//send mr addr
	I2CONCLR=(1<<3);//clear SI 
	while(SI==0);
	if(I2STAT==0x30){
	 uart0_tx_string("Err:Memory Addr\r\n");
	 goto exit;
	}

	/*step4: send data & check ack*/
	I2DAT=data;//send data
	I2CONCLR=(1<<3);//clear SI 
	while(SI==0);
	if(I2STAT==0x30){
	 uart0_tx_string("Err:data\r\n");
	 goto exit;
	}

	/*step5: generate stop condi*/
	exit:
	I2CONSET=(1<<4);//STO=1
	I2CONCLR=(1<<3);//clear SI flag
}

/*random read frame*/
u8 i2c_read(u8 sa, u8 mr){
	u8 temp=0;
	/*step1: generate start condi*/
	I2CONSET=(1<<5);//STA=1 (generates start condi)
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);//wait for start condi to get generated
	I2CONCLR=(1<<5);//STA=0*
	
	/*step2: send sa+w & check ack*/
	I2DAT=sa^1;//send sa+w
	I2CONCLR=(1<<3);//clear SI 
	while(SI==0);
	if(I2STAT==0x20){
	 uart0_tx_string("Err:SA+W\r\n");
	 goto exit;
	}
	
	/*step3: send memory addr & check ack*/
	I2DAT=mr;//send mr addr
	I2CONCLR=(1<<3);//clear SI 
	while(SI==0);
	if(I2STAT==0x30){
	 uart0_tx_string("Err:Memory Addr\r\n");
	 goto exit;
	}
	
	/*step4: regenerate start condi*/
	I2CONSET=(1<<5);//STA=1 (generates start condi)
	I2CONCLR=(1<<3);//clear SI flag
	while(SI==0);//wait for start condi to get generated
	I2CONCLR=(1<<5);//STA=0*
	
	/*step5: send sa+r & check ack*/
	I2DAT=sa;//send sa+r
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);
	if(I2STAT==0x48){
		uart0_tx_string("Err: SA+R\r\n");
		goto exit;
	}
	
	/*step6: read data & send noack*/
	I2CONCLR=(1<<3);//clear SI
	while(SI==0);//waiting for data to receive
	temp=I2DAT;
	
	/*step7: generate stop condi*/
	exit:
	I2CONSET=(1<<4);//STO=1
	I2CONCLR=(1<<3);//clear SI flag
	
	/*step8: return received data*/
	return temp;
}