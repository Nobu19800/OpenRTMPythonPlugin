#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file TankIoRTC_Py.py
 @brief TankIoRTC using Python
 @date $Date$

 @author 宮本 信彦 n-miyamoto@aist.go.jp
 産業技術総合研究所 ロボットイノベーション研究センター
 ロボットソフトウェアプラットフォーム研究チーム

 LGPL

"""

import cnoid.OpenRTMPythonPlugin
import cnoid.Body
import time
import sys
import RTC
import OpenRTM_aist
sys.path.append(".")

# Import RTM module

# from CnoidLink import *


# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
tankiortc_py_spec = ["implementation_id", "TankIoRTC_Py",
                     "type_name",         "TankIoRTC_Py",
                     "description",       "TankIoRTC using Python",
                     "version",           "1.0.0",
                     "vendor",            "AIST",
                     "category",          "Simulator",
                     "activity_type",     "STATIC",
                     "max_instance",      "1",
                     "language",          "Python",
                     "lang_type",         "SCRIPT",
                     "conf.default.wheel_radius", "0.05",
                     "conf.default.wheel_distance", "0.2",
                     "conf.__widget__.wheel_radius", "text",
                     "conf.__widget__.wheel_distance", "text",
                     "conf.__type__.wheel_radius", "double",
                     "conf.__type__.wheel_distance", "double",
                     ""]
# </rtc-template>

##
# @class TankIoRTC_Py
# @brief TankIoRTC using Python
#
# Choreonoid付属TankIoRTCのPython版
#
#


class TankIoRTC_Py(OpenRTM_aist.DataFlowComponentBase):

    ##
    # @brief constructor
    # @param manager Maneger Object
    #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_velocities = RTC.TimedVelocity2D(
            RTC.Time(0, 0), RTC.Velocity2D(0.0, 0.0, 0.0))
        """
		車体の目標速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s, rad/s
		"""
        self._velocitiesIn = OpenRTM_aist.InPort(
            "velocities", self._d_velocities)

        self._d_torques = RTC.TimedDoubleSeq(RTC.Time(0, 0), [])
        """
		アームのトルクを入力
		 - Type: RTC::TimedDoubleSeq
		 - Number: 2
		 - Unit: N・m
		"""
        self._torquesIn = OpenRTM_aist.InPort("torques", self._d_torques)

        self._d_lightSwitch = RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
        """
		ライトのオンオフ
		 - Type: RTC::TimedBooleanSeq
		"""
        self._lightSwitchIn = OpenRTM_aist.InPort(
            "lightSwitch", self._d_lightSwitch)

        self._d_angles = RTC.PanTiltAngles(RTC.Time(0, 0), 0.0, 0.0)
        """
		カメラの角度
		 - Type: RTC::PanTiltAngles
		 - Unit: rad
		"""
        self._anglesOut = OpenRTM_aist.OutPort("angles", self._d_angles)

        self.body = None

        """
		車輪半径
		 - Name: wheel_radius wheel_radius
		 - DefaultValue: 0.05
		 - Unit: m
		"""
        self._wheel_radius = [0.05]

        """
		車輪間の距離
		 - Name: wheel_distance wheel_distance
		 - DefaultValue: 0.2
		 - Unit: m
		"""
        self._wheel_distance = [0.2]

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">

        # </rtc-template>

    # ボディオブジェクト設定関数
    def setBody(self, body):

        self.ioBody = body

        # Linkオブジェクト取得
        self.cannonY = self.ioBody.link("TURRET_Y")
        self.cannonP = self.ioBody.link("TURRET_P")
        self.crawlerL = self.ioBody.link("TRACK_L")
        self.crawlerR = self.ioBody.link("TRACK_R")
        self.cannonY.setActuationMode(cnoid.Body.Link.JointTorque)
        self.cannonP.setActuationMode(cnoid.Body.Link.JointTorque)
        cnoid.OpenRTMPythonPlugin.setJointSurfaceVelocity(self.crawlerL)
        cnoid.OpenRTMPythonPlugin.setJointSurfaceVelocity(self.crawlerR)
        # self.crawlerL.setActuationMode(512)
        # self.crawlerR.setActuationMode(512)
        # Lightオブジェクト取得
        #self.light = self.ioBody.getLight("MainLight")

    # センサの計測値などをアウトポートから出力する処理等を記述する関数
    # シミュレーションステップ後に実行される

    def inputFromSimulator(self):
        if self.ioBody:
            # 砲台の角度取得、格納
            self._d_angles.pan = self.cannonY.q
            self._d_angles.tilt = self.cannonP.q

            # 砲台の角度出力
            OpenRTM_aist.setTimestamp(self._d_angles)
            self._anglesOut.write()

    # アクチュエータのトルクなどをインポートから入力する処理等を記述する関数
    # シミュレーションステップ前に実行される

    def outputToSimulator(self):
        if self.ioBody:
            # 砲台のトルク入力
            if self._torquesIn.isNew():
                data = self._torquesIn.read()
                self.cannonY.u = data.data[0]
                self.cannonP.u = data.data[1]
            # 車体の速度入力
            if self._velocitiesIn.isNew():
                data = self._velocitiesIn.read()
                vx = data.data.vx
                va = data.data.va

                rms = (vx + va*self._wheel_distance[0])/self._wheel_radius[0]
                lms = (vx - va*self._wheel_distance[0])/self._wheel_radius[0]

                # クローラーの速度入力
                cnoid.OpenRTMPythonPlugin.set_dq_target(self.crawlerL, rms)
                cnoid.OpenRTMPythonPlugin.set_dq_target(self.crawlerR, lms)
                #self.crawlerL.dq = lms
                #self.crawlerR.dq = rms
            # ライトのオンオフ入力
            if self._lightSwitchIn.isNew():
                data = self._lightSwitchIn.read()
                cnoid.OpenRTMPythonPlugin.light_on(
                    self.ioBody, "Light", data.data[0])
                # self.light.on(data.data[0])
                # self.light.notifyStateChange()

    ##
    #
    # The initialize action (on CREATED->ALIVE transition)
    # formaer rtc_init_entry()
    #
    # @return RTC::ReturnCode_t
    #
    #

    def onInitialize(self):
        # Bind variables and configuration variable
        self.bindParameter("wheel_radius", self._wheel_radius, "0.05")
        self.bindParameter("wheel_distance", self._wheel_distance, "0.2")

        # Set InPort buffers
        self.addInPort("velocities", self._velocitiesIn)
        self.addInPort("torques", self._torquesIn)
        self.addInPort("lightSwitch", self._lightSwitchIn)

        # Set OutPort buffers
        self.addOutPort("angles", self._anglesOut)

        # Set service provider to Ports

        # Set service consumers to Ports

        # Set CORBA Service Ports

        return RTC.RTC_OK

    #	##
    #	#
    #	# The finalize action (on ALIVE->END transition)
    #	# formaer rtc_exiting_entry()
    #	#
    #	# @return RTC::ReturnCode_t
    #
    #	#
    # def onFinalize(self):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The startup action when ExecutionContext startup
    #	# former rtc_starting_entry()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onStartup(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The shutdown action when ExecutionContext stop
    #	# former rtc_stopping_entry()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onShutdown(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The activated action (Active state entry action)
    #	# former rtc_active_entry()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    def onActivated(self, ec_id):
        self.inputFromSimulator()
        return RTC.RTC_OK

    #	##
    #	#
    #	# The deactivated action (Active state exit action)
    #	# former rtc_active_exit()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onDeactivated(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The execution action that is invoked periodically
    #	# former rtc_active_do()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onExecute(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The aborting action when main logic error occurred.
    #	# former rtc_aborting_entry()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onAborting(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The error action in ERROR state
    #	# former rtc_error_do()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onError(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The reset action that is invoked resetting
    #	# This is same but different the former rtc_init_entry()
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onReset(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The state update action that is invoked after onExecute() action
    #	# no corresponding operation exists in OpenRTm-aist-0.2.0
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#

    #	#
    # def onStateUpdate(self, ec_id):
    #
    #	return RTC.RTC_OK

    #	##
    #	#
    #	# The action that is invoked when execution context's rate is changed
    #	# no corresponding operation exists in OpenRTm-aist-0.2.0
    #	#
    #	# @param ec_id target ExecutionContext Id
    #	#
    #	# @return RTC::ReturnCode_t
    #	#
    #	#
    # def onRateChanged(self, ec_id):
    #
    #	return RTC.RTC_OK


def TankIoRTC_PyInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=tankiortc_py_spec)
    manager.registerFactory(profile,
                            TankIoRTC_Py,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    TankIoRTC_PyInit(manager)

    # Create a component
    comp = manager.createComponent("TankIoRTC_Py")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
