#include "DrivePoseEstimator.h"

DrivePoseEstimator::DrivePoseEstimator(photonlib::PhotonCamera& photonCamera, SwerveDrive& swerveDrive, AHRS& navx) {
    this->swerveDrive = &swerveDrive;
    this->navx = &navx;
    this->photonCamera = &photonCamera;
}

/**
* @todo Determine how to get the pose for the vision measurement.
* @todo Switch from Limelight to Photonvision
*/
void DrivePoseEstimator::update() {
    estimator.Update(navx->GetRotation2d(), swerveDrive->getRealModuleStates());
    // TODO: figure out how to add camera measurement
    //estimator.AddVisionMeasurement(limelight->getPose(0.0, 0.0), frc::Timer::GetFPGATimestamp() - 0.3_s);
    //auto res = photonCamera->GetLatestResult();
    //if (res.HasTargets()) {
    //    auto imageCaptureTime = res.GetTimestamp();
    //    auto camTargetTrans = res.GetBestTarget().GetBestCameraToTarget();
    //    auto camPose = 
    //}

}