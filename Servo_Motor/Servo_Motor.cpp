#include <Servo_Motor.h>
#include <Sailboat.h>

void Servo_Motor::init(ros::NodeHandle* n){
	motorSetup();

	// Set the rudder at the Neutral position
	motorWrite(pwmNeutral);

	ActuatorROS::init(n);
}

void Servo_Motor::applyCommand(double command){
	unsigned int commandExact = pwmNeutral;
    if(command > anglemax)
        command = anglemax;
    if(command < anglemin)
        command = anglemin;
	

	// Generates the exact command:
	commandExact = mapf(command, anglemin, anglemax, pwmMin, pwmMax);
//	Logger::Log(0, F("MotorCommandExact"), String(commandExact));

	// Set the servo at the wanted position:
	motorWrite(commandExact);
    //Sailboat::Instance()->publishMsg("CommandExact: " + (String)commandExact);

    lastPwm = command*DEG_TO_RAD;

	if (anglemax > 45.00) {
		//Sailboat::Instance()->publishMsg(String("From Sail : max: ") + String(anglemax) + String(", min: ") + String(anglemin) + String(", cmd: ") + String(command) + String(", cmdEX: ") + String(commandExact));
		//Serial.println("Sail:		angleMax: " + String(anglemax) + ", angleMin: " + String(anglemin) + ", command: " + String(command) + String(", commandExact: ") + String(commandExact));
	} else {
		Sailboat::Instance()->publishMsg(String("From Rudder : max: ") + String(anglemax) + String(", min: ") + String(anglemin) + String(", cmd: ") + String(command) + String(", cmdEX: ") + String(commandExact));
		//Serial.println("Rudder:		angleMax: " + String(anglemax) + ", angleMin: " + String(anglemin) + ", command: " + String(command) + String(", commandExact: ") + String(commandExact));
	}
}

void Servo_Motor::communicateData(){
	msg.data = lastPwm;
	pub.publish(&msg);
}
