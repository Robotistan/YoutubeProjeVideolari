


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>  //Kütüphaneleri tanımladık
#include "OneButton.h"

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);






const unsigned char PROGMEM ptica[] = {
0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x7A, 0x84, 0x7A, 0x84, 0x84, 0xA4, 0x84, 0x84, 0x82, 0x7C,
0x7E, 0x1F, 0x20, 0x1F, 0x18, 0x20, 0x07, 0xC0, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

};



  
const unsigned char PROGMEM star[] = {

0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x3F, 0xF0, 0x3C, 0x00, 0x3C, 0x00, 0xFF, 0x00, 0x7F, 0xFF,
0x7F, 0xFF, 0xFF, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x1F, 0xF0, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00

};


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");  //Lcd ekranın boyutunu tanımladık
#endif

OneButton button(A1, true);
int razmak=32;
float zidx[3];
int prazan[3];
void setup()   {
  
pinMode(8,INPUT_PULLUP);

for(int i=0;i<2;i++)
  {
    zidx[i]=64+((i+1)*razmak);
    {prazan[i]=random(4,20);}
    }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();


  display.clearDisplay();
  display.setFont();
  display.setTextSize(0);
  display.setTextColor(WHITE);
display.setCursor(0,0);
            display.print("danko");
          

 
 
  display.display();
    delay(500);
}
int score=0;
int pres=0;
float birdY=20;
int smjer=0;        //Oyundaki skor sayacını vb. tanımladık
int game=0;
int fx=12;
unsigned long trenutno=0;
void loop()
  {
     display.clearDisplay();

     if(game==0)
     {
      
         display.setCursor(2,2);
     display.print("flappy");
       display.setCursor(2,12);       // Ekranda yazılacak olan yazıyı ve konumunu tanımladık
     display.print("bird");
     display.drawBitmap(20,30,ptica,16,16,1);

          if(digitalRead(8)==0)
    {
    if(pres==0)
      {
        
        game=1;
        pres=1;
       }
    
    }else{pres=0;}
     
      }

     if(game==1)
     {
     display.setCursor(2,2);
     display.print(score);
    

     if(digitalRead(8)==0)
    {
    if(pres==0)
      {
        trenutno=millis();
        smjer=1;
        pres=1;
       }
    
    }else{pres=0;}


 if(smjer==0)
 birdY=birdY+0.5;   // Oyun başladığı zaman tuşa basıldığında kuşun hangi eksene ne kadar gideceğini tanımladık
 else
 birdY=birdY-1;

 if((trenutno+185)<millis())
  smjer=0;

    for(int j=0;j<2;j++){
    display.fillRect(zidx[j],0,6,47,1);
    
    display.fillRect(zidx[j],prazan[j],6,28,0); 
   
    }
    for(int j=0;j<2;j++)
    {
    zidx[j]=zidx[j]-0.5;
    if(zidx[j]<-7){
      score=score+1;
      
      
      
    prazan[j]=random(4,20);
     
    zidx[j]=64;}}

    

        display.drawBitmap(12, birdY,  ptica, 16, 16,1);
       display.drawRect(0,0,64,48,1);

       if(birdY>38 || birdY<-4  ){
game=0;
birdY=20;
score=0;
delay(1000);
for(int i=0;i<2;i++)
    {
    zidx[i]=64+((i+1)*razmak);
    {prazan[i]=random(4,20);}
    }
}

for(int m=0;m<4;m++)
if(zidx[m]<=fx+7 && fx+7<=zidx[m]+6)
{
  
 
  if(birdY<prazan[m] || birdY+8>prazan[m]+28){
  game=0;
birdY=20;
score=0;
delay(1000);
for(int i=0;i<2;i++)
    {
    zidx[i]=64+((i+1)*razmak);
    {prazan[i]=random(4,20);}
    }

     }}}
      display.display();
  }
