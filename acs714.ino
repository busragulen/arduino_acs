// ACS714'ün analog pinini tanımla:
int AnalogInputPin = 1;
void setup() {
  Serial.begin(9600);
}

void loop() {
  //akımı hesaplayan rutin komutu
  double Current = currentSensor(analogRead(AnalogInputPin));
  Serial.println(Current);
  Serial.println("\n");
}

//ACS714 ile akımı hesaplama
double currentSensor(int RawADC) 
{
  int    Sensitivity    = 66; // mV/A
  long   InternalVcc    = readInternalVcc();
  double ZeroCurrentVcc = InternalVcc / 2;
  double SensedVoltage  = (RawADC * InternalVcc) / 1024;
  double Difference     = SensedVoltage - ZeroCurrentVcc;
  double SensedCurrent  = Difference / Sensitivity;
  //Serial.println("Sen: ");
  //Serial.println(RawADC);
  //Serial.println("/1024");
  return SensedCurrent;            
}

long readInternalVcc() 
{
  long result;
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);                          // Vref 'in ayarlanması
  ADCSRA |= _BV(ADSC);               // dönüştürme
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result;       // AVcc 'yi mV'de yeniden hesaplama
  return result;
} 
