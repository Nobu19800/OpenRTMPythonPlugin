set(target PyOpenRTMPythonPlugin)

add_cnoid_python_module(${target}
  PyOpenRTMPythonPlugin.cpp
)

target_link_libraries(${target} CnoidPyBase CnoidBody ${CHOREONOID_PYTHON_LIBRARIES})
