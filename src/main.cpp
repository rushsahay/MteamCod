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
  rightRotate.resetPosition();
  leftRotate.resetPosition();
  intert.resetHeading();
  intert.resetRotation();
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
  if(piston.value()){
    piston.set(false);
  }
  else{
    piston.set(true);
  }
}
// void release(){
//   piston.set(false);
// }
void contakeForward(){
  contake.spin(fwd);
}
void contakeBackward(){
  contake.spin(reverse);
}
void contakeStop(){
  contake.stop();
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
double kP = 0.2;
double kI = 0.1;
double kD = 0.2;
double turnkP = 3;
double turnkI = 1.2;
double turnkD = 0.2;
int desiredValue = 200;
int desiredTurnValue = 10;
bool PIDEnabled = true;
int error;
int prevError = 0;
int derivative; 
int totalError = 0;

int turnError;
int turnPrevError = 0;
int turnDerivative; 
int turnTotalError = 0;
int PIDControl(){
  while(PIDEnabled){
    int leftMotorPos = leftMotorA.position(degrees);
    int rightMotorPos = rightMotorA.position(degrees);
    int average = (leftMotorPos-rightMotorPos)/2;
    error = average-desiredValue;
    derivative = error-prevError;
    totalError+=error;
    double motorOut = (error*kP)+(totalError*kI)+(derivative*kD);

    int turnleftMotorPos = leftMotorA.position(degrees);
    int turnrightMotorPos = rightMotorA.position(degrees);
    int turnaverage = (turnleftMotorPos-turnrightMotorPos)/2;
    turnError = turnaverage-desiredTurnValue;
    turnDerivative = turnError-turnPrevError;
    turnTotalError+=turnError;
    double turnMotorOut = (turnError*turnkP)+(turnTotalError*turnkI)+(turnDerivative*turnkD);
    RightDriveSmart.spin(forward,motorOut+turnMotorOut,velocityUnits::pct);
    LeftDriveSmart.spin(forward,motorOut-turnMotorOut,velocityUnits::pct);
    turnPrevError = turnError;
  vex::task::sleep(20);
  }
  return 1;

}
void autonomous(void) {
  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  vex::task updatePid(PIDControl);
  if(PIDEnabled){
    
  }
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
  PIDEnabled = false;
  rc_auto_loop_function_Controller1();
  // while (1){
  //   // This is the main execution loop for the user control program.
  //   // Each time through the loop your program should update motor + servo
  //   // values based on feedback from the joysticks.

  //   // ........................................................................
  //   // Insert user code here. This is where you use the joystick values to
  //   // update your motors, etc.
  //   // ........................................................................
  //   // LeftDriveSmart.setStopping(brake);
  //   // RightDriveSmart.setStopping(brake);
  //   /*
  //   Controller1.ButtonB.pressed(contakeForward);
  //   Controller1.ButtonX.pressed(contakeBackward);
  //   Controller1.ButtonY.pressed(contakeStop);
  //   Controller1.ButtonR1.pressed(grabStake);
  //   */
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
