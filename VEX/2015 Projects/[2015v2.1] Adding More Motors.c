#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    Xaccel,         sensorAccelerometer)
#pragma config(Sensor, in3,    Yaccel,         sensorAccelerometer)
#pragma config(Sensor, in4,    Zaccel,         sensorAccelerometer)
#pragma config(Sensor, in5,    line,           sensorLineFollower)
#pragma config(Sensor, in7,    motion,         sensorAnalog)
#pragma config(Sensor, in8,    colorChoice,    sensorAnalog)
#pragma config(Sensor, dgtl1,  sonarY,         sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  sonarX,         sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           shooter1,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           shooter2,      tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           shooter3,      tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           shooter4,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           FL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           BL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          flashlight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//Variables in use during competition
int LIGHT_VALUE = 2500; //The value of light the robot needs or less to shoot
int DELAY_TIME = 100; //Time between detection of ball and shoot
int TIMER = 0;
bool LOCK = false;
bool pressed = false;

//Speed calculator variables
float ANGLE = 51.65725;
float DIMENSION = 365.76;
float DIMENSIONEXTRA = 63.20049;
float RADIUS = 5.08;
int COLOR;
int SHOOTSPEED = 127;

//POSITION CALCULATOR
//Have sonar on each side of robot, consistently measure angle
//Use angle and sonar to angle robot to 0 deg, use sonar for position
//Have preset net position
//Use formulas to find angle and turn
//Use formulas to find distance
//Use kinematic equations to calculate velocity

/*CONTROLLER GUIDE
Need to map launcher, intake
8* buttons will move to player 2 at some point
5D Motion turning 								 6D Intake
5U Confirm launch									 6U Force launch
7U Unlock									 8U No
7L Lock 7R DLock 					8L	Other 8R Button
7D Lift	^					  ^			 8D Sensors
Ch3 Left			|
<Ch4-FL>		<----Ch1>
|					 Ch2 Right
V					  V
*/

//Update task keeps track of time in match on cortex
task update () {
	while (true) {
		wait1Msec(1000);
		TIMER = TIMER + 1;
	}
}

//Check if speed locking is enabled
void setLock () {
	if (vexRT[Btn7L] == 1) {
		LOCK = true;
		} else if (vexRT[Btn7U] == 1) {
		LOCK = false;
	}
}

//Shoot function shoots balls at a specified rate in autonomous
void ushoot (int speed, int time) {
	wait1Msec(DELAY_TIME);
	motor[shooter1] = speed;
	motor[shooter2] = speed;
	motor[shooter3] = speed;
	motor[shooter4] = speed;
	wait1Msec(time);
	motor[shooter1] = 0;
	motor[shooter2] = 0;
	motor[shooter3] = 0;
	motor[shooter4] = 0;
}

//shoot function assigns launcher speed to 127
void shoot() {
	motor[shooter1] = SHOOTSPEED;
	motor[shooter2] = SHOOTSPEED;
	motor[shooter3] = SHOOTSPEED;
	motor[shooter4] = SHOOTSPEED;
}

void autoturn() {
	while (SensorValue[gyro] > 10 || SensorValue[gyro] < -10) {
		if ((SensorValue[gyro] > 10 && SensorValue[gyro] <= 1800) || (SensorValue[gyro] < -1800)) {
			motor[FR] = 127;
			motor[BR] = 127;
			motor[FL] = -127;
			motor[BL] = -127;
		}	else if ((SensorValue[gyro] < -10 && SensorValue[gyro] >= -1800) || (SensorValue[gyro] > 1800)) {
			motor[FR] = -127;
			motor[BR] = -127;
			motor[FL] = 127;
			motor[BL] = 127;
		}
	}
}

