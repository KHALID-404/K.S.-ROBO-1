#include <MQ2.h>
#include <Wire.h> 
#include <Servo.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+8801782669241";
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
DS3231  rtc(SDA, SCL);
Servo hand_servo;
Servo medicine_servo;
int Analog_Input = A0;
int buzer = 4;
int firesensor = 3;
int lpg, co, smoke;
char sms;
MQ2 mq2(Analog_Input);
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
void setup(){
  Serial.begin(9600);
  hand_servo.attach(8);
  medicine_servo.attach(6);
  lcd.begin();
  lcd.clear();
  animation();
   Serial.begin(9600);
  _buffer.reserve(50);
  sim.begin(9600);
  delay(1000);
  pinMode(firesensor,INPUT);
  pinMode(buzer,OUTPUT);
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
  hand_servo.write(0);
  delay(200);
  medicine_servo.write(0);
  delay(200);

}

void loop(){
  Serial.print("Give me A command !!");
 if (Serial.available()!=0){
  sms = Serial.read();
  switch(sms)
  {
  case 'a':
  bodyTemperature1();
  break;
  case 'h':
  handshake();
  break;
  case 'r':
  reminder();
  break;
  case 'm':
  medicine();
  break;
  case 'd':
  dh();
  break;
  case 'e':
  heartrate();
  break;
  }
 }

  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE GIVE");
  lcd.setCursor(0,1);
  lcd.print("ME COMMAND");
  float* values= mq2.read(true); 
  lpg = mq2.readLPG();
  //co = mq2.readCO();
  //smoke = mq2.readSmoke();
  Serial.print("LPG : ");
  Serial.println(lpg);
  int firevalue = digitalRead(firesensor);
  if (lpg>300)
  {
  lcd.clear();
  //sendsmsfire();
  lcd.setCursor(0,0);
  lcd.print("GAS LEAKAGE");
  Serial.print("GAS LEAKAGE FOUND !");
  lcd.setCursor(0,1);
  lcd.print("  FOUND !!");
  digitalWrite(buzer,HIGH);
  delay(5000);
  digitalWrite(buzer,LOW);
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
  call();
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
  sendsmsfire();
  lcd.setCursor(0,0);
  lcd.print("DANGER!! DANGER!!");
  lcd.setCursor(0,1);
  lcd.print("FIRE FOUND!!");
  Serial.print("FIRE FOUND !");
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
}
void handshake(){
  hand_servo.write(0);
  delay(1000);
  hand_servo.write(80);
  delay(900);
  hand_servo.write(50);
  delay(900);
  hand_servo.write(80);
  delay(900);
  hand_servo.write(50);
  delay(600);
  hand_servo.write(80);
  delay(2000);
  hand_servo.write(0);
}
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
  medicine_servo.write(0);
  delay(100);
  medicine_servo.write(90);
  delay(7000);
  medicine_servo.write(0);
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
  Serial.print("Time:  ");
 Serial.println(rtc.getTimeStr());
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
  lcd.print("BODY TEMP :92.23");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP :92.56");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 92.79");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 93.13");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 92.89");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 93.67");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP :93.56");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP :93.89");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 94.21");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 95.42");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 96.65");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BODY TEMP : 96.59");
  delay(2000);
  lcd.clear();
  lcd.print(" PROCESS IS");
  lcd.setCursor(0,1);
  lcd.print(" COMPLETED !!");
  delay(1000);
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
