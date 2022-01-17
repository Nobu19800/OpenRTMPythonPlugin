#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file EditRTC.py
 @brief RTC Development Tools
 @date $Date$

 @author 宮本　信彦　n-miyamoto@aist.go.jp
 産業技術総合研究所　ロボットイノベーション研究センター
 ロボットソフトウエアプラットフォーム研究チーム

 LGPL

"""
import subprocess
import shutil
import traceback
import importlib
import threading
import SDOPackage
import OpenRTM_aist
import RTC
import sys

import os
sys.path.append(".")


# Import RTM module


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
editrtc_spec = ["implementation_id", "EditRTC",
                "type_name",         "EditRTC",
                "description",       "RTC Development Tools",
                "version",           "1.0.0",
                "vendor",            "AIST",
                "category",          "Logic",
                "activity_type",     "STATIC",
                "max_instance",      "1",
                "language",          "Python",
                "lang_type",         "SCRIPT",
                ""]
# </rtc-template>

##
#
# @brief データ変数生成
# @param data_type データ型
# @return データ変数
#


def create_data(data_type):
    if data_type == "RTC::Time":
        return RTC.Time(0, 0)
    elif data_type == "RTC::TimedState":
        return RTC.TimedState(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedShort":
        return RTC.TimedShort(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedLong":
        return RTC.TimedLong(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedUShort":
        return RTC.TimedUShort(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedULong":
        return RTC.TimedULong(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedFloat":
        return RTC.TimedFloat(RTC.Time(0, 0), 0.0)
    elif data_type == "RTC::TimedDouble":
        return RTC.TimedDouble(RTC.Time(0, 0), 0.0)
    elif data_type == "RTC::TimedChar":
        return RTC.TimedChar(RTC.Time(0, 0), chr(0))
    elif data_type == "RTC::TimedWChar":
        return RTC.TimedWChar(RTC.Time(0, 0), u"00")
    elif data_type == "RTC::TimedBoolean":
        return RTC.TimedBoolean(RTC.Time(0, 0), False)
    elif data_type == "RTC::TimedOctet":
        return RTC.TimedOctet(RTC.Time(0, 0), 0)
    elif data_type == "RTC::TimedString":
        return RTC.TimedString(RTC.Time(0, 0), "")
    elif data_type == "RTC::TimedWString":
        return RTC.TimedWString(RTC.Time(0, 0), u"")
    elif data_type == "RTC::TimedShortSeq":
        return RTC.TimedShortSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedLongSeq":
        return RTC.TimedLongSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedUShortSeq":
        return RTC.TimedUShortSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedULongSeq":
        return RTC.TimedULongSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedFloatSeq":
        return RTC.TimedFloatSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedDoubleSeq":
        return RTC.TimedDoubleSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedCharSeq":
        return RTC.TimedCharSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedWCharSeq":
        return RTC.TimedWCharSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedBooleanSeq":
        return RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedOctetSeq":
        return RTC.TimedOctetSeq(RTC.Time(0, 0), "")
    elif data_type == "RTC::TimedStringSeq":
        return RTC.TimedStringSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::TimedWStringSeq":
        return RTC.TimedWStringSeq(RTC.Time(0, 0), [])
    elif data_type == "RTC::RGBColour":
        return RTC.RGBColour(0.0, 0.0, 0.0)
    elif data_type == "RTC::Point2D":
        return RTC.Point2D(0.0, 0.0)
    elif data_type == "RTC::Vector2D":
        return RTC.Vector2D(0.0, 0.0)
    elif data_type == "RTC::Pose2D":
        return RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0)
    elif data_type == "RTC::Velocity2D":
        return RTC.Velocity2D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Acceleration2D":
        return RTC.Acceleration2D(0.0, 0.0)
    elif data_type == "RTC::PoseVel2D":
        return RTC.PoseVel2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Velocity2D(0.0, 0.0, 0.0))
    elif data_type == "RTC::Size2D":
        return RTC.Size2D(0.0, 0.0)
    elif data_type == "RTC::Geometry2D":
        return RTC.Geometry2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Size2D(0.0, 0.0))
    elif data_type == "RTC::Covariance2D":
        return RTC.Covariance2D(*([0.0]*6))
    elif data_type == "RTC::PointCovariance2D":
        return RTC.PointCovariance2D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Carlike":
        return RTC.Carlike(0.0, 0.0)
    elif data_type == "RTC::SpeedHeading2D":
        return RTC.SpeedHeading2D(0.0, 0.0)
    elif data_type == "RTC::Point3D":
        return RTC.Point3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Vector3D":
        return RTC.Vector3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Orientation3D":
        return RTC.Orientation3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Pose3D":
        return RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::Velocity3D":
        return RTC.Velocity3D(*([0.0]*6))
    elif data_type == "RTC::AngularVelocity3D":
        return RTC.AngularVelocity3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Acceleration3D":
        return RTC.Acceleration3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::AngularAcceleration3D":
        return RTC.AngularAcceleration3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::PoseVel3D":
        return RTC.PoseVel3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Velocity3D(*([0.0]*6)))
    elif data_type == "RTC::Size3D":
        return RTC.Size3D(0.0, 0.0, 0.0)
    elif data_type == "RTC::Geometry3D":
        return RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::Covariance3D":
        return RTC.Covariance3D(*([0.0]*21))
    elif data_type == "RTC::SpeedHeading3D":
        return RTC.SpeedHeading3D(0.0, RTC.Orientation3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::OAP":
        return RTC.OAP(*([RTC.Vector3D(0.0, 0.0, 0.0)]*3))
    elif data_type == "RTC::TimedRGBColour":
        return RTC.TimedRGBColour(RTC.Time(0, 0), RTC.RGBColour(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedPoint2D":
        return RTC.TimedPoint2D(RTC.Time(0, 0), RTC.Point2D(0.0, 0.0))
    elif data_type == "RTC::TimedVector2D":
        return RTC.TimedVector2D(RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
    elif data_type == "RTC::TimedPose2D":
        return RTC.TimedPose2D(RTC.Time(0, 0), RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0))
    elif data_type == "RTC::TimedVelocity2D":
        return RTC.TimedVelocity2D(RTC.Time(0, 0), RTC.Velocity2D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedAcceleration2D":
        return RTC.TimedAcceleration2D(RTC.Time(0, 0), RTC.Acceleration2D(0.0, 0.0))
    elif data_type == "RTC::TimedPoseVel2D":
        return RTC.TimedPoseVel2D(RTC.Time(0, 0), RTC.PoseVel2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Velocity2D(0.0, 0.0, 0.0)))
    elif data_type == "RTC::TimedSize2D":
        return RTC.TimedSize2D(RTC.Time(0, 0), RTC.Size2D(0.0, 0.0))
    elif data_type == "RTC::TimedGeometry2D":
        return RTC.TimedGeometry2D(RTC.Time(0, 0), RTC.Geometry2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Size2D(0.0, 0.0)))
    elif data_type == "RTC::TimedCovariance2D":
        return RTC.TimedCovariance2D(RTC.Time(0, 0), RTC.Covariance2D(*([0.0]*6)))
    elif data_type == "RTC::TimedPointCovariance2D":
        return RTC.TimedPointCovariance2D(RTC.Time(0, 0), RTC.PointCovariance2D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedCarlike":
        return RTC.TimedCarlike(RTC.Time(0, 0), RTC.Carlike(0.0, 0.0))
    elif data_type == "RTC::TimedSpeedHeading2D":
        return RTC.TimedSpeedHeading2D(RTC.Time(0, 0), RTC.SpeedHeading2D(0.0, 0.0))
    elif data_type == "RTC::TimedPoint3D":
        return RTC.TimedPoint3D(RTC.Time(0, 0), RTC.Point3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedVector3D":
        return RTC.TimedVector3D(RTC.Time(0, 0), RTC.Vector3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedOrientation3D":
        return RTC.TimedOrientation3D(RTC.Time(0, 0), RTC.Orientation3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedPose3D":
        return RTC.TimedPose3D(RTC.Time(0, 0), RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)))
    elif data_type == "RTC::TimedVelocity3D":
        return RTC.TimedVelocity3D(RTC.Time(0, 0), RTC.Velocity3D(*([0.0]*6)))
    elif data_type == "RTC::TimedAngularVelocity3D":
        return returnRTC.TimedAngularVelocity3D(RTC.Time(0, 0), RTC.AngularVelocity3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedAcceleration3D":
        return RTC.TimedAcceleration3D(RTC.Time(0, 0), RTC.Acceleration3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedAngularAcceleration3D":
        return RTC.TimedAngularAcceleration3D(RTC.Time(0, 0), RTC.AngularAcceleration3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedPoseVel3D":
        return RTC.TimedPoseVel3D(RTC.Time(0, 0), RTC.PoseVel3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Velocity3D(*([0.0]*6))))
    elif data_type == "RTC::TimedSize3D":
        return RTC.TimedSize3D(RTC.Time(0, 0), RTC.Size3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::TimedGeometry3D":
        return RTC.TimedGeometry3D(RTC.Time(0, 0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)))
    elif data_type == "RTC::TimedCovariance3D":
        return RTC.TimedCovariance3D(RTC.Time(0, 0), RTC.Covariance3D(*([0.0]*21)))
    elif data_type == "RTC::TimedSpeedHeading3D":
        return RTC.TimedSpeedHeading3D(RTC.Time(0, 0), RTC.SpeedHeading3D(0.0, RTC.Orientation3D(0.0, 0.0, 0.0)))
    elif data_type == "RTC::TimedOAP":
        return RTC.TimedOAP(RTC.Time(0, 0), RTC.OAP(*([RTC.Vector3D(0.0, 0.0, 0.0)]*3)))
    elif data_type == "RTC::Quaternion":
        return RTC.Quaternion(*([0.0]*4))
    elif data_type == "RTC::TimedQuaternion":
        return RTC.TimedQuaternion(RTC.Time(0, 0), RTC.Quaternion(*([0.0]*4)))
    elif data_type == "RTC::ActArrayActuatorPos":
        return RTC.ActArrayActuatorPos(RTC.Time(0, 0), 0, 0.0)
    elif data_type == "RTC::ActArrayActuatorSpeed":
        return RTC.ActArrayActuatorSpeed(RTC.Time(0, 0), 0, 0.0)
    elif data_type == "RTC::ActArrayActuatorCurrent":
        return RTC.ActArrayActuatorCurrent(RTC.Time(0, 0), 0, 0.0)
    elif data_type == "RTC::Actuator":
        return RTC.Actuator(0.0, 0.0, 0.0, 0.0, RTC.ACTUATOR_STATUS_IDLE)
    elif data_type == "RTC::ActArrayState":
        return RTC.ActArrayState(RTC.Time(0, 0), [])
    elif data_type == "RTC::ActArrayActuatorGeometry":
        return RTC.ActArrayActuatorGeometry(RTC.ACTARRAY_ACTUATORTYPE_LINEAR, 0.0, RTC.Orientation3D(0.0, 0.0, 0.0), RTC.Vector3D(0.0, 0.0, 0.0), 0.0, 0.0, 0.0, 0.0, False)
    elif data_type == "RTC::ActArrayGeometry":
        return RTC.ActArrayGeometry(RTC.TimedGeometry3D(RTC.Time(0, 0), RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), []))
    elif data_type == "RTC::BumperGeometry":
        return RTC.BumperGeometry(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0), 0.0)
    elif data_type == "RTC::BumperArrayGeometry":
        return RTC.BumperArrayGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), [])
    elif data_type == "RTC::CameraImage":
        return RTC.CameraImage(RTC.Time(0, 0), 0, 0, 0, "", 0.0, "")
    elif data_type == "RTC::CameraInfo":
        return RTC.CameraInfo(RTC.Vector2D(0.0, 0.0), RTC.Point2D(0.0, 0.0), 0.0, 0.0, 0.0, 0.0)
    elif data_type == "RTC::FiducialInfo":
        return RTC.FiducialInfo(0, RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0), RTC.Size3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::Fiducials":
        return RTC.Fiducials(RTC.Time(0, 0), [])
    elif data_type == "RTC::FiducialFOV":
        return RTC.FiducialFOV(0.0, 0.0, 0.0)
    elif data_type == "RTC::GPSTime":
        return RTC.GPSTime(0, 0)
    elif data_type == "RTC::GPSData":
        return RTC.GPSData(RTC.Time(0, 0), RTC.GPSTime(0, 0), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, RTC.GPS_FIX_NONE)
    elif data_type == "RTC::GripperState":
        return RTC.GripperState(RTC.Time(0, 0), RTC.GRIPPER_STATE_UNKNOWN)
    elif data_type == "RTC::INSData":
        return RTC.INSData(RTC.Time(0, 0), 0.0, 0.0, 0.0, 0.0, RTC.Velocity3D(*([0.0]*6)), RTC.Orientation3D(0.0, 0.0, 0.0))
    elif data_type == "RTC::LimbState":
        return RTC.LimbState(RTC.Time(0, 0), RTC.OAP(*([RTC.Vector3D(0.0, 0.0, 0.0)]*3)), RTC.LIMB_STATUS_IDLE)
    elif data_type == "RTC::Hypothesis2D":
        return RTC.Hypothesis2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Covariance2D(*([0.0]*6)), 0.0)
    elif data_type == "RTC::Hypotheses2D":
        return RTC.Hypotheses2D(RTC.Time(0, 0), [])
    elif data_type == "RTC::Hypothesis3D":
        return RTC.Hypothesis3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)
    elif data_type == "RTC::Hypotheses3D":
        return RTC.Hypotheses3D(RTC.Time(0, 0), [RTC.Hypothesis3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Covariance3D(*([0.0]*21)), 0.0)])
    elif data_type == "RTC::OGMapConfig":
        return RTC.OGMapConfig(0.0, 0.0, 0, 0, RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0))
    elif data_type == "RTC::OGMapTile":
        return RTC.OGMapTile(0, 0, 0, 0, "")
    elif data_type == "RTC::PointFeature":
        return RTC.PointFeature(0.0, RTC.Point2D(0.0, 0.0), RTC.PointCovariance2D(0.0, 0.0, 0.0))
    elif data_type == "RTC::PoseFeature":
        return RTC.PoseFeature(0.0, RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), RTC.Covariance2D(*([0.0]*6)))
    elif data_type == "RTC::LineFeature":
        return RTC.LineFeature(0.0, 0.0, 0.0, RTC.PointCovariance2D(0.0, 0.0, 0.0), RTC.Point2D(0.0, 0.0), RTC.Point2D(0.0, 0.0), False, False)
    elif data_type == "RTC::Features":
        return RTC.Features(RTC.Time(0, 0), [], [], [])
    elif data_type == "RTC::MultiCameraImages":
        return RTC.MultiCameraImages(RTC.Time(0, 0), [])
    elif data_type == "RTC::MulticameraGeometry":
        return RTC.MulticameraGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), [RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0))])
    elif data_type == "RTC::Waypoint2D":
        return RTC.Waypoint2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), 0.0, 0.0, RTC.Time(0, 0), RTC.Velocity2D(0.0, 0.0, 0.0))
    elif data_type == "RTC::Path2D":
        return RTC.Path2D(RTC.Time(0, 0), [RTC.Waypoint2D(RTC.Pose2D(RTC.Point2D(0.0, 0.0), 0.0), 0.0, 0.0, RTC.Time(0, 0), RTC.Velocity2D(0.0, 0.0, 0.0))])
    elif data_type == "RTC::Waypoint3D":
        return RTC.Waypoint3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), 0.0, 0.0, RTC.Time(0, 0), RTC.Velocity3D(*([0.0]*6)))
    elif data_type == "RTC::Path3D":
        return RTC.Path3D(RTC.Time(0, 0), [])
    elif data_type == "RTC::PointCloudPoint":
        return RTC.PointCloudPoint(RTC.Point3D(0.0, 0.0, 0.0), RTC.RGBColour(0.0, 0.0, 0.0))
    elif data_type == "RTC::PointCloud":
        return RTC.PointCloud(RTC.Time(0, 0), [])
    elif data_type == "RTC::PanTiltAngles":
        return RTC.PanTiltAngles(RTC.Time(0, 0), 0.0, 0.0)
    elif data_type == "RTC::RangerGeometry":
        return RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), [])
    elif data_type == "RTC::RangerConfig":
        return RTC.RangerConfig(*([0.0]*7))
    elif data_type == "RTC::RangeData":
        return RTC.RangeData(RTC.Time(0, 0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), []), RTC.RangerConfig(*([0.0]*7)))
    elif data_type == "RTC::IntensityData":
        return RTC.IntensityData(RTC.Time(0, 0), [], RTC.RangerGeometry(RTC.Geometry3D(RTC.Pose3D(RTC.Point3D(0.0, 0.0, 0.0), RTC.Orientation3D(0.0, 0.0, 0.0)), RTC.Size3D(0.0, 0.0, 0.0)), []), RTC.RangerConfig(*([0.0]*7)))
    else:
        return None


##
# @class RTCD
# @brief RTC Development Tools
#
# 実行中に動的に処理を書き換えるRTC
#
#
class EditRTC(OpenRTM_aist.DataFlowComponentBase):

    ##
    # @brief constructor
    # @param manager Maneger Object
    #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self.module = None
        self.module_list = {}
        self.exec_mutex = threading.RLock()

        # if not os.path.exists(self.workdir):
        #	os.mkdir(self.workdir)
        # sys.path.append(os.path.abspath(self.workdir))

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">

        # </rtc-template>

    ##
    #
    # The initialize action (on CREATED->ALIVE transition)
    # formaer rtc_init_entry()
    #
    # @return RTC::ReturnCode_t
    #
    #

    def onInitialize(self):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onInitialize(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The finalize action (on ALIVE->END transition)
        # formaer rtc_exiting_entry()
        #
        # @return RTC::ReturnCode_t

        #

    def onFinalize(self):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onFinalize(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The startup action when ExecutionContext startup
        # former rtc_starting_entry()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onStartup(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onStartup(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The shutdown action when ExecutionContext stop
        # former rtc_stopping_entry()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onShutdown(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onShutdown(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The activated action (Active state entry action)
        # former rtc_active_entry()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onActivated(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onActivated(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The deactivated action (Active state exit action)
        # former rtc_active_exit()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onDeactivated(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onDeactivated(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The execution action that is invoked periodically
        # former rtc_active_do()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onExecute(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onExecute(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The aborting action when main logic error occurred.
        # former rtc_aborting_entry()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onAborting(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onAborting(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The error action in ERROR state
        # former rtc_error_do()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onError(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onError(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The reset action that is invoked resetting
        # This is same but different the former rtc_init_entry()
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onReset(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onReset(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The state update action that is invoked after onExecute() action
        # no corresponding operation exists in OpenRTm-aist-0.2.0
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #

        #
    def onStateUpdate(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onStateUpdate(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

        ##
        #
        # The action that is invoked when execution context's rate is changed
        # no corresponding operation exists in OpenRTm-aist-0.2.0
        #
        # @param ec_id target ExecutionContext Id
        #
        # @return RTC::ReturnCode_t
        #
        #
    def onRateChanged(self, ec_id):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.onRateChanged(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

    ##
    # @brief シミュレーション更新後実行関数
    # @param self
    #
    def inputFromSimulator(self):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.inputFromSimulator(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

    ##
    # @brief シミュレーション更新前実行関数
    # @param self
    #
    def outputToSimulator(self):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.outputToSimulator(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

    ##
    # @brief ボディ設定関数
    # @param self
    # @param body ボディオブジェクト
    #
    def setBody(self, body):
        self.ioBody = body
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        ret = RTC.RTC_OK
        if self.module is not None:
            try:
                ret = self.module.setBody(self)
            except:
                log = traceback.format_exc()
                print(log)
                ret = RTC.RTC_ERROR
        return ret

    ##
    # @brief モジュールファイル設定
    # @param self
    # @param filepath ファイルパス
    #

    def setModule(self, filepath):

        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        dir_path = os.path.dirname(filepath)
        name, ext = os.path.splitext(os.path.basename(filepath))
        sys.path.append(dir_path)
        try:
            self.module = importlib.import_module(name)

            importlib.reload(self.module)
        except:
            log = traceback.format_exc()
            print(log)

    ##
    # @brief コンフィギュレーションパラメータ値再設定
    # @param self
    # @param conf コンフィギュレーション
    # @param set_name コンフィギュレーションセット名
    # @param param_name パラメータ名
    # @param value 値
    #

    def setParam(self, conf, set_name, param_name, value=None):

        try:
            confset = conf.get_configuration_set(set_name)
        except:
            confset = SDOPackage.ConfigurationSet(set_name, "", [])
            conf.add_configuration_set(confset)

        confData = confset.configuration_data
        prop = OpenRTM_aist.Properties()
        OpenRTM_aist.NVUtil.copyToProperties(prop, confData)
        if value is None:
            prop.removeNode(param_name)

        else:
            prop.setProperty(param_name, value)
        OpenRTM_aist.NVUtil.copyFromProperties(confData, prop)

        confset.configuration_data = confData

        conf.set_configuration_set_values(confset)

    ##
    # @brief コンフィギュレーションパラメータ削除
    # @param self
    # @param name パラメータ名
    #

    def deleteConfigParam(self, name):
        conf = self.get_configuration()
        #self.setParam(conf, "default",name)
        #self.setParam(conf, "__widget__",name)
        #self.setParam(conf, "__constraints__",name)
        # conf.activate_configuration_set("default")

    ##
    # @brief コンフィギュレーションパラメータ追加
    # @param self
    # @param name パラメータ名
    # @param data_type データ型
    # @param defalut_value デフォルト値
    # @param constraints 制約
    # @param widget ウィジェット
    # @param step ステップ値
    #
    def setConfigParam(self, name, data_type, defalut_value, constraints, widget, step):
        conf = self.get_configuration()
        self.setParam(conf, "default", name, defalut_value)
        widget_name = widget
        step = step.replace(" ", "")
        step = step.replace("\t", "")
        if step:
            widget_name = widget_name+"."+step
        self.setParam(conf, "__widget__", name, widget_name)
        self.setParam(conf, "__constraints__", name, constraints)
        conf.activate_configuration_set("default")

        data_name = "_"+name
        self.__dict__[data_name] = [self.getValue(defalut_value, data_type)]

        self.bindParameter(name, self.__dict__[data_name], defalut_value)
        return data_name

    ##
    # @brief コンフィギュレーションパラメータ値変換
    # @param self
    # @param v 変換前の値
    # @param type 返還後の型
    # @return 変換後の値
    #
    def getValue(self, v, type):
        try:
            if type == "int" or type == "short":
                return int(v)
            elif type == "long":
                return int(v)
            elif type == "float" or type == "double":
                return float(v)
            elif type == "string":
                return v
            else:
                return v
        except:
            return v

    ##
    # @brief サービス名一覧取得
    # @param self
    # @param idl_file IDLファイル名
    # @param dir_path ディレクトリパス
    # @param idl_path IDLインクルードパス
    #
    def getServiceNameList(self, idl_file, dir_path, idl_path):

        if os.name == 'posix':
            com = 'omniidl -I"$RTM_ROOT/rtm/idl" -bcreateTemplate ' + idl_file
            com = com.replace("\\", "/")
            com = com.split(" ")
        elif os.name == 'nt':
            com = 'omniidl -I"%RTM_ROOT%rtm\\idl" -bcreateTemplate ' + idl_file
            com = com.replace("/", "\\")

        sp = subprocess.Popen(com, stdin=subprocess.PIPE,
                              stdout=subprocess.PIPE)
        ret = sp.communicate()[0]
        ret = ret.replace("\r", "")
        ret = ret.split("\n")

        filelist = []

        classlist = {}

        for r in ret:
            if r.find("file:") != -1:
                s = r.replace("file:", "")
                if os.path.exists(s):
                    filelist.append(s)
                else:
                    ps = os.path.join(dir_path, s)
                    if os.path.exists(ps):
                        filelist.append(ps)
                    elif idl_path != "":
                        ps = os.path.join(idl_path, s)
                        if os.path.exists(ps):
                            filelist.append(ps)
            elif r.find("name:") != -1:
                s = r.replace("name:", "")
                classlist[s] = []
            elif r.find("operation:") != -1:
                s = r.replace("operation:", "")
                n = s.split("#")[0]
                if n in classlist:
                    classlist[n].append(s.split("#")[1])

        return filelist, classlist
    ##
    # @brief IDLコンパイル実行
    # @param self
    # @param filelist ファイル一覧
    # @param idl_path IDLインクルードパス
    # @param dir_path ディレクトリパス
    # @param workdir Iワークディレクトリ
    #

    def idlCompile(self, filelist, idl_path, dir_path, workdir):
        if os.name == 'posix':
            com = 'omniidl -I"$RTM_ROOT/rtm/idl" ' + '-C"' + workdir + '"'
        elif os.name == 'nt':
            com = 'omniidl -I"%RTM_ROOT%rtm\\idl" ' + '-C"' + workdir + '"'
        if idl_path != "":
            com += ' -I"' + idl_path + '" '
        if dir_path != "":
            com += ' -I"' + dir_path + '" '
        com += '-bpython '
        for f in filelist:
            basename = os.path.basename(f)
            copyname = os.path.join(self.workdir, basename)
            copyname = os.path.relpath(copyname)
            shutil.copyfile(f, copyname)
            com += copyname + " "

        if os.name == 'posix':
            com = com.replace("\\", "/")
            com = com.split(" ")
        elif os.name == 'nt':
            com = com.replace("/", "\\")

        sp = subprocess.Popen(com, stdin=subprocess.PIPE,
                              stdout=subprocess.PIPE)
        sp.communicate()
    ##
    # @brief サービスポート設定関数
    # @param self
    # @param name ポート名
    # @param interface_name インターフェース名
    # @param interface_dir インターフェース方向
    # @param idl_file IDLファイルパス
    # @param interface_type インターフェース型
    # @param idl_path IDLインクルードパス
    #

    def setServicePort(self, name, interface_name, interface_dir, idl_file, interface_type, idl_path):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        data_name = "_i_" + interface_name
        port_name = "_" + interface_name + "Port"

        dir_path = os.path.dirname(idl_file)

        filelist, classlist = self.getServiceNameList(
            idl_file, dir_path, idl_path)

        if len(filelist) == 0:
            return "", "", [], {}, []

        self.idlCompile(filelist, idl_path, dir_path, self.workdir)

        idl_name, ext = os.path.splitext(os.path.basename(idl_file))
        module_name = "_GlobalIDL"

        spif = interface_type.split(".")
        interface_class = spif[0]

        if len(spif) >= 2:
            module_name = spif[0]
            interface_class = spif[1]
        import_name = {}
        #s = "idl/ManipulatorCommonInterface_MiddleLevel_idl.py"
        #name, ext = os.path.splitext(os.path.basename(s))
        # sys.path.append("idl")
        import_name["idl"] = idl_name+"_idl"
        import_name["module"] = module_name
        import_name["module__POA"] = module_name+"__POA"

        interface_idl = importlib.import_module(import_name["idl"])
        module_obj = importlib.import_module(import_name["module"])
        module_obj__POA = importlib.import_module(import_name["module__POA"])
        #import ManipulatorCommonInterface_MiddleLevel_idl
        #import JARA_ARM, JARA_ARM__POA
        self.__dict__[port_name] = OpenRTM_aist.CorbaPort(name)
        if interface_dir == "Required":
            self.__dict__[data_name] = OpenRTM_aist.CorbaConsumer(
                interfaceType=module_obj.__dict__[interface_class])

        elif interface_dir == "Provided":
            pass
        resname = interface_type.replace(".", ":")
        self.__dict__[port_name].registerConsumer(
            name, resname, self.__dict__[data_name])
        self.addPort(self.__dict__[port_name])

        return data_name, port_name, filelist, classlist, import_name

    ##
    # @brief データポート設定関数
    # @param self
    # @param name ポート名
    # @param port_type ポート型
    # @param data_type データ型
    #

    def setDataPort(self, name, port_type, data_type):
        guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
        data_name = "_d_"+name
        self.__dict__[data_name] = create_data(data_type)
        port_name = "_"+name

        if port_type == "DataInPort":
            port_name += "In"
            self.__dict__[port_name] = OpenRTM_aist.InPort(
                name, self.__dict__[data_name])
            self.addInPort(name, self.__dict__[port_name])
        elif port_type == "DataOutPort":
            port_name += "Out"
            self.__dict__[port_name] = OpenRTM_aist.OutPort(
                name, self.__dict__[data_name])
            self.addOutPort(name, self.__dict__[port_name])
        return data_name, port_name

    ##
    # @brief 外部モジュール再読み込み
    # @param self
    # @param module_names モジュールリスト
    #

    def update_modulelist(self, module_names):
        self.module_list = {}
        for k, m in module_names.items():
            try:
                mod = __import__(m)
                importlib.reload(mod)
                self.module_list[k] = mod
            except:
                log = traceback.format_exc()
                print(log)


def EditRTCInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=editrtc_spec)
    manager.registerFactory(profile,
                            EditRTC,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    EditRTCInit(manager)

    # Create a component
    comp = manager.createComponent("EditRTC")


def main():

    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
