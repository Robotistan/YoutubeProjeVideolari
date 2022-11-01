#include <LiquidCrystal_PCF8574.h>  // kütüphane Tamamalandı
LiquidCrystal_PCF8574 lcd(0x27);
 
#define para A0      
#define relay 12




int saniye = 0;          // Lcd ekranda süremizi belirtme komutu
int dakika = 10;
int saat = 0;
int basla = 0;
String displayText = "Para atiniz";

void setup()
{
  lcd.begin(16, 2); 
  lcd.setBacklight(HIGH);       
  fnkFormat();
  pinMode(para,INPUT);
  pinMode(relay,OUTPUT);
} 
void fnkFormat()
{
    char timeString[80];
    sprintf(timeString, "%02d:%02d:%02d", saat, dakika, saniye);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(timeString);
    lcd.setCursor(0, 1);
    lcd.print(displayText);
   
    
}
void loop(){
  if(saniye == 0 && dakika == 0 && saat == 0)
  {
    displayText = "süre bitti";
  }
  if(basla==0)
  {
    if(analogRead(para) < 300) 
    {
      digitalWrite(relay,HIGH);
      displayText = "sarj oluyor...";
      basla = 1;
      delay(50);
    }
    
  }
  if(basla==1)    
  {
      lcd.clear();
      fnkFormat();
        if(saniye == 0)
        {
          if(dakika == 0)
          {
            if(saat == 0)
            {
              digitalWrite(relay,LOW);
            }
            else
            {
              saat = saat - 1;
              dakika=59;         // Dakika ve saniye kodları
              saniye=59;
            }
          }
          else
          {
            dakika = dakika - 1;
            saniye=59;
          }
        }
      else
      {
        saniye = saniye - 1;
      }
       delay(1000);
  }
}
