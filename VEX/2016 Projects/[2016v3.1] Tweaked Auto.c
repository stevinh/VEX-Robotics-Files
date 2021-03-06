#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    clawEnc,        sensorPotentiometer)
#pragma config(Sensor, in2,    liftEnc,        sensorPotentiometer)
#pragma config(Sensor, in3,    gyro,           sensorGyro)
#pragma config(Sensor, in8,    betaTest,       sensorAnalog)
#pragma config(Sensor, dgtl1,  quadEnc,        sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  rightWheelEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftWheelEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           BR,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           liftTR,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftMR,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           clawL,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           clawR,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           liftML,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           liftTL,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          BL,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
#include "SongTasks.c" //Songs to be used in the program

int testVar = 1;
//int lspeed;
//int rspeed;
int time2 = 0;
string line1 = "1: Side stars";
string line2;
int mode = 0;
int mode2 = 0;
bool locked = true;
string linee1, linee2;
string mainBattery, backupBattery;

int automode = 1;
string side = "Left";
int turnDir = -1;
bool ready = false;
bool pressed = false;

int deadzone3;
int deadzone2;
int limit = 0;

int auSpeed = 25;
int debugSpeed = 50;
int driveEncVal = 400; //For one square
int turnLeftEncVal = 400; //For 90 deg IGNORE
int turnRightEncVal = 400; //For 90 deg IGNORE
int liftEncVal = 1700; //For one full lift (135 deg)
int minLift = 750;
//730 min, 2900 max
//730 + 1700 = 2430
//2900 - 730 = 2170 degrees of freedom for 135 degrees
int clawEncVal = 2900; //For 180 deg
int minClaw = 200; //3250 - 200 = 3050 degrees of freedom for 180 deg
int turnSpeed = 50; //For auto
int liftSpeed = 100; //For auto
int clawSpeed = 127; //For auto

//DRIVING - COMPLETE
//TURNING - COMPLETE
//LIFTING - COMPLETE
//CLAWING - COMPLETE?

//MODE 1 - COMPLETE, FIX SLOW TURN
//MODE 2 - COMPLETE, KINDA SKETCH BUT WORKS
//MODE 3 - COMPLETE, CHECK IF FULL POWER HELPS OR HURTS CUBE
//MODE 4
//MODE 5

float voltage = nImmediateBatteryLevel;

//bool click = false;
//bool check = false;
//int seed = 0;
//int step = 1;
//int timeleft = 15000;
//int timechosen;

//void setRandomSeed() {
//	clearLCDLine(0);
//	clearLCDLine(1);
//	check = false;
//	click = false;
//	while (check == false) {
//		bLCDBacklight = true;									// Turn on LCD Backlight
//		displayLCDPos(0,0);
//		string display1;
//		sprintf(display1, "SET RANDSEED");
//		displayNextLCDString(display1);
//		displayLCDPos(1,0);
//		string display2;
//		sprintf(display2, "SEED: %4d", seed);
//		displayNextLCDString(display2);
//		if (nLCDButtons == 1 && click == false) {
//			click = true;
//			seed = seed - 1;
//		} else if (nLCDButtons == 4 && click == false) {
//			click = true;
//			seed = seed + 1;
//		} else if (nLCDButtons == 2) {
//			check = true;
//		} else if (nLCDButtons == 0 && click == true) {
//			click = false;
//		}
//	}
//	clearLCDLine(0);
//	clearLCDLine(1);
//	bLCDBacklight = true;									// Turn on LCD Backlight
//	displayLCDPos(0,0);
//	string display1;
//	sprintf(display1, "RANDSEED SET!");
//	displayNextLCDString(display1);
//	displayLCDPos(1,0);
//	string display2;
//	sprintf(display2, "SEED: %4d", seed);
//	displayNextLCDString(display2);
//}

