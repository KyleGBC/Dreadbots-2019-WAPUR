/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <WPILib.h>
#include <rev/CanSparkMax.h>
#include <ctre/Phoenix.h>
#include <SparkDrive.h>

class Robot : public frc::IterativeRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  frc::Joystick *js1;
  rev::CANSparkMax *lFront;
  rev::CANSparkMax *rFront;
  rev::CANSparkMax *lBack;
  rev::CANSparkMax *rBack;
  SparkDrive *sparkDrive;
  WPI_TalonSRX *intake;
  WPI_TalonSRX *wrist;
  WPI_TalonSRX *lift;
  int count;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
};
