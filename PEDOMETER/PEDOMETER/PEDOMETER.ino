#include <Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;
float x[]={};
long magx,magy,magz;
int step_count=0;
float calorie=0;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  setupmpu();
   
}

void setupmpu(){
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);//accelerometer
  Wire.write(0b00000000);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.beginTransmission(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission();
  
  
}
void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0; 
  gForceZ = accelZ / 16384.0;
}

void recordgyroRegisters(){
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
  while(Wire.available()<6);
   gyroX =Wire.read()<<8|Wire.read();
   gyroY=Wire.read()<<8|Wire.read();
   gyroZ= Wire.read()<<8|Wire.read();
   processGyroData();
}

void processGyroData(){
  rotX=gyroX/131.0;
  rotY=gyroY/131.0;
  rotZ=gyroZ/131.0;
  for (int i=0;i<sizeof(x)/sizeof(x[0]);i++){
    int j = rotX;
    x[i]=j;
    
  }
}

void printData() {
  //Serial.print("Gyro (deg)");
  //Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(",");
   
  //Serial.print(" Y=");
 /* if (rotX > 75){
      step_count = step_count+1; 
      calorie=calorie+0.068; 
    }
    if(rotX < -20){
      step_count =step_count+1;
      calorie=calorie+0.068;
      
    }
   //Serial.print("; `");
    Serial.print(step_count);
    Serial.print(" ,");
   Serial.println(calorie);%//
  
  
 /** Serial.print(",");
  Serial.print(rotY);
  //Ser ial.print(" Z=");
  Serial.print(",");
  Serial.print(rotZ);
  Serial.print(",");//Serial.print(" Accel (g)");
  //Serial.print(" X=");
  
  Serial.print(gForceX);
  Serial.print(",");
  //Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(",");
  //Serial.print(" Z=");
  Serial.println(gForceZ);
*/

}

void loop() {
  recordAccelRegisters();
  recordgyroRegisters();
  printData();
  delay(300);}  
  
 
