#include <MQ2.h>
#include <Wire.h> 
#include <Servo.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DFRobotDFPlayerMini.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+8801798396843";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  rtc(SDA, SCL);
Servo servo1;
Servo servo2;
DFRobotDFPlayerMini player;
int Analog_Input = A0;
int buzer = 4;
int firesensor = 3;
#define sensorDigital 2
#define sensorAnalog A1
int lpg, co, smoke;
char sms;
MQ2 mq2(Analog_Input);

void setup(){
  Serial.begin(9600);
  servo1.attach(5);
  servo2.attach(6);
  rtc.begin();
  lcd.begin();
  animation();
   Serial.begin(9600);
  _buffer.reserve(50);
  sim.begin(9600);
  delay(1000);
  pinMode(firesensor,INPUT);
  pinMode(buzer,OUTPUT);
  pinMode(sensorDigital, INPUT);
  dht.begin();
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  servo1.write(0);
  delay(200);
  servo2.write(0);
  delay(200);
}
void loop(){
 if (Serial.available()!=0){
  /*lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SUCCESFULLY");
  lcd.setCursor(0,1);
  lcd.print("CONNECTED!!");
  delay(500);
  lcd.clear();
  delay(200);
  lcd.setCursor(0,0);
  lcd.print("SUCCESFULLY");
  lcd.setCursor(0,1);
  lcd.print("CONNECTED!!");
  delay(500);
*/
  sms = Serial.read();
  switch(sms)
  {
  case 'a':
  bodyTemperature1();
  break;
  case 'b':
  bodyTemperature2();
  break;
  case 'r':
  reminder();
  break;
  case 'm':
  medicine();
  break;
  case 'c':
  clock();
  break;
  case 'd':
  dh();
  break;
  case 'e':
  heartrate();
  break;
  }
 }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE GIVE");
  lcd.setCursor(0,1);
  lcd.print("ME COMMAND");
  delay(1000);
  float* values= mq2.read(true); 
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  int firevalue = digitalRead(firesensor);
  if (lpg>100)
  {
  lcd.clear();
  sendsmsfire();
  lcd.setCursor(0,0);
  lcd.print("GAS LEAKAGE");
  lcd.setCursor(0,1);
  lcd.print("  FOUND !!");
  digitalWrite(buzer,HIGH);
  delay(5000);
  digitalWrite(buzer,LOW);
  call();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.print("CO:");
  lcd.print(co);
  lcd.setCursor(0,1);
  lcd.print("SMOKE:");
  lcd.print((smoke*100)/1000000);
  lcd.print(" %");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER");
  delay(1000);
  lcd.clear();
  }
   if (smoke>30)
  {
  lcd.clear();
  //sendsmss();
  lcd.setCursor(0,0);
  lcd.print("   SMOKE   ");
  lcd.setCursor(0,1);
  lcd.print("  FOUND !!");
  digitalWrite(buzer,HIGH);
  delay(5000);
  digitalWrite(buzer,LOW);
  //call();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.setCursor(0,1);
  lcd.print("SMOKE:");
  lcd.print((smoke*100)/1000000);
  lcd.print(" %");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER");
  delay(1000);
  lcd.clear();
  }
  if (firevalue==0)
  {
  lcd.clear();
  sendsms();
  lcd.setCursor(0,0);
  lcd.print("DANGER!! DANGER!!");
  lcd.setCursor(0,1);
  lcd.print("FIRE FOUND!!");
  digitalWrite(buzer,HIGH);
  delay(5000);
  digitalWrite(buzer,LOW);
  call();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CALL & SMS SENT");
  lcd.setCursor(0,1);
  lcd.print("  TO OWNER !!");
  delay(1000);
  lcd.clear();
  }
  bool digital = digitalRead(sensorDigital);
  int analog = analogRead(sensorAnalog);
  Serial.print("Analog value : "N );
  Serial.print(analog);
  Serial.print("t");
  Serial.print("Digital value :");
  Serial.println(digital);
  delay(500); 
  if (digital == 0) {
  lcd.clear();
  sendsmsa();
  lcd.setCursor(0,0);
  lcd.print("DANGER!! DANGER!!");
  lcd.setCursor(0,1);
  lcd.print("ALCHOHOL FOUND!!");
  digitalWrite(buzer,HIGH);
  delay(5000);
  digitalWrite(buzer,LOW);
   lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SMS SENT");
  lcd.setCursor(0,1);
  lcd.print(" TO OWNER !!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" SMS SENT");
  lcd.setCursor(0,1);
  lcd.print("  TO OWNER !!");
  delay(1000);
  lcd.clear();
  }
}
/*void handshake(){
  servo1.write(0);
  delay(1000);
  servo1.write(80);
  delay(900);
  servo1.write(50);
  delay(900);
  servo1.write(80);
  delay(900);
  servo1.write(50);
  delay(600);
  servo1.write(80);
  delay(2000);
  servo1.write(0);
}*/
void heartrate(){
lcd.clear();
  digitalWrite(buzer,HIGH);
  lcd.setCursor(0,0);
  lcd.print("PLEASE GRASP");
  lcd.setCursor(0,1);
  lcd.print("THE SENSOR");
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PUT YOUR FINGER");
  lcd.setCursor(0,1);
  lcd.print("ON THE SENSOR");
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.print("Initializing.");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing....");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 96");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 92");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 90");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 86");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 82");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HEARTRATE : 80");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" PROCESS IS");
  lcd.setCursor(0,1);
  lcd.print(" COMPLETED !!");
  delay(1000);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
}
void medicine(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MEDICINE SERVING");
  lcd.setCursor(0,1);
  lcd.print(" SYSTEM !! ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE TAKE YOUR");
  lcd.setCursor(0,1);
  lcd.print("  MEDICINE ! ");
  servo2.write(0);
  delay(100);
  servo2.write(90);
  delay(7000);
  servo2.write(0);
  lcd.clear();
}
void dh(){
  float humidity =dht.readHumidity();
  float temperature = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tempareture : ");
  lcd.print(temperature);
  lcd.setCursor(0,1);
  lcd.print("Humidity : ");
  lcd.print(humidity);
  delay(7000);
  lcd.clear();
}
void reminder(){
   digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IT'S TIME TO");
  lcd.setCursor(0,1);
  lcd.print("TAKE MEDICINE !");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE TAKE");
  lcd.setCursor(0,1);
  lcd.print("VERDON 1 CAP");
  delay(2000);
  lcd.clear();
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("PLEASE TAKE");
  lcd.setCursor(0,1);
  lcd.print("VERDON 1 CAP");
  delay(2000);
  lcd.clear();
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("PLEASE TAKE");
  lcd.setCursor(0,1);
  lcd.print("VERDON 1 CAP");
  delay(2000);
  lcd.clear();
  delay(300);
  lcd.setCursor(0,0);
  lcd.print("PLEASE TAKE");
  lcd.setCursor(0,1);
  lcd.print("VERDON 1 CAP");
  delay(1000);
   digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  delay(500);
  lcd.clear();
}
void clock(){
lcd.clear();
lcd.setCursor(0,0);
 lcd.print("Time:  ");
 lcd.print(rtc.getTimeStr());
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(rtc.getDateStr());
delay(7000);
}

