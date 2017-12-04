option(BUILD_OPENRTM_PYTHON_PULUGIN "Building a OpenRTM-aist-Python plugin" OFF)
if(NOT BUILD_OPENRTM_PYTHON_PULUGIN)
  return()
endif()

set(target CnoidOpenRTMPythonPlugin)

make_gettext_mofiles(${target} mofiles)

set(srcdir ${PROJECT_SOURCE_DIR}/sample/OpenRTMPythonPlugin)
#add_library(${target} SHARED ${srcdir}/OpenRTMPythonPlugin.cpp ${srcdir}/PyRTCItem.cpp ${srcdir}/PyRTCItem.h)
#target_link_libraries(${target} CnoidBase CnoidPython CnoidBodyPlugin CnoidPythonPlugin CnoidOpenRTMPlugin)

include_directories(${OPENRTM_INCLUDE_DIRS})
link_directories(${OPENRTM_LIBRARY_DIRS})
message(STATUS ${OPENRTM_LIBRARY_DIRS})
if(WIN32)
  add_definitions(-D__WIN32__ -D__x86__ -D__NT__ -D__OSVERSION__=4 -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0500 -DRTC_CORBA_CXXMAPPING11)
endif()

set(CMAKE_AUTOMOC ON)
qt5_wrap_cpp(moc_mainwindow.cpp mainwindow.h)
qt5_wrap_cpp(moc_Editor.cpp Editor.h)
qt5_wrap_cpp(moc_BaseTab.cpp BaseTab.h)
qt5_wrap_cpp(moc_RTCViewWidget.cpp RTCViewWidget.h)

add_cnoid_plugin(${target} SHARED
  OpenRTMPythonPlugin.cpp
  PyRTCItem.cpp
  PyRTCItem.h
  RTCEditorItem.cpp
  RTCEditorItem.h
  ActivityCode.cpp
  ActivityCode.h
  ActivityTab.cpp
  ActivityTab.h
  addConfigurationTab.cpp
  addConfigurationTab.h
  addDataPortTab.cpp
  addDataPortTab.h
  addServicePortTab.cpp
  addServicePortTab.h
  BaseTab.cpp
  BaseTab.h
  ConfigurationTable.cpp
  ConfigurationTable.h
  ControlCompWidget.cpp
  ControlCompWidget.h
  CreateDataObject.cpp
  CreateDataObject.h
  DataPortTable.cpp
  DataPortTable.h
  PythonEditor.cpp
  PythonEditor.h
  highlighter.cpp
  highlighter.h
  RTC_MainWindow.cpp
  RTC_MainWindow.h
  RTC_XML.cpp
  RTC_XML.h
  RTCViewWidget.cpp
  RTCViewWidget.h
  ServicePortTable.cpp
  ServicePortTable.h
  ComponentListItem.cpp
  ComponentListItem.h
  ComponentList.cpp
  ComponentList.h
  ${mofiles}
  ${RC_SRCS}
  )
if(WIN32)
#	set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "CNOID_USE_GETTEXT_WRAPPER")
#	set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "BOOST_ASIO_DISABLE_STD_ARRAY")
endif(WIN32)




apply_common_setting_for_plugin(${target})
target_link_libraries(${target} CnoidBase CnoidBodyPlugin CnoidPythonPlugin CnoidCorbaPlugin CnoidOpenRTM CnoidOpenRTMPlugin)





configure_file(OpenRTM_Python_plugin.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/python/cnoid/OpenRTM_Python_plugin.py COPYONLY)
install(FILES OpenRTM_Python_plugin.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/python/cnoid/)

configure_file(EditRTC.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/python/cnoid/EditRTC.py COPYONLY)
install(FILES EditRTC.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/python/cnoid/)




configure_file(samples/TankIoRTC_Py/TankIoRTC_Py.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/TankIoRTC_Py.py COPYONLY)
install(FILES samples/TankIoRTC_Py/TankIoRTC_Py.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/TankIoRTC_Py/TankIoRTC_Py.conf ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/TankIoRTC_Py.conf COPYONLY)
install(FILES samples/TankIoRTC_Py/TankIoRTC_Py.conf DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)

configure_file(samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/TankJoystickControllerRTC_Py.py COPYONLY)
install(FILES samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.conf ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/TankJoystickControllerRTC_Py.conf COPYONLY)
install(FILES samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.conf DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)

configure_file(samples/JoystickPySDL2/JoystickPySDL2.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/JoystickPySDL2.py COPYONLY)
install(FILES samples/JoystickPySDL2/JoystickPySDL2.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/JoystickPySDL2/JoystickPySDL2.conf ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/JoystickPySDL2.conf COPYONLY)
install(FILES samples/JoystickPySDL2/JoystickPySDL2.conf DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)


configure_file(samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/QuadrupedRobot_Choreonoid.py COPYONLY)
install(FILES samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.conf ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/QuadrupedRobot_Choreonoid.conf COPYONLY)
install(FILES samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.conf DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)


configure_file(model/QuadrupedRobot/QuadrupedRobot.yaml ${PROJECT_BINARY_DIR}/${CNOID_SHARE_SUBDIR}/model/QuadrupedRobot/QuadrupedRobot.yaml COPYONLY)
install(FILES model/QuadrupedRobot/QuadrupedRobot.yaml DESTINATION ${CNOID_SHARE_SUBDIR}/model/QuadrupedRobot/)
