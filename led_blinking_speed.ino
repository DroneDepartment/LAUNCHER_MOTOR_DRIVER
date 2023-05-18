#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define led_red D8
#define led_green D7
#define led_blue D6
#define l1 D0
#define l2 D5
#define sensor D4
bool switch1 =false;
bool switch2 =false;
float t1=0.0;
float t2=0.0;
int count =0;
float velocity= 0.0;
float time_difference = 0.0;
float time_in_sec = 0.0;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
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
  pinMode(led_red,OUTPUT);
pinMode(led_green,OUTPUT);
pinMode(led_blue,OUTPUT);
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(sensor,INPUT);
digitalWrite(l1,HIGH);
digitalWrite(l2,HIGH);
  
  
}
void loop()
{ 
 if(digitalRead(l1) == LOW && switch1 == false)
 {
   switch1 = true;
   //count = 0;
 }
 if (digitalRead(l2) == LOW && switch2 == false)
 {
   switch2 = true;
   //count = 0;

 }

 if(digitalRead(l2) == HIGH && digitalRead(l1) == HIGH)
 {
   switch1= false;
   switch2= false;
   count = 0;


 }
 if (switch1 == true && switch2 == false)
 {
   digitalWrite(led_blue,LOW);
   digitalWrite(led_red,LOW);
   digitalWrite(led_green,HIGH);
 }
if (switch2 == true && switch1 == false)
 {
   digitalWrite(led_blue,LOW);
   digitalWrite(led_green,LOW);
   digitalWrite(led_red,HIGH);
 }
if( switch1 == false && switch2 == false)
{
  digitalWrite(led_green,LOW);
  digitalWrite(led_red,LOW);
  digitalWrite(led_blue,HIGH);
}
// Serial.println(digitalRead(D4)); 
 if ((digitalRead(sensor)==0) && (count == 0) && (switch1 == true || switch2 == true ))
  {t1= micros();
    digitalWrite(8,HIGH);
   digitalWrite(6,LOW);
   
     

    count = count+1;
 
  }
  if ((digitalRead(sensor)==1) && ( count == 1) && (switch1 == true || switch2 == true ))
  { t2= micros();
  count = count + 1;
  }
  if (count == 2 && (switch1 == true || switch2 == true ))
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

  
  
 
  }

}

