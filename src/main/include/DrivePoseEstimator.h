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

    const Eigen::Matrix<double, 5, 1, 0, 5, 1> stateStdDevs = {0.01, 0.01, 0.01, 0.01, 0.01};
    const Eigen::Matrix<double, 3, 1, 0, 3, 1> localMeasurementStdDevs = {0.1, 0.1, 0.1};
    const Eigen::Matrix<double, 3, 1, 0, 3, 1> visionMeasurementStdDevs = {0.1, 0.1, 0.1};

    

};