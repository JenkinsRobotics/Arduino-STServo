#include <SCServo.h>

SMS_STS sm;

void setup()
{
	Serial1.begin(115200);
	sm.pSerial = &Serial1;
	sm.pwmMode(1);
}

void loop()
{
	sm.WritePWM(1, 500);
	delay(3000);
	sm.WritePWM(1, 0);
	delay(2000);
	sm.WritePWM(1, -500);
	delay(3000);
	sm.WritePWM(1, 0);
	delay(2000);
}
