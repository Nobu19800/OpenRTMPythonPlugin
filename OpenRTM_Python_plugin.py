#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys

import OpenRTM_aist
import RTC
import os
import importlib
import cnoid.EditRTC

from cnoid.Body import *

try:
  os.environ["PATH"] = os.environ["PATH"].encode('utf-8')
except:
  pass


def createEditComp(modulePath):
  
  try:
    modulePath = modulePath.encode('utf-8')
  except:
    pass
  
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.createComponent("EditRTC"+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
  if comp:
    comp.setModule(modulePath)
    return comp.getInstanceName()
  else:
    return ""

def testFunc(v):
  print type(v),v
  try:
    v = v.encode('utf-8')
  except:
    pass
  print v

def updateEditComp(rtcname, modulePath):

  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setModule"):

    comp.setModule(modulePath)

def createComp(filepath):
  
  try:
    filepath = filepath.encode('utf-8')
  except:
    pass
  
  mgr = OpenRTM_aist.Manager.instance()
  

  filename = os.path.basename(filepath)
  compname, ext = os.path.splitext(filename)
  
  
  try:
    mgr._factory.unregisterObject(compname)
    mgr.unload(filepath)
  except:
    pass

  if compname in sys.modules.keys():
    sys.modules.pop(compname)

  ret = mgr.load(filepath, None)
  if ret is RTC.RTC_ERROR or ret is RTC.PRECONDITION_NOT_MET or ret is RTC.BAD_PARAMETER:
    return ""
  
  
  comp = mgr.createComponent(compname+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
  if comp:
    return comp.getInstanceName()
  else:
    return ""



def createCompList(filepath):
  
  try:
    filepath = filepath.encode('utf-8')
  except:
    pass
  
  mgr = OpenRTM_aist.Manager.instance()

  filename = os.path.basename(filepath)
  compname, ext = os.path.splitext(filename)
  
  

  ret = mgr.load(filepath, None)
  if ret is RTC.RTC_ERROR or ret is RTC.PRECONDITION_NOT_MET or ret is RTC.BAD_PARAMETER:
    return ""
  
  
  comp = mgr.createComponent(compname+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
  if comp:
    return comp.getInstanceName()
  else:
    return ""
  

def exitComp(rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp:
    comp.exit()
    mgr.cleanupComponents()


def addDataPort(rtcname, portname, porttype, datatype):
  

  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  try:
    portname = portname.encode('utf-8')
  except:
    pass
  try:
    porttype = porttype.encode('utf-8')
  except:
    pass
  try:
    datatype = datatype.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setDataPort"):
    comp.setDataPort(portname, porttype, datatype)


def getEC(comp, ecnum):
  if comp:
    if ecnum < 1000:
        ecs = comp.get_owned_contexts()
    else:
        ecnum -= 1000
        ecs = comp.get_paticipating_contexts()
    if ecnum < len(ecs):
        return ecs[ecnum]
  return None

def setBody(body, rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setBody"):
    comp.setBody(body)
    


def activateComp(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    ec.activate_component(comp.getObjRef())

def deactivateComp(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    ec.deactivate_component(comp.getObjRef())


def resetComp(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    ec.reset_component(comp.getObjRef())


def getStatus(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    status = ec.get_component_state(comp.getObjRef())
    if status == RTC.CREATED_STATE:
      return "CREATED"
    elif status == RTC.INACTIVE_STATE:
      return "INACTIVATE"
    elif status == RTC.ACTIVE_STATE:
      return "ACTIVATE"
    elif status == RTC.ERROR_STATE:
      return "ERROR"
  return "CREATED"


def startSimulation(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    if ec.get_component_state(comp.getObjRef()) == RTC.INACTIVE_STATE:
      ec.activate_component(comp.getObjRef())




def stopSimulation(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    if ec.get_component_state(comp.getObjRef()) == RTC.ACTIVE_STATE:
      ec.deactivate_component(comp.getObjRef())
    elif ec.get_component_state(comp.getObjRef()) == RTC.ERROR_STATE:
      ec.reset_component(comp.getObjRef())




def inputFromSimulator(rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "inputFromSimulator"):
    comp.inputFromSimulator()


def outputToSimulator(rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "outputToSimulator"):
    comp.outputToSimulator()

def tickEC(rtcname, ecnum):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec and hasattr(ec, "tick"):
    ec.tick()

def runManager():
  mgr = OpenRTM_aist.Manager.init(["test","-o","manager.shutdown_on_nortcs:NO","-o","manager.shutdown_auto:NO", "-o", "naming.formats:%n.rtc"])
  mgr.activateManager()
  cnoid.EditRTC.EditRTCInit(mgr)
  mgr.runManager(True)


def shutdownManager():
  mgr = OpenRTM_aist.Manager.instance()
  mgr.shutdown()



if __name__ == "__main__":
  pass
