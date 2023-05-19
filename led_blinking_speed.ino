#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
#define led_red D8
#define led_green D7
#define led_blue D6
#define l1 D0
#define l2 D3
#define sensor2 D4
bool switch1 =false;
bool switch2 =false;
float t1=0.0;
float t2=0.0;
int count =0;
float velocity= 0.0;
float time_difference = 0.0;
float time_in_sec = 0.0;
int limit_state = 0;


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
  pinMode(led_red,OUTPUT);
pinMode(led_green,OUTPUT);
pinMode(led_blue,OUTPUT);
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(sensor2,INPUT);
digitalWrite(l1,HIGH);
digitalWrite(l2,HIGH);
digitalWrite(led_red,LOW);
digitalWrite(led_blue,LOW);
digitalWrite(led_green,LOW);
  
  
}
void loop()
{ 
 if(digitalRead(l1) == LOW && limit_state == 0)
 {
   digitalWrite(led_red,LOW);
   digitalWrite(led_blue,LOW);
   digitalWrite(led_green,HIGH);
   limit_state++;
   switch1 = true;
   switch2 =false;
  // Serial.println("inside l1");
 }
 if(digitalRead(l2) == LOW && limit_state == 0)
 {
   digitalWrite(led_blue,LOW);
   digitalWrite(led_green,LOW);
   digitalWrite(led_red,HIGH);
   limit_state++;
   switch2 = true;
   switch1 = false;
  // Serial.println("inside l2");
 }
 if(digitalRead(l1) == HIGH && digitalRead(l2) == HIGH && limit_state == 1)
 {
   digitalWrite(led_red,LOW);
   digitalWrite(led_green,LOW);
   digitalWrite(led_blue,HIGH);
limit_state = 0;
switch1 = false;
switch2 = false;
count = 0;
  // Serial.println("inside outside");
 }

// Serial.println(digitalRead(D4)); 
 if ((digitalRead(sensor2)==0) && (count == 0) && (switch1 == true || switch2 == true ))
  {t1= micros();
    count = count+1;
 
  }
  if ((digitalRead(sensor2)==1) && ( count == 1) && (switch1 == true || switch2 == true ))
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
 count = count ++;
  //delay (1000);


 
  }
  
  
}