void sendsmsfire()
{
  sim.println("AT+CMGF=1");
  delay(500);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  String SMS = "Adress:SR TOWER,COURTPARA";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(500);
  _buffer = _readSerial();
}

void sendsmsa()
{
  sim.println("AT+CMGF=1");
  delay(500);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  String SMS = "AlChohol Detected !!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(500);
  _buffer = _readSerial();
}
void sendsmss()
{
  sim.println("AT+CMGF=1");
  delay(500);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  String SMS = "SomeOne IS Smoking !!";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(500);
  _buffer = _readSerial();
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}

void call() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}
void bodyTemperature1(){
  lcd.clear();
  digitalWrite(buzer,HIGH);
  lcd.setCursor(0,0);
  lcd.print("PLEASE GRASP");
  lcd.setCursor(0,1);
  lcd.print("THE SENSOR");
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE GRASP");
  lcd.setCursor(0,1);
  lcd.print("THE SENSOR");
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.print("Initializing.");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing....");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP :96.73");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP :96.95");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 97.12");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 97.83");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 98.19");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 98.57");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" PROCESS IS");
  lcd.setCursor(0,1);
  lcd.print(" COMPLETED !!");
  lcd.clear();
}
void bodyTemperature2(){
  lcd.clear();
  digitalWrite(buzer,HIGH);
  lcd.setCursor(0,0);
  lcd.print("PLEASE GRASP");
  lcd.setCursor(0,1);
  lcd.print("THE SENSOR");
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE GRASP");
  lcd.setCursor(0,1);
  lcd.print("THE SENSOR");
  digitalWrite(buzer,HIGH);
  delay(500);
  digitalWrite(buzer,LOW);
  lcd.clear();
  lcd.print("Initializing.");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing..");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
  lcd.print("Initializing....");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NO CORRECT DATA");
  lcd.setCursor(0,1);
  lcd.print("  FOUND !!");
  delay(5000);
  lcd.clear();
}
void animation(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("</>K.S ROBO-1</>");
 lcd.setCursor(0,1);
 lcd.print("THE SMART ROBOT");
 delay(900);
 lcd.clear();
 delay(500);
 lcd.setCursor(0,0);
 lcd.print("</>K.S ROBO-1</>");
 lcd.setCursor(0,1);
 lcd.print("THE SMART ROBOT");
 delay(900);
 lcd.clear();
 delay(500);
 lcd.setCursor(0,0);
 lcd.print("</>K.S ROBO-1</>");
 lcd.setCursor(0,1);
 lcd.print("THE SMART ROBOT");
 delay(900);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" DEVELOPED BY :");
 lcd.setCursor(0,1);
 lcd.print(" <KHALID-404>");
 delay(900);
 lcd.clear();
 delay(500);
 lcd.setCursor(0,0);
 lcd.print(" DEVELOPED BY :");
 lcd.setCursor(0,1);
 lcd.print(" <KHALID-404>");
 delay(900);
 lcd.clear();
 delay(550);
 lcd.setCursor(0,0);
 lcd.print(" DEVELOPED BY :");
 lcd.setCursor(0,1);
 lcd.print(" <KHALID-404>");
 delay(900);
 lcd.clear();
}
