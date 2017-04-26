option(BUILD_OPENRTM_PYTHON_PULUGIN "Building a OpenRTM-aist-Python plugin" OFF)
if(NOT BUILD_OPENRTM_PYTHON_PULUGIN)
  return()
endif()

set(target CnoidOpenRTMPythonPlugin)
set(srcdir ${PROJECT_SOURCE_DIR}/sample/OpenRTMPythonPlugin)
add_library(${target} SHARED ${srcdir}/OpenRTMPythonPlugin.cpp ${srcdir}/PyRTCItem.cpp ${srcdir}/PyRTCItem.h)
target_link_libraries(${target} CnoidBase CnoidPython CnoidBodyPlugin CnoidPythonPlugin)
apply_common_setting_for_plugin(${target})


configure_file(OpenRTM_Python_plugin.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/python/cnoid/OpenRTM_Python_plugin.py COPYONLY)
install(FILES OpenRTM_Python_plugin.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/python/cnoid/)




configure_file(samples/TankIoRTC.py ${PROJECT_BINARY_DIR}/${CNOID_PLUGIN_SUBDIR}/rtc_python/TankIoRTC.py COPYONLY)
install(FILES samples/TankIoRTC.py DESTINATION ${CNOID_PLUGIN_SUBDIR}/rtc_python/)



