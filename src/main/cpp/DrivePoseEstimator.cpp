#include "DrivePoseEstimator.h"
#include "Constants.h"

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
    //estimator.AddVisionMeasurement(limelight->getPose(0.0, 0.0), frc::Timer::GetFPGATimestamp() - 0.3_s);

    auto res = photonCamera->GetLatestResult();
    if (res.HasTargets()) {
        auto imageCaptureTime = res.GetTimestamp();
        frc::Transform3d camToTargetTrans = res.GetBestTarget().GetBestCameraToTarget();
        frc::Pose2d camPose = GeneralConstants::FAR_TARGET_POSE.TransformBy(camToTargetTrans.Inverse());
        estimator.AddVisionMeasurement(camPose.TransformBy(LimelightConstants::CAMERA_TO_ROBOT), imageCaptureTime);
    }
}