int coordX;
int coordY;
int goalX;
int goalY;
int DISTANCE;
void autoturnToGoal() {
	if (COLOR == 0) { //blue
		goalX = DIMENSION + DIMENSIONEXTRA;
		goalY = DIMENSION + DIMENSIONEXTRA;
		coordX = SensorValue[sonarX];
		coordY = SensorValue[sonarY];
		DISTANCE = sqrt(pow((goalX - coordX),2)+pow((goalY - coordY),2));
	} else { //red
	  goalX = -DIMENSIONEXTRA;
		goalY = DIMENSION + DIMENSIONEXTRA;
		coordX = SensorValue[sonarX];
		coordY = SensorValue[sonarY];
		DISTANCE = sqrt(pow((coordX - goalX),2)+pow((coordY - goalY),2));
	}
}

void tank() {
	motor[FL] = vexRT[Ch3];
	motor[BL] = vexRT[Ch3];
	motor[FR] = vexRT[Ch2];
	motor[BR] = vexRT[Ch2];
}

int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;
void tankMecanum() {
	//Create "deadzone" for Y1/Ch3
	if (abs(vexRT[Ch3]) > threshold) {
		Y1 = vexRT[Ch3];
		} else {
		Y1 = 0;
	}
	//Create "deadzone" for X1/Ch4
	if (abs(vexRT[Ch4]) > threshold) {
		X1 = -vexRT[Ch4];
		} else {
		X1 = 0;
	}
	//Create "deadzone" for X2/Ch1
	if (abs(vexRT[Ch1]) > threshold) {
		X2 = -vexRT[Ch1];
		} else {
		X2 = 0;
	}
	//Remote Control Commands
	motor[FR] = Y1 - X2 - X1;
	motor[BR] =  Y1 - X2 + X1;
	motor[FL] = Y1 + X2 + X1;
	motor[BL] =  Y1 + X2 - X1;
}

void tankMotion() {
	if (abs(vexRT[AccelX]) > abs(vexRT[AccelY])) {
		motor[BR] = (-(vexRT[AccelX])) / 2;
		motor[FR] = (-(vexRT[AccelX])) / 2;
		motor[BL] = (vexRT[AccelX]) / 2;
		motor[FL] = (vexRT[AccelX]) / 2;
		} else if (abs(vexRT[AccelY]) >= abs(vexRT[AccelX])) {
		motor[BR] = (-(vexRT[AccelY]));
		motor[FR] = (-(vexRT[AccelY]));
		motor[BL] = (-(vexRT[AccelY]));
		motor[FL] = (-(vexRT[AccelY]));
	}
}

void tankMotionMecanum() {
	if (abs(vexRT[AccelY]) > threshold) {
		Y1 = -(vexRT[AccelY]);
		} else {
		Y1 = 0;
	}
	//Create "deadzone" for X1/Ch4
	if ((abs(vexRT[AccelX]) > threshold) && (vexRT[Btn5DXmtr2] == 0)) {
		X1 = (vexRT[AccelX]);
		} else {
		X1 = 0;
	}
	//Create "deadzone" for X2/Ch1
	if ((abs(vexRT[AccelX]) > threshold) && (vexRT[Btn5DXmtr2] == 1)) {
		X2 = (vexRT[AccelX])/2;
		} else {
		X2 = 0;
	}
	//Remote Control Commands
	motor[FR] = Y1 - X2 - X1;
	motor[BR] =  Y1 - X2 + X1;
	motor[FL] = Y1 + X2 + X1;
	motor[BL] =  Y1 + X2 - X1;
}
////uTurn function assigns turntable speed and direction to joystick X direction
//void uTurn() {
//	motor[turntable] = vexRT[Ch4];
//}

//uShootMotion function assigns launcher speed to Y direction accelerometer
//void uShootMotion() {
//	if (vexRT[AccelY] < 0) {
//		motor[shooter1] = ((-vexRT[AccelY] * 127)/90);
//		motor[shooter2] = ((-vexRT[AccelY] * 127)/90);
//		} else {
//		motor[shooter1] = 0;
//		motor[shooter2] = 0;
//	}
//}

