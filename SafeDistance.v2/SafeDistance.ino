#include <LiquidCrystal.h>

#define echoPin    A0 
#define trigPin    A1

#define heaterPin  A4
#define alertPin   0
#define lm35Pin    A2

float time;

float old_distance_cm=0.0;
float distance_cm;
float distance_in;

int temp_adc_val;
float temp_val;
float old_temp_val=0;

bool alert_flag=0;
 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

pinMode(heaterPin, OUTPUT);
pinMode(alertPin, OUTPUT);

pinMode(lm35Pin, INPUT);

lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("  Safe Distance ");

delay(1000);
digitalWrite(heaterPin, HIGH);
lcd.clear();
}
 
void loop()
{

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

time = pulseIn(echoPin, HIGH);

distance_cm = (time/2) / 29.1; 


temp_adc_val = analogRead(lm35Pin);
temp_val = (temp_adc_val * 4.88);
temp_val = (temp_val/10);
if(alert_flag==0)
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Distance=");
//lcd.setCursor(14, 0);
lcd.print(distance_cm,0);
lcd.print("cm");

lcd.setCursor(0, 1);
lcd.print("Temperature=");
//lcd.setCursor(15, 1);   
lcd.print(temp_val,1);
lcd.print("°C");
delay(1000);
}
old_temp_val=temp_val;
old_distance_cm=distance_cm;


if(temp_val>=40&&temp_val<=50&& distance_cm<=27&&distance_cm>15)
{
  alert_flag=1;
digitalWrite(alertPin, HIGH);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System Alert");
lcd.setCursor(0, 1);
lcd.print("close object!");
}
/*
* Study Case2: temp=40°C , distance=20cm (1-ohm)
*/
else if(temp_val>60&& distance_cm>=20&&distance_cm<=30)
{
  alert_flag=1;
digitalWrite(alertPin, HIGH);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System Alert:");
lcd.setCursor(0, 1);
lcd.print("close object!");
}
else if(temp_val>60&& distance_cm<20)
{
  alert_flag=1;
digitalWrite(alertPin, HIGH);
digitalWrite(heaterPin, LOW);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System Alert:");
lcd.setCursor(0, 1);
lcd.print("System LOCKED!");
}
/*
* Study Case3: temp=50°C , distance=11cm (1-ohm)
*/
else if(temp_val>40&&temp_val<=50&& distance_cm<15)
{
  alert_flag=1;
digitalWrite(alertPin, HIGH);
digitalWrite(heaterPin, LOW);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("System Alert:");
lcd.setCursor(0, 1);
lcd.print("System LOCKED!");
}
/*
* Study Case1: temp=27°C , distance=11cm (1-ohm)
*/
else
{
  alert_flag=0;
  digitalWrite(heaterPin, HIGH);
  digitalWrite(alertPin, LOW);
}
delay(200);
}