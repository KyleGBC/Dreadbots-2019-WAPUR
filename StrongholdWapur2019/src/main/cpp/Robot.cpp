/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  js1 = new frc::Joystick(0);
  left1 = new WPI_TalonSRX(4);
  left2 = new WPI_TalonSRX(1);
  right1 = new WPI_TalonSRX(2);
  right2 = new WPI_TalonSRX(3);
  compressor = new frc::Compressor(0);
  incline = new frc::DoubleSolenoid(0, 1);
  tailFeathers = new frc::Solenoid(5);
  compressor->Start();

}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  int count = 0;
}

void Robot::AutonomousPeriodic() {
  if(count < 100){
    left1 -> Set(ControlMode::PercentOutput, -1);
    left2 -> Set(ControlMode::PercentOutput, -1);
    right1 -> Set(ControlMode::PercentOutput, 1);
    right2 -> Set(ControlMode::PercentOutput, 1);
  }
  else{
    left1 -> Set(ControlMode::PercentOutput, 0);
    left2 -> Set(ControlMode::PercentOutput, 0);
    right1 -> Set(ControlMode::PercentOutput, 0);
    right2 -> Set(ControlMode::PercentOutput, 0);
  }   
  count++;
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  left1 -> Set(ControlMode::PercentOutput, js1->GetRawAxis(1) + js1->GetRawAxis(2));
  left2 -> Set(ControlMode::PercentOutput, js1->GetRawAxis(1) + js1->GetRawAxis(2));
  right1 -> Set(ControlMode::PercentOutput, -1*js1->GetRawAxis(1) + js1->GetRawAxis(2));
  right2 -> Set(ControlMode::PercentOutput, -1*js1->GetRawAxis(1) + js1->GetRawAxis(2));

  if(js1->GetRawButton(5)){
    incline->Set(frc::DoubleSolenoid::Value::kForward);
  }
  else if(js1->GetRawButton(7)){
    incline->Set(frc::DoubleSolenoid::Value::kReverse);
  }
  else{
    incline->Set(frc::DoubleSolenoid::Value::kOff);
  }
  
  if(js1->GetRawButton(6)){
    tailFeathers->Set(true);
  }
  else if(js1->GetRawButton(8)){
    tailFeathers->Set(false);
  }
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
