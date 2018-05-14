#pragma config(Sensor, dgtl3,  sonar,          sensorSONAR_cm)
#pragma config(Motor,  port2,           FL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           BL,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           FR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           BR,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          flashlight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int timing = 500;
float pitch = 0.25;
int bpm = 120;

task music () {
	while (true) {
		if(bSoundQueueAvailable)  // if there is still space in the Sound Queue:
		{
			playImmediateTone(abs(SensorValue[sonar])*pitch, 50);  // play tone according to sensor readings
			wait1Msec(timing); //BPM
		}
	}
}

void tank() {
	motor[FL] = vexRT[Ch3];
	motor[BL] = vexRT[Ch3];
	motor[FR] = vexRT[Ch2];
	motor[BR] = vexRT[Ch2];
}

task main()
{
	startTask(music);
	while (true) {
		tank();
	}
}