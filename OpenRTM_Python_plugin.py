#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys

import RTC
import OpenRTM_aist
import os
import importlib
import cnoid.EditRTC

from cnoid.Body import *

try:
  os.environ["PATH"] = os.environ["PATH"].encode('utf-8')
except:
  pass

##
# @brief RTCEditor対応RTC生成
# @param modulePath モジュールパス
# @return RTC名
#
def createEditComp(modulePath):
  try:
    modulePath = modulePath.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.createComponent("EditRTC"+"?execution_contexts=PeriodicExecutionContext,OpenHRPExecutionContext")
  if comp:
    comp.setModule(modulePath)
    return comp.getInstanceName()
  else:
    return ""

  
##
# @brief RTCEditor対応RTC更新
# @param rtcname RTC名
# @param modulePath モジュールパス
#
def updateEditComp(rtcname, modulePath):

  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setModule"):

    comp.setModule(modulePath)

##
# @brief RTC生成
# @param filepath モジュールパス
# @return RTC名
#
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

  if mgr.load(filepath, None) is RTC.RTC_ERROR or mgr.load(filepath, None) is RTC.PRECONDITION_NOT_MET or mgr.load(filepath, None) is RTC.BAD_PARAMETER:
    return ""
  
  
  comp = mgr.createComponent(compname+"?execution_contexts=PeriodicExecutionContext,OpenHRPExecutionContext")
  if comp:
    return comp.getInstanceName()
  else:
    return ""

  
##
# @brief RTC終了
# @param rtcname RTC名
#
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


##
# @brief EditRTCにデータポート追加
# @param rtcname RTC名
# @param portname ポート名
# @param porttype ポート型
# @param datatype データ型
#
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

##
# @brief 実行コンテキスト取得
# @param comp RTC
# @param ecnum 実行コンテキストID
# @return 実行コンテキスト
#
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

##
# @brief ボディ設定関数呼び出し
# @param body ボディオブジェクト
# @param rtcname RTC名
#
def setBody(body, rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "setBody"):
    comp.setBody(body)
    

##
# @brief RTCのアクティブ化
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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

##
# @brief RTCの非アクティブ化
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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

##
# @brief RTCのリセット
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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

##
# @brief RTCの状態取得
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
# @return 状態
#
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

##
# @brief シミュレーション開始時実行関数
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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



##
# @brief シミュレーション終了時実行関数
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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



##
# @brief inputFromSimulator関数の実行
# @param rtcname RTC名
#
def inputFromSimulator(rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "inputFromSimulator"):
    comp.inputFromSimulator()

##
# @brief outputToSimulator
# @param rtcname RTC名
#
def outputToSimulator(rtcname):
  try:
    rtcname = rtcname.encode('utf-8')
  except:
    pass
  mgr = OpenRTM_aist.Manager.instance()
  comp = mgr.getComponent(rtcname)
  if comp and hasattr(comp, "outputToSimulator"):
    comp.outputToSimulator()

##
# @brief 実行コンテキストのtick駆動
# @param rtcname RTC名
# @param ecnum 実行コンテキストID
#
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

##
# @brief マネージャ開始
#
def runManager():
  mgr = OpenRTM_aist.Manager.init(["test","-o","manager.shutdown_on_nortcs:NO","-o","manager.shutdown_auto:NO", "-o", "naming.formats:%n.rtc"])
  mgr.activateManager()
  cnoid.EditRTC.EditRTCInit(mgr)
  mgr.runManager(True)

##
# @brief マネージャ終了
#
def shutdownManager():
  mgr = OpenRTM_aist.Manager.instance()
  mgr.shutdown()



if __name__ == "__main__":
  pass
