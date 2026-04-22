#include<LPC21xx.h>
 #include"header.h"
 volatile char a[30],flag=0;
 int main()
 {
         int flag1=0;
         unsigned char h,m,s,date,month,year,day;
         i2c_init();
					
         uart0_init(9600);
         config_uart0();
         lcd_init();
         i2c_write(0xD0,0x2,0x11);
         i2c_write(0xD0,0x1,0x20);
         i2c_write(0xD0,0x0,(0x20&0x7f));
         i2c_write(0xD0,0x04,0x29);
         i2c_write(0xD0,0x05,0x11);
         i2c_write(0xD0,0x06,0x25);
         i2c_write(0xD0,0x03,0x07);
         while(1)
      {
                 h=i2c_read(0xD1,0x02);
                 m=i2c_read(0xD1,0x01);
                 s=i2c_read(0xD1,0x00);
                 date=i2c_read(0xD1,0x04);
                 month=i2c_read(0xD1,0x05);
                 year=i2c_read(0xD1,0x06);
                 day=i2c_read(0xD1,0x03);
		s&=0x7f;
 //              uart0_tx((h/16)+48);
 //uart0_tx((h%16)+48);
 //uart0_tx(':');
 //uart0_tx((m/16)+48);
 //uart0_tx((m%16)+48);
 //uart0_tx(':');
 //uart0_tx((s/16)+48);
 //uart0_tx((s%16)+48);
 //delay_ms(700);
 //uart0_tx_string("\r\n");
 //
 //if((h>>5)&1==0)
 //                      flag1=0;
 //              else
 //                      flag1=1;
 //              if(flag1==1)
 //                      uart0_tx_string("PM");
 //              else if(flag1==0)
 //                      uart0_tx_string("AM");
 //
 //              uart0_tx((date/16)+48);
 //              uart0_tx((date%16)+48);
 //              uart0_tx('/');
 //              uart0_tx((month/16)+48);
 //              uart0_tx((month%16)+48);
 //              uart0_tx('/');
 //              uart0_tx((year/16)+48);
 //              uart0_tx((year%16)+48);
 //
 //              if(day==1)
 //                      uart0_tx_string("SUN");
 //              else if(day==2)
 //                      uart0_tx_string("MON");
 //              else if(day==3)
 //              uart0_tx_string("TUE");
 //              else if(day==4)
 //                      uart0_tx_string("WED");
 //              else if(day==5)
 //                      uart0_tx_string("THU");
 //              else if(day==6)
 //                      uart0_tx_string("FRI");
 //              else if(day==7)
 //                      uart0_tx_string("SAT");
 //
 //                      delay_ms(500);
                  lcd_cmd(0x80);
                 lcd_data((h/16)+48);
                 lcd_data((h%16)+48);
                 lcd_data(':');
                 lcd_data((m/16)+48);
                 lcd_data((m%16)+48);
                 lcd_data(':');
                 lcd_data((s/16)+48);
                 lcd_data((s%16)+48);
                 if(((h>>5)&1)==0)
                        flag1=0;
                 else
                         flag1=1;
                 if(flag1==1)
                         lcd_string("PM");
                 else if(flag1==0)
                         lcd_string("AM");
                 lcd_cmd(0xc0);
                 lcd_data((date/16)+48);
                 lcd_data((date%16)+48);
                 lcd_data('/');
                 lcd_data((month/16)+48);
                 lcd_data((month%16)+48);
                 lcd_data('/');
                 lcd_data((year/16)+48);
                 lcd_data((year%16)+48);
                 lcd_cmd(0xcf-3);

                 if(day==1)
                         lcd_string("SUN");
                 else if(day==2)
                         lcd_string("MON");
                 else if(day==3)
                         lcd_string("TUE");
                 else if(day==4)
                         lcd_string("WED");
                 else if(day==5)
                         lcd_string("THU");
                 else if(day==6)
                         lcd_string("FRI");
                 else if(day==7)
                         lcd_string("SAT");
                 if(flag==1)
                 {
                         uart0_tx_string(a);
                         uart0_tx_string("\r\n");
			lcd_cmd(0x01);
		        lcd_cmd(0x80);
			lcd_string("Attendance saved");
			delay_ms(1000);
	                lcd_cmd(0x01);
                         flag=0;
                 }
         }
 }