#pragma config(Sensor, port2,  leftLED,        sensorVexIQ_LED)
#pragma config(Sensor, port3,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port7,  bumpSensor,     sensorVexIQ_Touch)
#pragma config(Sensor, port9,  colorSensor,    sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port12, rightLED,       sensorVexIQ_LED)
#pragma config(Sensor, port8, thirdLED,       sensorVexIQ_LED)
#pragma config(Motor,  motor1,          Right,         tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor4,          CubeCatcher,   tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          BallCatcher,   tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          Left,          tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor10,         Shift,         tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         Arm,           tmotorVexIQ, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//define global variable
int turning;
//const int threshold = 200; //white ~ 500; black ~ 50 (gray scale)

//============================================| TASK LowGreenCube |============================================
task LowGreenCube()
{
	while(true)
	{
		/*Touch LED sensor to start the autonuous program*/
		waitUntil(getTouchLEDValue(rightLED) == 1);

		resetGyro(gyroSensor);

		setMotorTarget(Arm, -400, 80); //lower the arm
		wait1Msec(150);

		//slow start to avoid wheel slippery
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, 155, 20);
		setMotorTarget(Right, 155, 20);
		wait1Msec(50);
		setMotorTarget(Left, 155, 30);
		setMotorTarget(Right, 155, 30);
		wait1Msec(50);
		setMotorTarget(Left, 155, 35);
		setMotorTarget(Right, 155, 35);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(150);

		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		resetMotorEncoder(Arm);
		setMotorTarget(Left, 40, 25);
		setMotorTarget(Right, 40, 25);
		wait1Msec(50);
		setMotorTarget(Arm, 260, 60);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		waitUntilMotorStop(Arm);
		wait1Msec(150);

		//drive forward to low platform
		clearTimer(T1);
		while(time1[T1] < 2000) //1200
		{
			setMotorSpeed(Left, 40);
			setMotorSpeed(Right, 40);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(100);

		//lower arm to deposite 1st green cube
		resetMotorEncoder(Arm);
		setMotorTarget(Arm, -100, 30);
		waitUntilMotorStop(Arm);
		wait1Msec(10);

		//back up
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, -300, 80);
		setMotorTarget(Right, -300, 80);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);
	}
}
//============================================| TASK LowGreenCube |============================================

//============================================| TASK HighGreenCube |===========================================
task HighGreenCube()
{
	while(true)
	{
		/*Touch LED sensor to start the autonuous program*/
		waitUntil(getTouchLEDValue(leftLED) == 1);

		resetGyro(gyroSensor);
		setTouchLEDColor(leftLED, colorNone);
		setMotorTarget(Arm, -400, 80); //lower the arm

		//turn left
		resetGyro(gyroSensor);
		while(getGyroDegrees(gyroSensor) < 75)
		{
			turning = getGyroDegrees(gyroSensor);
			setMotorSpeed(Left, -50+turning/2);
			setMotorSpeed(Right, +50-turning/2);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(50);

		//forward
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, 420, 55);
		setMotorTarget(Right, 420, 55);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);

		//turn right towards green cube
		resetGyro(gyroSensor);
		while(getGyroDegrees(gyroSensor) > -25)
		{
			turning = getGyroDegrees(gyroSensor);
			setMotorSpeed(Left, 50+turning/2);
			setMotorSpeed(Right, -50-turning/2);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(10);

		//forward to pick up green cube
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left,200, 30);
		setMotorTarget(Right, 200, 30);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(20);

		//pick up green cube
		resetMotorEncoder(Arm);
		while(getBumperValue(bumpSensor) == 0)
		{
			setMotorSpeed(Arm, 100);
		}
		setMotorSpeed(Arm, 0);
		wait1Msec(100);

		//back up
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, -300, 55);
		setMotorTarget(Right, -300, 55);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);

		//turn left again
		resetGyro(gyroSensor);
		turning = getGyroDegrees(gyroSensor);
		while(getGyroDegrees(gyroSensor) < 70)
		{
			setMotorSpeed(Left, -50+turning/2);
			setMotorSpeed(Right, +50-turning/2);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(10);

		//forward
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, 155, 30);
		setMotorTarget(Right, 155, 30);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);

		//shift into position
		resetMotorEncoder(Shift);
		setMotorTarget(Shift, -260, 50);
		waitUntilMotorStop(Shift);
		wait1Msec(10);

		//deposite green cube on high platform
		resetMotorEncoder(Arm);
		setMotorTarget(Arm, -100, 30);
		waitUntilMotorStop(Arm);
		wait1Msec(10);

		//back up
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, -160, 50);
		setMotorTarget(Right, -160, 50);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);

	}
}
//============================================| TASK HighGreenCube |============================================

//============================================| TASK RedBlueCube |==============================================

