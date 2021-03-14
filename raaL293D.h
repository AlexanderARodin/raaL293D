#ifndef RAAL293D_H
#define RAAL293D_H

#include <Arduino.h>
//	############################################################
//	############################################################
//	############################################################
//	############################################################


class BaseL293D{
	byte pinEnable;
	byte pinInput1;
	byte pinInput2;
	
	bool isReversed;
	
	void initPins(){
	}
	
public:
	BaseL293D(){}
	void init(byte _pinEnable, byte _pinInput1, byte _pinInput2, bool _isReversed){
		pinEnable = _pinEnable;
		pinInput1 = _pinInput1;
		pinInput2 = _pinInput2;
		isReversed = _isReversed;
		
		pinMode( pinEnable, OUTPUT );
		pinMode( pinInput1, OUTPUT );
		pinMode( pinInput2, OUTPUT );
	}
	
	void setForward(){
		digitalWrite( pinInput1, isReversed );
		digitalWrite( pinInput2, !isReversed );
	}
	void setBackward(){
		digitalWrite( pinInput2, isReversed );
		digitalWrite( pinInput1, !isReversed );
	}
	void setVelocity(int _velocity){
		analogWrite( pinEnable, _velocity );
	}
	
};

//	############################################################

class L293D :  BaseL293D {
	int motorSpeed;
	int maxSpeed;
	
	void correctMotorSpeed(){
		if(motorSpeed> maxSpeed)motorSpeed= maxSpeed;
		if(motorSpeed<-maxSpeed)motorSpeed=-maxSpeed;
	}
	
public:
	
	L293D():BaseL293D(){
		maxSpeed = 255;
	}
	
	void init(byte _pinEnable, byte _pinInput1, byte _pinInput2, bool _isReversed){
		BaseL293D::init( _pinEnable, _pinInput1, _pinInput2, _isReversed);
	}
	
	void setMotorSpeed( int _motorSpeed){
		motorSpeed = _motorSpeed;
		if(motorSpeed >=0){
			correctMotorSpeed();
			setForward();
			setVelocity(motorSpeed);
		}else{
			correctMotorSpeed();
			setBackward();
			setVelocity(-motorSpeed);
		}
	}
	
	void setMaxSpeed(int _maxSpeed){maxSpeed=_maxSpeed;}
};

//	############################################################
//	############################################################
//	############################################################
//	############################################################
#endif
