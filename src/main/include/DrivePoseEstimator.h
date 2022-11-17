#pragma once

#include "SwerveDrive.h"
#include "Limelight.h"
#include "SwerveDrive.h"
#include <frc/estimator/SwerveDrivePoseEstimator.h>
#include <frc/StateSpaceUtil.h>
#include <frc/MathUtil.h>
#include "SwerveModule.h"

class DrivePoseEstimator {
    public:
        DrivePoseEstimator(Limelight& limelight, SwerveDrive& swerveDrive, AHRS& navx);
        void update();
    private:
        Limelight* limelight;
        SwerveDrive* swerveDrive;
        AHRS* navx;

        frc::Translation2d frontLeftLocation_{+0.381_m, +0.381_m};
        frc::Translation2d frontRightLocation_{+0.381_m, -0.381_m};
        frc::Translation2d backLeftLocation_{-0.381_m, +0.381_m};
        frc::Translation2d backRightLocation_{-0.381_m, -0.381_m};

        /*
        SwerveModule frontLeft_{1, 2, 0, 1, 2, 3};
        SwerveModule frontRight_{3, 4, 4, 5, 6, 7};
        SwerveModule backLeft_{5, 6, 8, 9, 10, 11};
        SwerveModule backRight_{7, 8, 12, 13, 14, 15};
        */

        frc::SwerveDriveKinematics<4> kinematics_{
            frontLeftLocation_, frontRightLocation_,
            backLeftLocation_, backRightLocation_
        };

        const wpi::array<double, 3> stateStdDevs = {0.01, 0.01, 0.01};
        const wpi::array<double, 1> localMeasurementStdDevs = {0.1};
        const wpi::array<double, 3> visionMeasurementStdDevs = {0.1, 0.1, 0.1};

        frc::SwerveDrivePoseEstimator<4> estimator {
            frc::Rotation2d(), frc::Pose2d(), kinematics_,
            stateStdDevs, localMeasurementStdDevs, 
            visionMeasurementStdDevs};
};