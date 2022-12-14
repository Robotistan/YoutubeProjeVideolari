#include <Adafruit_NeoPixel.h>      //kütüphanelerimiz tanımlanmış 
#include <SoftwareSerial.h>      

SoftwareSerial mySerial(9, 10);

#define PIN 6
#define NUMPIXELS 12             // Pinlerimiz bağlanmış
int kirmizi,yesil,mavi;

Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int bekleme = 20;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);               //Adreslenebilir ledlerimizin zamanlaması
  mySerial.setTimeout(50);
  led.begin();
  led.show();
 
}
 
void loop() {
 
  while (mySerial.available() > 0) {    // renk değiştirene kadar ki döngümüzü sağlamak
 
    kirmizi = mySerial.parseInt();
 
    yesil = mySerial.parseInt();
 
    mavi = mySerial.parseInt();
 
    if (mySerial.read() == ')') {

      for(int i=0;i<NUMPIXELS;i++){

    
      led.setPixelColor(i, led.Color(kirmizi,yesil,mavi));  //neo pixelimizin temel RGB renkleri
      led.show(); 
      delay(bekleme);

  }
 
      Serial.print(kirmizi);
      Serial.print(" ");
      Serial.print(yesil);
      Serial.print(" ");
      Serial.println(mavi);

    }
  }
}
