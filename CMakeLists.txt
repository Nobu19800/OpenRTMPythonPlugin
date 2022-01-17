set(IS_MASTER_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(IS_MASTER_PROJECT ON)
endif()


if(NOT IS_MASTER_PROJECT)
  option(BUILD_OPENRTM_PYTHON_PULUGIN "Building a OpenRTM-aist-Python plugin" OFF)
  if(NOT BUILD_OPENRTM_PYTHON_PULUGIN)
    return()
  elseif(NOT (BUILD_OPENRTM_PLUGIN AND PYTHON_ENABLE))
    message(FATAL_ERROR "The OpenRTM plugin needs to BUILD_OPENRTM_PLUGIN and ENABLE_PYTHON")
  endif()

else()
  cmake_minimum_required(VERSION 3.5.0)
  set(plugin CnoidOpenRTMPythonPlugin)
  project(${plugin})

  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
  endif()

  if(NOT Choreonoid_FOUND)
    file(GLOB choreonoid_search_path
      "c:/choreonoid*/share/choreonoid/cmake"
      "c:/choreonoid*/*/share/choreonoid/cmake")
  endif()
  if(choreonoid_search_path)
    find_package(Choreonoid REQUIRED HINTS ${choreonoid_search_path})
  else()
    find_package(Choreonoid REQUIRED)
  endif()
  
  if(NOT CHOREONOID_ENABLE_CORBA)
    message(FATAL_ERROR "CORBA is not available in Choreonoid")
  endif()

  if(CHOREONOID_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD ${CHOREONOID_CXX_STANDARD})
    set(CMAKE_CXX_EXTENSIONS OFF)
  else()
    add_compile_options(-std=c++14)
  endif()

  if(MSVC)
    if(${MSVC_VERSION} GREATER_EQUAL 1910)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
    endif()
  endif()

  option(INSTALL_SDK "Installing SDK files" ON)
  set(CHOREONOID_INSTALL_SDK ${INSTALL_SDK})

  #include_directories(${PROJECT_SOURCE_DIR})
  #include_directories(${PROJECT_BINARY_DIR}/include)

  include_directories(${CHOREONOID_INCLUDE_DIRS})
  link_directories(${CHOREONOID_LIBRARY_DIRS})
  set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS ${CHOREONOID_COMPILE_DEFINITIONS})
endif()


make_gettext_mofiles(${plugin} mofiles)

set(srcdir ${PROJECT_SOURCE_DIR}/sample/OpenRTMPythonPlugin)
#add_library(${plugin} SHARED ${srcdir}/OpenRTMPythonPlugin.cpp ${srcdir}/PyRTCItem.cpp ${srcdir}/PyRTCItem.h)
#target_link_libraries(${plugin} CnoidBase CnoidPython CnoidBodyPlugin CnoidPythonPlugin CnoidOpenRTMPlugin)

find_package(OpenRTM REQUIRED CONFIG)

include_directories(${OPENRTM_INCLUDE_DIRS})
link_directories(${OPENRTM_LIBRARY_DIRS})

if(WIN32)
  add_definitions(-D__WIN32__ -D__x86__ -D__NT__ -D__OSVERSION__=4 -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0500)
endif()

set(qt_wrap_cpp_files
  RTC_MainWindow.h 
  PythonEditor.h 
  BaseTab.h 
  ActivityTab.h 
  ComponentList.h 
  RTCViewWidget.h 
  ServicePortTable.h 
  DataPortTable.h 
  ControlCompWidget.h 
  ConfigurationTable.h 
  addConfigurationTab.h
  addDataPortTab.h
  addServicePortTab.h
  highlighter.h
)

set(CMAKE_AUTOMOC ON)
qt5_wrap_cpp(qtsources ${qt_wrap_cpp_files})


set(plugin_sources
  OpenRTMPythonPlugin.cpp
  PyRTCItem.cpp
  RTCEditorItem.cpp
  ActivityCode.cpp
  ActivityTab.cpp
  addConfigurationTab.cpp
  addDataPortTab.cpp
  addServicePortTab.cpp
  BaseTab.cpp
  ConfigurationTable.cpp
  ControlCompWidget.cpp
  CreateDataObject.cpp
  DataPortTable.cpp
  PythonEditor.cpp
  highlighter.cpp
  RTC_MainWindow.cpp
  RTC_XML.cpp
  RTCViewWidget.cpp
  ServicePortTable.cpp
  ComponentListItem.cpp
  ComponentList.cpp
  ${qtsources}
)

