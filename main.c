#include <16f877a.h>
#FUSES XT,protect                         //Crystal osc <= 4mhz

#use delay(clock=4000000)

#include <ds1307.c>

  
//#use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7)

#byte TRISA=0x85
#byte PORTA=0x05
#byte TRISB=0x86
#byte PORTB=0x06
#byte TRISE=0x89
#byte PORTE=0x09
#BYTE TRISD=0X88
#BYTE PORTD=0x08
#BYTE PORTC=0X07
#BYTE TRISC=0X87
#bit led=0x08.4
#bit relay=0x08.0
#bit toggle_sw=0x06.5
#bit mode_SW1=0X06.6
#bit mode_SW2=0X06.7
#bit setswitch=0x06.0
#bit gie=0x0b.7
#bit peie=0x0b.6
#bit inte=0x0b.4
#bit intf=0x0b.1
#bit integ=0x81.6

int8 shh=18,smm=30,ehh=21,emm=30;

int validateTime(int chh, int cmm)
{

  if(((chh>=shh) && ((((chh)*60)+cmm)>=(((shh)*60)+smm))) && ((chh<=ehh) && ((((chh)*60)+(cmm+1))<=(((ehh)*60)+emm))))

    return 1;
    else 
    return 0;
}


void main()
{
   int8 hr=0,min=0,sec=0;
   TRISA=0x00;
   TRISB=0x00;
   TRISC=0x00;
   TRISD=0x00;
   TRISE=0x00;
   
   PORTA=0x00;
   PORTB=0xf1;
   PORTC=0x00;
   PORTD=0x00;
   PORTE=0x00;
   
 
   ds1307_init();
//!   ds1307_set_time(17,47,0); // reset the rtc value to 6:00 pm
   delay_ms(100);

   while(true)
   {
      ds1307_get_time(hr,min,sec);
      delay_ms(10);

      if((mode_SW1==1) && (mode_SW2==1))
      {
         delay_ms(200);
         if(toggle_sw==0)
               {
                  led=~led;
                  delay_ms(500);         
                  relay=~relay;
                  delay_ms(500);
               }
         delay_ms(200);
          
         if((setswitch==0) && (toggle_sw==0))
               {
                  ds1307_set_time(18,0,0); // reset the rtc value to 6:00 pm
                  delay_ms(20);
               }         
      }
      if(mode_SW1==0)// 6 PM to 10PM
      {
         if(hr<=17)
         {
            relay=0;
            led=0;
         }
         
        if(hr>=18)
        {
            relay=1;
            led=1;
        }
       
       if(hr>=19 && hr<=21)
        {
            relay=1;
            led=1;
        }
          
       if(hr>=23)
        {
            relay=0;
            led=0;
        }
       if(hr<18)
        {
            relay=0;
            led=0;
        }
     }
      
     if(mode_SW2==0)     //6.30PM to 9.30PM
     { 
          
          if(hr>=18 && min<=29)
           {
               relay=0;
               led=0;
           }
          if(hr>=18 && min>=30)
           {
               relay=1;
               led=1;
           }
          if(hr>=19 && hr<=21)
           {
               relay=1;
               led=1;
           }
          if(hr==21 && min<=29 )
            {
               relay=1;
               led=1;
            }
            if(hr>=21 && min>=20 )
            {
               relay=0;
               led=0;
            }
           if(hr>=22)
           {
               relay=0;
               led=0;
           }
           if(hr<18)
           {
               relay=0;
               led=0;
           }
        
      }    
   }
}
//working
            
        

