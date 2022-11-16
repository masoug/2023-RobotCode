#include "DrivePoseEstimator.h"

DrivePoseEstimator::DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive) {
    this->limelight = &limelight;
    this->swerveDrive = &swerveDrive;
    frc::DifferentialDrivePoseEstimator estimator(
        frc::Rotation2d(), frc::Pose2d(),
        stateStdDevs,
        localMeasurementStdDevs,
        visionMeasurementStdDevs);
}

void DrivePoseEstimator::update() {
    //estimator.update();
    // add camera measurement
}