//void dumbAutonomous() {
//	srand(seed);
//	timeleft = 15000;
//	startTask(smb3);
//	while (timeleft > 0) {
//		clearLCDLine(0);
//		clearLCDLine(1);
//		bLCDBacklight = true;									// Turn on LCD Backlight
//		displayLCDPos(0,0);
//		string display1;
//		sprintf(display1, "RANDAUTO");
//		displayNextLCDString(display1);
//		displayLCDPos(1,0);
//		string display2;
//		sprintf(display2, "STEP: %2d", step);
//		displayNextLCDString(display2);
//		lspeed = random(254) - 127;
//		rspeed = random(254) - 127;
//		motor[BL] = lspeed;
//		motor[FL] = lspeed;
//		motor[BR] = rspeed;
//		motor[FR] = rspeed;
//		timechosen = random(timeleft);
//		timeleft = timeleft - timechosen;
//		wait1Msec(timechosen);
//		step = step + 1;
//	}
//	motor[BL] = 0;
//	motor[FL] = 0;
//	motor[BR] = 0;
//	motor[FR] = 0;
//	clearLCDLine(0);
//	clearLCDLine(1);
//	bLCDBacklight = true;									// Turn on LCD Backlight
//	displayLCDPos(0,0);
//	string display1;
//	sprintf(display1, "RANDAUTO");
//	displayNextLCDString(display1);
//	displayLCDPos(1,0);
//	string display2;
//	sprintf(display2, "COMPLETE");
//	displayNextLCDString(display2);
//}

task timer() {
	time2 = 0;
	while (true) {
		wait1Msec(1);
		time2 = time2 + 1;
	}
}

task encoderValues() {
	while (true) {
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0, 0, "Claw: ");
		sprintf(linee1, "%4d", SensorValue[clawEnc]);
		displayNextLCDString(linee1);
		displayLCDString(1, 0, "DriveEnc: ");
		sprintf(linee2, "%4d", nMotorEncoder[rightWheelEncoder]);
		displayNextLCDString(linee2);
		wait1Msec(100);
	}
}

void moving(int sp) {
	motor[BR] = sp;
	motor[FR] = sp;
	motor[BL] = sp;
	motor[FL] = sp;
}

void turning(int sp) {
	motor[BR] = sp;
	motor[FR] = sp;
	motor[BL] = -sp;
	motor[FL] = -sp;
}

void right(int sp) {
	motor[BR] = sp;
	motor[FR] = sp;
}

void left(int sp) {
	motor[BL] = sp;
	motor[FL] = sp;
}

void lifting(int sp) {
	motor[liftTL] = sp;
	motor[liftML] = sp;
	motor[liftTR] = sp;
	motor[liftMR] = sp;
}

