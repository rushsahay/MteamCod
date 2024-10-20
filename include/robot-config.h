using namespace vex;

 extern brain Brain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
 extern motor left1;
 extern motor left2;
 extern motor left3;
 extern motor_group leftMotors;
 extern motor right1;
 extern motor right2;
 extern motor right3;
 extern motor_group rightMotors;
 extern drivetrain drive;
 extern controller driver;
 extern digital_out piston;
 extern motor intake;
 extern motor conveyor;
 extern motor_group contake;
void vexcodeInit(void);
