#include "main.h"
#include <iostream>
using namespace std; //so I can use strings cuz they're nice for debugging
/*
Drive System Stuff
*/
static int portL1 = 14; //all 8 motor port variables
static int portL2 = 13; //port variables are unnecessary but make it easier to see what each port is.  
static int portL3 = 12;
static int portL4 = 11;
static int portR1 = 17;
static int portR2 = 18;
static int portR3 = 19;
static int portR4 = 20;
pros::Motor L1(portL1, MOTOR_GEAR_BLUE, false); //all 8 drive motors
pros::Motor L2(portL2, MOTOR_GEAR_BLUE, true);
pros::Motor L3(portL3, MOTOR_GEAR_BLUE, false);
pros::Motor L4(portL4, MOTOR_GEAR_BLUE, true);
pros::Motor R1(portR1, MOTOR_GEAR_BLUE, true);
pros::Motor R2(portR2, MOTOR_GEAR_BLUE, false);
pros::Motor R3(portR3, MOTOR_GEAR_BLUE, true);
pros::Motor R4(portR4, MOTOR_GEAR_BLUE, false);

//shortens the code later down, potentially can be used for autonomous code later?
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
End of Drive System Stuff 
*/


//only is so you can display numbers on brain screen for debugging purposes
void initialize() {
	pros::lcd::initialize();	
}

//probably won't use this, but don't delete it or pros might get angry.
void disabled() {}
void competition_initialize() {}

//runs auton code. If you want to test without the competition switch active you can do autonomous() inside opcontrol or initialize
void autonomous() 
{

}

//this function runs during driver control period. 
void opcontrol() {
	//makes sure you get controller inputs
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	int vL;
	int vR; //The v stands for voltage, can vary from -127 to 127. The further from 0 the faster the motor turns.
	while (true) {		
		//gets input from controller, cuts the value in half and makes the motors move at that speed.  
		vL = master.get_analog(ANALOG_LEFT_Y);
		vR = master.get_analog(ANALOG_RIGHT_Y);
		vL = int(vL/2);
		vR = int(vR/2);		
		moveLeftMotors(vL);
		moveRightMotors(vR); //moves the drive system motors :)

		pros::delay(20); //slows down code so brain doesn't kill itself :)

		//for debugging purposes
		pros::lcd::set_text(1,"Left speed: " + to_string(vL));
		pros::lcd::set_text(2,"Right Speed: " + to_string(vR));
	}
}