int quadSign;
int startQuad;
//driveSquares: wheels move based on multiple numSquares times rotation constant. updates in real time to adjust rotation
//amount based on current position. rotation amounts are summed or subtracted from current rotation on quad encoder.
void driveSquares(int speed, float numSquares) {
	numSquares = -numSquares;
	startQuad = SensorValue[quadEnc];
	quadSign = sgn(SensorValue[quadEnc] - (startQuad + numSquares*driveEncVal);
	motor[BR] = -speed*sgn(numSquares);
	motor[BL] = -speed*sgn(numSquares);
	motor[FL] = -speed*sgn(numSquares);
	motor[FR] = -speed*sgn(numSquares);
	while (sgn(SensorValue[quadEnc] - (startQuad + numSquares*driveEncVal)) == quadSign && quadSign != 0) {
	}
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	motor[BR] = 0;
	motor[BL] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
}
//garbage function, do not use
void turnDegrees(int speed, int degrees, int direction) {
	if (direction == -1) {
		motor[BR] = speed;
		motor[FR] = speed;
		while (abs(nMotorEncoder[BR]) < turnLeftEncVal*(degrees/90)) {
		}
		nMotorEncoder[BR] = 0;
		motor[BR] = 0;
		motor[FR] = 0;
	} else if (direction == 1) {
		motor[BL] = speed;
		motor[FL] = speed;
		while (abs(nMotorEncoder[BL]) < turnRightEncVal*(degrees/90)) {
		}
		nMotorEncoder[BL] = 0;
		motor[BL] = 0;
		motor[FL] = 0;
	}
}
//turnDegreesGyro: rotates the wheels in quickest direction towards specified degree plane. is incremental;
//degrees specified are summed to current degree. compass-type rotation; 0 deg is initial pos.
int degreeSign;
int startDegree;
void turnDegreesGyro(int speed, int degrees) {
	degrees = -degrees;
	startDegree = SensorValue[gyro];
	degreeSign = sgn(SensorValue[gyro] - (startDegree + degrees*10));
	motor[BL] = speed*(degreeSign);
	motor[FL] = speed*(degreeSign);
	motor[BR] = speed*(-degreeSign);
	motor[FR] = speed*(-degreeSign);
	while (sgn(SensorValue[gyro] - (startDegree + degrees*10)) == degreeSign && (degreeSign != 0)) {
		writeDebugStreamLine("%4f", SensorValue[gyro]);
	}
	motor[BL] = 0;
	motor[FL] = 0;
	motor[BR] = 0;
	motor[FR] = 0;
}
//liftAngle: angles the arm based upon a set angle. angles are exact arm positions and are not incremental.
//total liftAngle limit is 135 degrees. 0 deg = lowest point, 135 deg = upright, highest point before tipping.
int angleSign;
void liftAngle(int speed, float angle) { //Set the lift to a specified angle
	angleSign = sgn(SensorValue[liftEnc] - (liftEncVal*(angle/135) + minLift));
	motor[liftML] = speed*(-angleSign);
	motor[liftMR] = speed*(-angleSign);
	motor[liftTL] = speed*(-angleSign);
	motor[liftTR] = speed*(-angleSign);
	//Keep moving lift arm until the distance between the current and final angles are minimized
	while ((sgn(SensorValue[liftEnc] - (liftEncVal*(angle/135) + minLift)) == angleSign) && (angleSign != 0)) { //is 135 deg a good estimate for entire lift?
	}
	motor[liftML] = 0;
	motor[liftMR] = 0;
	motor[liftTL] = 0;
	motor[liftTR] = 0;
}
//clawAngle: angles the claw based upon a set angle. angles are exact claw positions and are not incremental.
//total clawAngle limit is 180 degrees. 0 deg = default flush mode, 90 deg = open mode, 180 deg = grab mode.
int clawSign;
void clawAngle(int speed, float angle) { //Set the claw to a specified angle
	clawSign = sgn(SensorValue[clawEnc] - (clawEncVal*(angle/180) + minClaw));
	motor[clawL] = speed*(clawSign);
	motor[clawR] = speed*(clawSign);
	//Keep moving claw arm until the distance between the current and final angles are minimized
	while ((sgn(SensorValue[clawEnc] - (clawEncVal*(angle/180) + minClaw)) == clawSign) && (clawSign != 0)) { //is 135 deg a good estimate for entire lift?
	}
	motor[clawL] = 0;
	motor[clawR] = 0;
}

//experimental drive lift and throw function
void driveLiftAndClaw(int dSpeed, int lSpeed, int cSpeed, float dSquares, float lAngle, float cAngle) {
	dSquares = -dSquares;
	startQuad = SensorValue[quadEnc];
	quadSign = sgn(SensorValue[quadEnc] - (startQuad + dSquares*driveEncVal));
	motor[BR] = -dSpeed*sgn(dSquares);
	motor[BL] = -dSpeed*sgn(dSquares);
	motor[FL] = -dSpeed*sgn(dSquares);
	motor[FR] = -dSpeed*sgn(dSquares);
	angleSign = sgn(SensorValue[liftEnc] - (liftEncVal*(lAngle/135) + minLift));
	motor[liftML] = lSpeed*(-angleSign);
	motor[liftMR] = lSpeed*(-angleSign);
	motor[liftTL] = lSpeed*(-angleSign);
	motor[liftTR] = lSpeed*(-angleSign);
	clawSign = sgn(SensorValue[clawEnc] - (clawEncVal*(cAngle/180) + minClaw));
	motor[clawL] = cSpeed*(clawSign);
	motor[clawR] = cSpeed*(clawSign);
	while ((sgn(SensorValue[quadEnc] - (startQuad + dSquares*driveEncVal)) == quadSign && quadSign != 0)
		|| ((sgn(SensorValue[liftEnc] - (liftEncVal*(lAngle/135) + minLift)) == angleSign) && (angleSign != 0))
    || ((sgn(SensorValue[clawEnc] - (clawEncVal*(cAngle/180) + minClaw)) == clawSign) && (clawSign != 0))) {
		if ((sgn(SensorValue[quadEnc] - (startQuad + dSquares*driveEncVal)) != quadSign)  || (quadSign == 0)) {
			motor[BR] = 0;
			motor[BL] = 0;
			motor[FL] = 0;
			motor[FR] = 0;
		}
		if ((sgn(SensorValue[liftEnc] - (liftEncVal*(lAngle/135) + minLift)) != angleSign) || (angleSign == 0)) {
			motor[liftML] = 0;
			motor[liftMR] = 0;
			motor[liftTL] = 0;
			motor[liftTR] = 0;
		}
		if ((sgn(SensorValue[clawEnc] - (clawEncVal*(cAngle/180) + minClaw)) != clawSign) || (clawSign == 0)) {
			motor[clawL] = 0;
			motor[clawR] = 0;
		}
	}
	motor[BR] = 0;
	motor[BL] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
	motor[liftML] = 0;
	motor[liftMR] = 0;
	motor[liftTL] = 0;
	motor[liftTR] = 0;
	motor[clawL] = 0;
	motor[clawR] = 0;
}
//void auto1() {
//	moving(-127);
//	wait1Msec(1500);
//	moving(0);
//	wait1Msec(500);
//	lifting(-127);
//	motor[clawR] = 127;
//	motor[clawL] = 127;
//	wait1Msec(1000);
//	motor[clawR] = 0;
//	motor[clawL] = 127;
//	wait1Msec(1000);
//	lifting(0);
//}

//start backwards

void auto1() { //Go to corner star, throw, knock off side stars
	driveSquares(127, -0.5); //Move up one
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -1.5); //Go up to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open up claw
	liftAngle(liftSpeed, 0); //Lift down
	driveSquares(127, 1); //Go up near back
	turnDegreesGyro(turnSpeed, 40*(-turnDir)); //Go right/left if left/right
	driveSquares(127, 0.75); //Drive forward a square
	clawAngle(clawSpeed, 180); //Grab the star
	turnDegreesGyro(turnSpeed,40*turnDir); //Align backwards; go left/right if left/right
	driveSquares(127, -2.5); //Go back
	liftAngle(liftSpeed, 135); //Lift up, knock off fence
	clawAngle(clawSpeed, 90); //Open up claw wide, let go of stars
}

