using namespace vex;

 extern brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
// //  extern motor left1;
//  extern motor left2;
//  extern motor left3;
//  extern motor_group leftMotors;
//  extern motor right1;
//  extern motor right2;
//  extern motor right3;
//  extern motor_group rightMotors;
//  extern drivetrain drive;
//  extern controller driver;

extern controller Controller1;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor_group LeftDriveSmart;

extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;
extern motor_group RightDriveSmart;

extern drivetrain Drivetrain;
 extern digital_out mogomech;
 extern digital_out arm;
 extern digital_out intakePiston;
//  extern digital_out colorCodePiston;
 extern motor conveyor;
 extern motor intake;
 extern motor_group contake;
  extern motor wallStake;
  
 // extern rotation parallelRotational;
 // extern rotation perpendicularRotational;
 extern inertial inert;
 int rc_auto_loop_function_Controller1();
void vexcodeInit(void);
