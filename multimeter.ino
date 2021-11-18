#include <Adafruit_GFX.h> //ekran kütüphaneleri
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display; 

const int currentSensor = A0;
const int voltageSensor = A1;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 10000.0;
float R2 = 1980.0;
float Vdata = 0;
float V,I,I1;
float Cdata;
float value;

void setup(){ 

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.display();

}
void loop(){

//float vIN = 0.0;

   for(int i = 0; i < 300; i++) // daha kararlı ortalama bir sonuç almak için 300 kez okuma yapma:
   {
     Cdata = Cdata + analogRead(currentSensor);
     Vdata = Vdata + analogRead(voltageSensor);
     delay(1);
   }

 Cdata=Cdata/300;           
 V=(Cdata/1024.0)*5000;                       
 I=((V - 2500)/ 96);

 Vdata=Vdata/300;
 vOUT = (Vdata * 5.0) / 1024.0;
 vIN = (vOUT / (R2/(R1+R2)));

// oled ekrana yazma:
  display.setTextColor(WHITE);
  
  // watt hesaplaması ve yazdırma:
  display.setTextSize(1);
  display.setCursor(58,8);
  display.print(" Watt");
  display.setCursor(0,0);
  display.setTextSize(2);
  value=(I * vIN);
  if (value<0){display.println("0.0");} else {display.println(value);} 
  
  // amper değerini yazdırma:
  display.setTextSize(1);
  display.setCursor(58,23);
  display.print(" Amper");
  display.setCursor(0,16);
  display.setTextSize(2);
  if (I<0) {display.println("0.0");} else {display.println(I);}
  
  // voltaj değerini yazdırma:
  display.setTextSize(1);
  display.setCursor(58,39);
  display.print(" Volt");
  display.setCursor(0,32);
  display.setTextSize(2);
  display.println(vIN);
  
display.display();
display.clearDisplay();

// değerleri sıfırlama:
  Cdata=0;
  I=0;
  V=0;
  Vdata=0;
  vIN=0;
  value;
}
