#pragma once

#include "SwerveDrive.h"
#include <frc/estimator/SwerveDrivePoseEstimator.h>
#include <frc/MathUtil.h>
#include "SwerveModule.h"
#include <photonlib/PhotonCamera.h>

class DrivePoseEstimator {
    public:
        DrivePoseEstimator(photonlib::PhotonCamera& photonCamera, SwerveDrive& swerveDrive, AHRS& navx);
        void update();
    private:
        SwerveDrive* swerveDrive;
        AHRS* navx;
        photonlib::PhotonCamera* photonCamera;

        frc::Translation2d frontLeftLocation_{+0.381_m, +0.381_m};
        frc::Translation2d frontRightLocation_{+0.381_m, -0.381_m};
        frc::Translation2d backLeftLocation_{-0.381_m, +0.381_m};
        frc::Translation2d backRightLocation_{-0.381_m, -0.381_m};

        frc::SwerveDriveKinematics<4> kinematics_{
            frontLeftLocation_, frontRightLocation_,
            backLeftLocation_, backRightLocation_
        };

        // TODO tune these hyperparameters
        const wpi::array<double, 3> stateStdDevs = {0.01, 0.01, 0.01};
        const wpi::array<double, 1> localMeasurementStdDevs = {0.1};
        const wpi::array<double, 3> visionMeasurementStdDevs = {0.1, 0.1, 0.1};

        frc::SwerveDrivePoseEstimator<4> estimator {
            frc::Rotation2d(), frc::Pose2d(), kinematics_,
            stateStdDevs, localMeasurementStdDevs, 
            visionMeasurementStdDevs};
};