set(plugin_headers
  PyRTCItem.h
  RTCEditorItem.h
  ActivityCode.h
  CreateDataObject.h
  RTC_XML.h
  ComponentListItem.h
  ${qt_wrap_cpp_files}
)


if(WIN32)
#	set_target_properties(${plugin} PROPERTIES COMPILE_DEFINITIONS "CNOID_USE_GETTEXT_WRAPPER")
#	set_target_properties(${plugin} PROPERTIES COMPILE_DEFINITIONS "BOOST_ASIO_DISABLE_STD_ARRAY")
endif(WIN32)


choreonoid_add_plugin(${plugin} ${plugin_sources} ${mofiles} ${RC_SRCS} ${plugin_headers})

if(IS_MASTER_PROJECT)
  target_compile_definitions(${plugin} PUBLIC ${CHOREONOID_QT_COMPILE_DEFINITIONS})
  target_link_libraries(${plugin}
    CnoidBodyIoRTC
    ${OPENRTM_LIBRARIES} ${CHOREONOID_CORBA_PLUGIN_LIBRARIES} ${CHOREONOID_BODY_PLUGIN_LIBRARIES} ${CHOREONOID_PYTHON_UTIL_LIBRARIES} ${CHOREONOID_PYTHON_LIBRARIES} CnoidPythonPlugin CnoidOpenRTM CnoidOpenRTMPlugin)
else()
  target_link_libraries(${plugin}
    CnoidBodyPlugin CnoidCorbaPlugin CnoidBodyIoRTC CnoidOpenRTM CnoidOpenRTMPlugin CnoidPyUtil CnoidPythonPlugin ${OPENRTM_LIBRARIES})
endif()






configure_file(OpenRTM_Python_plugin.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/python/cnoid/OpenRTM_Python_plugin.py COPYONLY)
install(FILES OpenRTM_Python_plugin.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/python/cnoid/)

configure_file(EditRTC.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/python/cnoid/EditRTC.py COPYONLY)
install(FILES EditRTC.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/python/cnoid/)




configure_file(samples/TankIoRTC_Py/TankIoRTC_Py.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/TankIoRTC_Py.py COPYONLY)
install(FILES samples/TankIoRTC_Py/TankIoRTC_Py.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/TankIoRTC_Py/TankIoRTC_Py.conf ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/TankIoRTC_Py.conf COPYONLY)
install(FILES samples/TankIoRTC_Py/TankIoRTC_Py.conf DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)

configure_file(samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/TankJoystickControllerRTC_Py.py COPYONLY)
install(FILES samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.conf ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/TankJoystickControllerRTC_Py.conf COPYONLY)
install(FILES samples/TankJoystickControllerRTC_Py/TankJoystickControllerRTC_Py.conf DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)

configure_file(samples/JoystickPySDL2/JoystickPySDL2.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/JoystickPySDL2.py COPYONLY)
install(FILES samples/JoystickPySDL2/JoystickPySDL2.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/JoystickPySDL2/JoystickPySDL2.conf ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/JoystickPySDL2.conf COPYONLY)
install(FILES samples/JoystickPySDL2/JoystickPySDL2.conf DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)


configure_file(samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.py ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/QuadrupedRobot_Choreonoid.py COPYONLY)
install(FILES samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.py DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)
configure_file(samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.conf ${PROJECT_BINARY_DIR}/${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/QuadrupedRobot_Choreonoid.conf COPYONLY)
install(FILES samples/QuadrupedRobot_Choreonoid/QuadrupedRobot_Choreonoid.conf DESTINATION ${CHOREONOID_PLUGIN_SUBDIR}/rtc_python/)


configure_file(model/QuadrupedRobot/QuadrupedRobot.yaml ${PROJECT_BINARY_DIR}/${CHOREONOID_SHARE_SUBDIR}/model/QuadrupedRobot/QuadrupedRobot.yaml COPYONLY)
install(FILES model/QuadrupedRobot/QuadrupedRobot.yaml DESTINATION ${CHOREONOID_SHARE_SUBDIR}/model/QuadrupedRobot/)

set(CMAKE_AUTOMOC OFF)
add_subdirectory(pybind11)