/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tues OCT 24 2023                                          */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    19, 20, 14, 13, 18
// IntakeMotor          motor         20
// CataMotor            motor         19
// IntakeSol            digitalout    a
// WingsSol          digitalout    20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

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
  Drivetrain.setHeading(90, deg);
  IntakeMotor.setVelocity(100, percent);
  Drivetrain.setTurnVelocity(30, percent);
  Drivetrain.setDriveVelocity(40, percent);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  MogoSol.set(false);
  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.driveFor(reverse, 37.75, inches);
  Drivetrain.turnToHeading(0, deg);
  Drivetrain.driveFor(reverse, 7, inches);
  IntakeMotor.spinFor(reverse, 1000, degrees, false);
  wait(1000, msec);
  Drivetrain.driveFor(16, inches);
  Drivetrain.setTurnVelocity(10, percent);
  Drivetrain.turnToHeading(55, deg);
  wait(100, msec);
  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.driveFor(120, inches);
  IntakeMotor.spin(reverse);
  Drivetrain.driveFor(20, inches);
  IntakeMotor.stop();
  Drivetrain.turnToHeading(91, deg);
  Drivetrain.setTurnVelocity(30, percent);
  Drivetrain.setDriveVelocity(25, percent);
  Drivetrain.driveFor(reverse, 60, inches, false);
  wait(1250, msec);
  MogoSol.set(true);
  IntakeMotor.spin(reverse); 
  Drivetrain.setDriveVelocity(50, percent);
  wait(1, sec);
  Drivetrain.driveFor(37, inches);
  Drivetrain.turnToHeading(5, deg);
  IntakeMotor.spin(reverse);
  Drivetrain.setDriveVelocity(40, percent);
  Drivetrain.driveFor(30, inches);
  Drivetrain.driveFor(reverse, 5, inches);
  Drivetrain.turnToHeading(-75, deg);
  Drivetrain.setDriveVelocity(30, percent);
  Drivetrain.driveFor(35, inches);
  IntakeMotor.stop();
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
  vexcodeInit();
  CataMotor.setPosition(1, degrees);
  CataMotor.setVelocity(75, percent);
  CataMotor.setStopping(hold);
  Drivetrain.setStopping(coast);
  Drivetrain.setTurnVelocity(40, percent);
  Drivetrain.setDriveVelocity(50, percent);
  

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

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
