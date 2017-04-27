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
import sys
import time
sys.path.append(".")

# Import RTM module
import RTC
import OpenRTM_aist

from CnoidLink import *


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

		

		
		self._d_velocities = RTC.TimedVelocity2D(RTC.Time(0,0), RTC.Velocity2D(0.0,0.0,0.0))
		"""
		車体の目標速度
		 - Type: RTC::TimedVelocity2D
		 - Unit: m/s, rad/s
		"""
		self._velocitiesIn = OpenRTM_aist.InPort("velocities", self._d_velocities)

		self._d_torques = RTC.TimedDoubleSeq(RTC.Time(0,0), [])
		"""
		アームのトルクを入力
		 - Type: RTC::TimedDoubleSeq
		 - Number: 2
		 - Unit: N・m
		"""
		self._torquesIn = OpenRTM_aist.InPort("torques", self._d_torques)
		
		self._d_lightSwitch = RTC.TimedBooleanSeq(RTC.Time(0,0), [])
		"""
		ライトのオンオフ
		 - Type: RTC::TimedBooleanSeq
		"""
		self._lightSwitchIn = OpenRTM_aist.InPort("lightSwitch", self._d_lightSwitch)
		
		self._d_angles = RTC.PanTiltAngles(RTC.Time(0,0), 0.0,0.0)
		"""
		カメラの角度
		 - Type: RTC::PanTiltAngles
		 - Unit: rad
		"""
		self._anglesOut = OpenRTM_aist.OutPort("angles", self._d_angles)

		self.body = None
		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>


	def setBody(self, body, ControlLinkObj):
		self.ioBody = body
		self.ControlLink = ControlLinkObj
		#self.cannonY = self.ioBody.link("CANNON_Y")
		#self.cannonP = self.ioBody.link("CANNON_P")
		#self.crawlerL = self.ioBody.link("CRAWLER_TRACK_L")
		#self.crawlerR = self.ioBody.link("CRAWLER_TRACK_R")
		self.cannonY = self.ControlLink.getLink(self.ioBody, "CANNON_Y")
		self.cannonP = self.ControlLink.getLink(self.ioBody, "CANNON_P")
		self.crawlerL = self.ControlLink.getLink(self.ioBody, "CRAWLER_TRACK_L")
		self.crawlerR = self.ControlLink.getLink(self.ioBody, "CRAWLER_TRACK_R")
		
		
		self.light = self.ControlLink.getLight(self.ioBody, "MainLight")
		

	def inputFromSimulator(self):
		if self.ioBody:
			self._d_angles.pan = self.ControlLink.getJointPosition(self.cannonY)
			self._d_angles.tilt = self.ControlLink.getJointPosition(self.cannonP)
			
			OpenRTM_aist.setTimestamp(self._d_angles)
			self._anglesOut.write()


	def outputToSimulator(self):
		wheel_radius = 0.05
		wheel_distance = 0.2
		if self.ioBody:
			if self._torquesIn.isNew():
				data = self._torquesIn.read()
				self.ControlLink.setJointForce(self.cannonY, data.data[0])
				self.ControlLink.setJointForce(self.cannonP, data.data[1])
			if self._velocitiesIn.isNew():
				data = self._velocitiesIn.read()
				vx = data.data.vx
				va = data.data.va
				
				rms = (vx + va*wheel_distance)/wheel_radius
				lms = (vx - va*wheel_distance)/wheel_radius
				
				self.ControlLink.setJointVelocity(self.crawlerL, lms)
				self.ControlLink.setJointVelocity(self.crawlerR, rms)
			if self._lightSwitchIn.isNew():
				data = self._lightSwitchIn.read()
				
				self.ControlLink.lightOn(self.light, data.data[0])




		 
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
		self.addInPort("velocities",self._velocitiesIn)
		self.addInPort("torques",self._torquesIn)
		self.addInPort("lightSwitch",self._lightSwitchIn)
		
		# Set OutPort buffers
		self.addOutPort("angles",self._anglesOut)
		
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
	#def onFinalize(self):
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
	#def onStartup(self, ec_id):
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
	#def onShutdown(self, ec_id):
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
	#def onDeactivated(self, ec_id):
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
	#def onExecute(self, ec_id):
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
	#def onAborting(self, ec_id):
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
	#def onError(self, ec_id):
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
	#def onReset(self, ec_id):
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
	#def onStateUpdate(self, ec_id):
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
	#def onRateChanged(self, ec_id):
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

