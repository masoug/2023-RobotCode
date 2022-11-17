#pragma once
#include "SwerveDrive.h"
#include "Limelight.h"
#include "SwerveDrive.h"
#include <frc/estimator/DifferentialDrivePoseEstimator.h>
#include <frc/StateSpaceUtil.h>
#include <frc/MathUtil.h>

class DrivePoseEstimator {
public:
    DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive);
    void update();

private:
    Limelight* limelight;
    SwerveDrive* swerveDrive;

    const wpi::array<double, 5> stateStdDevs = {0.01, 0.01, 0.01, 0.01, 0.01};
    const wpi::array<double, 3> localMeasurementStdDevs = {0.1, 0.1, 0.1};
    const wpi::array<double, 3> visionMeasurementStdDevs = {0.1, 0.1, 0.1};

    frc::DifferentialDrivePoseEstimator estimator{
        frc::Rotation2d(), frc::Pose2d(),
        stateStdDevs,
        localMeasurementStdDevs,
        visionMeasurementStdDevs};

};