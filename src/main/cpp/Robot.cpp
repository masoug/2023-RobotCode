#include "Robot.h"

#include <fmt/core.h>
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>

//Initialize pointer objects
void Robot::RobotInit() {
  navx_ = new AHRS(frc::SPI::Port::kMXP);
  swerveDrive_ = new SwerveDrive(navx_, limelight_);

  //initialize datalogger
  //may want to read fields from a file as they get extensive
  datalogFields_ = {
    {"swerve.X", DataLogger::DataType::FLOAT64},
    {"swerve.Y", DataLogger::DataType::FLOAT64},
  };

  //get current date & time in desireable format, append to log file name
  std::time_t t = std::time(0);
  std::tm * now = std::localtime(&t);
  std::string dateTimeStamp = std::to_string(now->tm_year + 1900) + "-" + std::to_string(now->tm_mon) + "-" + std::to_string(now->tm_mday) 
    + "_" + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec);
  std::string path = "robotlog-" + dateTimeStamp;

  //initialzie datalogger object
  logger = new DataLogger(path, datalogFields_);
}

void Robot::RobotPeriodic() {
  limelight_.lightOn(false);

  //log value of registerd data fields
  logger->get_float64("swerve.X") = swerveDrive_->getX();
  logger->get_float64("swerve.Y") = swerveDrive_->getY();

  logger->publish(); //flush logged values to file
}

void Robot::AutonomousInit() {
  swerveDrive_->initializeAutoTraj(SwerveConstants::testPath); //todo would be done with auto chooser depending on auto mode
}

//commented out for testing purposes
void Robot::AutonomousPeriodic() {
  // swerveDrive_->setState(SwerveDrive::State::PATH_FOLLOW); //todo would be moved into auto executor
  // swerveDrive_->Periodic( 0_mps, 0_mps, 0_rad / 1_s, 0);
}

void Robot::TeleopInit() {
  navx_->ZeroYaw();
  swerveDrive_->setState(SwerveDrive::State::DRIVE);
}

void Robot::TeleopPeriodic() {

  //get joystick input
  double vx = ljoy.GetRawAxis(1);
  double vy = ljoy.GetRawAxis(0);
  double vtheta = rjoy.GetX();
  //apply deadband
  vx = abs(vx) < 0.1 ? 0.0: vx; 
  vy = abs(vy) < 0.1 ? 0.0: vy;
  vtheta = abs(vtheta) < 0.05 ? 0.0: vtheta;

  //convert joystick input to desired velocities in meters or radians per second
  vx = joy_val_to_mps(vx);
  vy = joy_val_to_mps(vy);
  vtheta = joy_rot_to_rps(vtheta);

  //drive the robot with joystick inputs
  swerveDrive_->Periodic(
    units::meters_per_second_t{vx},
    units::meters_per_second_t{vy},
    units::radians_per_second_t{0.7*vtheta},
    0);

  //REMEMBER TO COMMENT IN USE OF SPEED PID BEFORE TESTING
 // swerveDrive_->Periodic( 1_mps, 0_mps, 0_rad / 1_s, 0); //go 1 meter per second in the x direction. for testing speed tuning
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

//NOTE: should these two functions go in swerve?
/**
 * @returns joystick value converted to meters per second
**/
double Robot::joy_val_to_mps(double val) {
  return val* SwerveConstants::MAX_SPEED.value();
}

/**
 * @returns joystick value converted to radians per second
**/
double Robot::joy_rot_to_rps(double rot) {
  return rot * SwerveConstants::MAX_ROT.value();
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
