#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;
controller Controller1 = controller(primary);

// Left Motors and motor group
motor leftMotorA = motor(PORT16, ratio6_1, true);
motor leftMotorB = motor(PORT15, ratio6_1, true);
motor leftMotorC = motor(PORT14, ratio6_1, true);
motor_group LeftDriveGroup = motor_group(leftMotorA, leftMotorB, leftMotorC);

// Right Motors and motor group
motor rightMotorA = motor(PORT19, ratio6_1, false);
motor rightMotorB = motor(PORT18, ratio6_1, false);
motor rightMotorC = motor(PORT17, ratio6_1, false);
motor_group RightDriveGroup = motor_group(rightMotorA, rightMotorB, rightMotorC);

// misc
motor IntakeMotor = motor(PORT20, ratio6_1, true);
motor CataMotor = motor(PORT11, ratio36_1, false);
digital_out IntakeSol = digital_out(Brain.ThreeWirePort.A);
digital_out DoinkSol = digital_out(Brain.ThreeWirePort.B);
digital_out MogoSol = digital_out(Brain.ThreeWirePort.H);

//Drivetrain code if using an Inertial Sensor
inertial DrivetrainInertial = inertial(PORT21);
smartdrive Drivetrain = smartdrive(LeftDriveGroup, RightDriveGroup, DrivetrainInertial, 319.19, 320, 40, mm, 1.5);

//Use the following Drivetrain code if NOT using an Inertial Sensor
//drivetrain robotDrive(LeftDriveGroup, RightDriveGroup, wheelTravel, trackWidth, wheelBase, distanceUnits::in );

// VEXcode generated functions
// define variable for remote controller enable/disable1
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool IntakeStopped = true;
bool CataStopped = true;
bool liftStopped = false;
int toggleIntake = 0;
int toggleMogo = 0;
int toggleDoink = 0;
int cautiousDrive = 0;
int cataPos = 0;
int driveMultiplier = 100;

bool checkMotor = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;


// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();

      // if (Controller1.Axis3.position() > 10 || Controller1.Axis3.position() < -10 || Controller1.Axis1.position() > 10 || Controller1.Axis1.position() < -10){
      //   Drivetrain.setStopping(hold);
      // } else if (!DrivetrainLNeedsToBeStopped_Controller1 || !DrivetrainRNeedsToBeStopped_Controller1){
      //   wait(75, msec);
      //   Drivetrain.setStopping(coast);
      // } else
      //   Drivetrain.setStopping(coast);

      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveGroup.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor 
          RightDriveGroup.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }

      if (drivetrainRightSideSpeed != drivetrainLeftSideSpeed){
        drivetrainRightSideSpeed = drivetrainRightSideSpeed;
        drivetrainLeftSideSpeed = drivetrainLeftSideSpeed;
      }

     if (Controller1.ButtonB.pressing()) {

        if (cautiousDrive == 0){
          Drivetrain.setDriveVelocity(10, percent);
          Drivetrain.setTurnVelocity(10, percent);
          Brain.Screen.print("Cautious Drive is on");
          Brain.Screen.newLine();
          cautiousDrive = 1;
        } else {
          Drivetrain.setDriveVelocity(100, percent);
          Drivetrain.setTurnVelocity(100, percent);
          Brain.Screen.print("Cautious Drive is off");
          Brain.Screen.newLine();
          cautiousDrive = 0;
        }
        while (Controller1.ButtonB.pressing()){}
      }

      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveGroup.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveGroup.spin(forward);
      }
      
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveGroup.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveGroup.spin(forward);
      }

      if (Controller1.ButtonB.pressing()) {

        if (cautiousDrive == 0){
          Drivetrain.setDriveVelocity(10, percent);
          Drivetrain.setTurnVelocity(10, percent);
          Brain.Screen.print("Cautious Drive is on");
          Brain.Screen.newLine();
          cautiousDrive = 1;
        } else {
          Drivetrain.setDriveVelocity(100, percent);
          Drivetrain.setTurnVelocity(100, percent);
          Brain.Screen.print("Cautious Drive is off");
          Brain.Screen.newLine();
          cautiousDrive = 0;
        }
        while (Controller1.ButtonB.pressing()){}
      }

      if (Controller1.ButtonL1.pressing()) {
        IntakeMotor.spin(forward);
        IntakeMotor.setVelocity(400, percent);
        IntakeStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {     
        IntakeMotor.setVelocity(400, percent);
        IntakeMotor.spin(reverse);
        IntakeStopped = false;
      } else if (!IntakeStopped) {
        IntakeMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        IntakeStopped = true;
      }

      if (Controller1.ButtonR1.pressing()) {
        liftStopped = false;
        CataMotor.spin(forward);
        CataStopped = false;
      } else if (Controller1.ButtonR2.pressing() /*&& !liftStopped*/) {     
        CataMotor.spin(reverse);
        CataStopped = false;
      } else if (!CataStopped) {
        CataMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        CataStopped = true;
      }

      if (CataMotor.position(degrees) < 0){
        wait(10, msec);
        CataMotor.spinToPosition(2, deg);
      }

      if (Controller1.ButtonA.pressing()){
        CataMotor.setPosition(1, deg);
      }

      if (Controller1.ButtonRight.pressing()) {
        if (toggleDoink == 0){
          DoinkSol.set(true);
          toggleDoink = 1;
        } else {
          DoinkSol.set(false);
          toggleDoink = 0;
        }
      while (Controller1.ButtonRight.pressing()){}
      }
    
      if (Controller1.ButtonY.pressing()) {
        if (toggleMogo == 0) {
          MogoSol.set(true);
          toggleMogo = 1;
        } else {
          MogoSol.set(false);
          toggleMogo = 0;
        }
      while (Controller1.ButtonY.pressing()) {}
      }

      /*while(checkMotor){
        if (LeftDriveGroup.temperature() > 32 || RightDriveGroup.temperature() > 32){
          Brain.Screen.print();
          checkMotor = false;
        }
      }*/

    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  DrivetrainInertial.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}

