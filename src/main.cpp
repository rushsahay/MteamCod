/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/


// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include "robot-config.h"
using namespace vex;
// A global instance of competition
competition Competition;
// define your global instances of motors and other devices here
//left motors aren't inverted && have gear ratio of 18 to 1
/*Might be useful to consider putting these values in a constants file as done in frc to minimize the amount of 
things needed to change when changing these values*/
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // rightRotate.resetPosition();
  // leftRotate.resetPosition();
  inert.resetHeading();
  inert.resetRotation();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void forwardDrive(double x){
  LeftDriveSmart.spinFor(fwd, x, turns, false);
  RightDriveSmart.spinFor(fwd, x, turns, false);
}
void backwardDrive(double x){
  LeftDriveSmart.spinFor(reverse, x, turns, false);
  RightDriveSmart.spinFor(reverse, x, turns, false);
}
void turnRight(double x){
  LeftDriveSmart.spinFor(fwd, x, turns, false);
  RightDriveSmart.spinFor(reverse, x, turns, false);
}
void turnLeft(double x){
  LeftDriveSmart.spinFor(reverse, x, turns, false);
  RightDriveSmart.spinFor(fwd, x, turns, false);
}

void grabStake(){
    mogomech.set(true);
}
void releaseStake(){
  mogomech.set(false);
}
// void release(){
//   mogomech.set(false);
// }
void arm_up_down(){
  if(arm.value()){
    arm.set(false);
  }
  else{
    arm.set(true);
  }
}
void contakeForward(){
  contake.spin(fwd);
}
void contakeBackward(){
  contake.spin(reverse);
}
void contakeStop(){
  contake.stop();
}
void setDriveSpeeds(){
  intake.setVelocity(50, percent);
  conveyor.setVelocity(80, percent);
}
void setAutonSpeeds(){
  intake.setVelocity(50, percent);
  conveyor.setVelocity(80, percent);
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
double wheelCircumference = 10.2101761242; //drivetrain wheel circumference in inches
double kP = 0.2;
double kI = 0.1;
double kD = 0.2;
double turnkP = 3;
double turnkI = 1.2;
double turnkD = 0.2;
// int desiredValue = 200;
// int desiredTurnValue = 10;
// bool PIDEnabled = true;
double error;
double prevError = 0;
double derivative; 
double totalError = 0;

double turnError;
double turnPrevError = 0;
int turnDerivative; 
double turnTotalError = 0;

void moveForwardPID(double distance){
  int encoderCounts = (distance / wheelCircumference) * 360;
  LeftDriveSmart.resetPosition();
  RightDriveSmart.resetPosition();
  while(true){
    double leftMotorPos = LeftDriveSmart.position(degrees);
    double rightMotorPos = RightDriveSmart.position(degrees);
    double averagePosition = (leftMotorPos + rightMotorPos) / 2.0;

    error = encoderCounts - averagePosition;
    derivative = error-prevError;
    totalError+=error;

    // if (fabs(error) < 10) {
    //   break;
    // }

    double motorOut = (error*kP)+(totalError*kI)+(derivative*kD);

    LeftDriveSmart.spin(fwd, motorOut, percent);
    RightDriveSmart.spin(fwd, motorOut, percent);

    prevError=error;
    vex::task::sleep(20);
  }
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

void moveBackwardPID(double distance){
  int encoderCounts = (distance / wheelCircumference) * 360;
  LeftDriveSmart.resetPosition();
  RightDriveSmart.resetPosition();
  while(true){
    double leftMotorPos = fabs(LeftDriveSmart.position(degrees));
    double rightMotorPos = fabs(RightDriveSmart.position(degrees));
    double averagePosition = (leftMotorPos + rightMotorPos) / 2.0;

    error = encoderCounts - averagePosition;
    derivative = error-prevError;
    totalError+=error;

    // if (fabs(error) < 10) {
    //   break;
    // }

    double motorOut = (error*kP)+(totalError*kI)+(derivative*kD);

    LeftDriveSmart.spin(reverse, motorOut, percent);
    RightDriveSmart.spin(reverse, motorOut, percent);

    prevError=error;
    vex::task::sleep(20);
  }
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

void turnToHeading(double targetHeading) {
  while (true) {
    // Get current heading from the inertial sensor
    double currentHeading = inert.heading();

    // Error calculation for turning
    turnError = targetHeading - currentHeading;
    turnDerivative = turnError-turnPrevError;
    turnTotalError+=turnError;

    double turnMotorOut = (turnError*turnkP)+(turnTotalError*turnkI)+(turnDerivative*turnkD);

    // Spin motors to correct heading
    LeftDriveSmart.spin(forward, -turnMotorOut, percent);
    RightDriveSmart.spin(forward, turnMotorOut, percent);

    // Stop condition: when robot is close to desired heading
    // if (fabs(turnError) < 1.0) {
    //   break;
    // }
    turnPrevError = turnError;
    vex::task::sleep(20);
  }

  // Stop motors once desired heading is reached
  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

// int PIDControl(){
//   while(PIDEnabled){
//     int leftMotorPos = leftMotorA.position(degrees);
//     int rightMotorPos = rightMotorA.position(degrees);
//     int average = (leftMotorPos-rightMotorPos)/2;
//     error = average-desiredValue;
//     derivative = error-prevError;
//     totalError+=error;
//     double motorOut = (error*kP)+(totalError*kI)+(derivative*kD);

//     int turnleftMotorPos = leftMotorA.position(degrees);
//     int turnrightMotorPos = rightMotorA.position(degrees);
//     int turnaverage = (turnleftMotorPos-turnrightMotorPos)/2;
//     turnError = turnaverage-desiredTurnValue;
//     turnDerivative = turnError-turnPrevError;
//     turnTotalError+=turnError;
//     double turnMotorOut = (turnError*turnkP)+(turnTotalError*turnkI)+(turnDerivative*turnkD);
//     RightDriveSmart.spin(forward,motorOut+turnMotorOut,velocityUnits::pct);
//     LeftDriveSmart.spin(forward,motorOut-turnMotorOut,velocityUnits::pct);
//     turnPrevError = turnError;
//   vex::task::sleep(20);
//   }
//   return 1;

// }
void autonomous(void) {
  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  //
  //
  // ADD AUTON CODE FROM OTHER GIT FILES
  //
  //

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



void usercontrol(void) {
  // User control code here, inside the loop
  // PIDEnabled = false;
  setDriveSpeeds();
  while(1){
    rc_auto_loop_function_Controller1();
     Controller1.ButtonUp.pressed(grabStake);
     Controller1.ButtonDown.pressed(releaseStake);
     Controller1.ButtonRight.pressed(contakeForward);
     Controller1.ButtonLeft.pressed(contakeBackward);
     Controller1.ButtonL1.pressed(contakeStop);
     Controller1.ButtonL2.pressed(arm_up_down);
     wait(20, msec);
  }
  //   
  //   wait(20, msec); // Sleep the task for a short amount of time to
  //                   // prevent wasted resources.
  // }
  
}

//
// Main will set up the competition functions and callbacks.
//


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
    pre_auton();
  

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
