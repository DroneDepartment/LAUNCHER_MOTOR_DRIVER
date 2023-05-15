#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

float t1=0.0;
float t2=0.0;
int count =0;
float velocity= 0.0;
float time_difference = 0.0;
float time_in_sec = 0.0;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("WELCOME TO");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("LAUNCHER");
  lcd.setCursor(2,1);
  lcd.print("SPEEDOMETER");
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(4,INPUT);
  Serial.begin(9600);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
}
void loop()
{ 
 
// Serial.println(digitalRead(D4)); 
 if ((digitalRead(4)==0) && (count == 0))
  {t1= micros();
    digitalWrite(8,HIGH);
   digitalWrite(6,LOW);
   
     

    count = count+1;
 
  }
  if ((digitalRead(4)==1) && ( count == 1))
  { t2= micros();
  count = count + 1;
  }
  if (count == 2)
  {
  time_difference = t2-t1;
 


  time_in_sec = time_difference/1000000;

  velocity = 0.46/time_in_sec;
  Serial.print("t1=");
  Serial.print(t1);
  Serial.println("   ");
  Serial.print("t2 =");
  Serial.print(t2);
  Serial.println("   ");

Serial.print("time_difference =");
  Serial.print(time_difference);
  Serial.println("   ");
  Serial.print("time_in_seconds =");
  Serial.print(time_in_sec);
  Serial.println("     ");
  Serial.print("speed =");
  Serial.print(velocity);
  Serial.println("     ");

  lcd.clear();
   lcd.setCursor(5,0);
   lcd.print("SPEED");
   lcd.setCursor(3,1);
  lcd.print((velocity));
  lcd.setCursor(10,1);
  lcd.print("m/s");

  //delay (1000);

  
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  count = 0;
  }

}
