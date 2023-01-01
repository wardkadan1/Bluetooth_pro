#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define m11 3 // M1a
#define m12 5 // M1b
#define m21 6 // M2a
#define m22 9 // M2b

int x, TRIGPIN = 13, ECHOPIN = 12, pulseTime, distance, minDisInCm = 15;

LiquidCrystal_I2C lcd (0x3f,16,2);
SoftwareSerial BT(7,8);

void setup ()
{
  Serial.begin(9600);
  BT.begin(9600);
  
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  
  lcd.init();
  lcd.backlight();
}

void loop ()
{
  Distance();                                       
  Lcd();

  x = BT.read();
  
  if (x == 'F') if (distance >= minDisInCm) forward(); else Stop();
  if (x == 'L') left();
  if (x == 'R') right();
  if (x == 'B') backward();
  if (x == 'f' || x == 'b' || x == 'r' || x == 'l' || x == 'o') Stop();
}

void forward ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void left ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  
  delay(800);
  
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void backward ()
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
}

void right ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
  
  delay(800);
  
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
}

void Stop ()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

void Distance ()
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                   
  delayMicroseconds(10);                  
  digitalWrite(TRIGPIN, LOW);
                       
  pulseTime = pulseIn(ECHOPIN, HIGH);             
  distance = pulseTime/58;
}

void Lcd ()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("distance=");
  lcd.print(distance);
  delay(2);
  lcd.setCursor(12,0);
  lcd.print("cm");
}
