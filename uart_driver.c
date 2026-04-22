#include<lpc21xx.h>
extern char a[30];
extern volatile char flag;
void uart0_string(void) __irq{
	static int i;
	int v=U0IIR;
	v&=0x0E;
	if(v==4)
	{
		a[i]=U0RBR;
		U0THR=a[i];
		i++;
		if(a[i-1]==13)
		{
			a[i-1]='\0';
			i=0;
			flag=1;
		}
		VICVectAddr=0;
	}
}

void config_uart0(void)
{
	VICIntSelect=0;
	VICVectCntl1=6|(1<<5);
	VICVectAddr1=(unsigned int)uart0_string;
	VICIntEnable=1<<6;
	U0IER=1;
}