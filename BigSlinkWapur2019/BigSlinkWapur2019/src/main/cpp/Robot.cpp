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
  lFront = new rev::CANSparkMax(10, rev::CANSparkMax::MotorType::kBrushless);
  rFront = new rev::CANSparkMax(1, rev::CANSparkMax::MotorType::kBrushless);
  lBack = new rev::CANSparkMax(2, rev::CANSparkMax::MotorType::kBrushless);
  rBack = new rev::CANSparkMax(3, rev::CANSparkMax::MotorType::kBrushless);
  sparkDrive = new SparkDrive(lFront, lBack, rFront, rBack);
  intake = new WPI_TalonSRX(4);
  wrist = new WPI_TalonSRX(5);
  lift = new WPI_TalonSRX(8);
  }

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  std::cout << "Auto selected: " << m_autoSelected << std::endl;
  if (m_autoSelected == kAutoNameCustom) {
  } else {
  }
}

void Robot::AutonomousPeriodic() {
  std::cout << "wrist: " << wrist->GetSelectedSensorPosition() << std::endl;
  std::cout << "Lift: " << lift->GetSelectedSensorPosition() << std::endl;
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  sparkDrive->MecDrive(js1->GetRawAxis(0), -(js1->GetRawAxis(1)), js1->GetRawAxis(2), false, true);
  if(js1->GetRawButton(6)){
    intake->Set(ControlMode::PercentOutput, 1);
  }
  else if(js1->GetRawButton(8)){
    intake->Set(ControlMode::PercentOutput, -1);
  }
  else {
    intake->Set(ControlMode::PercentOutput, .2);
  }

  if(js1->GetRawButton(7)){
    wrist->Set(ControlMode::PercentOutput, .5);
  }
  else if(js1->GetRawButton(5)){
    wrist->Set(ControlMode::PercentOutput, -.5);
  }
  else{
    wrist->Set(ControlMode::PercentOutput, 0);
  }

  if(js1->GetRawButton(4)){
    lift->Set(ControlMode::PercentOutput, 1);
  }
  else if(js1->GetRawButton(2)){
    lift->Set(ControlMode::PercentOutput, -1);
  }
  else
    lift->Set(ControlMode::PercentOutput, 0);

}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