void auto2() { //Go to middle stars, throw, knock off side stars
	driveSquares(127, -0.5); //Move up one
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -1.5); //Go up to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open up claw
	liftAngle(liftSpeed, 0); //Lift down
	driveSquares(127, 1); //Go up near back
	turnDegreesGyro(turnSpeed, 30*(turnDir)); //Go left/right if left/right
	driveSquares(127, 0.75); //Drive forward a square
	clawAngle(clawSpeed, 180); //Grab the stars
	driveSquares(127, -0.75); //Go back
	turnDegreesGyro(turnSpeed, 30*(-turnDir)); //Align backwards; go right/left if left/right
	driveSquares(127, -1); //Go backwards to wall
	liftAngle(liftSpeed, 135); //Lift up, knock off fence
	clawAngle(clawSpeed, 90); //Open up claw wide, let go of stars
}

void auto3() { //Go to middle cube, throw, knock off side stars
	driveSquares(127, -0.5); //Move up one
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -1.5); //Go up to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open up claw
	liftAngle(liftSpeed, 0); //Lift down
	driveSquares(127, 1); //Go up near back
	turnDegreesGyro(turnSpeed, 90*turnDir); //Go left/right if left/right
	driveSquares(127, 1); //Go up to cube
	clawAngle(clawSpeed, 165); //Grab cube
	motor[clawL] = -127;
	motor[clawR] = -127;
	driveSquares(127, -1); //Go back
	turnDegreesGyro(127, 90*(-turnDir)); //Go right/left if left/right
	driveSquares(127, -1); //Go back to fence
	liftAngle(127, 135); //Lift up
	motor[clawL] = 0;
	motor[clawR] = 0;
	clawAngle(clawSpeed, 90);
}

