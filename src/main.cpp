#include "main.h"
#include <iostream>
using namespace std; //so I can use strings cuz they're nice for debugging
int robotNumber = 0; //0 = code bot, 1 = robot 1, 2 = robot 2

/*
Drive System Stuff
*/
int portL1;
int portL2;
int portL3;
int portL4;
int portR1;
int portR2;
int portR3;
int portR4;
pros::Motor L1(portL1, MOTOR_GEAR_BLUE, false); //all 8 drive motors
pros::Motor L2(portL2, MOTOR_GEAR_BLUE, true);
pros::Motor L3(portL3, MOTOR_GEAR_BLUE, false);
pros::Motor L4(portL4, MOTOR_GEAR_BLUE, true);
pros::Motor R1(portR1, MOTOR_GEAR_BLUE, true);
pros::Motor R2(portR2, MOTOR_GEAR_BLUE, false);
pros::Motor R3(portR3, MOTOR_GEAR_BLUE, true);
pros::Motor R4(portR4, MOTOR_GEAR_BLUE, false);
int lDriveVoltage;
int rDriveVoltage; //can vary from -127 to 127. The further from 0 the faster the motor turns.
void moveLeftMotors (int voltage)
{
	L1.move(voltage);
	L2.move(voltage);
	L3.move(voltage);
	L4.move(voltage);
}
void moveRightMotors (int voltage)
{
	R1.move(voltage);
	R2.move(voltage);
	R3.move(voltage);
	R4.move(voltage);
}

/*
Intake Stuff
*/
int portI1;
int portI2;
int intakeVoltage = 80;
pros::Motor I1(portI1, MOTOR_GEAR_GREEN, false);
pros::Motor I2(portI2, MOTOR_GEAR_GREEN, true);

/*
Shooter Stuff
*/
int portS1;
int portS2;
int shooterVoltage = 120;
pros:: Motor S1(portS1, MOTOR_GEAR_BLUE, false);
pros:: Motor S2(portS2, MOTOR_GEAR_BLUE, true);

/*
Gives all the ports a value, based on what the robotNumber is.
Robot number 0 = test bot
Robot number 1 = main robot 1
Robot number 2 = main robot 2
*/
void initialize() {
	pros::lcd::initialize();	

	if (robotNumber == 0)
	{
		pros::lcd::set_text(1, "Test Robot");
		portL1 = 14; //all 8 motor port variables
		portL2 = 8; //port variables are unnecessary but make it easier to see what each port is.  
		portL3 = 10;
		portL4 = 3;
		portR1 = 17;
		portR2 = 6;
		portR3 = 7;
		portR4 = 18;
		portI1 = 1; //intake
		portI2 = 2;
		portS1 = 4; //shooter
		portS2 = 5;
	}
	if (robotNumber == 1)
	{
		pros::lcd::set_text(1, "Robot 1");
		portL1 = 14; //all 8 motor port variables
		portL2 = 8; //port variables are unnecessary but make it easier to see what each port is.  
		portL3 = 10;
		portL4 = 3;
		portR1 = 17;
		portR2 = 6;
		portR3 = 7;
		portR4 = 18;
		portI1 = 1; //intake
		portI2 = 2;
		portS1 = 4; //shooter
		portS2 = 5;
	}
	if (robotNumber == 2)
	{
		pros::lcd::set_text(1, "Robot 2");
		portL1 = 14; //all 8 motor port variables
		portL2 = 8; //port variables are unnecessary but make it easier to see what each port is.  
		portL3 = 10;
		portL4 = 3;
		portR1 = 17;
		portR2 = 6;
		portR3 = 7;
		portR4 = 18;
		portI1 = 1; //intake
		portI2 = 2;
		portS1 = 4; //shooter
		portS2 = 5;
	}
}

//probably won't use this, but don't delete it or pros might get angry.
void disabled() {}
void competition_initialize() {}

//runs auton code. If you want to test without the competition switch active you can do autonomous() inside opcontrol or initialize
void autonomous() 
{

}

//exponentialControl made by ChatGPT, not sure if it works will test later!
int exponentialControl(int joystickValue)
{
	// Check if joystick value is within deadband threshold
	if (std::abs(joystickValue) < 10) {
		// Set motor speed to zero when joystick value is close to zero
		return 0;
	} 
	else {
	// Convert joystick value to a range of -1 to 1
		double normalizedValue = static_cast<double>(joystickValue) / 127.0;

		// Calculate the exponential increase
		double v = std::pow(std::abs(normalizedValue), 2.0);

		// Scale the speed value to the motor range (-127 to 127)
		v = v * 127;
		int intV = (int) v;
		// Set the motor speed
		return intV;
	}
}
//this function runs during driver control period. 
void opcontrol() {
	//makes sure you get controller inputs
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	while (true) {		
		//gets input from controller, cuts the value in half and makes the motors move at that speed.  
		lDriveVoltage = master.get_analog(ANALOG_LEFT_Y);
		rDriveVoltage = master.get_analog(ANALOG_RIGHT_Y);

		//potential exponential control? ChatGPT made it so not sure how good it is
		//lDriveVoltage = exponentialControl(lDriveVoltage);
		//rDriveVoltage = exponentialControl(rDriveVoltage);
		lDriveVoltage = int(lDriveVoltage/2);
		rDriveVoltage = int(rDriveVoltage/2);		
		moveLeftMotors(lDriveVoltage);
		moveRightMotors(rDriveVoltage); //moves the drive system motors :)

		//intake is the L1 button
		if (master.get_digital(DIGITAL_L1)){
			I1.move(intakeVoltage);
			I2.move(intakeVoltage);
		}
		else {
			I1.move(0);
			I2.move(0);
		}

		//shooter is the R1 button
		if (master.get_digital(DIGITAL_R1)){
			S1.move(shooterVoltage);
			S2.move(shooterVoltage);
		}
		else{
			S1.move(0);
			S2.move(0);
		}

		pros::delay(20); //slows down code so brain doesn't kill itself :)
	}
}


