#include <LiquidCrystal_PCF8574.h>  // Kütüphane tamamlandı
LiquidCrystal_PCF8574 lcd(0x27);
 
#define baslaButton 5      // Buton ve buzzer pinleri tanımlandı
#define ledveBuzzer 4

int saniye = 0;          // LCD ekranda süremizi belirtme komutu
int dakika = 20;
int saat = 0;
int basla = 0;
String displayText = "Tusa basiniz";

void setup()
{
  lcd.begin(16, 2); 
  lcd.setBacklight(HIGH);       //Butonların giriş ve çıkışlarını ayarlama
  fnkFormat();
  pinMode(baslaButton,INPUT);
  pinMode(ledveBuzzer,OUTPUT);
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
    displayText = "Afiyet Olsun...";
  }
  if(basla==0)
  {
    if(digitalRead(baslaButton) == 1) // Butonu başlatma 
    {
      displayText = "Demleniyor...";
      basla = 1;
      delay(50); 
    }
    
  }
  if(basla==1)    // Butona basıldığında ve zaman sıfırlandığında buzzer aktif hale gelsin
  {
      lcd.clear();
      fnkFormat();
        if(saniye == 0)
        {
          if(dakika == 0)
          {
            if(saat == 0)
            {
              digitalWrite(ledveBuzzer,HIGH);
              delay(1000);
              digitalWrite(ledveBuzzer,LOW);
              delay(1000);
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