void auto4() { //Go to middle cube, throw, knock off middle stars
	driveSquares(127, -0.5); //Move up one
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -1.5); //Go up to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open up claw
	liftAngle(liftSpeed, 0); //Lift down
	turnDegreesGyro(turnSpeed, 45*turnDir); //Go left/right if left/right
	driveSquares(127, 1.5); //Go up to cube
	clawAngle(clawSpeed, 165); //Grab cube
	motor[clawL] = -127;
	motor[clawR] = -127;
	turnDegreesGyro(127, 45*(-turnDir)); //Go right/left if left/right
	driveSquares(127, -1); //Go back to fence
	liftAngle(127, 135); //Lift up
	motor[clawL] = 0;
	motor[clawR] = 0;
	clawAngle(clawSpeed, 90); //Drop
}

void auto5() { //Clear the field
	driveSquares(127, -0.5); //Move up one
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -1.5); //Go up to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open up claw
	liftAngle(liftSpeed, 0); //Lift down
	turnDegreesGyro(turnSpeed, 45*turnDir); //Go left/right if left/right
	driveSquares(127, 1.5); //Go up to cube
	clawAngle(clawSpeed, 165); //Grab cube
	motor[clawL] = -127;
	motor[clawR] = -127;
	turnDegreesGyro(127, 45*(-turnDir)); //Go right/left if left/right
	driveSquares(127, -1); //Go back to fence
	liftAngle(127, 135); //Lift up
	motor[clawL] = 0;
	motor[clawR] = 0;
	clawAngle(clawSpeed, 90); //Drop
	liftAngle(liftSpeed, 0); //Lower lift
	driveSquares(127, 2); //Go to back
	clawAngle(clawSpeed, 180); //Close claw
	driveSquares(127, -2); //Go to fence
	liftAngle(liftSpeed, 135); //Lift up
	clawAngle(clawSpeed, 90); //Open claw
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	if (vexRT[Btn5D] == 1 || vexRT[Btn5U] == 1 || vexRT[Btn6D] == 1 || vexRT[Btn6U] == 1) {
	}	//Skip bootup
	else {
	SensorType[clawEnc] = sensorNone;
	SensorType[liftEnc] = sensorNone;
	SensorType[gyro] = sensorNone;
	SensorType[quadEnc] = sensorNone;
	wait1Msec(1000);
	SensorType[clawEnc] = sensorPotentiometer;
	SensorType[liftEnc] = sensorPotentiometer;
	SensorType[gyro] = sensorGyro;
	SensorType[quadEnc] = sensorQuadEncoder;
	SensorValue[gyro] = 0;
	SensorValue[quadEnc] = 0;
	SensorFullCount[gyro] = 7200;
	clearDebugStream();
	bStopTasksBetweenModes = true;
	if (SensorValue[betaTest] == 0) {
		testVar = 0; //Enable beta features
		//setRandomSeed();
		} else {
		testVar = 1; //Disable beta features
	}
	//Reset controller
	deadzone2 = vexRT[Ch2];
	deadzone3 = vexRT[Ch3];
	//Reset encoders
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	//Reset motors
	motor[BL] = 0;
	motor[BR] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;
	//Show battery data before match
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);
	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
	displayNextLCDString(backupBattery);
	wait1Msec(2000);
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;
	sprintf(line2, "Side: %5s", side);
	displayLCDPos(0, 0);
	displayNextLCDString(line1);
	displayLCDPos(1, 0);
	displayNextLCDString(line2);
	startTask(timer);
	while (ready == false) {
		if (time2 > 5000) { //Failsafe, normally 3000
			ready = true;
		}
		if (nLCDButtons == 1 && pressed == false) {
			pressed = true;
			automode = automode + 1;
			if (automode == 6) {
				automode = 1;
			}
			if (automode == 1) {
				line1 = "1: Side stars";
				}	else if (automode == 2) {
				line1 = "2: Midl stars";
				} else if (automode == 3) {
				line1 = "3: Side cube";
				} else if (automode == 4) {
				line1 = "4: Midl cube";
				} else if (automode == 5) {
				line1 = "5:CLEARFIELD";
			}
			clearLCDLine(0);
			displayLCDPos(0, 0);
			displayNextLCDString(line1);
			}	else if (nLCDButtons == 2 && pressed == false) {
			pressed = true;
			if (side == "Left") {
				side = "Right";
				}	else {
				side = "Left";
			}
			turnDir = -turnDir;
			line2 = "";
			sprintf(line2, "Side: %5s", side);
			clearLCDLine(1);
			displayLCDPos(1, 0);
			displayNextLCDString(line2);
			}	else if (nLCDButtons == 4 && pressed == false) {
			pressed = true;
			ready = true;
			}	else if (nLCDButtons == 0 && pressed == true) {
			pressed = false;
		}
	}
	stopTask(timer);
	bLCDBacklight = true;
	clearLCDLine(0);
	clearLCDLine(1);
	if ((time2 % 10) <= 3) {
		sprintf(line1, "AUTO SET!");
		sprintf(line2, "READY");
		}	else if ((time2 % 10) <= 5) {
		sprintf(line1, "AUTO GET!");
		sprintf(line2, "REEFY");
		}	else if ((time2 % 10) <= 7) {
		sprintf(line1, "SET AUTO!");
		sprintf(line2, "GRAVY");
		}	else if ((time2 % 10) <= 8) {
		sprintf(line1, "SORRY BRO!");
		sprintf(line2, "- YOUNG");
		}	else if ((time2 % 10) <= 9) {
		sprintf(line1, "HEY, THAT'S");
		sprintf(line2, "PRETTY GOOD!");
	}
	displayLCDPos(0, 0);
	displayNextLCDString(line1);
	displayLCDPos(1, 0);
	displayNextLCDString(line2);
	wait1Msec(2000);
	clearLCDLine(0);
	clearLCDLine(1);
	}
	playSound(soundBlip);
	playSound(soundException);
	playSound(soundBeepBeep);
	playSound(soundLowBuzz);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	stopTask(timer);
	//startTask(timer);
	startTask(encoderValues);
	startTask(pacman);
	//Reset encoders
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	soundPlay = true;
	//startTask(placeholder);
	if (automode == 1) { //Side stars
		auto1();
		}	else if (automode == 2) { //Middle stars
		auto2();
		} else if (automode == 3) { //Side cube
		auto3();
		} else if (automode == 4) { //Middle cube
		auto4();
		} else if (automode == 5) { //Clear the field
		auto5();
		} else {
		auto1();
	}
	stopTask(pacman);
	soundPlay = true;
	startTask(smbdeath);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	clearDebugStream();
	stopTask(timer);
	startTask(encoderValues);
	//Reset encoders
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	//Reset motors
	motor[BL] = 0;
	motor[BR] = 0;
	motor[FL] = 0;
	motor[FR] = 0;
	//Start tasks here
	stopTask(timer);
	//startTask(timer);
	soundPlay = true;
	startTask(balloon);
	while (true)
	{

		//Claw controls
		if (vexRT[Btn5U] == 1) {
			motor[clawR] = 127;
			motor[clawL] = 127;
		}	else if (vexRT[Btn6U] == 1) {
			motor[clawR] = -127;
			motor[clawL] = -127;
		} else {
			motor[clawR] = 0;
			motor[clawL] = 0;
		}

		//Lift controls
		if (vexRT[Btn5D] == 1) {
			motor[liftTL] = 127;
			motor[liftML] = 127;
			motor[liftTR] = 127;
			motor[liftMR] = 127;
		}	else if (vexRT[Btn6D] == 1) {
			motor[liftTL] = -127;
			motor[liftML] = -127;
			motor[liftTR] = -127;
			motor[liftMR] = -127;
		} else {
			motor[liftTL] = 0;
			motor[liftML] = 0;
			motor[liftTR] = 0;
			motor[liftMR] = 0;
		}

		//Drive motor controls
		if (vexRT[Btn8D] == 0 && vexRT[Btn8U] == 0 && vexRT[Btn8L] == 0 && vexRT[Btn8R] == 0) {
			if (testVar == 1) {
				if (abs(vexRT[Ch3]) <= abs(deadzone3)) {
					motor[BL] = 0;
					motor[FL] = 0;
					}	else {
					motor[BL] = vexRT[Ch3];
					motor[FL] = vexRT[Ch3];
				}
				if (abs(vexRT[Ch2]) <= abs(deadzone2)) {
					motor[BR] = 0;
					motor[FR] = 0;
					} else {
					motor[BR] = vexRT[Ch2];
					motor[FR] = vexRT[Ch2];
				}
				} else { //Motion controls
				if (abs(vexRT[AccelX]) > abs(vexRT[AccelY])) { //Turning Activated
					motor[BL] = vexRT[AccelX];
					motor[FL] = vexRT[AccelX];
					motor[BR] = -vexRT[AccelX];
					motor[FR] = -vexRT[AccelX];
					} else { //Moving Activated
					motor[BL] = -vexRT[AccelY];
					motor[FL] = -vexRT[AccelY];
					motor[BR] = -vexRT[AccelY];
					motor[FR] = -vexRT[AccelY];
				}
			}
		}
		//Sound controls
		if (soundPlay == false) {
			if (vexRT[Btn7R] == 1) {
				soundPlay = true;
				startTask(PokemonGO2);
				} else if (vexRT[Btn7D] == 1) {
				soundPlay = true;
				startTask(PPAP);
			} else if (vexRT[Btn7L] == 1) {
				soundPlay = true;
				startTask(smb3);
			} else if (vexRT[Btn7U] == 1) {
				soundPlay = true;
				startTask(smw2_map);
			}
		}
		if (vexRT[Btn8D] == 1) {
			clawAngle(clawSpeed, 90);
			}	else if (vexRT[Btn8U] == 1) {
			driveSquares(127,1);
			}	else if (vexRT[Btn8L] == 1) {
			turnDegreesGyro(turnSpeed, -90);
			} else if (vexRT[Btn8R] == 1) {
			turnDegreesGyro(turnSpeed, 90);
			} else { //AutoGenerator
			//if (mode != 0) {
			//	if (mode == 1) {
			//		writeDebugStreamLine("while (nMotorEncoder[BR] > %d) {", nMotorEncoder[BR]);
			//		writeDebugStreamLine("	moving(-auSpeed);");
			//		writeDebugStreamLine("}");
			//		writeDebugStreamLine("moving(0);");
			//		writeDebugStreamLine("wait1Msec(100);");
			//		}	else if (mode == 2) {
			//		writeDebugStreamLine("while (nMotorEncoder[BR] < %d) {", nMotorEncoder[BR]);
			//		writeDebugStreamLine("	moving(auSpeed);");
			//		writeDebugStreamLine("}");
			//		writeDebugStreamLine("moving(0);");
			//		writeDebugStreamLine("wait1Msec(100);");
			//		} else if (mode == 3) {
			//		writeDebugStreamLine("while (nMotorEncoder[BR] < %d) {", nMotorEncoder[BR]);
			//		writeDebugStreamLine("	right(auSpeed);");
			//		writeDebugStreamLine("}");
			//		writeDebugStreamLine("right(0);");
			//		writeDebugStreamLine("wait1Msec(100);");
			//		} else if (mode == 4) {
			//		writeDebugStreamLine("while (nMotorEncoder[BL] < %d) {", nMotorEncoder[BL]);
			//		writeDebugStreamLine("	left(auSpeed);");
			//		writeDebugStreamLine("}");
			//		writeDebugStreamLine("left(0);");
			//		writeDebugStreamLine("wait1Msec(100);");
			//	}
			//	mode = 0;
			}
		}
	}
