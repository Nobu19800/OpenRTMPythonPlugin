option(BUILD_OPENRTM_PYTHON_PULUGIN "Building a OpenRTM-aist-Python plugin" OFF)
if(NOT BUILD_OPENRTM_PYTHON_PULUGIN)
  return()
endif()

set(target CnoidOpenRTMPythonPlugin)

make_gettext_mofiles(${target} mofiles)

set(srcdir ${PROJECT_SOURCE_DIR}/sample/OpenRTMPythonPlugin)
#add_library(${target} SHARED ${srcdir}/OpenRTMPythonPlugin.cpp ${srcdir}/PyRTCItem.cpp ${srcdir}/PyRTCItem.h)
#target_link_libraries(${target} CnoidBase CnoidPython CnoidBodyPlugin CnoidPythonPlugin)

add_cnoid_plugin(${target} SHARED
  OpenRTMPythonPlugin.cpp
  PyRTCItem.cpp
  PyRTCItem.h
  ${mofiles}
  ${RC_SRCS}
  )
if(WIN32)
#	set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "CNOID_USE_GETTEXT_WRAPPER")
#	set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "BOOST_ASIO_DISABLE_STD_ARRAY")
endif(WIN32)

apply_common_setting_for_plugin(${target})
target_link_libraries(${target} CnoidBase CnoidBodyPlugin CnoidPythonPlugin)





configure_file(OpenRTM_Python_plugin.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/python/cnoid/OpenRTM_Python_plugin.py COPYONLY)
install(FILES OpenRTM_Python_plugin.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/python/cnoid/)




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


