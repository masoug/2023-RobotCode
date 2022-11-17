#include "DrivePoseEstimator.h"

DrivePoseEstimator::DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive) {
    this->limelight = &limelight;
    this->swerveDrive = &swerveDrive;
}

void DrivePoseEstimator::update() {
    //estimator.update();
    // add camera measurement
}