task RedBlueCube()
{
		while(true)
	{
		/*Touch LED sensor to start the autonuous program*/
		/*******************Turn left pick up red***********************/
		waitUntil(getTouchLEDValue(thirdLED) == 1);

		resetGyro(gyroSensor);
		setMotorTarget(Arm, -400, 80); //lower the arm

		//turn left
		resetGyro(gyroSensor);
		while(getGyroDegrees(gyroSensor) <90)
		{
			turning = 95-getGyroDegrees(gyroSensor);
  			setMotorSpeed(Left, -turning);
  			setMotorSpeed(Right, turning);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(50);

		//forward
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left,270, 50);
		setMotorTarget(Right,270, 50);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);

		//pick up red cube
		resetMotorEncoder(Arm);
		while(getBumperValue(bumpSensor) == 0)
		{
			setMotorSpeed(Arm, 100);
		}
		setMotorSpeed(Arm, 0);
		wait1Msec(10);

		/****************************Turn right push to score********************/
		waitUntil(getTouchLEDValue(thirdLED) == 1);

		setMotorTarget(Arm, -400, 80); //lower the arm

		resetGyro(gyroSensor);

		//Turn right
		while(getGyroDegrees(gyroSensor) >-90)
		{
			turning = 95+getGyroDegrees(gyroSensor);
  			setMotorSpeed(Left, turning);
  			setMotorSpeed(Right,-turning);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		resetMotorEncoder(Shift);
		setMotorTarget(Shift,40,40);
		waitUntilMotorStop(Shift);
		wait1Msec(10);
		while(getGyroDegrees(gyroSensor) >-90)
		{
			turning = 95+getGyroDegrees(gyroSensor);
  			setMotorSpeed(Left, turning);
  			setMotorSpeed(Right,-turning);
		}
		wait1Msec(50);
		//forward
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left, 250, 47);
		setMotorTarget(Right, 250, 47);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(50);
		setMotorTarget(Left, 150, 55);
		setMotorTarget(Right, 150, 55);


		//pick up red cube
		resetMotorEncoder(Arm);
		while(getBumperValue(bumpSensor) == 0)
		{
			setMotorSpeed(Arm, 100);
		}
		setMotorSpeed(Arm, 0);
		wait1Msec(50);
		setMotorTarget(Left,80,80);
		setMotorTarget(Right,80,80);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);


		//==============|Push left|==
		waitUntil(getTouchLEDValue(thirdLED) == 1);

		setMotorTarget(Arm, -400, 80); //lower the arm

		//turn left
		resetGyro(gyroSensor);

		//resetMotorEncoder(Left);
		//resetMotorEncoder(Right);
		//setMotorTarget(Left, 10, 30);
		//setMotorTarget(Right, 10, 30);
		//waitUntilMotorStop(Left);
		//waitUntilMotorStop(Right);
		//wait1Msec(10);

		while(getGyroDegrees(gyroSensor) <90)
		{
			turning = 95-getGyroDegrees(gyroSensor);
  			setMotorSpeed(Left, -turning);
  			setMotorSpeed(Right, turning);
		}
		setMotorSpeed(Left, 0);
		setMotorSpeed(Right, 0);
		wait1Msec(50);

		//forward
		resetMotorEncoder(Left);
		resetMotorEncoder(Right);
		setMotorTarget(Left,250, 55);
		setMotorTarget(Right,250, 55);
		waitUntilMotorStop(Left);
		waitUntilMotorStop(Right);
		wait1Msec(10);
		setMotorTarget(Left,0, 80);
		setMotorTarget(Right,0, 80);

	}
}
//============================================| TASK RedBlueCube |==============================================

task main()
{
	/*initialization steps start*/
	setTouchLEDColor(rightLED, colorRed); //start initialization steps

	//reset sensors/encoders
	resetGyro(gyroSensor); //Reset gyro sensor to 0 reading
	resetMotorEncoder(BallCatcher); //Reset BsllCatcher motor encoder to 0 position
	resetMotorEncoder(Arm); //Reset Arm motor encoder to 0 position

	//Calibrate gyro sensor
	startGyroCalibration(gyroSensor, gyroCalibrateSamples1024); // longer cal, works better
	wait1Msec(100);
	// wait for calibration to finish
	while(getGyroCalibrationFlag(gyroSensor))
	{
		displayTextLine(1, "Calibrating... %02d");
		wait1Msec(100);
	}

	//Gyro sensor calibration completed
	setTouchLEDColor(rightLED, colorGreen);
	setTouchLEDColor(leftLED,colorLimeGreen);
	setTouchLEDColor(thirdLED, colorRed);
	playSound(soundTada);
	eraseDisplay();
	resetGyro(gyroSensor);
	/*initialization steps complete*/


	/*autonomous program starts here*/
	startTask(LowGreenCube);   // start task LowGreenCube
	startTask(HighGreenCube);  // start task HighGreenCube
	startTask(RedBlueCube); 	// start task RedBlueCube

	while(true)
	{
		sleep(25); // Keep the program alive, but let the other tasks have the processor by "sleeping"
	}
	/*autonomous program ends here*/

}
