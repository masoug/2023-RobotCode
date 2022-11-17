#include "DrivePoseEstimator.h"

DrivePoseEstimator::DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive, AHRS& navx) {
    this->limelight = &limelight;
    this->swerveDrive = &swerveDrive;
    this->navx = &navx;
}

void DrivePoseEstimator::update() {
    //estimator.update();
    //estimator.Update(navx->GetRotation2d(), )
    // add camera measurement
}