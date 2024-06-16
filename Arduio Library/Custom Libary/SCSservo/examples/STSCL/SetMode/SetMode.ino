// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 16
#define S_TXD 17

#include <SCServo.h>

//int SERVO_TYPE_SELECT = 2;

// 定义SC总线舵机的ID
const byte servoID = 2;

// 定义伺服模式和电机模式的常量
const byte SERVO_MODE = 0;
const byte MOTOR_MODE = 1;

// 初始化舵机驱动
SMS_STS st;

void setup()
{
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  st.pSerial = &Serial1;
  delay(1000);
}

void servo()
{
  setMode(servoID, SERVO_MODE);
  st.WritePosEx(servoID, 4095, 3400, 50);//servo(ID1) speed=3400，acc=50，move to position=4095.
  delay(5000);
  st.WritePosEx(servoID, 2000, 1500, 50);//servo(ID1) speed=3400，acc=50，move to position=2000.
  delay(5000);
}

void motor()
{
  setMode(servoID, MOTOR_MODE);
  st.WriteSpe(servoID, 3400, 100); //The servo (ID1) rotates at the maximum speed V=2000 steps/second, acceleration A=100 (100*100 steps/second^2)
  delay(5000);
  st.WriteSpe(servoID, -3400, 100);//舵机(ID1)以最高速度V=2000步/秒，加速度A=100(100*100步/秒^2)，旋转
  delay(5000);
}

void setMode(byte InputID, byte InputMode){
	// Modes: 0 (servo mode), 1 (closed-loop) wheel mode
  st.unLockEprom(InputID);
  if (InputMode == 0) {
      st.writeWord(InputID, 11, 4095);
      st.writeByte(InputID, SMS_STS_MODE, InputMode);
  } 
  else if (InputMode == 1) {
      st.writeByte(InputID, SMS_STS_MODE, InputMode);
      st.writeWord(InputID, 11, 0);
  }
  st.LockEprom(InputID);
}

void stopMotor(byte InputID) {
  st.EnableTorque(servoID, 0);
  delay(10);
  st.EnableTorque(servoID, 1);
}



void loop() {
  //Servo(ID1)  forward: 10-1000; reverse: (10-1000)+1024; stop: 0; unit:0.10%; 
  //The servo moves at 50% speed in the forward direction.
  servo();
  delay(2000);
   motor();
  delay(2000);
  stopMotor(servoID);
  delay(2000);
}