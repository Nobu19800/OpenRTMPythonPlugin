#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys

import RTC
import OpenRTM_aist
import os
import importlib




def createComp(filepath):
  
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

  mgr.load(filepath, None)
  

  comp = mgr.createComponent(compname+"?execution_contexts=PeriodicExecutionContext,OpenHRPExecutionContext")
  if comp:
    return comp.getInstanceName()
  else:
    return ""

  

def exitComp(rtcname):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp:
    comp.exit()
    mgr.cleanupComponents()


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
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setBody"):
    comp.setBody(body)
    


def activateComp(rtcname, ecnum):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    ec.activate_component(comp.getObjRef())

def deactivateComp(rtcname, ecnum):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    ec.deactivate_component(comp.getObjRef())


def startSimulation(rtcname, ecnum):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    if ec.get_component_state(comp.getObjRef()) == RTC.INACTIVE_STATE:
      ec.activate_component(comp.getObjRef())




def stopSimulation(rtcname, ecnum):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec:
    if ec.get_component_state(comp.getObjRef()) == RTC.ACTIVE_STATE:
      ec.deactivate_component(comp.getObjRef())
    elif ec.get_component_state(comp.getObjRef()) == RTC.ERROR_STATE:
      ec.reset_component(comp.getObjRef())




def inputFromSimulator(rtcname):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "inputFromSimulator"):
    comp.inputFromSimulator()


def outputToSimulator(rtcname):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "outputToSimulator"):
    comp.outputToSimulator()

def tickEC(rtcname, ecnum):
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  ec = getEC(comp, ecnum)
  if ec and hasattr(ec, "tick"):
    ec.tick()

def runManager():
  mgr = OpenRTM_aist.Manager.init(["test","-o","manager.shutdown_on_nortcs:NO","-o","manager.shutdown_auto:NO", "-o", "naming.formats:%n.rtc"])
  mgr.activateManager()
  mgr.runManager(True)


def shutdownManager():
  mgr = OpenRTM_aist.Manager.instance()
  mgr.shutdown()



if __name__ == "__main__":
  pass
