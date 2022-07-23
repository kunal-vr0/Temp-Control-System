#include <LiquidCrystal.h>

int rs = 12;
int en = 11;
int db4 = 5;
int db5 = 4;
int db6 = 3;
int db7 = 2;
int led = 10;
int Mt1 = 9;
int Mt2 = 8;
int Mdelay = 10;
int dt = 3000;
int tempread = A2;
float sensorread;
float eqvolt;
float temp;
float Maxtemp = 25.00;
float Mintemp = 20.00;
int fanstat = 0;
int ledstat = 0;

LiquidCrystal Lcd(rs,en,db4,db5,db6,db7);

void setup(){
  Lcd.begin(16,2);
  pinMode(led,OUTPUT);
  pinMode(tempread,INPUT);
  pinMode(Mt1,OUTPUT);
  pinMode(Mt2,OUTPUT);
  digitalWrite(Mt2,LOW);
}

void loop(){
  sensorread = analogRead(tempread);
  eqvolt = sensorread*(5.00/1023.00);
  temp = 100.00*eqvolt-50.00;
  
  Lcd.clear();
  Lcd.print("Sensor Reading:");
  Lcd.setCursor(2,1);
  Lcd.print(temp);
  Lcd.print(" C");
  delay(dt);
  
  if(temp >= Maxtemp){
    if(ledstat == 1){
      Lcd.clear();
      Lcd.print("It's too Hot!!");
      Lcd.setCursor(1,1);
      Lcd.print("Turn off Heater");
      digitalWrite(led,LOW);
      ledstat = 0;
      delay(dt);
    }
    Lcd.clear();
    Lcd.print("It's too Hot!!");
    Lcd.setCursor(2,1);
    if(fanstat == 0){
      Lcd.print("Turn on Fan");
      for(int i=0; i<=255; i++){
        analogWrite(Mt1,i);
        delay(Mdelay);
      }
      fanstat = 1;
    }
    else if(fanstat == 1){
      Lcd.print("Fan is On");
    }
    delay(dt);
  }
  else if(temp <= Maxtemp && temp >= Mintemp){
    Lcd.clear();
    Lcd.print("Temp is Normal");
    Lcd.setCursor(2,1);
    if(fanstat == 1){
      Lcd.print("Turning off Fan");
      fanstat = 0;
      for(int i=255; i>=0; i--){
      	analogWrite(Mt1,i);
      	delay(Mdelay);
      }
    }
    else if(ledstat == 1){
      Lcd.setCursor(1,1);
      Lcd.print("Turn off Heater");
      ledstat = 0;
      digitalWrite(led,LOW);
    }
    else{
      Lcd.print("All are Off");
    }
    delay(dt);
  }
  else if(temp <= Mintemp){
    if(fanstat == 1){
      Lcd.clear();
      Lcd.print("It's too Cold!!");
      Lcd.setCursor(2,1);
      Lcd.print("Turn off Fan");
      fanstat = 0;
      for(int i=255; i>=0; i--){
      	analogWrite(Mt1,i);
      	delay(Mdelay);
      }
      delay(dt);
    }
    Lcd.clear();
    Lcd.print("It's too Cold!!");
    Lcd.setCursor(2,1);
    if(ledstat == 0){
      Lcd.print("Turn On Heater");
      ledstat = 1;
      digitalWrite(led,HIGH);
    }
    else if(ledstat == 1){
      Lcd.print("Heater is On");
    }
    delay(dt);
  }
  else{
    Lcd.clear();
    Lcd.print("Something Went Wrong");
    Lcd.setCursor(2,1);
    Lcd.print("Error in the Circuit");
    delay(dt);
  }
}