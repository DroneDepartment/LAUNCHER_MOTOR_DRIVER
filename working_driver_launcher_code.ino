#include <PIDController.h>
#include <EEPROM.h>
#define led_blue  11
#define led_green  10
#define led_red 12
volatile long int encoder_pos = 0 ;
signed int position2 = 0;
signed int position1= 200;
signed int position = 0;
volatile long signed int encoder_pos_write = 0;
PIDController pos_pid;
int motor_value = 255;
signed int count = 0;

bool locked = false;
bool switch1=false;
bool switch2=false;



void setup ()
{ Serial.begin(9600);
digitalWrite(4,HIGH);
pinMode(4,OUTPUT);
pinMode(2,INPUT_PULLUP);
//pinMode(4,OUTPUT);
pinMode(3,INPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(5,OUTPUT);
pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT);
pinMode(led_green,OUTPUT);
pinMode(led_blue,OUTPUT);
pinMode(led_red,OUTPUT);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);

attachInterrupt(digitalPinToInterrupt(2),encoder,RISING);
pos_pid.begin();
pos_pid.tune(10,2,10);
pos_pid.limit(-255,255);

locked = EEPROM.read(0);
position = EEPROM.read(1);

if(position == 200 )
{
  position1 = 0;
  position2 = -200;
}
if(position == 0 )
{
  position1 = 200;
  position2 = 0;
}
if(position == 0 && locked == true )
{
  position1 = 0;
  position2 = -200;
}


}

void loop()
{
 
 




if (locked== true)
{
digitalWrite(led_blue,LOW);
  digitalWrite(led_green,LOW);
  digitalWrite(led_red,HIGH);
  
}
if (locked == false)
{
digitalWrite(led_blue,LOW);
    digitalWrite(led_red,LOW);
    digitalWrite(led_green,HIGH);
}

if (digitalRead(8)== LOW && switch1 == false)
{ 
  switch1=true;

}


if(digitalRead(9)==LOW && switch2 == false)
{
switch2=true;

}

if(digitalRead(8) == HIGH && digitalRead(9)== HIGH)
{
  switch1=false;
  switch2=false;
}
 
if(switch1==true && count ==0 )
{
  locked = true;
  EEPROM.write(0,locked);
  pos_pid.setpoint(position1);
  EEPROM.write(1,position1);
  count = 1;
 
} 
if( switch2 == true && count == 1)
{
  locked = false;
  EEPROM.write(0,locked);
  pos_pid.setpoint(position2);
  EEPROM.write(1,position2);
 count = 0;

}


  motor_value= pos_pid.compute(encoder_pos);
 
if (motor_value > 0)
{ 
  MotorCounterClockwise(motor_value);
 
}
else
{ 
  MotorClockwise(abs(motor_value));
 
}
 
Serial.println(encoder_pos);

}
void encoder()
{ 
  if (digitalRead(3)== HIGH)
  {encoder_pos++;
  }
  else
  {encoder_pos--;
  }
}
void MotorClockwise(int power)
{ analogWrite(5,power);
  if (power>100)
{
digitalWrite(7,HIGH);
digitalWrite(6,LOW);
}
else{
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
 
}

}
void MotorCounterClockwise(int power)
{ analogWrite(5,power);
  if (power>100)
{
digitalWrite(6,HIGH);
digitalWrite(7,LOW);

}
else{
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
 
}

}