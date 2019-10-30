//#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define LDRpin A0
#define LMpin A1
#define MQpin A2

#define LEDpin 0
#define IN1pin 4
#define IN2pin 3
#define IN3pin 2
#define IN4pin 1
#define BUZZERpin 5
#define BUTTONpin 7

SoftwareSerial mybluetooth(10, 11);
//Ultrasonic ultrasonic(13,12); //change
Servo myservo;

int LMvalue;
boolean buzzer_lm_status=false;
int BluetoothData;
int LDRvalue;
int MQvalue;
boolean buzzer_mq_status=false;
int ultasonicValue;
int Position=0;
int temp=0;

void setup()
{
    mybluetooth.begin(38400);
    pinMode(LEDpin,OUTPUT);
    pinMode(IN1pin,OUTPUT);
    pinMode(IN2pin,OUTPUT);
    pinMode(IN3pin,OUTPUT);
    pinMode(IN4pin,OUTPUT);
    pinMode(BUZZERpin,OUTPUT);
    pinMode(BUTTONpin,INPUT);
    myservo.attach(6);   
}

void LM35()
{
    LMvalue = analogRead(LMpin);
    if((LMvalue > 50)&& (buzzer_lm_status==false))
    {
      digitalWrite(BUZZERpin,HIGH);
      mybluetooth.println("Warning !! The temperature is too high .If you want to turn off the buzzer press 1 or press the button on the robot");
    }
    delay(15);
    BluetoothData=mybluetooth.read();
    if ((BluetoothData=='1') || (digitalRead(BUTTONpin)== HIGH))
    {
      buzzer_lm_status=true;
      digitalWrite(BUZZERpin,LOW);
    }
    if(LMvalue < 40)
      buzzer_lm_status=false;
}

void LDR()
{
    LDRvalue=analogRead(LDRpin);
    if(LDRvalue>80)
      digitalWrite(LEDpin,HIGH);
   else if(LDRvalue<120)
      digitalWrite(LEDpin,LOW);
}

void MQ5()
{
    MQvalue = analogRead(MQpin);
    if((MQvalue > 400)&& (buzzer_mq_status==false))
    {
      digitalWrite(BUZZERpin,HIGH);
      mybluetooth.println("Attention !! Most probably that there is a fire .If you want to turn off the buzzer press 2 or press the button on the robot");
    }
    delay(15);
    BluetoothData=mybluetooth.read();
    if ((BluetoothData=='2') || (digitalRead(BUTTONpin)== HIGH))
    {
      buzzer_mq_status=true;
      digitalWrite(BUZZERpin,LOW);
    }
    if(MQvalue < 380)
      buzzer_mq_status=false;
}

void forword()
{
  digitalWrite(IN1pin,LOW);
  digitalWrite(IN2pin,HIGH);
  digitalWrite(IN3pin,LOW);
  digitalWrite(IN4pin,HIGH);
  delay(50);
} 

void background()
{
  digitalWrite(IN1pin,HIGH);
  digitalWrite(IN2pin,LOW);
  digitalWrite(IN3pin,HIGH);
  digitalWrite(IN4pin,LOW);
  delay(50);
}

void right(){
  digitalWrite(IN1pin,HIGH);
  digitalWrite(IN2pin,LOW);
  digitalWrite(IN3pin,LOW);
  digitalWrite(IN4pin,HIGH);
  delay(50);
}

 void left()
 {
  digitalWrite(IN1pin,LOW);
  digitalWrite(IN2pin,HIGH);
  digitalWrite(IN3pin,HIGH);
  digitalWrite(IN4pin,LOW);
  delay(50);
 }
 
 void STOP()
 {
  digitalWrite(IN1pin,LOW);
  digitalWrite(IN2pin,LOW);
  digitalWrite(IN3pin,LOW);
  digitalWrite(IN4pin,LOW);
  delay(50);
 }

void loop()
{
    LM35();
    delay(50);
    LDR();
    delay(50);
    MQ5();
    delay(50);
    myservo.write(90);
    delay(500) ;
//    ultasonicValue =ultrasonic.Ranging(CM);
    while (ultasonicValue > 20)
    {
      forword();
//      ultasonicValue =ultrasonic.Ranging(CM);
    }
    while (ultasonicValue <= 20)
    {
      STOP();
      myservo.write(Position);
      delay(500);
//      ultasonicValue =ultrasonic.Ranging(CM);
      delay(1000);
      temp=Position;
      Position=Position+45;
      if(Position==225)
        Position=0;
     }
     myservo.write(90);
    switch(temp)
    {
      case 0:
      left();
      delay(500);
      STOP();
      break;
      case 45 :
      left();
      delay(250);
      STOP();
      break;
      case 135 :
      right();
      delay(250);
      STOP();
      break;
      case 180 :
      right();
      delay(500);
      STOP();
      break;
    }
}