int flashValue = 0;

task flashlightCtrl () { //Control flashlight
	while (true) {
		if (vexRT[Ch2] > 10 && flashValue < 127) {
			flashValue = flashValue + 1;
			motor[flashlight] = flashValue;
			}	else if (vexRT[Ch2] < -10 && flashValue > -1) {
			flashValue = flashValue - 1;
			motor[flashlight] = flashValue;
		}
		wait1Msec(50);
	}
}

//int pos = 0;
//int num = 32;
//task typer () { //A button test
//	pos = 0;
//	clearLCDLine(0);
//	clearLCDLine(1);
//	while (true) {
//		bLCDBacklight = true;
//		num = 32;
//		if (pos < 16) {
//			displayLCDPos(0,pos);
//			while (SensorValue[lever] == 0) {
//				displayNextLCDChar(num);
//				displayLCDPos(0,pos);
//				wait1Msec(50);
//				if (SensorValue[button] == 1 && (num < 90 && num >= 65)) {
//					num = num + 1;
//					while (SensorValue[button] == 1) {
//					}
//					}	else if (SensorValue[button] == 1 && (num >= 90 || num < 65)) {
//					num = 65;
//					while (SensorValue[button] == 1) {
//					}
//				}
//			}
//			pos = pos + 1;
//			while (SensorValue[lever] == 1) {
//			}
//			} else if (pos < 32) {
//			displayLCDPos(1,pos - 16);
//			while (SensorValue[lever] == 0) {
//				displayNextLCDChar(num);
//				displayLCDPos(1,pos - 16);
//				wait1Msec(50);
//				if (SensorValue[button] == 1 && (num < 90 && num >= 65)) {
//					num = num + 1;
//					while (SensorValue[button] == 1) {
//					}
//					}	else if (SensorValue[button] == 1 && (num >= 90 || num < 65)) {
//					num = 65;
//					while (SensorValue[button] == 1) {
//					}
//				}
//			}
//			pos = pos + 1;
//			while (SensorValue[lever] == 1) {
//			}
//			} else {
//			pos = 0;
//			clearLCDLine(0);
//			clearLCDLine(1);
//		}
//	}
//}

//task music () {
//	while (true) {
//		if(bSoundQueueAvailable)  // if there is still space in the Sound Queue:
//		{
//			playImmediateTone(abs(SensorValue[sonar])/4, 50);  // play tone according to sensor readings
//			wait1Msec(500);
//		}
//	}
//}

//Debug task alerts user of robot shooters active
task debug () {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;									// Turn on LCD Backlight
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "FIRING!!! %3d", TIMER);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		string display2;
		sprintf(display2, "C3:%4d  C2:%4d", vexRT[Ch3], vexRT[Ch2]);
		displayNextLCDString(display2);
	}
}

////debugMotion task alerts user of robot shooters active with accelerometer
//task debugMotion () {
//	clearLCDLine(0);
//	clearLCDLine(1);
//	while (true) {
//		bLCDBacklight = true;									// Turn on LCD Backlight
//		displayLCDPos(0,0);
//		string display1;
//		sprintf(display1, "FIRING!!! %3d", TIMER);
//		displayNextLCDString(display1);
//		displayLCDPos(1,0);
//		string display2;
//		sprintf(display2, "CtrlAcc:%4d", vexRT[AccelY]);
//		displayNextLCDString(display2);
//	}
//}

//Debug2 task alerts user of lift mechanism activating
task debug2 () {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;									// Turn on LCD Backlight
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "LIFTING!!! %3d", TIMER);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		string display2;
		sprintf(display2, "C3:%4d  C2:%4d", vexRT[Ch3], vexRT[Ch2]);
		displayNextLCDString(display2);
	}
}

//NoDebug task alerts user of game time and battery level
task nodebug () {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;									// Turn on LCD Backlight
		string mainBattery;
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "TIMER: %3d", TIMER);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		displayNextLCDString("Battery : ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);
	}
}

