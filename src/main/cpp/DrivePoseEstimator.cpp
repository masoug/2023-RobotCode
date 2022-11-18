#include "DrivePoseEstimator.h"

DrivePoseEstimator::DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive, AHRS& navx) {
    this->limelight = &limelight;
    this->swerveDrive = &swerveDrive;
    this->navx = &navx;
}

/**
* @todo Determine how to get the pose for the vision measurement.
* @todo Switch from Limelight to Photonvision
*/
void DrivePoseEstimator::update() {
    estimator.Update(navx->GetRotation2d(), frontLeft_.getState(), 
        frontRight_.getState(), backLeft_.getState(), backRight_.getState());
    estimator.AddVisionMeasurement(limelight->getPose(0.0, 0.0), frc::Timer::GetFPGATimestamp() - 0.3_s);
}