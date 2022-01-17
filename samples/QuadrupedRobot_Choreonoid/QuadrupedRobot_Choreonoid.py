#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file QuadrupedRobot_Choreonoid.py
 @brief Choreonoid Simulator Sample
 @date $Date$

 @author 宮本　信彦
 n-miyamoto@aist.go.jp
 産業技術総合研究所　ロボットイノベーション研究センター
 ロボットソフトウエアプラットフォーム研究チーム

 LGPL

"""
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
quadrupedrobot_choreonoid_spec = ["implementation_id", "QuadrupedRobot_Choreonoid",
                                  "type_name",         "QuadrupedRobot_Choreonoid",
                                  "description",       "Choreonoid Simulator Sample",
                                  "version",           "1.0.0",
                                  "vendor",            "AIST",
                                  "category",          "Simulator",
                                  "activity_type",     "STATIC",
                                  "max_instance",      "1",
                                  "language",          "Python",
                                  "lang_type",         "SCRIPT",
                                  ""]
# </rtc-template>

##
# @class QuadrupedRobot_Choreonoid
# @brief Choreonoid Simulator Sample
#
# Choreonoid OpenRTMプラグインサンプル(四足歩行ロボット)
#
#


class QuadrupedRobot_Choreonoid(OpenRTM_aist.DataFlowComponentBase):

    ##
    # @brief constructor
    # @param manager Maneger Object
    #
    def __init__(self, manager):
        OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

        self._d_in = OpenRTM_aist.instantiateDataType(RTC.TimedDoubleSeq)
        """
		関節角度
		 - Type: RTC::TimedDoubleSeq
		 - Number: 12
		 - Unit: rad
		"""
        self._inIn = OpenRTM_aist.InPort("in", self._d_in)

        self.ioBody = None
        self.joints = []
        self.target_pos = [0]*12
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
        # Bind variables and configuration variable

        # Set InPort buffers
        self.addInPort("in", self._inIn)

        # Set OutPort buffers

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

    def setBody(self, body):

        self.ioBody = body
        self.joints = []
        for i in range(0, 4):
            for j in range(0, 3):
                name = "LEG"+str(i)+str(j)
                self.joints.append(self.ioBody.link(name))

    def inputFromSimulator(self):
        if self.ioBody:
            pass

    def outputToSimulator(self):
        K = 10
        if self._inIn.isNew():
            data = self._inIn.read()
            self.target_pos = data.data[:]

        count = 0
        for joint in self.joints:
            # print(count)
            # print(target)
            joint.dq = K * (self.target_pos[count] - joint.q)
            count += 1
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
        self.target_pos = [0]*12
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


def QuadrupedRobot_ChoreonoidInit(manager):
    profile = OpenRTM_aist.Properties(
        defaults_str=quadrupedrobot_choreonoid_spec)
    manager.registerFactory(profile,
                            QuadrupedRobot_Choreonoid,
                            OpenRTM_aist.Delete)


def MyModuleInit(manager):
    QuadrupedRobot_ChoreonoidInit(manager)

    # Create a component
    comp = manager.createComponent("QuadrupedRobot_Choreonoid")


def main():
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()


if __name__ == "__main__":
    main()
