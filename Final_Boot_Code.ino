#include <Wire.h>
#include <Servo.h>

Servo Spin;
Servo Claw;





long gyroX, gyroY, gyroZ;

float  SpinDegree = 90;
float ClawDegree = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();

  
  Claw.attach(6);
  Spin.attach(9);


  Claw.write(ClawDegree);
  Spin.write(SpinDegree);
  
}




void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}



void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  
}



void printData() {
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(gyroX);
  Serial.print(" Y=");
  Serial.print(gyroY);
  Serial.print(" Z=");
  Serial.println(gyroZ);
 
}

void loop() {
  
  recordGyroRegisters();
  printData();
  
  if(gyroX !=0 & gyroY !=0 & gyroZ !=0){
    digitalWrite(13, HIGH);   
  delay(100);              
  digitalWrite(13, LOW);   
  delay(100); 
  }
  
  
  if((gyroY > 20000) && (SpinDegree == 90) )
 
  {
Serial.println("a");
    SpinDegree = 0;
    for(int i =90; i >= 0; i-=5){
      Spin.write(i);
      delay(30);
    }
 Spin.write(0);
     
  
      delay(100);
  
  
}
else if((gyroY < -20000 && SpinDegree ==0) || (gyroY >10000 && SpinDegree == 180)){
  if(gyroY < -20000 && SpinDegree ==0) {
  Serial.println("b");
  SpinDegree =90;
  for(int i =0; i <= 90; i+=5){
      Spin.write(i);
      delay(30);
    }
 Spin.write(90);
     
  
   



   
  delay(100);
  }  else if (gyroY >10000 && SpinDegree == 180){
     Serial.println("d");
  SpinDegree =90;
   for(int i =180; i >= 90; i-=5){
      Spin.write(i);
      delay(30);
    }
 Spin.write(90);
     
  


   
  delay(100);
    
  }
}
  else if((gyroY < -20000) && (SpinDegree == 90) ){
Serial.println("c");

  //Serial.println("bbB");
      SpinDegree = 180;
       for(int i =90; i <= 180; i+=5){
      Spin.write(i);
      delay(30);
    }
 Spin.write(180);
     
    
     delay(100);
   }

   
    
  
//claw code
  if(gyroZ >30000 )
  
 
  { Serial.print("Claw Open");
  
     Claw.write(90);
     // delay(100);
 
}
  else if(gyroZ < -30000){
   Serial.print("Claw Close");
     
      Claw.write(0);
     // delay(100);
      
   
   }
  delay(100);

  
  
  
  

}