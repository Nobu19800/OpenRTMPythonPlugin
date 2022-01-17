#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file TankJoystickControllerRTC_Py.py
 @brief TankJoystickControllerRTC using Python
 @date $Date$

 @author 宮本 信彦 n-miyamoto@aist.go.jp
 産業技術総合研究所 ロボットイノベーション研究センター
 ロボットソフトウェアプラットフォーム研究チーム

 LGPL

"""
import math
import OpenRTM_aist
import RTC
import sys
import time
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
tankjoystickcontrollerrtc_py_spec = ["implementation_id", "TankJoystickControllerRTC_Py",
                                     "type_name",         "TankJoystickControllerRTC_Py",
                                     "description",       "TankJoystickControllerRTC using Python",
                                     "version",           "1.0.0",
                                     "vendor",            "AIST",
                                     "category",          "Controller",
                                     "activity_type",     "STATIC",
                                     "max_instance",      "1",
                                     "language",          "Python",
                                     "lang_type",         "SCRIPT",
                                     "conf.default.timeStep", "0.001",
                                     "conf.default.KP", "200.0",
                                     "conf.default.KD", "50.0",

                                     "conf.__widget__.timeStep", "text",
                                     "conf.__widget__.KP", "text",
                                     "conf.__widget__.KD", "text",

                                     "conf.__type__.timeStep", "double",
                                     "conf.__type__.KP", "double",
                                     "conf.__type__.KD", "double",

                                     ""]
# </rtc-template>

##
# @class TankJoystickControllerRTC_Py
# @brief TankJoystickControllerRTC using Python
#
# Choreonoid付属TankJoystickControllerRTCのPython版
#
#


class TankJoystickControllerRTC_Py(OpenRTM_aist.DataFlowComponentBase):

    ##
    # @brief constructor
    # @param manager Maneger Object
    #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_angles = RTC.PanTiltAngles(RTC.Time(0, 0), 0.0, 0.0)
        """
		カメラの角度
		 - Type: RTC::PanTiltAngles
		 - Unit: rad
		"""
        self._anglesIn = OpenRTM_aist.InPort("angles", self._d_angles)

        self._d_axes_1 = RTC.TimedVector2D(
            RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
        """
		ジョイスティックの位置
		車輪の速さに対応
		 - Type: RTC::TimedVector2D
		"""
        self._axes_1In = OpenRTM_aist.InPort("axes_1", self._d_axes_1)

        self._d_axes_2 = RTC.TimedVector2D(
            RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
        """
		ジョイスティックの位置
		カメラの角度に対応
		 - Type: RTC::TimedVector2D
		"""
        self._axes_2In = OpenRTM_aist.InPort("axes_2", self._d_axes_2)

        self._d_buttons = RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
        """
		ボタン入力
		 - Type: RTC::TimedBooleanSeq
		"""
        self._buttonsIn = OpenRTM_aist.InPort("buttons", self._d_buttons)

        self._d_velocities = RTC.TimedVelocity2D(
            RTC.Time(0, 0), RTC.Velocity2D(0.0, 0.0, 0.0))
        """
		ロボットの速度
		 - Type: TimedVelocity2D
		 - Unit: m/s,rad/s
		"""
        self._velocitiesOut = OpenRTM_aist.OutPort(
            "velocities", self._d_velocities)

        self._d_torques = RTC.TimedDoubleSeq(RTC.Time(0, 0), [])
        """
		アームの関節トルク
		 - Type: RTC::TimedDoubleSeq
		 - Number: 2
		 - Unit: N・m
		"""
        self._torquesOut = OpenRTM_aist.OutPort("torques", self._d_torques)

        self._d_lightSwitch = RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
        """
		ライトのオンオフ
		 - Type: RTC::TimedBooleanSeq
		"""
        self._lightSwitchOut = OpenRTM_aist.OutPort(
            "lightSwitch", self._d_lightSwitch)

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">
        """
		シミュレーションのステップ時間
		 - Name: timeStep timeStep
		 - DefaultValue: 0.001
		 - Unit: s
		"""
        self._timeStep = [0.001]
        """
		比例ゲイン
		 - Name: KP KP
		 - DefaultValue: 200.0
		"""
        self._KP = [200.0]
        """
		微分ゲイン
		 - Name: KD KD
		 - DefaultValue: 50.0
		"""
        self._KD = [50.0]

        # </rtc-template>

        self.qref = [0.0, 0.0]
        self.qprev = [0.0, 0.0]
        self.axis_data = [0.0, 0.0]
        self.prevLightButtonState = False
        self.isLightOn = True

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
        self.bindParameter("timeStep", self._timeStep, "0.001")
        self.bindParameter("KP", self._KP, "200.0")
        self.bindParameter("KD", self._KD, "50.0")

        # Set InPort buffers
        self.addInPort("angles", self._anglesIn)
        self.addInPort("axes_1", self._axes_1In)
        self.addInPort("axes_2", self._axes_2In)
        self.addInPort("buttons", self._buttonsIn)

        # Set OutPort buffers
        self.addOutPort("velocities", self._velocitiesOut)
        self.addOutPort("torques", self._torquesOut)
        self.addOutPort("lightSwitch", self._lightSwitchOut)

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

        count = 100
        stime = 0.1
        for c in range(count):
            if self._anglesIn.isNew():
                data = self._anglesIn.read()
                self.qref[0] = data.pan
                self.qref[1] = data.tilt
                self.qprev[0] = data.pan
                self.qprev[1] = data.tilt

                break
            time.sleep(stime)
            if c == count-1:
                return RTC.RTC_ERROR

        self.axis_data = [0.0, 0.0]

        return RTC.RTC_OK

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

        return RTC.RTC_OK

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
        cannonAxisRatio = [-1.0, 1.0]
        KW = 0.002

        self._d_torques.data = [0.0, 0.0]
        if self._anglesIn.isNew():

            data = self._anglesIn.read()
            val = [data.pan, data.tilt]

            for i in range(2):
                q = val[i]
                dq = (q - self.qprev[i]) / self._timeStep[0]
                dqref = 0.0

                command = cannonAxisRatio[i] * self.axis_data[i]

                if math.fabs(command) > 0.2:

                    deltaq = command * KW

                    self.qref[i] += deltaq

                    dqref = deltaq / self._timeStep[0]

                self._d_torques.data[i] = self._KP[0] * \
                    (self.qref[i] - q) + self._KD[0] * (dqref - dq)

            self.qprev = val

            OpenRTM_aist.setTimestamp(self._d_torques)
            self._torquesOut.write()

        if self._axes_2In.isNew():

            data = self._axes_2In.read()

            self.axis_data = [data.data.y, data.data.x]

        if self._axes_1In.isNew():
            data = self._axes_1In.read()

            if math.fabs(data.data.x) < 0.2:
                data.data.x = 0
            if math.fabs(data.data.y) < 0.2:
                data.data.y = 0

            self._d_velocities.data.vx = -0.5*data.data.y
            self._d_velocities.data.vy = 0
            self._d_velocities.data.va = -1.0*data.data.x
            OpenRTM_aist.setTimestamp(self._d_velocities)
            self._velocitiesOut.write()

        if self._buttonsIn.isNew():
            data = self._buttonsIn.read()

            if len(data.data) > 0 and data.data[0]:

                if not self.prevLightButtonState:
                    self.isLightOn = not self.isLightOn
                    self._d_lightSwitch.data = [self.isLightOn]
                    OpenRTM_aist.setTimestamp(self._d_lightSwitch)
                    self._lightSwitchOut.write()

            self.prevLightButtonState = data.data[0]

        return RTC.RTC_OK

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


def TankJoystickControllerRTC_PyInit(manager):
    profile = OpenRTM_aist.Properties(
        defaults_str=tankjoystickcontrollerrtc_py_spec)
    manager.registerFactory(profile,
                            TankJoystickControllerRTC_Py,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    TankJoystickControllerRTC_PyInit(manager)

    # Create a component
    comp = manager.createComponent("TankJoystickControllerRTC_Py")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
