#include <raaDBG.h>

#include <raaL293D.h>



L293D motorThr;
L293D motorYaw;

void setup() {
	delay(200);
	Serial.begin(115200);
	msg("\n\n\n\n#################\n"
					"# >> Started << #\n"
					"#################\n\n");
	
	motorYaw.init( 6, 5, 4, false );
	motorThr.init( 9, 8, 7, false );
	
}

void loop() {
	static float anAngle = 0;
	dbg( String(anAngle) );
	motorThr.setMotorSpeed(300* sin(anAngle));
	motorYaw.setMotorSpeed(300* cos(anAngle));
	anAngle += 0.03;
	delay(75);
}
