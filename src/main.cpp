#include "main.h"

//motor port variables. Number corresponding to what number port on the brain the motor is plugged into
//these variables are given values in initialize()
int portL1;
int portL2;
int portL3;
int portL4;
int portR1;
int portR2;
int portR3;
int portR4;

//determines kind of control arcade or tank. Variable explained further where it's declared
//this variable is given a value in initialize()
bool arcadeOrTank;

//variables to determine voltage of right and left motors. The v stands for voltage
//these variables are given values in opcontrol(), in the while loop inside the if(arcadeOrTank == ?) statements
//voltage can vary from -127 to 127. The further from 0 the faster the motor turns.
int vL;
int vR;



/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	/*
	Gives every single variable a value
	*/
	//initializing all the drive motor ports
	portL1 = 14;
	portL2 = 13;
	portL3 = 12;
	portL4 = 11;
	portR1 = 17;
	portR2 = 18;
	portR3 = 19;
	portR4 = 20;

	//When arcadeOrTank = true, the left joystick moves robot forward backward and right joystick turns robot
	//when arcadeOrTank = false, the left joystick controls the left 4 motors and the right joystick controls the right 4 motors
	arcadeOrTank = true;
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	/*
	the parameters are as follows: (port number, gearset, direction)
	you can change direction by changing the bool true or false
	we want motors to alternate directions so gears work!
	L1 should be opposite direction of L2
	*/
	pros::Motor L1(portL1, MOTOR_GEAR_BLUE, false);
	pros::Motor L2(portL2, MOTOR_GEAR_BLUE, true);
	pros::Motor L3(portL3, MOTOR_GEAR_BLUE, false);
	pros::Motor L4(portL4, MOTOR_GEAR_BLUE, true);

	pros::Motor R1(portR1, MOTOR_GEAR_BLUE, false);
	pros::Motor R2(portR2, MOTOR_GEAR_BLUE, true);
	pros::Motor R3(portR3, MOTOR_GEAR_BLUE, false);
	pros::Motor R4(portR4, MOTOR_GEAR_BLUE, true);

	pros::Controller master(pros::E_CONTROLLER_MASTER);
	

	while (true) {
		//not entirely sure what this does but make sure you keep it! It was in the default pros setup.
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);


		//arcade mode. Turn by moving right joystick left or right
		if (arcadeOrTank == true)
		{
			//detects how much you moved the left joystick up/down
			int power = master.get_analog(ANALOG_LEFT_Y);
			//detects how much you moved the right joystick left/right
			int turn = master.get_analog(ANALOG_RIGHT_X);
			//determines how the motors will move
			int vL = power + turn;
			int vR = power - turn;
		}
		//tank mode. Turn by moving one joystick up and down less than the other
		else if (arcadeOrTank == false)
		{
			//detects how much you moved the left and right joysticks up and down. 
			int vL = master.get_analog(ANALOG_LEFT_Y);
			int vR = master.get_analog(ANALOG_RIGHT_Y);
		}

		//moves left motors
		L1.move(vL);
		L2.move(vL);
		L3.move(vL);
		L4.move(vL);

		//moves right motors
		R1.move(vR);
		R2.move(vR);
		R3.move(vR);
		R4.move(vR);

		//slows down the code so the brain isn't overwhelmed
		pros::delay(20);
	}
}
