#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
Servo servo_DO;  //서보모터 객체 생성
Servo servo_RE;  
Servo servo_MI;
Servo servo_FA;
Servo servo_SOL;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup(){
  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  servo_DO.attach(8);  //서보모터 DO 8번핀 세팅
  servo_RE.attach(11);  //서보모터 RE 11번핀 세팅
  servo_MI.attach(10);//서보모터 MI 10번핀 세팅
  servo_FA.attach(9);//서보모터 FA 9번핀 세팅
  servo_SOL.attach(12);//서보모터 SOL 12번핀 세팅
  lcd.setCursor(5,0);
  lcd.print("Hello");//시작함을 알림
  delay(5000);
  lcd.clear();//lcd 다지움
  Serial.println("ok");
  delay(200);
  Serial.println(Serial.read());//파이썬으로 ok 보냄
  servo_DO.write(0);
  servo_RE.write(0);
  servo_MI.write(90);
  servo_FA.write(0);
  servo_SOL.write(0);

}

void loop() {
  while (Serial.available()>0) {
    char c = Serial.read();
    if (c=='d') {
      
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);// 0번 행 6번 열부터 출력합니다.
      lcd.print("Do");    
      delay(2000);
      servo_DO.write(0);  //DO 0도로 회전
      delay(1000);
      servo_DO.write(90); //DO 90도로 회전
      lcd.clear();
      Serial.println("ok");
      delay(200);
      Serial.println(Serial.read());//파이썬으로 ok 보냄
    }
    else if (c=='r') {
      
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);// 0번 행 6번 열부터 출력합니다.
      lcd.print("Re");    
      delay(2000);
      servo_RE.write(0);  //DO 0도로 회전
      delay(1000);
      servo_RE.write(90); //DO 90도로 회전
      lcd.clear();
      Serial.println("ok");
      delay(200);
      
      
    }
    else if (c == 'm') {
      
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);
      lcd.print("Mi");     
      delay(2000);
      servo_MI.write(90);
      delay(1000);
      servo_MI.write(0);
      lcd.clear();
      Serial.println("ok");
      delay(200);
      Serial.println(Serial.read());
 
    }
    else if (c=='f') {
      
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);// 0번 행 0번 열부터 출력합니다.
      lcd.print("Fa");     
      delay(2000);
      servo_FA.write(90);
      delay(1000);
      servo_FA.write(0);
      lcd.clear();  
      Serial.println("ok");
      delay(200);
      Serial.println(Serial.read()); 
      
      
    }
    else if (c=='s') {
      
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);
      lcd.print("SOl");     
      delay(2000);
      servo_SOL.write(90);
      delay(1000);
      servo_SOL.write(0);
      lcd.clear();
      Serial.println("ok");
      delay(200);
      Serial.println(Serial.read());
      
      
    }
    
    else{
      lcd.setCursor(1,0);
      lcd.print("This Tone is");  
      lcd.setCursor(0,6);
      lcd.print("background");     
      delay(1000);     
      servo_DO.write(90);
      servo_RE.write(0);
      servo_MI.write(0);
      servo_FA.write(0);
      servo_SOL.write(0);
      lcd.clear();  
      Serial.println("ok");
      delay(200);
      Serial.println(Serial.read());
      

  }
  
}}
