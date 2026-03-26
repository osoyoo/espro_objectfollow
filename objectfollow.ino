/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * OSOYOO Espro Car Object follower project
 * Tutorial URL https://osoyoo.com/?p=61327
 * CopyRight www.osoyoo.com 
 * 
 */
//Define L298N Dual H-Bridge Motor Controller Pins
#define speedPinR 16   // RIGHT PWM pin connect   ENA
#define RightDirectPin1  23    //  Right Motor direction pin 1 to  IN1 
#define RightDirectPin2  25    // Right Motor direction pin 2 to  IN2
#define speedPinL 17        //  Left PWM pin connect  ENB
#define LeftDirectPin1  26    // Left Motor direction pin 1 to  IN3
#define LeftDirectPin2  27   ///Left Motor direction pin 1 to  IN4
 
#define RightObstacleSensor 14  //Right obstacle sensor to D14 (front direction is from arduino point to voltage meter)
#define LeftObstacleSensor 15   //Left obstacle sensor to D15

#define TURN_SPEED   220 //motor in   speed
#define SLOW_SPEED   90 //motor in   speed
#define SPEED   120 //motor in   speed
void go_Advance(int l_speed=SPEED,int r_speed=SPEED)  //Forward
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  set_Motorspeed(l_speed,r_speed);
}
void turn_left(int l_speed=TURN_SPEED,int r_speed=SPEED)  //Turn left
{
  digitalWrite(RightDirectPin1, HIGH);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  set_Motorspeed(l_speed,r_speed);
}
void turn_right(int l_speed=SPEED,int r_speed=TURN_SPEED)  //Turn right
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,HIGH);
  digitalWrite(LeftDirectPin2,LOW);
  set_Motorspeed(l_speed,r_speed);
}
void go_Back(int l_speed=SPEED,int r_speed=SPEED)  //Reverse
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,HIGH);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,HIGH);
  set_Motorspeed(l_speed,r_speed);
}
void stop_Stop()    //Stop
{
  digitalWrite(RightDirectPin1, LOW);
  digitalWrite(RightDirectPin2,LOW);
  digitalWrite(LeftDirectPin1,LOW);
  digitalWrite(LeftDirectPin2,LOW);
}
/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void setup()
{
 pinMode(speedPinL,OUTPUT); //left motor PWM pin
 pinMode(speedPinR,OUTPUT); //rignt motor PWM  pin
 pinMode(RightDirectPin1,OUTPUT); //left motor direction pin1
 pinMode(RightDirectPin2,OUTPUT); //left motor direction pin2
 pinMode(LeftDirectPin1,OUTPUT); //right motor direction Pin 1
 pinMode(LeftDirectPin2,OUTPUT);  //right motor direction Pin 2

  /*line follow sensors */
 pinMode(RightObstacleSensor,INPUT); 
 pinMode(LeftObstacleSensor,INPUT); 
 Serial.begin(9600);
}

void auto_following(){
 int IRvalueLeft= digitalRead(LeftObstacleSensor);
  int IRvalueRight=digitalRead(RightObstacleSensor);
 if (IRvalueLeft==LOW && IRvalueRight==LOW)
 { 

       go_Advance();  //Turn left
 }
 else  if (IRvalueLeft==HIGH && IRvalueRight==HIGH)
 {
     stop_Stop();   //no obstacle, stop
     set_Motorspeed(0,0);
    }
 else if (IRvalueLeft==LOW && IRvalueRight==HIGH)
 { 
  Serial.println("left");
      turn_left(SLOW_SPEED,TURN_SPEED);  //Turn left
 }
  else if (IRvalueLeft==HIGH && IRvalueRight==LOW)
 { 
    Serial.println("right");
     turn_right(TURN_SPEED,SLOW_SPEED);  //Turn left
  
 }
}

void loop(){
 
auto_following();
}
