#include <LiquidCrystal.h>

// LCD AYARLARI

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int analogIn = 0; // bağlantı pini
int mVperAmp = 66; // 185 5A MODÜL İÇİN , 100 20A MODÜL İÇİN VE 66  30A MODÜL İÇİN
int RawValue = 0;
int ACSoffset = 2500;

double Voltage = 0; //VOLT HESABI
double Amps = 0;// AMPER HESABI

void setup() {

// LCD AYARI

lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("ACS 712");
lcd.setCursor(0, 1);
lcd.print("  AKIM OLCUM  ");
delay(2000);

}

void loop()

{

RawValue = analogRead(analogIn);//MODUL ANALOG DEĞERI OKUNUYOR
Voltage = (RawValue / 1024.0) * 5000; // VOLT HESABI YAPILIYOR
Amps = ((Voltage - ACSoffset) / mVperAmp); // AKIM HESAPLA


lcd.clear();//clears the display of LCD
delay(1000);//delay of 1 sec
lcd.display();

// VOLTAJI EKRANA YAZ

lcd.setCursor(1, 0);
lcd.print("Voltaj= ");
lcd.setCursor(8, 0);
lcd.print(Voltage, 3);
lcd.setCursor(12, 0);
lcd.print("mV");

// AKIMI EKRANA YAZ

lcd.setCursor(1, 1);
lcd.print("AMPER= ");
lcd.setCursor(7, 2);
lcd.print(Amps, 3);
lcd.setCursor(11, 2);
lcd.print("A");

delay(2500);

}
