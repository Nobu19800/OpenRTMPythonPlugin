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


def createEditComp(modulePath):
    mgr = OpenRTM_aist.Manager.instance()
    comp = mgr.createComponent(
        "EditRTC"+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
    if comp:
        comp.setModule(modulePath)
        return comp.getInstanceName()
    else:
        return ""


def testFunc(v):
    print(type(v), v)


def updateEditComp(rtcname, modulePath):
    mgr = OpenRTM_aist.Manager.instance()
    comp = mgr.getComponent(rtcname)
    if comp and hasattr(comp, "setModule"):

        comp.setModule(modulePath)


def createComp(filepath):
    mgr = OpenRTM_aist.Manager.instance()
    filepath = filepath.replace("\\", "/")

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

    comp = mgr.createComponent(
        compname+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
    if comp:
        return comp.getInstanceName()
    else:
        return ""


def createCompList(filepath):
    mgr = OpenRTM_aist.Manager.instance()

    filename = os.path.basename(filepath)
    compname, ext = os.path.splitext(filename)

    ret = mgr.load(filepath, None)
    if ret is RTC.RTC_ERROR or ret is RTC.PRECONDITION_NOT_MET or ret is RTC.BAD_PARAMETER:
        return ""

    comp = mgr.createComponent(
        compname+"?execution_contexts=PeriodicExecutionContext,SimulatorExecutionContext")
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


def addDataPort(rtcname, portname, porttype, datatype):
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
            ecs = comp.get_participating_contexts()
        if ecnum < len(ecs):
            return ecs[ecnum]
    return None


def stopECs(comp, ecnum):
    if comp:
        ecs = comp.get_owned_contexts()
        for i in range(len(ecs)):
            if i != ecnum:
                ecs[i].stop()
            elif ecnum < 1000:
                ecs[i].start()

        ecs = comp.get_participating_contexts()
        if ecnum >= 1000:
            for i in range(len(ecs)):
                if i != (ecnum-1000):
                    ecs[i].stop()
                else:
                    ecs[i].start()


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


def resetComp(rtcname, ecnum):
    mgr = OpenRTM_aist.Manager.instance()
    comp = mgr.getComponent(rtcname)
    ec = getEC(comp, ecnum)
    if ec:
        ec.reset_component(comp.getObjRef())


def getStatus(rtcname, ecnum):
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
    mgr = OpenRTM_aist.Manager.instance()
    comp = mgr.getComponent(rtcname)
    stopECs(comp, ecnum)
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
    mgr = OpenRTM_aist.Manager.init(["test", "-o", "manager.shutdown_on_nortcs:NO",
                                     "-o", "manager.shutdown_auto:NO", "-o", "naming.formats:%n.rtc"])
    mgr.activateManager()
    cnoid.EditRTC.EditRTCInit(mgr)
    mgr.runManager(True)


def shutdownManager():
    mgr = OpenRTM_aist.Manager.instance()
    mgr.shutdown()


if __name__ == "__main__":
    pass
