

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>      //Kütüphaneyi tanımladık
#include <Fonts/FreeSans9pt7b.h>    
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans12pt7b.h>


// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);



const unsigned char PROGMEM icon [] = {
0x00, 0x1F, 0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x1F, 0xF8, 0x00,
0x00, 0x1F, 0xF8, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0xE0,
0x00, 0x1F, 0xF8, 0xF0, 0x00, 0x7F, 0xFE, 0x70, 0x00, 0xFF, 0xFF, 0x20, 0x01, 0xF0, 0x0F, 0x80,
0x03, 0xC1, 0x83, 0xC0, 0x03, 0x81, 0x81, 0xC0, 0x07, 0x01, 0x80, 0xE0, 0x07, 0x01, 0x80, 0xE0,
0x0E, 0x01, 0x80, 0x70, 0x0E, 0x01, 0x80, 0x70, 0x0E, 0x03, 0xC0, 0x70, 0x0E, 0x03, 0xC0, 0x70,
0x0E, 0x03, 0xC0, 0x70, 0x0E, 0x01, 0x80, 0x70, 0x0E, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0xE0,
0x07, 0x00, 0x00, 0xE0, 0x07, 0x80, 0x01, 0xE0, 0x03, 0xC0, 0x03, 0xC0, 0x01, 0xE0, 0x07, 0x80,
0x00, 0xF8, 0x1F, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x07, 0xE0, 0x00

};

const unsigned char PROGMEM mali [] = {
0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x00, 0x08, 0x07, 0xEC, 0x0E, 0x70, 0x18, 0x18, 0x30, 0x0C,
0x30, 0x8C, 0x21, 0x84, 0x21, 0x84, 0x30, 0x0C, 0x10, 0x08, 0x18, 0x18, 0x0F, 0xF0, 0x03, 0xC0
};




#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");   //oled ekranın büyüklüğünü ayarladık
#endif




void setup()   {
  pinMode(8,INPUT_PULLUP);                                    // oled ekranın pinlerini tanımladık
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display();


  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);                            // oled ekranın fontunu tanımladık
  
  display.setTextColor(WHITE);   // Yazı renklerini tanımladık
  display.setCursor(0,0);
  display.print("danko");
    display.display();
    delay(800);
}
int poz=1;
int broj=1;
int kretanjeY=30;

int sec1=0;
int min1=0;
unsigned long msec=0;
unsigned long mili=0;      // Saniyeyi dakikayı saati tanımladık ve başlama sürelerini belirttik
int pres=0;
int fase=0;
int start=0;
unsigned long tim=0;
void loop()
  {
      display.clearDisplay();
      if(digitalRead(8)==0)
      {
        if(pres==0)
           {
            fase=fase+1;
            pres=1;
            if(fase>2)
            fase=0;
            }
        
        }else{pres=0;}

     if(fase==0)
      {
        display.setFont();
      display.setCursor(10,0);
      display.print("press..");
      display.drawBitmap(14, 12,  icon, 32, 32, 1);

      sec1=0;
      min1=0;
      tim=0;
      mili=0;
      msec=0;
      start=0;
      }

      if(fase==1)
      {
        display.clearDisplay();
        display.setFont();
        display.setCursor(2,0);          // Ekranda gözüken yazıyı belirttik
        display.print("stopwatch");
        display.setFont(&FreeSans9pt7b);
        
        if(start==0)
          {
            start=1;
            tim=millis();  
          }
       msec=(millis()-tim); 

        
      
        min1=msec/60000;
     
       
        if((msec/1000)>59)                        // 60 saniyenin 1 dakika olduğunu vb. tanıttık
           {
            sec1=(msec/1000)-(min1*60);
            }else{
              sec1=msec/1000;
              }

          mili=(msec%1000)/10;
      
           display.setCursor(0,24);
           if(min1<=9)
           {
            display.print("0");
            display.print(min1);
            }else {display.print(min1);}

            display.print(":");

             if(sec1<=9)
           {
            display.print("0");
            display.print(sec1);
            }else {display.print(sec1);}
            display.setFont(&FreeSans12pt7b);
            display.setCursor(0,47);

                  if(mili<=9)
           {
            display.print("0");
            display.print(mili);
            }else {display.print(mili);}


           

    
       }

if(fase==2)
{
     display.clearDisplay();
        display.setFont();
        display.setCursor(0,0);
        display.print("time:");
        display.setFont(&FreeSans9pt7b);
        display.setCursor(0,24);
           if(min1<=9)
           {
            display.print("0");
            display.print(min1);
            }else {display.print(min1);}

            display.print(":");

             if(sec1<=9)
           {
            display.print("0");
            display.print(sec1);
            }else {display.print(sec1);}
            display.setFont(&FreeSans12pt7b);
            display.setCursor(0,47);

                  if(mili<=9)
           {
            display.print("0");
            display.print(mili);
            }else {display.print(mili);}
             display.drawBitmap(36, 31,  mali, 16, 16, 1);

  
  }
      
      
      display.display();
  }
