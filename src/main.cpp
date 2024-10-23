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
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void forwardDrive(double x){
  leftMotors.spinFor(fwd, x, turns, false);
  rightMotors.spinFor(fwd, x, turns, false);
}
void backwardDrive(double x){
  leftMotors.spinFor(reverse, x, turns, false);
  rightMotors.spinFor(reverse, x, turns, false);
}
void turnRight(double x){
  leftMotors.spinFor(fwd, x, turns, false);
  rightMotors.spinFor(reverse, x, turns, false);
}
void turnLeft(double x){
  leftMotors.spinFor(reverse, x, turns, false);
  rightMotors.spinFor(fwd, x, turns, false);
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

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  double PVal = 0;
  double IVal = 0;
  double DVal = 0;
  // turnLeft(30);
  // forwardDrive(30);
  // turnRight(30);
  // backwardDrive(30);
  // forwardIntake();
  // forwardDrive(10);
  // backwardIntake();
  // forwardDrive(20);
  forwardDrive(2.31);
  turnLeft(1.83);
  backwardDrive(0.6);
  grabStake();
  contakeForward();
  wait(3, sec);
  turnRight(1.58);
  forwardDrive(1.3);
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

double pidCalc(double PVal, double IVal, double DVal){
  double KP = 0;
  double KI = 0;
  double KD = 0;
  return PVal*KP+IVal*KI+DVal*KD;
}

void usercontrol(void) {
  // User control code here, inside the loop
    
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    drive.arcade(driver.Axis3.value(),driver.Axis1.value());
    driver.ButtonB.pressed(contakeForward);
    driver.ButtonX.pressed(contakeBackward);
    driver.ButtonR1.pressed(grabStake);
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
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
