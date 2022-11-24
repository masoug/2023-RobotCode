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

    /*
    TODO: figure out how to add PhotonVision camera measurement
    This is not yet incorporated in PhotonVision C++, we have to wait until they get it out.
    You can see on [this](https://docs.photonvision.org/en/latest/docs/examples/simposeest.html) page that
    the C++ code sections have "Coming soon!" for the time being.
    I created a draft for how it will get done using the Java code samples - however, this may
    require some changes as the C++ method names and signatures may be a little different.
    It's commented it out becaues it won't compile.
    */

    /*auto res = photonCamera->GetLatestResult();
    if (res.HasTargets()) {
        auto imageCaptureTime = res.GetTimestamp();
        frc::Transform2d camToTargetTrans = res.GetBestTarget().GetCameraToTarget();
        frc::Pose2d camPose = GeneralConstants::FAR_TARGET_POSE.TransformBy(camToTargetTrans.Inverse());
        estimator.AddVisionMeasurement(camPose.TransformBy(LimelightConstants::CAMERA_TO_ROBOT), imageCaptureTime);
    }*/

    /*
    Plan for constants:
    in namespace GeneralConstants:
    const frc::Pose2d FAR_TARGET_POSE;

    in namespace LimelightConstants:
    const frc::Transform3d CAMERA_TO_ROBOT(
        frc::Translation3d(units::meter_t(ROBOT_TURRET_CENTER_DISTANCE), units::meter_t(0.0), 
        units::meter_t(ROBOT_TURRET_CENTER_DISTANCE)), frc::Rotation3d());
    */
}