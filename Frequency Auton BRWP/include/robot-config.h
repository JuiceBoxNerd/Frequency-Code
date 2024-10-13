using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern smartdrive Drivetrain;
extern motor IntakeMotor;
extern motor CataMotor;
extern digital_out WingsSol;
extern digital_out IntakeSol;
extern digital_out MogoSol;
extern inertial DrivetrainInertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );