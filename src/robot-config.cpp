#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
motor left1 = motor(PORT1,ratio18_1,false);
 motor left2 = motor(PORT2,ratio18_1,false);
motor left3 = motor(PORT3,ratio18_1,false);
motor_group leftMotors = motor_group(left1,left2,left3);
//right motors are inverted and have gear ratio of 18 to 1
motor right1 = motor(PORT4,ratio18_1,true); 
motor right2 = motor(PORT5,ratio18_1,true);
motor right3 = motor(PORT6,ratio18_1, true);
motor_group rightMotors = motor_group(right1,right2,right3);
drivetrain drive = drivetrain(leftMotors,rightMotors);
motor intake = motor(PORT7,ratio18_1, false);
motor conveyor = motor(PORT8, ratio18_1,true);
motor_group contake = motor_group(intake, conveyor);
digital_out piston = digital_out(Brain.ThreeWirePort.A);
//initialize the driver and operate(operator caused error) controllers
controller driver = controller(primary);
}
  
