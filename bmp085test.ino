#include <Wire.h>
#include <bmp085.h>

/*
1. call bmp085_init
   - parameter pressure at sealevel (in Pascal) or 0
     if 0 then 101325 (std pressure at sea level) is used

2. Measurement by
  a. call bmp085_measure()
  b. now pressure and temperature is in float variables bmp085_temp and bmp085_pres
*/

float phojde;
float highsc = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

  bmp085Init(101300.0); // ress at sealevel today

}

float temp, atm, alt, pres;


#define LOOPTIME 200
unsigned long t1, t3;

void loop()
{
float tryk, temp, hojde;
  bmp085Measure(&temp, &tryk, &hojde);

  hojde += 109;
  digitalWrite(13, LOW);

  if(hojde > phojde) highsc = hojde;

  if((highsc - hojde) >= 7) {
    //Shoot the chute
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    delay(75);
  }

  if(hojde >= 3) {  
  Serial.print(temp);
  Serial.print("  "); Serial.print(tryk);
  Serial.print("  "); Serial.print(hojde); Serial.println(";");
  }

  phojde = hojde;
  
  delay(25);
}



