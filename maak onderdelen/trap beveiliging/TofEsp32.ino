#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

// set the pins to shutdown
#define SHT_LOX1 18
#define SHT_LOX2 19
#define SHT_LOX3 23

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setup(){
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial){
    delay(1);
  }
  Serial.println(F("serial port opened\n"));
  setID();
  
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}

void loop(){  
  Serial.print("Reading a measurement... ");

  int distance_total_1 = 0;
  int distance_total_2 = 0;
  int distance_total_3 = 0;
  int max_dis_1 = 0;
  int max_dis_2 = 0;
  int max_dis_3 = 0;
  int min_dis_1 = 1201;
  int min_dis_2 = 1201;
  int min_dis_3 = 1201;
  
  for (int i = 0; i < 6; i++){
    lox1.rangingTest(&measure1, false);
    lox2.rangingTest(&measure2, false);
    lox3.rangingTest(&measure3, false);
    
    if (measure1.RangeStatus != 4){ // phase failures have incorrect data
      distance_total_1 = distance_total_1 + measure1.RangeMilliMeter;
      distance_total_2 = distance_total_2 + measure2.RangeMilliMeter;
      distance_total_3 = distance_total_3 + measure3.RangeMilliMeter;
      
      if(measure1.RangeMilliMeter < min_dis_1){
        min_dis_1 = measure1.RangeMilliMeter;
      }
      if(measure2.RangeMilliMeter < min_dis_2){
        min_dis_2 = measure2.RangeMilliMeter;
      }
      if(measure3.RangeMilliMeter < min_dis_3){
        min_dis_3 = measure3.RangeMilliMeter;
      }
      
      if(measure1.RangeMilliMeter > max_dis_1){
        max_dis_1 = measure1.RangeMilliMeter;
      }
      if(measure2.RangeMilliMeter > max_dis_2){
        max_dis_2 = measure2.RangeMilliMeter;
      }
      if(measure3.RangeMilliMeter > max_dis_3){
        max_dis_3 = measure3.RangeMilliMeter;
      }
    }
    else{
      Serial.println(" out of range ");
    }
  }
  distance_total_1 = distance_total_1 - min_dis_1 - max_dis_1;
  distance_total_2 = distance_total_2 - min_dis_2 - max_dis_2;
  distance_total_3 = distance_total_3 - min_dis_3 - max_dis_3;
  Serial.print("Distance sensor 1 (mm): "); Serial.println(distance_total_1 / 4);
  Serial.print("Distance sensor 2 (mm): "); Serial.println(distance_total_2 / 4);
  Serial.print("Distance sensor 3 (mm): "); Serial.println(distance_total_3 / 4);
}

void setID() {
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  // all unreset
  Serial.println(F("all low\n"));
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);
  Serial.println(F("all high\n"));

  // activating LOX1 and resetting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  Serial.println(F("setting 1\n"));

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);
  Serial.println(F("1 set\n"));
  
  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);
  Serial.println(F("setting 2\n"));
  //initing LOX2
  if(!lox2.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);
  Serial.println(F("2 set\n"));

  // activating LOX3
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);
  Serial.println(F("setting 3\n"));
  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
  Serial.println(F("3 set\n"));
}
