#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file JoystickPySDL2.py
 @brief Joystick using PySDL2
 @date $Date$

 @author 宮本 信彦 n-miyamoto@aist.go.jp
 産業技術総合研究所 ロボットイノベーション研究センター
 ロボットソフトウェアプラットフォーム研究チーム

 LGPL

"""
import sdl2
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
joystickpysdl2_spec = ["implementation_id", "JoystickPySDL2",
                       "type_name",         "JoystickPySDL2",
                       "description",       "Joystick using PySDL2",
                       "version",           "1.0.0",
                       "vendor",            "AIST",
                       "category",          "Device",
                       "activity_type",     "STATIC",
                       "max_instance",      "1",
                       "language",          "Python",
                       "lang_type",         "SCRIPT",
                       "conf.default.index", "0",

                       "conf.__widget__.index", "text",

                       "conf.__type__.index", "int",

                       ""]
# </rtc-template>

##
# @class JoystickPySDL2
# @brief Joystick using PySDL2
#
# PySDL2利用のジョイスティックコンポーネント
#
#


class JoystickPySDL2(OpenRTM_aist.DataFlowComponentBase):
    max_axis_value = 32768
    ##
    # @brief constructor
    # @param manager Maneger Object
    #

    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_axes_1 = RTC.TimedVector2D(
            RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
        """
		ジョイスティックの位置出力(-1.0～1.0)
		 - Type: RTC::TimedFloatSeq
		"""
        self._axes_1Out = OpenRTM_aist.OutPort("axes_1", self._d_axes_1)

        self._d_axes_2 = RTC.TimedVector2D(
            RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
        """
		ジョイスティックの位置出力(-1.0～1.0)
		 - Type: RTC::TimedFloatSeq
		"""
        self._axes_2Out = OpenRTM_aist.OutPort("axes_2", self._d_axes_2)

        self._d_buttons = RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
        """
		ボタンのオンオフ出力
		 - Type: RTC::TimedBooleanSeq
		"""
        self._buttonsOut = OpenRTM_aist.OutPort("buttons", self._d_buttons)

        self._d_hats = RTC.TimedBooleanSeq(RTC.Time(0, 0), [])
        """
		十字キーの入力を出力
		 - Type: RTC::TimedBooleanSeq
		 - Number: 4
		"""
        self._hatsOut = OpenRTM_aist.OutPort("hats", self._d_hats)

        self._d_balls = RTC.TimedVector2D(
            RTC.Time(0, 0), RTC.Vector2D(0.0, 0.0))
        """
		ボールの移動距離出力
		 - Type: RTC::TimedVector2D
		"""
        self._ballsOut = OpenRTM_aist.OutPort("balls", self._d_balls)

        # initialize of configuration-data.
        # <rtc-template block="init_conf_param">
        """
		接続しているJoystickの番号
		 - Name: index index
		 - DefaultValue: 0
		"""
        self._index = [0]

        # </rtc-template>

        self.stick = None

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
        self.bindParameter("index", self._index, "0")

        # Set InPort buffers

        # Set OutPort buffers
        self.addOutPort("axes_1", self._axes_1Out)
        self.addOutPort("axes_2", self._axes_2Out)
        self.addOutPort("buttons", self._buttonsOut)
        self.addOutPort("hats", self._hatsOut)
        self.addOutPort("balls", self._ballsOut)

        # Set service provider to Ports

        # Set service consumers to Ports

        # Set CORBA Service Ports

        sdl2.SDL_Init(sdl2.SDL_INIT_JOYSTICK)

        return RTC.RTC_OK

    #	##
    #	#
    #	# The finalize action (on ALIVE->END transition)
    #	# formaer rtc_exiting_entry()
    #	#
    #	# @return RTC::ReturnCode_t
    #
    #	#
    def onFinalize(self):
        # sdl2.SDL_QuitSubSystem(sdl2.SDL_INIT_JOYSTICK)
        # sdl2.SDL_Quit()
        return RTC.RTC_OK

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
        jcount = sdl2.joystick.SDL_NumJoysticks()
        if self._index[0] >= jcount:
            return RTC.RTC_ERROR

        self.stick = sdl2.joystick.SDL_JoystickOpen(self._index[0])

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
        if self.stick:
            sdl2.joystick.SDL_JoystickClose(self.stick)
            self.stick = None

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
        sdl2.joystick.SDL_JoystickUpdate()
        axes = sdl2.joystick.SDL_JoystickNumAxes(self.stick)
        for i in range(axes):
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, i)

        if axes >= 2:
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 0)
            self._d_axes_1.data.x = float(
                val) / float(JoystickPySDL2.max_axis_value)
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 1)
            self._d_axes_1.data.y = float(
                val) / float(JoystickPySDL2.max_axis_value)
            OpenRTM_aist.setTimestamp(self._d_axes_1)
            self._axes_1Out.write()
        if axes == 4:
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 2)
            self._d_axes_2.data.x = float(
                val) / float(JoystickPySDL2.max_axis_value)
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 3)
            self._d_axes_2.data.y = float(
                val) / float(JoystickPySDL2.max_axis_value)
            OpenRTM_aist.setTimestamp(self._d_axes_2)
            self._axes_2Out.write()
        elif axes == 5:
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 3)
            self._d_axes_2.data.x = float(
                val) / float(JoystickPySDL2.max_axis_value)
            val = sdl2.joystick.SDL_JoystickGetAxis(self.stick, 4)
            self._d_axes_2.data.y = float(
                val) / float(JoystickPySDL2.max_axis_value)
            OpenRTM_aist.setTimestamp(self._d_axes_2)
            self._axes_2Out.write()

        buttons = sdl2.joystick.SDL_JoystickNumButtons(self.stick)
        self._d_buttons.data = []
        for button in range(buttons):
            val = sdl2.joystick.SDL_JoystickGetButton(self.stick, button)
            if val == 0:
                self._d_buttons.data.append(False)
            else:
                self._d_buttons.data.append(True)

        OpenRTM_aist.setTimestamp(self._d_buttons)
        self._buttonsOut.write()

        hats = sdl2.joystick.SDL_JoystickNumHats(self.stick)
        if hats > 0:
            val = sdl2.joystick.SDL_JoystickGetHat(self.stick, 0)
            lb = val & 0x08
            bb = val & 0x04
            rb = val & 0x02
            ub = val & 0x01
            self._d_hats.data = [bool(ub), bool(rb), bool(bb), bool(lb)]
            OpenRTM_aist.setTimestamp(self._d_hats)
            self._buttonsOut.write()

        balls = sdl2.joystick.SDL_JoystickNumBalls(self.stick)
        if balls > 0:
            dx, dy = sdl2.joystick.SDL_JoystickGetBall(self.stick, 0)
            self._d_balls.data.x = dx
            self._d_balls.data.y = dy
            OpenRTM_aist.setTimestamp(self._d_balls)
            self._ballsOut.write()

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


def JoystickPySDL2Init(manager):
    profile = OpenRTM_aist.Properties(defaults_str=joystickpysdl2_spec)
    manager.registerFactory(profile,
                            JoystickPySDL2,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    JoystickPySDL2Init(manager)

    # Create a component
    comp = manager.createComponent("JoystickPySDL2")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
