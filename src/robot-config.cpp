#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */

// motor left1 = motor(PORT7,ratio18_1,false);
// motor left2 = motor(PORT6,ratio18_1,false);
// motor left3 = motor(PORT5,ratio18_1,false);
// motor_group leftMotors = motor_group(left2,left3);
//right motors are inverted and have gear ratio of 18 to 1
// motor right1 = motor(PORT10,ratio18_1,true); 
// motor right2 = motor(PORT9,ratio18_1,true);
// motor right3 = motor(PORT8,ratio18_1, true);
// motor_group rightMotors = motor_group(right2,right3);
// drivetrain drive = drivetrain(leftMotors,rightMotors);

controller Controller1 = controller(primary);
// rotation rightRotate = rotation(PORT8,false);
// rotation leftRotate = rotation(PORT9, true);
inertial inert = inertial(PORT4);
motor leftMotorA = motor(PORT3, ratio18_1, true);//
motor leftMotorB = motor(PORT6, ratio18_1, true);//
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT2, ratio18_1, false); //
motor rightMotorB = motor(PORT10, ratio18_1, false);//
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 295, 40, mm, 1);

motor conveyor = motor(PORT8,ratio18_1, true);//
motor intake = motor(PORT20, ratio18_1, true);
motor_group contake = motor_group(conveyor, intake);
digital_out mogomech = digital_out(Brain.ThreeWirePort.D);//
digital_out arm = digital_out(Brain.ThreeWirePort.F);//

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + (0.6)*Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - (0.6)*Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 3 && drivetrainLeftSideSpeed > -3) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 3 && drivetrainRightSideSpeed > -3) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);//1.75
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);//1.85
        RightDriveSmart.spin(forward);
      }
    }
  
  return 0;
}


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}
