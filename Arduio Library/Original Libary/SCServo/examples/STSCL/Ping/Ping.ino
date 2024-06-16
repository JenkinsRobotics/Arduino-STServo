/*
Ping the servo to check if it is ready.
*/

#include <SCServo.h>

SMS_STS sms_sts;
// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 16
#define S_TXD 17

int TEST_ID = 0;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  sms_sts.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int ID = sms_sts.Ping(TEST_ID);
  if(ID!=-1){
    Serial.print("Servo ID:");
    Serial.println(ID, DEC);
    delay(100);
    TEST_ID++;

  }else{
        Serial.print(TEST_ID);

    Serial.println("Ping servo ID error!");
    delay(200);
    TEST_ID++;
  }
  if (TEST_ID>=260){TEST_ID=0;}
}