//ButtonDebug task alerts user of joystick values
task buttonDebug() {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "C4:%4d  C1:%4d", vexRT[Ch4], vexRT[Ch1]);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		string display2;
		sprintf(display2, "C3:%4d  C2:%4d", vexRT[Ch3], vexRT[Ch2]);
		displayNextLCDString(display2);
	}
}

//SensorDebug task alerts user of gyro/accelerometer values
task sensorDebug() {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "G: %4d  X: %4d", (SensorValue[gyro]/10), SensorValue[Xaccel]);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		string display2;
		sprintf(display2, "Y: %4d  Z: %4d", SensorValue[Yaccel], SensorValue[Zaccel]);
		displayNextLCDString(display2);
	}
}

//OtherDebug task alerts user of line sensor and motor values
task otherDebug() {
	clearLCDLine(0);
	clearLCDLine(1);
	while (true) {
		bLCDBacklight = true;
		displayLCDPos(0,0);
		string display1;
		sprintf(display1, "Line : %9d", SensorValue[line]);
		displayNextLCDString(display1);
		displayLCDPos(1,0);
		string display2;
		sprintf(display2, "S1:%4d  S2:%4d", motor[shooter1], motor[shooter2]);
		displayNextLCDString(display2);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

//Pre_auton is used to reset sensor values for accuracy
void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;
	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
	SensorType[gyro] = sensorNone;
	SensorType[line] = sensorNone;
	SensorType[Xaccel] = sensorNone;
	SensorType[Yaccel] = sensorNone;
	SensorType[Zaccel] = sensorNone;
	wait1Msec(1000);
	//Reconfigure sensors and allow time for ROBOTC to calibrate it
	SensorType[gyro] = sensorGyro;
	SensorType[line] = sensorLineFollower;
	SensorType[Xaccel] = sensorAccelerometer;
	SensorType[Yaccel] = sensorAccelerometer;
	SensorType[Zaccel] = sensorAccelerometer;
	wait1Msec(2000);
	displayLCDPos(0,0);
	displayNextLCDString("CALIBRATED");
	wait1Msec(1000);
	startTask(sensorDebug);
	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

//Autonomous tracks line sensor to know when it has a ball, then fires it
task autonomous() {
	stopTask(sensorDebug);
	motor[BL] = 127;
	motor[BR] = 127;
	motor[FL] = 127;
	motor[FR] = 127;
	wait1Msec(6000);
	motor[BL] = 0;
	motor[BR] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
	motor[shooter1] = 127;
	motor[shooter2] = 127;
	motor[shooter3] = 127;
	motor[shooter4] = 127;
	motor[intake] = 127;
	wait1Msec(5000);
	for (int i = 127; i >= 0; i--) {
		motor[shooter1] = i;
		motor[shooter2] = i;
		motor[shooter3] = i;
		motor[shooter4] = i;
	}
	motor[intake] = 0;
	motor[BL] = -127;
	motor[BR] = -127;
	motor[FL] = -127;
	motor[FR] = -127;
	wait1Msec(2000);
	motor[BL] = 0;
	motor[BR] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
	//while (true) {
	//	if (SensorValue[line] <= LIGHT_VALUE) { //Check if it has a ball
	//		stopTask(nodebug);
	//		startTask(debug); // Alert user of firing
	//		ushoot(127,4000); //Fire ball
	//		//stopTask(debug);
	//	}
	//	else {
	//		stopTask(debug); //Alert user of not firing
	//		startTask(nodebug);
	//	}
	//}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

//User control handles main movement and debugging
task usercontrol() {
	if (SensorValue[colorChoice] == 0) {
		COLOR = 0; //BLUE
	} else {
	  COLOR = 1; //RED
	}
	//startTask(music); //Sound fun
	startTask(update); //Begin clock
	startTask(flashlightCtrl); //Begin flashlight control
	while (true) {
		setLock(); //Check to see if speed lock enabled
		if (vexRT[Btn8D] == 1) {
			autoturn();
		}
		if (LOCK == true) {
			if (vexRT[Btn7R] == 1) {
				if (SensorValue[motion] == 0) {
					tankMotionMecanum();
					} else {
					tankMecanum();
				}
			}
			}	else {
			if (SensorValue[motion] == 0) {
				tankMotionMecanum();
				} else {
				tankMecanum();
			}
		}
		//uTurn(); //Check to see if it should turn
		if (SensorValue[line] <= LIGHT_VALUE) { //Check line sensor value to shoot
			if (vexRT[Btn5UXmtr2] == 1) { //Button needed to confirm
				stopTask(nodebug);
				stopTask(buttonDebug);
				stopTask(sensorDebug);
				stopTask(otherDebug);
				stopTask(debug2);
				//stopTask(typer);
				startTask(debug);
				shoot();
				pressed = true;
			}
		}
		if ((vexRT[Btn5UXmtr2] == 0) && (vexRT[Btn6U] == 0) && (pressed == true)) { //Turn off shooters
			for (int i = 127; i >= 0; i--) {
				motor[shooter1] = i;
				motor[shooter2] = i;
				motor[shooter3] = i;
				motor[shooter4] = i;
			}
			pressed = false;
		}
		if (vexRT[Btn5U] == 1) {
			motor[intake] = 127;
		}
		else if (vexRT[Btn5D] == 1) {
			motor[intake] = -127;
		}
		else if (vexRT[Btn5U] == 0) {
			motor[intake] = 0;
		}
		if (vexRT[Btn6U] == 1) { //Failsafe if sensor breaks
			stopTask(nodebug);
			stopTask(buttonDebug);
			stopTask(sensorDebug);
			stopTask(otherDebug);
			stopTask(debug2);
			//stopTask(typer);
			startTask(debug);
			shoot();
			pressed = true;
		}
		else if (vexRT[Btn7D] == 1 && TIMER >= 100) { //Activate lift only at end
			stopTask(nodebug);
			stopTask(buttonDebug);
			stopTask(sensorDebug);
			stopTask(otherDebug);
			stopTask(debug);
			//stopTask(typer);
			startTask(debug2);
		}
		else if (vexRT[Btn8U] == 1 || nLCDButtons == 1){ //Begin NoDebug task
			stopTask(debug);
			stopTask(buttonDebug);
			stopTask(sensorDebug);
			stopTask(otherDebug);
			stopTask(debug2);
			//stopTask(typer);
			startTask(nodebug);
		}

		else if (vexRT[Btn8R] == 1 || nLCDButtons == 2) { //Begin ButtonDebug task
			stopTask(debug);
			stopTask(nodebug);
			stopTask(sensorDebug);
			stopTask(otherDebug);
			stopTask(debug2);
			//stopTask(typer);
			startTask(buttonDebug);
		}
		else if (vexRT[Btn8DXmtr2] == 1 || nLCDButtons == 4) { //Begin SensorDebug task
			stopTask(debug);
			stopTask(nodebug);
			stopTask(otherDebug);
			stopTask(buttonDebug);
			stopTask(debug2);
			//stopTask(typer);
			startTask(sensorDebug);
		}
		else if (vexRT[Btn8L] == 1 || nLCDButtons == 3) { //Begin OtherDebug task

	stopTask(debug);
			stopTask(nodebug);
			stopTask(buttonDebug);
			stopTask(sensorDebug);
			stopTask(debug2);
			//stopTask(typer);
			startTask(otherDebug);
		}
		else if (nLCDButtons == 7) {
			stopTask(debug);
			stopTask(nodebug);
			stopTask(buttonDebug);
			stopTask(sensorDebug);
			stopTask(debug2);
			stopTask(otherDebug);
			//startTask(typer);
		}
	}
}